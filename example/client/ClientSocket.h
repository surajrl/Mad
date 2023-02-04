#pragma once

#include <iostream>
#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define BUFFER_LEN 512

class ClientSocket {
public:
	ClientSocket(std::string ipv4Address, std::string tcpPort)
		: m_IPv4Address(ipv4Address), m_TCPPort(tcpPort), m_ConnectSocket(INVALID_SOCKET)
	{
	}

	~ClientSocket()
	{
		closesocket(m_ConnectSocket);
		WSACleanup();
	}
	
	int Init();
	void Run();
private:
	std::string m_IPv4Address;
	std::string m_TCPPort;
	SOCKET m_ConnectSocket;

	void Send(std::string message);
	void Receive();
	int CreateSocket();
};