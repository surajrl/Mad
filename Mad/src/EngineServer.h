#pragma once

#include "matching/Market.h"
#include "fixlatest/FIXHandler.h"

#include <thread>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

namespace Mad { 

	constexpr auto BUFFER_LEN = 512;

	class EngineServer;

	typedef void(*MessageReceivedHandler)(EngineServer* listenSocket, SOCKET clientSocket, std::string message);

	class EngineServer
	{
	public:
		EngineServer(std::string ipv4Address, std::string tcpPort, MessageReceivedHandler messageReceivedHandler, FIXHandler fixHandler)
			: m_IPv4Address(ipv4Address), m_TCPPort(tcpPort), m_MessageReceivedHandler(messageReceivedHandler), m_FIXHandler(fixHandler)
		{};

		~EngineServer()
		{
			WSACleanup();
		};

		FIXHandler& getFIXHandler() { return m_FIXHandler; };

		void ActiveConnection(SOCKET clientSocket);

		int Init();
		void Run();

	private:
		std::string m_IPv4Address;
		std::string m_TCPPort;
		MessageReceivedHandler m_MessageReceivedHandler;

		FIXHandler m_FIXHandler;
		
		SOCKET CreateSocket();
		SOCKET WaitForConnections(SOCKET listenSocket);

	};

}

