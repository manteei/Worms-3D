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
	Packet packetShoot;
	bool flag = false;
	packet << "DATA";
	for (int i = 0; i < netS.clientsVec.size(); i++)
	{
		packet << netS.clientsVec[i].name << netS.clientsVec[i].pos[0].x << netS.clientsVec[i].pos[0].y << netS.clientsVec[i].pos[0].z << netS.clientsVec[i].pos[1].x << netS.clientsVec[i].pos[1].y << netS.clientsVec[i].pos[1].z
			<< netS.clientsVec[i].pos[2].x << netS.clientsVec[i].pos[2].y << netS.clientsVec[i].pos[2].z << netS.clientsVec[i].pos[3].x << netS.clientsVec[i].pos[3].y << netS.clientsVec[i].pos[3].z
			<< netS.clientsVec[i].pos[4].x << netS.clientsVec[i].pos[4].y << netS.clientsVec[i].pos[4].z << netS.clientsVec[i].pos[5].x << netS.clientsVec[i].pos[5].y << netS.clientsVec[i].pos[5].z;

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
				packet << netS.clientsVec[i].name << netS.clientsVec[i].pos[0].x << netS.clientsVec[i].pos[0].y << netS.clientsVec[i].pos[0].z << netS.clientsVec[i].pos[1].x << netS.clientsVec[i].pos[1].y << netS.clientsVec[i].pos[1].z
					<< netS.clientsVec[i].pos[2].x << netS.clientsVec[i].pos[2].y << netS.clientsVec[i].pos[2].z << netS.clientsVec[i].pos[3].x << netS.clientsVec[i].pos[3].y << netS.clientsVec[i].pos[3].z
					<< netS.clientsVec[i].pos[4].x << netS.clientsVec[i].pos[4].y << netS.clientsVec[i].pos[4].z << netS.clientsVec[i].pos[5].x << netS.clientsVec[i].pos[5].y << netS.clientsVec[i].pos[5].z;
				
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
						float x, y, z, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5;

						if (netS.clientsVec[receivedClientIndex].rDataPacket >> x) netS.clientsVec[receivedClientIndex].pos[0].x = x;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> y) netS.clientsVec[receivedClientIndex].pos[0].y = y;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> z) netS.clientsVec[receivedClientIndex].pos[0].z = z;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> x1) netS.clientsVec[receivedClientIndex].pos[1].x = x1;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> y1) netS.clientsVec[receivedClientIndex].pos[1].y = y1;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> z1) netS.clientsVec[receivedClientIndex].pos[1].z = z1;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> x2) netS.clientsVec[receivedClientIndex].pos[2].x = x2;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> y2) netS.clientsVec[receivedClientIndex].pos[2].y = y2;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> z2) netS.clientsVec[receivedClientIndex].pos[2].z = z2;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> x3) netS.clientsVec[receivedClientIndex].pos[3].x = x3;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> y3) netS.clientsVec[receivedClientIndex].pos[3].y = y3;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> z3) netS.clientsVec[receivedClientIndex].pos[3].z = z3;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> x4) netS.clientsVec[receivedClientIndex].pos[4].x = x4;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> y4) netS.clientsVec[receivedClientIndex].pos[4].y = y4;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> z4) netS.clientsVec[receivedClientIndex].pos[4].z = z4;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> x5) netS.clientsVec[receivedClientIndex].pos[5].x = x5;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> y5) netS.clientsVec[receivedClientIndex].pos[5].y = y5;
						if (netS.clientsVec[receivedClientIndex].rDataPacket >> z5) netS.clientsVec[receivedClientIndex].pos[5].z = z5;
						
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
