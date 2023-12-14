#include "GameStart.h"


GamеStart::GamеStart(NetworkClient& netC0, IpAddress S_Ip0, unsigned short S_port0, TeamWorms player0, vector<string> namesVec0)
	:netC(netC0), S_Ip(S_Ip0), S_port(S_port0), player(player0), namesVec(namesVec0)
{
	//player.createTeam();
}

void GamеStart::addPlayer(string clientName)
{
	TeamWorms enemy;
	enemyVec.push_back(enemy);
	enemyVec.back().name = clientName;
};



void GamеStart::start()
{
	
	RenderWindow window(VideoMode::getDesktopMode(), L"WORMS", Style::Default, ContextSettings(32));
	bool isDragging = false;
	Vector2i offset;

	window.setVerticalSyncEnabled(true);

	window.setActive(true);
	float width = VideoMode::getDesktopMode().width/2;
	float height = VideoMode::getDesktopMode().height/2;

	Texture t;
	t.loadFromFile("resources/cursor.png");
	Sprite s(t);

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

 
	String name_menu[]{L"Дробовик",L"Ракета",L"Парашут",L"Бита",L"Динамит",L"Граната",L"Пулемет",L"Телепорт",L"Чермагеддон",L"Электромагнит",L"Бананобомба",L"Злой ослик" ,L"Супер овца",L"Мегакулак",L"Турборанец" };


	Options mymenu(window, 1533, 700, 15, name_menu, 30, 57);
	Health health(window);

	s.setOrigin(8, 8); s.setPosition(width, height);

//	initText.texts(Titul, 50, 950, L"чтобы открыть опциии, кликните правой кнопкой", 20, Color::Black);

	std::vector<GLuint> skybox = textureManager.createSkybox();
	GLuint box = textureManager.createBox();
	GLuint worm = textureManager.createWorm();
	GLuint sand = textureManager.createSand();


	Map myMap(64, 15, 64);
	std::vector<std::vector<std::vector<bool>>> mass(100, std::vector<std::vector<bool>>(100, std::vector<bool>(100, false)));
	
	Camera camera(player.team[player.selectesWorm]);
	
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
					if (s == "DATA")
					{
						while (!receivedDataPacket.endOfPacket())
						{
							float x, y, z, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5;
							receivedDataPacket >> s;
							receivedDataPacket >> x; receivedDataPacket >> y; receivedDataPacket >> z;
							receivedDataPacket >> x1; receivedDataPacket >> y1; receivedDataPacket >> z1;
							receivedDataPacket >> x2; receivedDataPacket >> y2; receivedDataPacket >> z2;
							receivedDataPacket >> x3; receivedDataPacket >> y3; receivedDataPacket >> z3;
							receivedDataPacket >> x4; receivedDataPacket >> y4; receivedDataPacket >> z4;
							receivedDataPacket >> x5; receivedDataPacket >> y5; receivedDataPacket >> z5;
							
							for (int i = 0; i < enemyVec.size(); i++)
							{
								if (s == enemyVec[i].name) {
									enemyVec[i].team[0].setPosition(x, y, z);
									enemyVec[i].team[1].setPosition(x1, y1, z1);
									enemyVec[i].team[2].setPosition(x2, y2, z2);
									enemyVec[i].team[3].setPosition(x3, y3, z3);
									enemyVec[i].team[4].setPosition(x4, y4, z4);
									enemyVec[i].team[5].setPosition(x5, y5, z5);
								}
									
							//	if (name == enemyVec[i].name) enemyVec[i].health -= damage;
							}
						//	if (name == player.name) player.health -= damage;
						}
					}
				}
			}
		}

		

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				window.close();
			
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left )
			{
				
				if (camera.showMap) {
					offset = Mouse::getPosition();
					player.team[player.selectesWorm].x = int(offset.x * 0.7);
					player.team[player.selectesWorm].z = int(offset.y * 1.3);
					for (int i = myMap.maxY; i >= myMap.minY; i--) {
						if (mass[int(player.team[player.selectesWorm].x / size0)][i][int(player.team[player.selectesWorm].z / size0)] == 1) {
							player.team[player.selectesWorm].y = i * size0 + size0;
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
				if (mymenu.showWindow) {
					if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
					if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
					if (event.key.code == Keyboard::Left) { mymenu.MoveLeft(); }
					if (event.key.code == Keyboard::Right) { mymenu.MoveRight(); }
					if (event.key.code == Keyboard::Enter) {
						mymenu.showWindow = false;
						windowIsActive = true;
						invoker.executeCommand(name_menu[mymenu.getSelectedMenuNumber()], player.team[player.selectesWorm], camera);
						timer.restart();
					}
				}
				else {
					if (event.key.code == Keyboard::Left) { player.changeWorm(player.selectesWorm -= 1); }
					if (event.key.code == Keyboard::Right) { player.changeWorm(player.selectesWorm += 1); }
				}

				
				if (event.key.code == Keyboard::Space && player.team[player.selectesWorm].canShoot) { shoot = 1; }
			}
		}
		

		if (timer.getElapsedTime().asSeconds() < 10 && (player.team[player.selectesWorm].flying || player.team[player.selectesWorm].canShoot)) {
			initText.timer(Titul, 126, 780, 10- timer.getElapsedTime().asSeconds(), 100, Color(66, 170, 255), 4, Color::White);
			
		}
		else {
			player.team[player.selectesWorm].flying = false; player.team[player.selectesWorm].canShoot = false;
		}



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (windowIsActive) {
			player.team[player.selectesWorm].keyboard(angleX);
			for (int i = 0; i < 6; i++) {
				player.team[i].update(cycleTime, mass, myMap);
				
			}
			
			camera.keyboard();
			camera.update(cycleTime, player.team[player.selectesWorm]);

			POINT mousexy;
			GetCursorPos(&mousexy);
			int xt = window.getPosition().x + width;
			int yt = window.getPosition().y + height;

			angleX += (xt - mousexy.x) / 4;
			angleY += (yt - mousexy.y) / 4;

			if (angleY < -89.0) { angleY = -89.0; }
			if (angleY > 89.0) { angleY = 89.0; }

			SetCursorPos(xt, yt);

			//if (shoot)
			//{
			//	float x = player.x;
			//	float y = player.y + player.h;
			//	float z = player.z;

			//	int X, Y, Z;
			//	int dist = 0;
			//	bool flag = false;
			//	
			//	while (dist < 120)  // радиус действия
			//	{		
			//		dist++;
			//		x += -sin(angleX / 180 * PI);    X = x ;
			//		y += tan(angleY / 180 * PI);    Y = y ;
			//		z += -cos(angleX / 180 * PI);    Z = z ;

			//		for (int i = 0; i < enemyVec.size(); i++) {
			//			if (x  <= enemyVec[i].x + size0 /2 && x   >= enemyVec[i].x - size0 / 2 &&
			//				y  <= enemyVec[i].y + size0 / 2 && y   >= enemyVec[i].y - size0 / 2 &&
			//				z  <= enemyVec[i].z + size0 / 2 && z  >= enemyVec[i].z - size0 / 2)
			//			{
			//				damage = player.damage;
			//				flag = true;
			//				nameEnemy = enemyVec[i].name;
			//				break;
			//			}
			//		}
			//		if (flag) break;
			//	}
			//}
			//shoot = 0;
		}
		sendDataPacket.clear();
		sendDataPacket << "DATA" << player.team[0].x << player.team[0].y << player.team[0].z << player.team[1].x << player.team[1].y << player.team[1].z
			<< player.team[2].x << player.team[2].y << player.team[2].z << player.team[3].x << player.team[3].y << player.team[3].z 
			<< player.team[4].x << player.team[4].y << player.team[4].z << player.team[5].x << player.team[5].y << player.team[5].z;
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
			for (int j = 0; j < 6; j++) {
				glTranslatef(enemyVec[i].team[j].x, enemyVec[i].team[j].y, enemyVec[i].team[j].z);
				textureManager.drawBox(worm, size0 / 5);
				glTranslatef(-enemyVec[i].team[j].x, -enemyVec[i].team[j].y, -enemyVec[i].team[j].z);
			}
		}
		/*for (int i = 0; i < enemyVec.size(); i++)
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
		}*/
		for (int i = 0; i < 6; i++) {
			glTranslatef(player.team[i].x, player.team[i].y, player.team[i].z);
			textureManager.drawBox(worm, size0 / 10);
			glTranslatef(-player.team[i].x, -player.team[i].y, -player.team[i].z);
		}
		


		window.pushGLStates();
		window.draw(s);
		if (mymenu.showWindow) {
			window.draw(background_ab);
			mymenu.draw();
		}
		if (player.team[player.selectesWorm].flying || player.team[player.selectesWorm].canShoot) {
			window.draw(background_timer);
			window.draw(Titul);
		}
	//	health.draw();
		window.popGLStates();
		window.display();

	}


};

