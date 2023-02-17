#include "Market.h"

namespace Mad {

	void Market::AddOrderBook(const OrderBook& orderBook)
	{
		m_OrderBooks.emplace(orderBook.getSymbol(), orderBook);
	}

	void Market::AddLimitOrder(const LimitOrder& limitOrder)
	{
		const std::string symbol = limitOrder.getSymbol();
		
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

	void Market::MatchMarketOrder(const MarketOrder& marketOrder)
	{
		const std::string symbol = marketOrder.getSymbol();
	
		if (m_OrderBooks.find(symbol) != m_OrderBooks.end())
		{
			m_OrderBooks
				.at(symbol)
				.MatchMarketOrder(marketOrder);
		}
		else
		{
			// Send pending filled status ??
			// Send not filled status ??
			std::cerr << "No books for " << symbol << std::endl;
		}
	}
}