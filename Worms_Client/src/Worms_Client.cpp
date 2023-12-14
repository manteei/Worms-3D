#include <iostream>
#include "GameMenu.h"
#include "GameStart.h"
#include "InitText.h"
#include "About_Game.h"
#include "player.h"
#include "TeamWorms.h"
#include "NetworkClient.h"
using namespace sf;


InitText initText;
About_Game about_Game;

IpAddress S_Ip;
unsigned short S_port;

TeamWorms teamWorms;
NetworkClient netC;

void getUserInputData(string& playerName);


int main()
{
    getUserInputData(teamWorms.name);
    netC.init();
    netC.registerOnServer(S_Ip, S_port, teamWorms.name);
    vector<string> namesVec;
    netC.receiveConnectedClientsNames(namesVec);
    Gam�Start games(netC, S_Ip, S_port, teamWorms, namesVec);

   

    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), L"��� ����", Style::Default);

    //��������� ��������� �������
    window.setMouseCursorVisible(false);

    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    // ������������� ��� ��� ������������ ���� 
    // ������ �������������
    RectangleShape background(Vector2f(width, height));
    // ��������� � ������������� �������� � ������������ menu9.jpg
    Texture texture_window;
    if (!texture_window.loadFromFile("resources/4.jpg")) return 4;
    background.setTexture(&texture_window);

   
    Text Titul;
   
    initText.texts(Titul, 730, 50, L"WORMS", 150, Color(237, 147, 0), 3);

    // �������� ������� ����
    String name_menu[]{ L"�����",L"���������", L"� ����",L"�����" };

    // ������ ������� ����
    GameMenu mymenu(window, 950, 350, 4, name_menu, 100, 120);
    // ��������� ����� ��������� ������� ����
    mymenu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
    // ������������ �� ������ ������� ���� 
    mymenu.AlignMenu(2);



    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::KeyReleased)
            {
                // ������� ����� ������� ����
                    // ������ �� ���������� ������� �����
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
                // ������ �� ���������� ������� ����
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
                // ������ �� ���������� ������� Enter
                if (event.key.code == Keyboard::Return)
                {
                    // ��������� �� ��������� ����� ����
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