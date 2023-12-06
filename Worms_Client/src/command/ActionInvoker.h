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
	Player player;
	Turboranec ranec;

public:
	ActionInvoker(Player player0);
	void setCommand();
	void addCommand(String name, Actions* command);

	void executeCommand(String& name);
};