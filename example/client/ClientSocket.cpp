#include "ClientSocket.h"

int ClientSocket::Init()
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

int ClientSocket::CreateSocket()
{
	m_ConnectSocket = socket(
		AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP
	);

	if (m_ConnectSocket == INVALID_SOCKET)
	{
		std::cout << "socket() failed with error: " << WSAGetLastError << std::endl;
		WSACleanup();
		return -1;
	}

	addrinfo hints;
	addrinfo* addressInfo = NULL;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int getaddrinfoResult = getaddrinfo(
		m_IPv4Address.c_str(),
		m_TCPPort.c_str(),
		&hints,
		&addressInfo
	);

	if (getaddrinfoResult != 0)
	{
		std::cout << "getaddrinfo() failed with error: " << getaddrinfoResult << std::endl;
		closesocket(m_ConnectSocket);
		WSACleanup();
		return -1;
	}

	int connectResult = connect(
		m_ConnectSocket,
		addressInfo->ai_addr,
		(int)addressInfo->ai_addrlen
	);

	if (connectResult == SOCKET_ERROR)
	{
		std::cout << "connect() failed with error: " << WSAGetLastError << std::endl;
		closesocket(m_ConnectSocket);
		freeaddrinfo(addressInfo);
		WSACleanup();
		return -1;
	}

	freeaddrinfo(addressInfo);

	if (m_ConnectSocket == INVALID_SOCKET)
	{
		std::cout << "Unable to connect to server" << std::endl;
		WSACleanup();
		return -1;
	}

	return 1;
}

void ClientSocket::Run()
{
	std::string sendBuffer;

	if (CreateSocket())
	{

		while (true)
		{
			std::string symbol;
			std::string price;
			std::string quantity;
			std::string side;

			std::cout << "Enter Symbol: ";
			std::cin >> symbol;
			
			std::cout << "Enter Price: ";
			std::cin >> price;

			std::cout << "Enter Quantity: ";
			std::cin >> quantity;

			std::cout << "Enter 1 for BUY or 2 for SELL: ";
			std::cin >> side;

			std::cout << "\n";

			std::time_t now = std::time(NULL);
			std::tm now_tm;
			gmtime_s(&now_tm, &now);
			char timestamp[42];
			std::strftime(timestamp, sizeof(timestamp), "%Y%m%d-%X", &now_tm);

			std::string message = "8=FIX.4.49=14835=D34=108049=TESTBUY152=20180920-18:14:19.50856=TESTSELL111=63673064027889863415=USD21=238=" + quantity + "40=244=" + price + "54=" + side + "55=" + symbol + "60=" + timestamp + "10=092";

			Send(message);
		}
	}
	
	closesocket(m_ConnectSocket);
}


void ClientSocket::Send(std::string message)
{
	int sendResult = send(m_ConnectSocket, message.c_str(), (int)message.size(), 0);
	if (sendResult == SOCKET_ERROR)
	{
		std::cout << "send() failed with error: " << WSAGetLastError() << std::endl;
		closesocket(m_ConnectSocket);
		WSACleanup();
	}
}

void ClientSocket::Receive()
{
	char recvBuffer[BUFFER_LEN];
	int recvBytes;

	ZeroMemory(recvBuffer, BUFFER_LEN);
	recvBytes = recv(m_ConnectSocket, recvBuffer, BUFFER_LEN, 0);

	if (recvBytes > 0)
	{
		std::cout << "SERVER> " << std::string(recvBuffer, 0, recvBytes) << std::endl;
	}
	else
	{
		std::cout << "recv() failed with error: " << WSAGetLastError() << std::endl;
	}
}
