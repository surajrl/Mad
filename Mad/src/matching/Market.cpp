#include "Market.h"

namespace Mad {

	OrderBook& Market::AddOrderBook(const OrderBook& orderBook)
	{
		m_OrderBooks.emplace(orderBook.getSymbol(), orderBook);
		return m_OrderBooks.at(orderBook.getSymbol());
	}

	void Market::AddNewOrderSingle(NewOrderSingle& newOrderSingle)
	{
		if (m_OrderBooks.find(newOrderSingle.getSymbol()) != m_OrderBooks.end())	// OrderBook already exists for that symbol
		{
			m_OrderBooks
				.at(newOrderSingle.getSymbol())
				.AddNewOrderSingle(newOrderSingle);
		}
		else
		{
			OrderBook& newOrderBook = AddOrderBook({ newOrderSingle.getSymbol() });	// OrderBook for that symbol needs to be created and added to the market
			newOrderBook.AddNewOrderSingle(newOrderSingle);
		}
	}

	std::ostream& operator<<(std::ostream& out, const Market& other)
	{
		for (auto&[symbol, orderBook] : other.m_OrderBooks)
		{
			out << "Order Book: " << orderBook.getSymbol() << "\n";
			out << orderBook << "\n";
		}

		return out;
	}

}