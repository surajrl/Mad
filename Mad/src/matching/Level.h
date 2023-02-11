#pragma once

#include <iostream>
#include <vector>

#include "../fixlatest/NewOrderSingle.h"

#include "Order.h"

namespace Mad {

	struct Level {
		Level(const LimitOrder& limitOrder) : m_Price(limitOrder.getPrice()), m_TotalVolume(0) {};
		
		uint64_t getPrice()			const { return m_Price; };
		uint64_t getTotalVolume()	const { return m_TotalVolume; };

		bool isEmpty() { return m_LimitOrders.empty(); };

		void AddLimitOrder(const LimitOrder& limitOrder) const;

		friend std::ostream& operator<<(std::ostream& out, const Level& other);

		uint64_t m_Price;								// Price of the level
		mutable uint64_t m_TotalVolume;					// Total amount of orders in the price level
		mutable std::vector<LimitOrder> m_LimitOrders;	// All the orders in this level
	};

}