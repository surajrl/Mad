#include "../../Mad/include/Mad.h"

void MessageReceived(Mad::EngineServer* listenSocket, SOCKET clientSocket, std::string message)
{
	std::cout << "\nCLIENT " << clientSocket << "> " << message << "\n" << std::endl;

	listenSocket->getFIXHandler().ProcessMessage(message);

	int sendResult = send(clientSocket, message.c_str(), (int)message.size() + 1, 0);
	if (sendResult == SOCKET_ERROR)
	{
		std::cout << "send() failed with error: " << WSAGetLastError() << std::endl;
		closesocket(clientSocket);
		WSACleanup();
	}
};


int main(int argc, char* argv[])
{
	Mad::Market market;
	Mad::FIXHandler fixHandler(market);
	Mad::EngineServer server("127.0.0.1", "3500", MessageReceived, fixHandler);

	if (server.Init())
	{
		server.Run();
	}

	return 0;
}