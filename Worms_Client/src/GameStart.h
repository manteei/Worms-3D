#pragma once
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
#include "Options.h"
#include "Health.h"
#include "InitText.h"
#include "command/ActionInvoker.h"
#include "TeamWorms.h"


using namespace sf;
using namespace std;
class GamåStart
{
	vector<TeamWorms> enemyVec;
	Clock cycleTimer;
	vector<string> namesVec;
	Time cycleTime;
	IpAddress S_Ip;
	unsigned short S_port;
	string clientName;
	NetworkClient& netC;
	float size0 = 20.f;
	bool shoot = 0;
	TextureManager textureManager;
	float angleX, angleY;
	const float PI = 3.141592653;
	TeamWorms player;
	Text Titul;
	InitText initText;
	Clock timer;
	float damage;
	string nameEnemy;
	/*Player player1, player2, player3, player4, player5, player6;
	vector<Player> team;*/
public:
	bool windowIsActive = false;
	GamåStart(NetworkClient& netC0, IpAddress S_Ip0, unsigned short S_port0, TeamWorms player0, vector<string> namesVec0);
	void start();
	void addPlayer(string clientName);

};

