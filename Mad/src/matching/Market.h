#pragma once

#include <unordered_map>

#include "OrderBook.h"

namespace Mad {

	class Market {
	public:
		Market()
			: m_OrderBooks()
		{};

		void AddNewOrderSingle(NewOrderSingle& newOrderSingle);

		friend std::ostream& operator<<(std::ostream& out, const Market& other);

	private:
		std::unordered_map<std::string, OrderBook> m_OrderBooks;
	
		OrderBook& AddOrderBook(const OrderBook& orderBook);
	};

}