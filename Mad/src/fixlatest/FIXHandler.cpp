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
		
		m_Market.AddNewOrderSingle(newOrderSingle);

		std::cout << m_Market;
	}

}
