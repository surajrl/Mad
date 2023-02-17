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

std::string FIXMessage(
	const std::string symbol,
	const Mad::Side side,
	const uint64_t qty,
	const uint64_t price
)
{
	std::time_t now = std::time(NULL);
	std::tm now_tm;
	gmtime_s(&now_tm, &now);
	char timestamp[42];
	std::strftime(timestamp, sizeof(timestamp), "%Y%m%d-%X", &now_tm);

	static int i = 0;

	std::string message = "8=FIX.4.49=14835=D34=108049=TESTBUY152=20180920-18:14:19.50856=TESTSELL111=" + std::to_string(i) + "15=USD21=238=" + std::to_string(qty) + "40=244=" + std::to_string(price) + "54=" + std::to_string(side) + "55=" + symbol + "60=" + timestamp + "10=092";
	
	i++;
	
	return message;
}

std::string FIXMessage(
	const std::string symbol,
	const Mad::OrdType ordType,
	const Mad::Side side,
	const uint64_t qty,
	const uint64_t price
)
{
	std::time_t now = std::time(NULL);
	std::tm now_tm;
	gmtime_s(&now_tm, &now);
	char timestamp[42];
	std::strftime(timestamp, sizeof(timestamp), "%Y%m%d-%X", &now_tm);
	
	std::string message;
	
	static int i = 0;
	
	if (ordType == Mad::LIMIT)
		message = "8=FIX.4.49=14835=D34=108049=TESTBUY152=20180920-18:14:19.50856=TESTSELL111=" + std::to_string(i) + "15=USD21=238=" + std::to_string(qty) + "40="+ std::to_string(ordType) +"44=" + std::to_string(price) + "54=" + std::to_string(side) + "55=" + symbol + "60=" + timestamp + "10=092";
	else if (ordType == Mad::MARKET)
		message = "8=FIX.4.49=14835=D34=108049=TESTBUY152=20180920-18:14:19.50856=TESTSELL111=" + std::to_string(i) + "15=USD21=238=" + std::to_string(qty) + "40=" + std::to_string(ordType) + "54=" + std::to_string(side) + "55=" + symbol + "60=" + timestamp + "10=092";

	i++;

	return message;
}

void ClientSocket::Run()
{
	std::string sendBuffer;

	if (CreateSocket())
	{
		//int i = 0;
		//while (i != 10)
		//{
		//	std::string symbol = "MSFT";

		//	std::random_device rd; // obtain a random number from hardware
		//	std::mt19937 gen(rd()); // seed the generator

		//	std::uniform_int_distribution<> distr(1, 2); // define the range
		//	std::string side = std::to_string(distr(gen));

		//	std::uniform_int_distribution<> distr2(1, 100); // define the range
		//	std::string price = std::to_string(distr2(gen));
		//	std::string quantity = std::to_string(distr2(gen));

		//	std::time_t now = std::time(NULL);
		//	std::tm now_tm;
		//	gmtime_s(&now_tm, &now);
		//	char timestamp[42];
		//	std::strftime(timestamp, sizeof(timestamp), "%Y%m%d-%X", &now_tm);

		//	srand((unsigned)time(NULL));
		//	std::string message = "8=FIX.4.49=14835=D34=108049=TESTBUY152=20180920-18:14:19.50856=TESTSELL111=" + std::to_string(i) + "15=USD21=238=" + quantity + "40=244=" + price + "54=" + side + "55=" + symbol + "60=" + timestamp + "10=092";
		//	Send(message);
		//	
		//	Sleep(1);

		//	i++;
		//}

		while (true)
		{
			Send(FIXMessage("MSFT", Mad::LIMIT, Mad::BUY, 1000, 50));
			Sleep(1);
			Send(FIXMessage("MSFT", Mad::MARKET, Mad::SELL, 500, NULL));

			return;
		}

		closesocket(m_ConnectSocket);
	}
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
