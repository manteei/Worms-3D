#pragma once
#include "Actions.h"
#include <map>
#include <iostream>
#include "../player.h"
#include "Turboranec.h"
using namespace sf;

class ActionInvoker 
{
private:
	std::map<String, Actions*> commands;
	

public:
	Player player;
	Turboranec ranec;
	ActionInvoker(Player player0);
	void setCommand();
	void addCommand(String name, Actions* command);

	void executeCommand(String& name, Player& player0);
};