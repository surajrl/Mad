#include "FIXHandler.h"

namespace Mad {

	void FIXHandler::ProcessMessage(std::string message)
	{
		Message incomingMessage(message);

		switch (Message::MsgTypeToInt(incomingMessage.getStandardHeader().MsgType))
		{
		case 0:
			ProcessBidRequest();
		case 18:
			ProcessNewOrderSingle(message);
		}
	}

	void FIXHandler::ProcessNewOrderSingle(std::string message)
	{
		NewOrderSingle newOrderSingle(message);

		if (m_Market.HasOrderBook(newOrderSingle.getSymbol()))
		{
			m_Market.AddNewOrderSingle(newOrderSingle);
		}
		else
		{
			OrderBook newOrderBook(newOrderSingle.getSymbol());
			newOrderBook.AddNewOrderSingle(newOrderSingle);
			m_Market.AddOrderBook(newOrderBook);
		}

		std::cout << m_Market;
	}

}
