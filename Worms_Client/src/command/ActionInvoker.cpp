#include "ActionInvoker.h"


void ActionInvoker::setCommand() {
	addCommand(L"Турборанец", &ranec);
	addCommand(L"Телепорт", &teleport);
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
		
		std::cout << "Команда не найдена" << std::endl;
	}
}