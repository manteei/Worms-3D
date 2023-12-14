#include "TeamWorms.h"

int TeamWorms::generateRandomNumber() {
	// srand(time(0)); 
	int randomNumber = rand() % 501 + 500;
	return randomNumber;
}
TeamWorms::TeamWorms()
{
	/*player1 = new Player();
	player2 = new Player();
	player3 = new Player();
	player4 = new Player();
	player5 = new Player();
	player6 = new Player();*/

	team = vector<Player> {player1,player2,player3,player4,player5,player6};
}

void TeamWorms::changeWorm(int selectesWorm0) {
	selectesWorm = selectesWorm0 % 6;
}

void TeamWorms::createTeam() {
	
	
}