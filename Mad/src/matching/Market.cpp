#include "Market.h"

namespace Mad {

	void Market::AddOrderBook(const OrderBook& orderBook)
	{
		m_OrderBooks.emplace(orderBook.getSymbol(), orderBook);
	}

	void Market::AddLimitOrder(const LimitOrder& limitOrder)
	{
		std::string symbol = limitOrder.getSymbol();
		
		if (m_OrderBooks.find(symbol) != m_OrderBooks.end())
		{
			m_OrderBooks
				.at(symbol)
				.AddLimitOrder(limitOrder);
		}
		else
		{
			OrderBook newOrderBook(symbol);
			AddOrderBook(newOrderBook);
			m_OrderBooks
				.at(symbol)
				.AddLimitOrder(limitOrder);
		}
	}
	
	std::ostream& operator<<(std::ostream& out, const Market& other)
	{
		for (auto&[symbol, orderBook] : other.m_OrderBooks)
		{
			out << orderBook << "\n";
		}

		return out;
	}

}