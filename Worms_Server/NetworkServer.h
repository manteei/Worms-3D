#pragma once
#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

struct Client
{
	string name;
	string nameEnemy;
	float damage;
	IpAddress Ip;
	UdpSocket* dataSocket;
	unsigned short port;
	Packet rDataPacket;
	Packet sDataPacket;
	bool done = true;

	Vector3f pos{ 100,100,100 };

};

class NetworkServer
{

	short regStep = 0;

	TcpListener listener;
	TcpSocket regSocket;

	Packet packet;

	Clock sendingsRateTimer;
	Int32 sendingsRate = 80;

public:
	vector<Client> clientsVec;

	NetworkServer();

	Socket::Status init();
	Socket::Status registerNewClients();
	Socket::Status sendConnectedClientsRecords();
	void handleClientDisconnection(unsigned int clientIndex);
	Socket::Status receiveData(unsigned int& receivedClientIndex);
	Socket::Status sendDataToAll(Packet dataPacket);
	int xyu;
	string sdf = "";

private:

	Socket::Status acceptIncomingConnection();
	Socket::Status receiveClientRegData();

	Socket::Status sendNewClientDataToAll();
	Socket::Status sendDedicatedDataPort();
	
};
