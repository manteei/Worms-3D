#include "settings.h"

Settings::Settings(){}

void Settings::inputName() {
    RenderWindow setting(VideoMode::getDesktopMode(), L"Настройки", Style::Default);
    RectangleShape background_ab(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    setting.setMouseCursorVisible(true);
    if (!texture_ab.loadFromFile("resources/3.jpg")) exit(3);
    background_ab.setTexture(&texture_ab);
    float width = VideoMode::getDesktopMode().width / 2;
    float height = VideoMode::getDesktopMode().height / 2;
    float boxWidth = 700;
    float boxHeight = 120;

    initText.texts(Titul, width - boxWidth / 2, height - boxHeight/2- 100, L"Введите своё имя:", 60, Color(255, 239, 213), 3);

    Font font;
    font.loadFromFile("resources/troika.otf");
  
    RectangleShape inputBox(Vector2f(boxWidth, boxHeight));
    inputBox.setFillColor(Color(125,153,92));
    inputBox.setOutlineColor(Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(width - boxWidth/2, height - boxHeight/2);

    
    inputText.setFont(font);
    inputText.setCharacterSize(60);
    inputText.setFillColor(Color(255, 239, 213));
    inputText.setOutlineColor(Color::Black);
    inputText.setOutlineThickness(2);
    inputText.setPosition(width - boxWidth / 2+15, height - boxHeight / 2+15);


    std::string playerName;
    while (setting.isOpen())
    {
        Event event;
        while (setting.pollEvent(event))
        {
            if (event.type == Event::Closed) setting.close();
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape) setting.close();
                if (event.key.code == Keyboard::Enter) { name = playerName; nameCreated = true; }
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128 && event.text.unicode != 8) // 8 is backspace
                {
                    playerName += static_cast<char>(event.text.unicode);

                    // Ограничиваем ширину текста
                    inputText.setString(playerName);
                    while (inputText.getLocalBounds().width > inputBox.getSize().x - 10) // 10 - отступ
                    {
                        playerName.pop_back();
                        inputText.setString(playerName);
                    }
                }
                else if (event.text.unicode == 8 && playerName.length() > 0) // Handle backspace
                {
                    playerName.pop_back();
                    inputText.setString(playerName);
         
                }
            }
        }

        initText.texts(Titul2, width - boxWidth / 2, height - boxHeight / 2 - 100, L"Ваше имя: " + name, 60, Color(255, 239, 213), 3);
        setting.clear();
        setting.draw(background_ab);
        if (!nameCreated) {
            setting.draw(Titul);
            setting.draw(inputBox);
            setting.draw(inputText);
        }else  setting.draw(Titul2);
        
        setting.display();
    }

}

std::string Settings::getName() {
    
    return name;
}