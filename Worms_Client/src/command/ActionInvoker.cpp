#include "ActionInvoker.h"


void ActionInvoker::setCommand() {
	addCommand(L"Турборанец", &ranec);
}
ActionInvoker::ActionInvoker(Player player0) 
	:player(player0)
{
	setCommand();
}
void ActionInvoker::addCommand(String name, Actions* command) {
	commands[name] = command;

}

void ActionInvoker::executeCommand(String& name, Player& player0) {
	if (commands.find(name) != commands.end()) {
		commands[name]->execute(player0);
	}
	
	else {
		
		std::cout << "Команда не найдена" << std::endl;
	}
}