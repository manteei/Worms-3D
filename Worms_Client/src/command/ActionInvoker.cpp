#include "ActionInvoker.h"


void ActionInvoker::setCommand() {
	addCommand(L"Турборанец", &ranec);
	addCommand(L"Телепорт", &teleport);
	addCommand(L"Пулемет", &machineGun);
	addCommand(L"Дробовик", &shotGun);
	addCommand(L"Ракета", &rocker);
	addCommand(L"Граната", &grenade);
	addCommand(L"Динамит", &dynamite);
	addCommand(L"Бананобомба", &bananaBomb);
}
ActionInvoker::ActionInvoker() 
{
	setCommand();
}
void ActionInvoker::addCommand(String name, Actions* command) {
	commands[name] = command;

}

void ActionInvoker::executeCommand(String& name, Player& player0, Camera& camera0) {
	if (commands.find(name) != commands.end()) {
		commands[name]->execute(player0, camera0);
	}
	
	else {
		
		std::cout << "Command not found" << std::endl;
	}
}