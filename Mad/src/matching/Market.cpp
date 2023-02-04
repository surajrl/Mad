#include "Market.h"

namespace Mad {

	void Market::AddOrderBook(const OrderBook& orderBook)
	{
		m_OrderBooks.push_back(orderBook);
	}

	void Market::AddNewOrderSingle(const NewOrderSingle& newOrderSingle)
	{
		for (OrderBook& orderBook : m_OrderBooks)
		{
			if (orderBook.getSymbol() == newOrderSingle.getSymbol())
			{
				orderBook.AddNewOrderSingle(newOrderSingle);
			}
		}
	}

	bool Market::HasOrderBook(std::string symbol)
	{
		for (OrderBook orderBook : m_OrderBooks)
		{
			if (orderBook.getSymbol() == symbol) return true;
		}

		return false;
	}

	std::ostream& operator<<(std::ostream& out, const Market& other)
	{
		for (OrderBook orderBook : other.m_OrderBooks)
		{
			out << "**********************************************************\n";
			out << "\tOrder Book " << orderBook.getSymbol() << std::endl;
			out << "\t" << orderBook << std::endl;
			out << "**********************************************************\n";
		}

		return out;
	}

}