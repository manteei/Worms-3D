#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class NetworkClient
{
	UdpSocket dataSocket;
	TcpSocket regSocket;

	Packet sendPacket;

	Clock sendRateTimer;
	Int16 sendRate = 2;

	IpAddress S_Ip;
	unsigned short S_regPort;
	unsigned short S_dataPort;
public:
	NetworkClient();

	Socket::Status init(unsigned short preferablePort = Socket::AnyPort);

	Socket::Status registerOnServer(IpAddress serverIp, unsigned short serverRegPort, string clientName);
	Socket::Status receiveConnectedClientsNames(vector<string>& namesVec);

	Socket::Status receiveData(Packet& dataPacket, IpAddress S_Ip, unsigned short S_dataPort);

	Socket::Status sendData(Packet dataPacket);
	void setSendFreq(Int32 milliseconds);
private:

	Socket::Status connectRegTcpSocket(IpAddress serverIp, unsigned short serverRegPort);

	Socket::Status sendClientRecipientData(string clientName);
  
	Socket::Status recieveDedicatedDataServerPort();


};
