#pragma once

#include <vector>

#include "OrderBook.h"

namespace Mad {

	class Market {
	public:
		Market()
			: m_OrderBooks()
		{};

		bool HasOrderBook(std::string symbol);

		void AddOrderBook(const OrderBook& orderBook);
		void AddNewOrderSingle(const NewOrderSingle& newOrderSingle);

		friend std::ostream& operator<<(std::ostream& out, const Market& other);

	private:
		std::vector<OrderBook> m_OrderBooks;
	};

}