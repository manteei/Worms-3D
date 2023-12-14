#pragma once
#include "player.h"

using namespace sf;
using namespace std;

class TeamWorms 
{
	float size = 20.0f;
	int generateRandomNumber();
	Player player1;
	Player player2;
	Player player3;
	Player player4;
	Player player5;
	Player player6;
public:
	TeamWorms();
	vector<Player> team;
	string name;
	int selectesWorm = 0;
	void changeWorm(int selectesWorm0);
	void createTeam();
};