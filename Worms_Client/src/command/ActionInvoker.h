#pragma once
#include "Actions.cpp"
#include <map>
#include <iostream>
#include "../player.h"
#include "Turboranec.cpp"
#include "MachineGun.cpp"
#include "ShotGun.cpp"
#include "Rocker.cpp"
#include "Grenade.cpp"
#include "Dynamite.cpp"
#include "BananaBomb.cpp"
#include "../camera.h"
#include "Teleport.cpp"
using namespace sf;

class ActionInvoker 
{
private:
	std::map<String, Actions*> commands;
	Turboranec ranec;
	Teleport teleport;
	MachineGun machineGun;
	ShotGun shotGun;
	Rocker rocker;
	Grenade grenade;
	Dynamite dynamite;
	BananaBomb bananaBomb;

	void setCommand();
	void addCommand(String name, Actions* command);
public:
	ActionInvoker();
	void executeCommand(String& name, Player& player0, Camera& camera);
};