#include <iostream>
#include "GameMenu.h"
#include "GameStart.h"
#include "InitText.h"
#include "About_Game.h"
#include "player.h"
#include "NetworkClient.h"
using namespace sf;


InitText initText;
About_Game about_Game;

IpAddress S_Ip;
unsigned short S_port;
Player player(20.f);
NetworkClient netC;

void getUserInputData(string& playerName);


int main()
{
    getUserInputData(player.name);
    netC.init();
    netC.registerOnServer(S_Ip, S_port, player.name);
    vector<string> namesVec;
    netC.receiveConnectedClientsNames(namesVec);
    GamеStart games(netC, S_Ip, S_port, player, namesVec);
    
   

    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), L"Моя игра", Style::Fullscreen);

    //отключаем видимость курсора
    window.setMouseCursorVisible(false);

    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    // Устанавливаем фон для графического окна 
    // Создаём прямоугольник
    RectangleShape background(Vector2f(width, height));
    // Загружаем в прямоугольник текстуру с изображением menu9.jpg
    Texture texture_window;
    if (!texture_window.loadFromFile("resources/4.jpg")) return 4;
    background.setTexture(&texture_window);

    // Устанавливаем шрифт для названия игры
    Font font;
    if (!font.loadFromFile("resources/troika.otf")) return 5;
    Text Titul;
    Titul.setFont(font);
    // Текст с названием игры
    initText.texts(Titul, 730, 50, L"WORMS", 150, Color(237, 147, 0), 3);

    // Название пунктов меню
    String name_menu[]{ L"Старт",L"Настройки", L"О игре",L"Выход" };

    // Объект игровое меню
    GameMenu mymenu(window, 950, 350, 4, name_menu, 100, 120);
    // Установка цвета элементов пунктов меню
    mymenu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
    // выравнивание по центру пунктов меню 
    mymenu.AlignMenu(2);



    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::KeyReleased)
            {
                // События выбра пунктов меню
                    // нажати на клавиатуре стрелки вверх
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
                // нажати на клавиатуре стрелки вниз
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
                // нажати на клавиатуре клавиши Enter
                if (event.key.code == Keyboard::Return)
                {
                    // Переходим на выбранный пункт меню
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:games.start(); break;
                    case 1: break;
                    case 2:about_Game.showInformation(); break;
                    case 3:window.close(); break;

                    }
                }
            }
        }
        window.clear();
        window.draw(background);
        window.draw(Titul);
        mymenu.draw();
        window.display();
    }
	return 0;
};


void getUserInputData(string& playerName)
{
    //cout << "Enter server IP: ";
    //cin >> serverIp;
    S_Ip = "localhost";
    std::cout << endl;
    std::cout << "Enter server registration port: ";
    std::cin >> S_port;
    std::cout << endl;
    std::cout << "Enter name: ";
    std::cin >> playerName;
};