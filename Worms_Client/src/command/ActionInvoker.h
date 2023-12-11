#pragma once
#include "Actions.h"
#include <map>
#include <iostream>
#include "../player.h"
#include "Turboranec.h"
#include "../camera.h"
#include "Teleport.h"
using namespace sf;

class ActionInvoker 
{
private:
	std::map<String, Actions*> commands;
	Turboranec ranec;
	Teleport teleport;

public:
	
	ActionInvoker();
	void setCommand();
	void addCommand(String name, Actions* command);

	void executeCommand(String& name, Player& player0, Camera& camera);
};