#include "OrderBook.h"

namespace Mad {

	void OrderBook::AddNewOrderSingle(const NewOrderSingle& newOrderSingle)
	{
		if (newOrderSingle.getSide() == Side::BUY)
		{
			for (Level& bid : m_Bids)
			{
				if (bid.getPrice() == newOrderSingle.getPrice())
				{
					bid.AddNewOrderSingle(newOrderSingle);
					return;
				}
			}

			Level newBidLevel(newOrderSingle.getPrice());
			newBidLevel.AddNewOrderSingle(newOrderSingle);
			m_Bids.push_back(newBidLevel);
		}
		else if (newOrderSingle.getSide() == Side::SELL)
		{
			for (Level& ask : m_Asks)
			{
				if (ask.getPrice() == newOrderSingle.getPrice())
				{
					ask.AddNewOrderSingle(newOrderSingle);
					return;
				}
			}

			Level newAskLevel(newOrderSingle.getPrice());
			newAskLevel.AddNewOrderSingle(newOrderSingle);
			m_Asks.push_back(newAskLevel);
		}
		else
		{
			std::cerr << "Unknown side, must be a bid or ask" << std::endl;
		}
	}

	std::ostream& operator<<(std::ostream& out, const OrderBook& other)
	{
		out << "\n\tBids" << std::endl;
		out << "\tTotal Volume\tPrice\n";
		for (Level bid : other.m_Bids)
		{
			out << bid;
		}

		out << "\n\tAsks" << std::endl;
		out << "\tTotal Volume\tPrice\n";
		for (Level ask : other.m_Asks)
		{
			out << ask;
		}

		return out;
	}

}