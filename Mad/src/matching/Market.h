#pragma once

#include <unordered_map>

#include "OrderBook.h"

namespace Mad {

	class Market {
	public:
		Market() {};

		void AddOrderBook(const OrderBook& orderBook);

		void AddLimitOrder(const LimitOrder& limitOrder);

		const OrderBook& getOrderBook(const std::string& symbol) { return m_OrderBooks.at(symbol); };

	private:
		std::unordered_map<std::string, OrderBook> m_OrderBooks;
	
	};

}