#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>

#include "NetworkServer.h"

using namespace sf;
using namespace std;

NetworkServer netS;


int main()
{
	netS.init();
	Packet packet;
	packet << "DATA";
	for (int i = 0; i < netS.clientsVec.size(); i++)
	{
		packet << netS.clientsVec[i].name << netS.clientsVec[i].pos.x << netS.clientsVec[i].pos.y << netS.clientsVec[i].pos.z;
		
	}

	while (true)
	{
		netS.registerNewClients();
		netS.sendConnectedClientsRecords();

		if (netS.sendDataToAll(packet) == Socket::Status::Done)
		{
			packet.clear();
			packet << "DATA";
			for (int i = 0; i < netS.clientsVec.size(); i++)
			{
				packet << netS.clientsVec[i].name << netS.clientsVec[i].pos.x << netS.clientsVec[i].pos.y << netS.clientsVec[i].pos.z;
				//cout << netS.clientsVec[i].name << " "<< netS.clientsVec[i].pos.x << " " <<netS.clientsVec[i].pos.y << " " << netS.clientsVec[i].pos.z << endl;
			}
		}


		unsigned int receivedClientIndex;
		if (netS.receiveData(receivedClientIndex) == Socket::Status::Done)
		{
			if (netS.clientsVec[receivedClientIndex].rDataPacket.getDataSize() > 0)
			{
				string s;
				if (netS.clientsVec[receivedClientIndex].rDataPacket >> s)
				{
					if (s == "DATA")
					{
						float x, y, z;

						if (netS.clientsVec[receivedClientIndex].rDataPacket >> x)
						{
							netS.clientsVec[receivedClientIndex].pos.x = x;

						}
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> y)
						{
							netS.clientsVec[receivedClientIndex].pos.y = y;
						}
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> z)
						{
							netS.clientsVec[receivedClientIndex].pos.z = z;
						}
						netS.clientsVec[receivedClientIndex].rDataPacket.clear();

						//cout << netS.clientsVec[receivedClientIndex].name << netS.clientsVec[receivedClientIndex].pos.x << " " << netS.clientsVec[receivedClientIndex].pos.y << " " << netS.clientsVec[receivedClientIndex].pos.z << endl;
					}
				}
			}
		}
	}


	getchar();
	return 0;
}
