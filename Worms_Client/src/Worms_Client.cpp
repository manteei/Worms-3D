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
#include "camera.h"

using namespace sf;

vector<Player> enemyVec;

Clock cycleTimer;
Time cycleTime;

IpAddress S_Ip;
unsigned short S_port;
string clientName;

Map myMap(64, 10, 64);
NetworkClient netC;
float size0 = 20.f;

std::vector<std::vector<std::vector<bool>>> mass(64, std::vector<std::vector<bool>>(64, std::vector<bool>(64, false)));
TextureManager textureManager;

float angleX, angleY;
const float PI = 3.141592653;

void getUserInputData(string& playerName);
void addPlayer(string clientName);

bool windowIsActive = false;

Player player(size0);

int main()
{
	RenderWindow window(VideoMode(800, 600), "OpenGL", Style::Default, ContextSettings(32));

	bool isDragging = false;
	sf::Vector2i offset;

	window.setVerticalSyncEnabled(true);

	window.setActive(true);



	Texture t;
	t.loadFromFile("resources/cursor.png");
	Sprite s(t); s.setOrigin(8, 8); s.setPosition(400, 300);


	Font font;
	font.loadFromFile("8bitOperatorPlus-Regular.ttf");


	std::vector<GLuint> skybox = textureManager.createSkybox();
	GLuint box = textureManager.createBox();
	GLuint worm = textureManager.createWorm();
	GLuint sand = textureManager.createSand();


	Camera camera(player);

	getUserInputData(player.name);
	
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
	
	netC.init();
	netC.registerOnServer(S_Ip, S_port, player.name);

	vector<string> namesVec;
	
	netC.receiveConnectedClientsNames(namesVec);

	for (int i = 0; i < namesVec.size(); i++)
	{
		addPlayer(namesVec[i]);
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
								addPlayer(s);
								cout << "New player connected: " << enemyVec.back().name << endl;
								
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
						
							for (int i = 0; i < enemyVec.size(); i++)
							{
								if (s == enemyVec[i].name) {
									enemyVec[i].setPosition(x, y, z); 
									//cout << "!!!Rendering coordinat for enemy " << enemyVec[i].name << "\n ";
									//cout << "x: " << enemyVec[i].x << " y: " << enemyVec[i].y << " z: " << enemyVec[i].z << "\n";
									
								}
							}
						}
					}
				}
			}
		}



		sendDataPacket.clear();
		sendDataPacket << "DATA"  << player.getPosX() << player.getPosY() << player.getPosZ();
		//cout << "x " << player.getPosX() << " y " << player.getPosY() << " z " << player.getPosZ() << "\n";
		netC.sendData(sendDataPacket);


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				window.close();
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::F)) {
					windowIsActive = false;
					ShowCursor(TRUE);

			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::G)) {
				windowIsActive = true;
				ShowCursor(FALSE);

			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				isDragging = true;
				offset = window.getPosition() - sf::Mouse::getPosition();
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				isDragging = false;
			}
			
				
		}

		if (isDragging)
		{
			window.setPosition(sf::Mouse::getPosition() + offset);
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (windowIsActive) {
			player.keyboard(angleX);
			player.update(cycleTime, mass, myMap);
			camera.keyboard();
			camera.update(cycleTime, player);
			
			POINT mousexy;
			GetCursorPos(&mousexy);
			int xt = window.getPosition().x + 400;
			int yt = window.getPosition().y + 300;

			angleX += (xt - mousexy.x) / 4;
			angleY += (yt - mousexy.y) / 4;

			if (angleY < -89.0) { angleY = -89.0; }
			if (angleY > 89.0) { angleY = 89.0; }

			SetCursorPos(xt, yt);

		}
		window.clear();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(camera.x, camera.y + camera.h / 2, camera.z, camera.x - sin(angleX / 180 * PI), camera.y + camera.h / 2 + (tan(angleY / 180 * PI)), camera.z - cos(angleX / 180 * PI), 0, 1, 0);

		glTranslatef(camera.x, camera.y, camera.z);
		textureManager.drawSkybox(skybox, 1000);
		glTranslatef(-camera.x, -camera.y, -camera.z);

		myMap.drawMap(textureManager, size0, box, sand, mass);

		for (int i = 0; i < enemyVec.size(); i++)
		{
			Vector2f windowCoords;
			textureManager. convertWorldToWindowCoordinates(enemyVec[i].getPosX(), enemyVec[i].getPosY(), enemyVec[i].getPosZ(), windowCoords, window);
			Vector3f vectorToEnemy(enemyVec[i].getPosX() - camera.x, enemyVec[i].getPosY() - camera.y, enemyVec[i].getPosZ() - camera.z);
			Vector3f viewVector(-sin(angleX / 180 * PI), tan(angleY / 180 * PI), -cos(angleX / 180 * PI));

			float length1 = std::sqrt(vectorToEnemy.x * vectorToEnemy.x + vectorToEnemy.y * vectorToEnemy.y + vectorToEnemy.z * vectorToEnemy.z);
			vectorToEnemy.x /= length1;
			vectorToEnemy.y /= length1;
			vectorToEnemy.z /= length1;

			float length2 = std::sqrt(viewVector.x * viewVector.x + viewVector.y * viewVector.y + viewVector.z * viewVector.z);
			viewVector.x /= length2;
			viewVector.y /= length2;
			viewVector.z /= length2;

			float fontScale = 1.0f - (length1 / 250); 
			float fontSize = 30.0f * fontScale;
			
			float angleToEnemy = std::acos(vectorToEnemy.x * viewVector.x + vectorToEnemy.y * viewVector.y + vectorToEnemy.z * viewVector.z) * 180.0 / PI;
			
			glTranslatef(enemyVec[i].getPosX(), enemyVec[i].getPosY(), enemyVec[i].getPosZ());
			textureManager.drawBox(worm, size0 / 10);
			glTranslatef(-enemyVec[i].getPosX(), -enemyVec[i].getPosY(), -enemyVec[i].getPosZ());

			
			if (angleToEnemy >= -90 && angleToEnemy <= 90)
			{
				glTranslatef(enemyVec[i].getPosX(), enemyVec[i].getPosY(), enemyVec[i].getPosZ());
				window.pushGLStates();

				if (fontSize > 0.0f)
				{
					textureManager.addName(enemyVec[i].name, font, windowCoords, window, fontSize);
				}
				window.popGLStates();
				glTranslatef(-enemyVec[i].getPosX(), -enemyVec[i].getPosY(), -enemyVec[i].getPosZ());
			}
		}

		glTranslatef(player.getPosX(), player.getPosY(), player.getPosZ());
		textureManager.drawBox(worm, size0 / 10);
		glTranslatef(-player.getPosX(), -player.getPosY(), -player.getPosZ());
	

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

void addPlayer(string clientName)
{
	Player enemy(size0);
	enemyVec.push_back(enemy);
	enemyVec.back().name = clientName;
	
};