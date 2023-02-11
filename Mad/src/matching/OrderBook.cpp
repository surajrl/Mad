#include "OrderBook.h"

namespace Mad {

	void OrderBook::AddLimitOrder(const LimitOrder& limitOrder)
	{
		uint64_t price = limitOrder.getPrice();
		uint64_t qty = limitOrder.getQty();

		switch (limitOrder.getSide())
		{
		case Side::BUY:
		{
			if (m_Bids.find(price) == m_Bids.end())
			{
				m_Bids.emplace(price, limitOrder);
				m_BidPrices.push_back(price);
			}

			m_Bids.at(price).AddLimitOrder(limitOrder);
			m_TotalBidsVolume += qty;
			
			break;
		}
		case Side::SELL:
		{
			if (m_Asks.find(price) == m_Asks.end())
			{
				m_Asks.emplace(price, limitOrder);
				m_AskPrices.push_back(price);
			}

			m_Asks.at(price).AddLimitOrder(limitOrder);
			m_TotalAsksVolume += qty;

			break;
		}
		default:
			std::cerr << "Unknown side\n";
			break;
		}
	}

	std::ostream& operator<<(std::ostream& out, const OrderBook& other)
	{
		out <<
			"Symbol: " << other.m_Symbol << "\t" <<
			"Total Bids: " << other.m_TotalBidsVolume << "\t" <<
			"Total Asks: " << other.m_TotalAsksVolume << "\t" <<
			"\n";

		for (auto& [price, bidLevel] : other.m_Bids)
		{
			out << bidLevel;
		}

		for (auto& [price, askLevel] : other.m_Asks)
		{
			out << askLevel;
		}

		return out;
	}

}