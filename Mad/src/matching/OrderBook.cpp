#include "OrderBook.h"

namespace Mad {

	void OrderBook::AddNewOrderSingle(NewOrderSingle& newOrderSingle)
	{
		uint64_t price = newOrderSingle.getPrice();
		uint64_t qty = newOrderSingle.getOrderQtyData();

		switch (newOrderSingle.getSide())
		{
		case Side::BUY:
		{
			if (m_Asks.find(price) != m_Asks.end())
			{
				Level& askLevel = m_Asks.at(price);

				if (qty < askLevel.getTotalVolume())
				{
					askLevel.ExecuteOrder(newOrderSingle);
					break;
				}
				else if (qty == askLevel.getTotalVolume())
				{
					m_Asks.erase(price);
					break;
				}

				newOrderSingle.setOrderQtyData(qty - askLevel.getTotalVolume());
				m_Asks.erase(price);
			}

			m_Bids.emplace(price, newOrderSingle.getPrice());	// Create the price level
			m_Bids.at(price).AddNewOrderSingle(newOrderSingle);
			break;
		}
		case Side::SELL:
		{
			if (m_Bids.find(price) != m_Bids.end())
			{
				Level& bidLevel = m_Bids.at(price);

				if (qty < bidLevel.getTotalVolume())
				{
					bidLevel.ExecuteOrder(newOrderSingle);
					break;
				}
				else if (qty == bidLevel.getTotalVolume())
				{
					m_Bids.erase(price);
					break;
				}

				newOrderSingle.setOrderQtyData(qty - bidLevel.getTotalVolume());
				m_Bids.erase(price);
			}

			m_Asks.emplace(price, newOrderSingle.getPrice());
			m_Asks.at(price).AddNewOrderSingle(newOrderSingle);
			break;
		}

		default:
			std::cerr << "Unknown side\n";
			break;
		}
	}

	std::ostream& operator<<(std::ostream& out, const OrderBook& other)
	{
		out << "Bids\n";
		for (auto& [price, bidLevel] : other.m_Bids)
		{
			out << "Bid Level of Price: " << price << "\n" << bidLevel;
		}

		out << "Asks\n";;
		for (auto& [price, askLevel] : other.m_Asks)
		{
			out << "Ask Level of Price: " << price << "\n" << askLevel;
		}

		return out;
	}

}