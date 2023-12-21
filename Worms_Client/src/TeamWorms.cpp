#include "TeamWorms.h"


TeamWorms::TeamWorms()
{
	Player player1;
	Player player2;
	Player player3;
	Player player4;
	Player player5;
	Player player6;

	team = vector<Player> {player1,player2,player3,player4,player5,player6};
}

void TeamWorms::changeWorm(int selectesWorm0) {
	selectesWorm = selectesWorm0 % 6;
}

void TeamWorms::createTeam() {
	
	
}