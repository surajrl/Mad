#include "ClientSocket.h"

int main(int argc, char argv[])
{
	ClientSocket client("127.0.0.1", "3500");

	if (client.Init())
	{
		client.Run();
	}

	return 0;
}