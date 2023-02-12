#include "FIXHandler.h"

namespace Mad {

	void FIXHandler::ProcessMessage(std::string message)
	{
		Message incomingMessage(message);

		switch (Message::MsgTypeToInt(incomingMessage.getStandardHeader().MsgType))
		{
		case 0:
			ProcessBidRequest();
			break;
		case 18:
			ProcessNewOrderSingle(message);
			break;
		default:
			std::cerr << "Unknown message type" << std::endl;
		}
	}

	void FIXHandler::ProcessNewOrderSingle(std::string message)
	{
		NewOrderSingle newOrderSingle(message);
		
		switch (newOrderSingle.getOrdType())
		{
		case LIMIT:
		{
			LimitOrder limitOrder(newOrderSingle);
			m_Market.AddLimitOrder(limitOrder);
			break;
		}
		case MARKET:
		{
			// TODO
		}
		default:
			std::cerr << "Unknown order type" << std::endl;
		}

		std::cout << m_Market.getOrderBook("MSFT");
	}
}
