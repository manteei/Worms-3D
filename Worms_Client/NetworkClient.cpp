#include "NetworkClient.h"

NetworkClient::NetworkClient()
{
}

Socket::Status NetworkClient::init(unsigned short preferablePort)
{
	Socket::Status status = dataSocket.bind(preferablePort);

	if (status == Socket::Status::Done)
	{
		cout << "init(): Успешно подключились к порту: " << dataSocket.getLocalPort() << endl;
		return Socket::Status::Done;
	}
	else
	{
		cout << "(!)init(): Не удалось подключиться к порту\n";
		do
		{
			unsigned short newPort = Socket::AnyPort;
			cout << "init(): Пытаюсь привязать другой порт - " << newPort << endl;
			status = dataSocket.bind(newPort);
			if (status != Socket::Status::Done)
				cout << "(!)init(): Не удалось привязать другой порт. Повторная попытка...\n";

		} while (status != Socket::Done);

		cout << "init(): Успешно подключились к другому порту - " << dataSocket.getLocalPort() << endl;
		return Socket::Status::Done;
	}
}

Socket::Status NetworkClient::registerOnServer(IpAddress serverIp, unsigned short serverRegPort, string clientName)
{
	if (connectRegTcpSocket(serverIp, serverRegPort) != Socket::Status::Done)
		return Socket::Status::Error;

	if (sendClientRecipientData(clientName) != Socket::Status::Done)
		return Socket::Status::Error;

	if (recieveDedicatedDataServerPort() != Socket::Status::Done)
		return Socket::Status::Error;

}

Socket::Status NetworkClient::receiveConnectedClientsNames(vector<string>& namesVec)
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	Packet tempPacket;

	if (regSocket.receive(tempPacket) == Socket::Status::Done)
	{
		if (tempPacket.getDataSize() > 0)
		{
			while (!tempPacket.endOfPacket())
			{
				string name;
				if (tempPacket >> name)
				{
					if (name == "FIRST")
					{
						"receiveConnectedClientsNames(): Ни один клиент не подключен, вы первый\n";
						return Socket::Status::Done;
					}
					namesVec.push_back(name);
				}
				else
				{
					cout << "(!)receiveConnectedClientsNames() :Не удалось прочитать пакет\n";
					return Socket::Status::Error;
				}
			}
			cout << "receiveConnectedClientsNames() :Имена клиентов прочитаны\n";
			/*for (int i = 0; i < namesVec.size(); i++)
			{
				cout << namesVec[i];
			}
			cout << endl;*/
			return Socket::Status::Done;

		}
		else cout << "(!)receiveConnectedClientsNames(): Принимаемый пакет пуст. Убедитесь, что пакет содержит: (string name1 << string name2 << ...) или \"FIRST\" если это первый подключенный клиент\n";
	}
	else cout << "(!)receiveConnectedClientsNames(): Не удалось получить имена клиентов.\n";

	return Socket::Status::Error;
}

Socket::Status NetworkClient::receiveData(Packet& dataPacket, IpAddress S_Ip, unsigned short S_dataPort)
{
	if (dataSocket.isBlocking())dataSocket.setBlocking(false);

	if (dataSocket.receive(dataPacket, S_Ip, S_dataPort) == Socket::Status::Done)
	{
		if (dataPacket.getDataSize() > 0)
		{
			//cout << "receiveData(): Data received\n";
			return Socket::Status::Done;
		}
		else
		{
			cout << "(!)receiveData(): Полученный пакет пустой\n";
			return Socket::Status::Error;
		}
	}
	return Socket::Status::NotReady;
}

Socket::Status NetworkClient::sendData(Packet dataPacket)
{
	if (sendRateTimer.getElapsedTime().asMilliseconds() > sendRate)
	{
		if (dataSocket.isBlocking())dataSocket.setBlocking(false);

		if (sendPacket.getDataSize() == 0) sendPacket = dataPacket;

		IpAddress tempIp = S_Ip;
		unsigned short tempDataPort = S_dataPort;
		if (dataSocket.send(sendPacket, tempIp, tempDataPort) == Socket::Status::Done)
		{
			sendPacket.clear();
			sendRateTimer.restart();
			return Socket::Status::Done;
		}
		else return Socket::Status::NotReady;
	}
	else return Socket::Status::NotReady;
}

void NetworkClient::setSendFreq(Int32 milliseconds)
{
	sendRate = milliseconds;
}

Socket::Status NetworkClient::connectRegTcpSocket(IpAddress serverIp, unsigned short serverRegPort)
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	if (regSocket.connect(serverIp, serverRegPort, seconds(10)) == Socket::Status::Done)
	{
		cout << "connectRegTcpSocket(): Подключено к серверу\n";
		S_Ip = serverIp;
		S_dataPort = serverRegPort;
		return Socket::Status::Done;
	}
	else
	{
		cout << "(!)connectRegTcpSocket(): Ошибка подключения к серверу!\n";
		return Socket::Status::Error;
	}
}

Socket::Status NetworkClient::sendClientRecipientData(string clientName)
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	Packet tempPacket;
	tempPacket << clientName << static_cast<Uint16>(dataSocket.getLocalPort());

	if (regSocket.send(tempPacket) == Socket::Status::Done)
	{
		cout << "sendClientRecipientData(): Данные получателя клиента успешно отправлены.\n";
		return Socket::Status::Done;
	}
	else
	{
		cout << "(!)sendClientRecipientData(): Не удалось отправить данные получателя клиента.\n";
		return Socket::Status::Error;
	}
}

Socket::Status NetworkClient::recieveDedicatedDataServerPort()
{
	if (!regSocket.isBlocking()) regSocket.setBlocking(true);

	Packet tempPacket;

	if (regSocket.receive(tempPacket) == Socket::Status::Done)
	{
		if (tempPacket.getDataSize() > 0)
		{
			if (tempPacket.getDataSize() == sizeof(Uint16))
			{
				if (tempPacket >> S_dataPort)
				{
					cout << "recieveDedicatedDataServerPort(): Успешно получены данные клиентского выделенного порта сервера - " << S_dataPort << endl;
					return Socket::Status::Done;
				}
				else cout << "(!)recieveDedicatedDataServerPort(): Не удалось прочитать полученный пакет.\n";
			}
			else cout << "(!)recieveDedicatedDataServerPort(): недопустимый размер пакета, убедитесь, что сервер отправляет только Uint16 \n";
		}
		else cout << "(!)recieveDedicatedDataServerPort(): Полученный пакет пустой\n";
	}
	else cout << "(!)recieveDedicatedDataServerPort(): Не удалось получить выделенный клиентский порт сервера.\n";

	return Socket::Status::Error;
}