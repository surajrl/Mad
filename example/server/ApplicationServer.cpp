#include "../../Mad/include/Mad.h"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>


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

	// Boost asio setup
	//std::string const host = "stream.binance.com";
	//boost::asio::io_context ioc{ 1 };
	//boost::asio::ip::tcp::resolver resolver(ioc);
	//boost::asio::ip::tcp::socket socket(ioc);

	//boost::beast::websocket::stream<boost::asio::ip::tcp::socket&> ws(socket);
	//const auto results = resolver.resolve({ host, "9443" });
	//boost::beast::net::connect(
	//	ws.next_layer(),
	//	results.begin(),
	//	results.end()
	//);

	//ws.next_layer().nect

	//// Binance websocket
	//try {
	//	ws.handshake(host, "/ws");

	//	while (true)
	//	{
	//		boost::beast::flat_buffer buffer;
	//		ws.read(buffer);

	//		auto out = boost::beast::buffers_to_string(buffer.cdata());
	//		std::cout << out << std::endl;
	//	}
	//}
	//catch (boost::beast::system_error err) {
	//	std::cout << err.what() << std::endl;
	//}

	// Receive

	

	if (server.Init())
	{
		server.Run();
	}

	return 0;
}