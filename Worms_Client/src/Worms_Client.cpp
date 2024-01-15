#include <iostream>
#include "GameMenu.h"
#include "GameStart.h"
#include "InitText.h"
#include "About_Game.h"
#include "player.h"
#include "settings.h"
#include "NetworkClient.h"


using namespace sf;
InitText initText;
About_Game about_Game;
Settings setting;
IpAddress S_Ip = "localhost";
unsigned short S_port;

Player player(20.f);
Text warning;


int main()
{


    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), L"��� ����", Style::Default);
    window.setMouseCursorVisible(false);

    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    RectangleShape background(Vector2f(width, height));
    Texture texture_window;
    if (!texture_window.loadFromFile("resources/4.jpg")) return 4;
    background.setTexture(&texture_window);

    RectangleShape load(Vector2f(70, 70));
    Texture texture_loading;
    if (!texture_loading.loadFromFile("resources/loading.png")) return 4;
    load.setTexture(&texture_loading);
    load.setPosition(1100, 380);
   
    Text Titul;
   
    initText.texts(Titul, 730, 50, L"WORMS", 150, Color(237, 147, 0), 3);
    String name_menu[]{ L"�����",L"���������", L"� ����",L"�����" };

    GameMenu mymenu(window, 950, 350, 4, name_menu, 100, 120);
    mymenu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
    mymenu.AlignMenu(2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::KeyReleased)
            {
                
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }

                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }

                if (event.key.code == Keyboard::Return)
                {
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0: {
                        window.draw(load);
                        window.display();
                        NetworkClient netC;
                        netC.init();
                        netC.registerOnServer(S_Ip, 12345, setting.getName());
                        player.name = setting.getName();
                        if (player.name == "") {
                            initText.texts(warning,400,900,L"!!! ������� � ���������, ����� ������ ���",60,Color::Red,3);
                            break;
                        }
                        vector<string> namesVec;
                        netC.receiveConnectedClientsNames(namesVec);
                        Gam�Start games(netC, S_Ip, S_port, player, namesVec);
                        games.start(); 
                            break;}
                    case 1:setting.inputName(); break;
                    case 2:about_Game.showInformation(); break;
                    case 3:window.close(); break;

                    }
                }
            }
        }
        window.clear();
        window.draw(background);
        window.draw(Titul);
        if (setting.getName()=="") window.draw(warning);

        mymenu.draw();
        window.display();
    }
	return 0;
};


