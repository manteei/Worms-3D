#include "GameStart.h"


Gam�Start::Gam�Start(NetworkClient& netC0, IpAddress S_Ip0, unsigned short S_port0, Player player0, vector<string> namesVec0)
	:netC(netC0), S_Ip(S_Ip0), S_port(S_port0), player(player0), namesVec(namesVec0)
{
}

void Gam�Start::addPlayer(string clientName)
{
	Player enemy(size0);
	enemyVec.push_back(enemy);
	enemyVec.back().name = clientName;

};
void Gam�Start::deletePlayer(string clientName)
{
	Player enemy(size0);
	enemyVec.push_back(enemy);
	enemyVec.back().name = clientName;

};



void Gam�Start::start()
{
	
	RenderWindow window(VideoMode::getDesktopMode(), L"WORMS", Style::Default, ContextSettings(32));
	bool isDragging = false;
	Vector2i offset;
	ConfirmClosure confirmClosure;
	ResultGame resultGame;
	window.setVerticalSyncEnabled(true);

	window.setActive(true);
	float width = VideoMode::getDesktopMode().width/2;
	float height = VideoMode::getDesktopMode().height/2;

	Texture t;
	t.loadFromFile("resources/cursor.png");
	Sprite s(t);

	Texture tShot;
	tShot.loadFromFile("resources/cursorShot.png");
	Sprite sShot(tShot);
	sShot.setOrigin(tShot.getSize().x / 2.0f, tShot.getSize().y / 2.0f);
	float scaleFactor = 0.5f;
	sShot.setScale(scaleFactor, scaleFactor);

	Font font;
	font.loadFromFile("8bitOperatorPlus-Regular.ttf");
	
	RectangleShape background_ab(Vector2f(350, 400));
	Texture texture_ab;
	if (!texture_ab.loadFromFile("resources/tools/back.png")) exit(3);
	background_ab.setTexture(&texture_ab);
	background_ab.setPosition(1500, 600);


	

	RectangleShape background_timer(Vector2f(100, 100));
	Texture texture_timer;
	if (!texture_timer.loadFromFile("resources/q.png")) exit(4);
	background_timer.setTexture(&texture_timer);
	background_timer.setPosition(100, 800);

 
	String name_menu[]{L"��������",L"������",L"�������",L"����",L"�������",L"�������",L"�������",L"��������",L"�����������",L"�������������",L"�����������",L"���� �����" ,L"����� ����",L"���������",L"����������" };


	Options mymenu(window, 1533, 700, 15, name_menu, 30, 57);
	Health health(window);

	s.setOrigin(8, 8); s.setPosition(width, height);
	sShot.setPosition(width, height);

	std::vector<GLuint> skybox = textureManager.createSkybox();
	GLuint box = textureManager.createBox();
	GLuint worm = textureManager.createWorm();
	GLuint sand = textureManager.createSand();


	Map myMap(64, 15, 64);
	std::vector<std::vector<std::vector<bool>>> mass(100, std::vector<std::vector<bool>>(100, std::vector<bool>(100, false)));

	Camera camera(player);
	
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 2000.f);
	glEnable(GL_TEXTURE_2D);
	ShowCursor(FALSE);

	myMap.createMap(mass);
	ActionInvoker invoker;
	mymenu.showWindow = false;

	for (int i = 0; i < namesVec.size(); i++)
	{
		addPlayer(namesVec[i]);
	}

	Packet receivedDataPacket;
	Packet sendDataPacket;
	Packet sendPacketShoot;

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
					else if (s == "DATA")
					{
						while (!receivedDataPacket.endOfPacket())
						{
							float x, y, z;
							float damage;
							string name;
							receivedDataPacket >> s;
							receivedDataPacket >> x;
							receivedDataPacket >> y;
							receivedDataPacket >> z;
							receivedDataPacket >> name;
							receivedDataPacket >> damage;

							for (int i = 0; i < enemyVec.size(); i++)
							{
								if (s == enemyVec[i].name) enemyVec[i].setPosition(x, y, z);
								if (name == enemyVec[i].name) enemyVec[i].health -= damage;
							}
							if (name == player.name) {
								player.health -= damage;
								
							}
						}
					}
					else if (s == "DEAD") {
						string name;
						receivedDataPacket >> name;
						auto it = find_if(enemyVec.begin(), enemyVec.end(), [&](const Player& player) {
							return player.name == name;
							});

						if (it != enemyVec.end()) {
							enemyVec.erase(it);
							
						}

					}

				}
			}
		}

		damage = 0;
		nameEnemy = "";
		health.updateHealth(player, enemyVec);

		if (player.health <= 0) {
			resultGame.gameIsLost();
			window.close();
		}
		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)) {
				confirmClosure.showConfirmClosure();
				if (confirmClosure.needClose){ window.close(); }
			}
			
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left )
			{
				
				if (camera.showMap) {
					offset = Mouse::getPosition();
					player.x = int(offset.x * 0.7);
					player.z = int(offset.y * 1.3);
					for (int i = myMap.maxY; i >= myMap.minY; i--) {
						if (mass[int(player.x / size0)][i][int(player.z / size0)] == 1) {
							player.y = i * size0 + size0;
							break;
						}
					}
					ShowCursor(FALSE);
					camera.showMap = false;
					camera.farPlayers = 0;
				}
				
				windowIsActive = true;
				window.setMouseCursorVisible(false);
				mymenu.showWindow = false;
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right && !camera.showMap)
			{
				mymenu.showWindow = true;
				windowIsActive = false;
				window.setMouseCursorVisible(true);
			}

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
				if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
				if (event.key.code == Keyboard::Left) { mymenu.MoveLeft(); }
				if (event.key.code == Keyboard::Right) { mymenu.MoveRight(); }
				if (event.key.code == Keyboard::Enter) { 
					mymenu.showWindow = false;
					windowIsActive = true; 
					invoker.executeCommand(name_menu[mymenu.getSelectedMenuNumber()],player, camera); 
					timer.restart();
					
					
				}
				if (event.key.code == Keyboard::Space && player.canShoot) { shoot = 1; }
				
			}
		}
		

		if (timer.getElapsedTime().asSeconds() < 10 && (player.flying || player.canShoot)) {
			initText.timer(Titul, 126, 780, 10- timer.getElapsedTime().asSeconds(), 100, Color(66, 170, 255), 4, Color::White);
			
		}
		else { player.flying = false; player.canShoot = false;
		}



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (windowIsActive) {
			player.keyboard(angleX);
			player.update(cycleTime, mass, myMap);
			camera.keyboard();
			camera.update(cycleTime, player);

			POINT mousexy;
			GetCursorPos(&mousexy);
			int xt = window.getPosition().x + width;
			int yt = window.getPosition().y + height;

			angleX += (xt - mousexy.x) / 4;
			angleY += (yt - mousexy.y) / 4;

			if (angleY < -89.0) { angleY = -89.0; }
			if (angleY > 89.0) { angleY = 89.0; }

			SetCursorPos(xt, yt);

			if (shoot)
			{
				float x = player.x;
				float y = player.y + player.h;
				float z = player.z;

				int X, Y, Z;
				int dist = 0;
				bool flag = false;
				
				while (dist < 120)  // ������ ��������
				{		
					dist++;
					x += -sin(angleX / 180 * PI);   
					y += tan(angleY / 180 * PI);   
					z += -cos(angleX / 180 * PI);    

					for (int i = 0; i < enemyVec.size(); i++) {
						if (x  <= enemyVec[i].x + size0 /2 && x   >= enemyVec[i].x - size0 / 2 &&
							y  <= enemyVec[i].y + size0 / 2 && y   >= enemyVec[i].y - size0 / 2 &&
							z  <= enemyVec[i].z + size0 / 2 && z  >= enemyVec[i].z - size0 / 2)
						{
							damage = player.damage;
							flag = true;
							nameEnemy = enemyVec[i].name;
							break;
						}
					}
					if (flag) break;
				}
			}
			shoot = 0;
		}
		sendDataPacket.clear();
		sendDataPacket << "DATA" << player.x << player.y << player.z << nameEnemy << damage;
		netC.sendData(sendDataPacket);

		if (camera.showMap ) {
			angleX = 0; angleY = -89;
			windowIsActive = false;
			ShowCursor(TRUE);
			window.setMouseCursorVisible(true);
			mymenu.showWindow = false;

		}
		window.clear();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(camera.x, camera.y + camera.farPlayers + camera.h / 2, camera.z, camera.x - sin(angleX / 180 * PI), camera.y + camera.farPlayers + camera.h / 2 + (tan(angleY / 180 * PI)), camera.z - cos(angleX / 180 * PI), 0, 1, 0);
	
		glTranslatef(camera.x, camera.y + camera.farPlayers, camera.z);
		textureManager.drawSkybox(skybox, 1000);
		glTranslatef(-camera.x, -camera.y - camera.farPlayers, -camera.z);

		myMap.drawMap(textureManager, size0, box, sand, mass);

		for (int i = 0; i < enemyVec.size(); i++)
		{
			Vector2f windowCoords;
			textureManager.convertWorldToWindowCoordinates(enemyVec[i].x, enemyVec[i].y, enemyVec[i].z, windowCoords, window);
			Vector3f vectorToEnemy(enemyVec[i].x - camera.x, enemyVec[i].y - camera.y, enemyVec[i].z - camera.z);
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

			glTranslatef(enemyVec[i].x, enemyVec[i].y, enemyVec[i].z);
			textureManager.drawBox(worm, size0 / 2);
			glTranslatef(-enemyVec[i].x, -enemyVec[i].y, -enemyVec[i].z);


			if (angleToEnemy >= -90 && angleToEnemy <= 90)
			{
				glTranslatef(enemyVec[i].x, enemyVec[i].y, enemyVec[i].z);
				window.pushGLStates();

				if (fontSize > 0.0f)
				{
					textureManager.addName(enemyVec[i].name, font, windowCoords, window, fontSize);
				}
				window.popGLStates();
				glTranslatef(-enemyVec[i].x, -enemyVec[i].y, -enemyVec[i].z);
			}
		}

		glTranslatef(player.x, player.y, player.z);
		textureManager.drawBox(worm, size0 / 10);
		glTranslatef(-player.x, -player.y, -player.z);


		window.pushGLStates();
		
		if (player.flying || player.canShoot) {
			window.draw(background_timer);
			window.draw(Titul);
		}
		if (player.canShoot) window.draw(sShot);
		else window.draw(s);
		if (mymenu.showWindow) {
			window.draw(background_ab);
			mymenu.draw();
		}
		health.draw();
		window.popGLStates();
		window.display();

	}


};

