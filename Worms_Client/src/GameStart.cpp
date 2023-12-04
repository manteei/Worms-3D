#include "GameStart.h"
#include "Options.h"

GamеStart::GamеStart(NetworkClient& netC0, IpAddress S_Ip0, unsigned short S_port0, Player player0, vector<string> namesVec0)
	:netC(netC0), S_Ip(S_Ip0), S_port(S_port0), player(player0), namesVec(namesVec0)
{
}

void GamеStart::addPlayer(string clientName)
{
	Player enemy(size0);
	enemyVec.push_back(enemy);
	enemyVec.back().name = clientName;

};



void GamеStart::start()
{
	
	RenderWindow window(VideoMode::getDesktopMode(), L"WORMS", Style::Fullscreen);
	bool isDragging = false;
	Vector2i offset;

	window.setVerticalSyncEnabled(true);

	window.setActive(true);
	float width = VideoMode::getDesktopMode().width/2;
	float height = VideoMode::getDesktopMode().height/2;

	Texture t;
	t.loadFromFile("resources/cursor.png");
	Sprite s(t);

	
	
	RectangleShape background_ab(Vector2f(350, 400));
	Texture texture_ab;
	if (!texture_ab.loadFromFile("resources/tools/back.png")) exit(3);
	background_ab.setTexture(&texture_ab);
	background_ab.setPosition(1500, 600);


	// Название пунктов меню
	String name_menu[]{L"Дробовик",L"Ракета",L"Парашут",L"Бита",L"Динамит",L"Граната",L"Пулемет",L"Телепорт",L"Чермагеддон",L"Электромагнит",L"Бананобомба",L"Злой ослик" ,L"Супер овца",L"Мегакулак" };
	String file[]{ L"resources/tools/drobovik.png",L"resources/tools/raketa.png",L"resources/tools/parashut.png",L"resources/tools/dubinka.png",L"resources/tools/vzryv.png",L"resources/tools/granata.png",
		L"resources/tools/pulemet.png",L"resources/tools/teleport.png",L"resources/tools/chermageddon.png",L"resources/tools/magnit.png",L"resources/tools/banan.png",L"resources/tools/oslik.png" ,
	L"resources/tools/sheep.png",L"resources/tools/kulak.png" };

	Options mymenu(window, 1533, 700, 14, name_menu, file, 30, 57);


	s.setOrigin(8, 8); s.setPosition(width, height);

	initText.texts(Titul, 50, 1000, L"чтобы открыть опциии, нажмите F", 20, Color::Black);

	vector<GLuint> skybox = textureManager.createSkybox();
	GLuint box = textureManager.createBox();
	GLuint worm = textureManager.createWorm();

	Map myMap(30, 10, 30);
	vector<vector<vector<bool>>> mass(500, vector<vector<bool>>(500, vector<bool>(500, false)));

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

								}
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
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::F)) {
				windowIsActive = false;
				mymenu.showWindow = true;
			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::G)) {
				windowIsActive = true;
				ShowCursor(FALSE);
				mymenu.showWindow = false;
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

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
				if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
				if (event.key.code == Keyboard::Left) { mymenu.MoveLeft(); }
				if (event.key.code == Keyboard::Right) { mymenu.MoveRight(); }
			}
		}

		if (isDragging)
		{
			window.setPosition(Mouse::getPosition() + offset);
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

		}
		window.clear();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(camera.x, camera.y + camera.h / 2, camera.z, camera.x - sin(angleX / 180 * PI), camera.y + camera.h / 2 + (tan(angleY / 180 * PI)), camera.z - cos(angleX / 180 * PI), 0, 1, 0);


		glTranslatef(camera.x, camera.y, camera.z);
		textureManager.drawSkybox(skybox, 1000);
		glTranslatef(-camera.x, -camera.y, -camera.z);


		myMap.drawMap(textureManager, size0, box, mass);


		for (int i = 0; i < enemyVec.size(); i++)
		{
			glTranslatef(enemyVec[i].x, enemyVec[i].y, enemyVec[i].z);
			textureManager.drawBox(worm, size0 / 10);
			glTranslatef(-enemyVec[i].x, -enemyVec[i].y, -enemyVec[i].z);
		}
		glTranslatef(player.x, player.y, player.z);
		textureManager.drawBox(worm, size0 / 10);
		glTranslatef(-player.x, -player.y, -player.z);

		
		window.pushGLStates();
		window.draw(s);
		if (mymenu.showWindow) {
			window.draw(background_ab);
			mymenu.draw();
		}else window.draw(Titul);
		window.popGLStates();
		window.display();

	}

};

