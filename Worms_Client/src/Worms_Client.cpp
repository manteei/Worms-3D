#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include "textureManager.h"
#include "player.h"
#include "map.h"
#include "NetworkClient.h"

using namespace sf;

vector<Player> playersVec;

Clock cycleTimer;
Time cycleTime;

IpAddress S_Ip;
unsigned short S_port;
string clientName;
Map myMap(80, 40, 80);
NetworkClient netC;
float size0 = 20.f;

std::vector<std::vector<std::vector<bool>>> mass(500, std::vector<std::vector<bool>>(500, std::vector<bool>(500, false)));
TextureManager textureManager;

float angleX, angleY;
const float PI = 3.141592653;

void getUserInputData(string& playerName);
void addPlayer(Font& font, string clientName);

int main()
{
	RenderWindow window(VideoMode(800, 600), "OpenGL", Style::Default, ContextSettings(32));

	window.setVerticalSyncEnabled(true);

	window.setActive(true);

	Texture t;
	t.loadFromFile("resources/cursor.png");
	Sprite s(t); s.setOrigin(8, 8); s.setPosition(400, 300);
	std::vector<GLuint> skybox = textureManager.createSkybox();
	GLuint box = textureManager.createBox();
	GLuint worm = textureManager.createWorm();

	Font font;
	font.loadFromFile("8bitOperatorPlus-Regular.ttf");

	Player player(100, 200, 100, size0);
	

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 2000.f);
	glEnable(GL_TEXTURE_2D);
	ShowCursor(FALSE);

	myMap.createMap(mass);

	Clock clock;

	getUserInputData(player.name);
	
	netC.init();
	netC.registerOnServer(S_Ip, S_port, player.name);

	vector<string> namesVec;
	netC.receiveConnectedClientsNames(namesVec);
	for (int i = 0; i < namesVec.size(); i++)
	{
		addPlayer(font, namesVec[i]);
	}

	Packet receivedDataPacket;
	Packet sendDataPacket;


	while (window.isOpen())
	{
		cycleTime = cycleTimer.restart();


		if (netC.receiveData(receivedDataPacket, S_Ip, S_port) == Socket::Status::Done)
		{
			if (receivedDataPacket.getDataSize() > 0)
			{
				string s;
				if (receivedDataPacket >> s)
				{
					if (s == "NEW")
					{
						if (receivedDataPacket >> s)
						{
							if (s != clientName)
							{
								addPlayer(font, s);
								cout << "New player connected: " << playersVec.back().name << endl;
							}
						}
					}
					if (s == "DATA")
					{
						while (!receivedDataPacket.endOfPacket())
						{
							float x, y, z;
							receivedDataPacket >> s;
							receivedDataPacket >> x;
							receivedDataPacket >> y;
							receivedDataPacket >> z;
							for (int i = 0; i < playersVec.size(); i++)
							{
								if (s == playersVec[i].name)
									playersVec[i].setPosition( x, y, z );
							}
						}
					}
				}
			}
		}



		sendDataPacket.clear();
		sendDataPacket << "DATA" << player.x << player.y << player.z;
		netC.sendData(sendDataPacket);


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				window.close();
		}

		for (int i = 0; i < playersVec.size(); i++)
		{
			playersVec[i].draw(window);
		}

		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time = time / 50;
		if (time > 3) time = 3;

		player.draw(window);  

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player.keyboard(angleX);
		player.update(time, mass, myMap);

		POINT mousexy;
		GetCursorPos(&mousexy);
		int xt = window.getPosition().x + 400;
		int yt = window.getPosition().y + 300;

		angleX += (xt - mousexy.x) / 4;
		angleY += (yt - mousexy.y) / 4;

		if (angleY < -89.0) { angleY = -89.0; }
		if (angleY > 89.0) { angleY = 89.0; }

		SetCursorPos(xt, yt);

		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(player.x, player.y + player.h / 2, player.z, player.x - sin(angleX / 180 * PI), player.y + player.h / 2 + (tan(angleY / 180 * PI)), player.z - cos(angleX / 180 * PI), 0, 1, 0);
		
		glTranslatef(player.x, player.y, player.z);
		textureManager.drawSkybox(skybox, 1000);
		glTranslatef(-player.x, -player.y, -player.z);


		myMap.drawMap(textureManager, size0, box, mass);

		glTranslatef(player.x, player.y + 5, player.z);
		textureManager.drawBox(worm, size0 / 10);
		glTranslatef(-player.x, -player.y - 5, -player.z);

		window.pushGLStates();
		window.draw(s);
		window.popGLStates();

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

void addPlayer(Font& font, string clientName)
{
	Player p(100, 200, 100, size0);
	playersVec.push_back(p);
	playersVec.back().name = clientName;
	playersVec.back().load(font);
};