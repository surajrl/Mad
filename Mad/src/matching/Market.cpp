#include "Market.h"

namespace Mad {

	void Market::AddOrderBook(const OrderBook& orderBook)
	{
		m_OrderBooks.emplace(orderBook.getSymbol(), orderBook);
	}

	void Market::AddLimitOrder(const LimitOrder& limitOrder)
	{
		try
		{
			OrderBook& orderBook = m_OrderBooks.at(limitOrder.getSymbol());
			orderBook.AddLimitOrder(limitOrder);
		}
		catch (std::out_of_range ex)
		{
			std::cerr << "No order book for " << limitOrder.getSymbol() << std::endl;
		}
	}

	void Market::MatchMarketOrder(const MarketOrder& marketOrder)
	{
		try
		{
			OrderBook& orderBook = m_OrderBooks.at(marketOrder.getSymbol());
			orderBook.MatchMarketOrder(marketOrder);
		}
		catch (std::out_of_range ex)
		{
			std::cerr << "No order book for " << marketOrder.getSymbol() << std::endl;
		}
	}
}