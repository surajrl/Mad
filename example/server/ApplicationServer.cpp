#include "../../Mad/include/Mad.h"

void MessageReceived(Mad::EngineServer* listenSocket, SOCKET clientSocket, std::string message)
{
	listenSocket->getFIXHandler().ProcessMessage(message);
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
}