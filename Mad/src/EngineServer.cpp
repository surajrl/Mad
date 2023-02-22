#include "EngineServer.h"

namespace Mad {

	void EngineServer::ActiveConnection(SOCKET clientSocket)
	{
		char recvBuffer[BUFFER_LEN];
		int recvBytes;

		while (true)
		{
			ZeroMemory(recvBuffer, BUFFER_LEN);

			recvBytes = recv(clientSocket, recvBuffer, BUFFER_LEN, 0);

			if (recvBytes > 0)
			{
				m_MessageReceivedHandler(this, clientSocket, std::string(recvBuffer, 0, recvBytes));
			}

			else
			{
				std::cout << "Client " << clientSocket << " disconnected\n" << std::endl;
				int shutdownResult = shutdown(clientSocket, SD_SEND);

				if (shutdownResult == SOCKET_ERROR)
				{
					std::cout << "shutdown() failed with error: " << WSAGetLastError() << std::endl;
				}

				closesocket(clientSocket);
				return;
			}
		}
	}

	int EngineServer::Init()
	{
		WSADATA wsaData;
		WORD dllVersion = MAKEWORD(2, 2);

		if (WSAStartup(dllVersion, &wsaData) != 0)
		{
			std::cout << "WSAStartup() failed" << std::endl;
			return -1;
		}

		return 1;
	}

	void EngineServer::Run()
	{
		SOCKET listenSocket = CreateSocket();

		while (true)
		{
			SOCKET clientSocket = WaitForConnections(listenSocket);
		
			std::thread worker(&EngineServer::ActiveConnection, this, clientSocket);
			worker.detach();
		}
	}

	SOCKET EngineServer::CreateSocket()
	{
		SOCKET listenSocket = socket(
			AF_INET,
			SOCK_STREAM,
			IPPROTO_TCP
		);

		if (listenSocket == INVALID_SOCKET)
		{
			std::cout << "socket() failed with error: " << WSAGetLastError() << std::endl;
			WSACleanup();
			return -1;
		}

		addrinfo hints;
		addrinfo* addressInfo = NULL;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		int getaddrinfoResult = getaddrinfo(
			m_IPv4Address.c_str(),
			m_TCPPort.c_str(),
			&hints,
			&addressInfo
		);

		if (getaddrinfoResult != 0)
		{
			std::cout << "getaddrinfo() failed with error" << getaddrinfoResult << std::endl;
			closesocket(listenSocket);
			WSACleanup();
			return -1;
		}

		int bindResult = bind(
			listenSocket,
			addressInfo->ai_addr,
			(int)addressInfo->ai_addrlen
		);

		if (bindResult == SOCKET_ERROR)
		{
			std::cout << "bind() failed with error" << WSAGetLastError() << std::endl;
			freeaddrinfo(addressInfo);
			closesocket(listenSocket);
			WSACleanup();
			return -1;
		}

		freeaddrinfo(addressInfo);

		int listenResult = listen(listenSocket, SOMAXCONN);
		if (listenResult == SOCKET_ERROR)
		{
			std::cout << "listen() failed with error: " << WSAGetLastError() << std::endl;
			closesocket(listenSocket);
			WSACleanup();
			return -1;
		}

		return listenSocket;
	}

	SOCKET EngineServer::WaitForConnections(SOCKET listenSocket)
	{
		SOCKET clientSocket = accept(listenSocket, NULL, NULL);
		
		if (clientSocket == INVALID_SOCKET)
		{
			std::cout << "accept() failed with error: " << WSAGetLastError() << std::endl;
			closesocket(listenSocket);
			WSACleanup();
			return -1;
		}
		
		std::cout << "Client " << clientSocket << " connected\n" << std::endl;

		return clientSocket;
	}
}