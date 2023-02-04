#pragma once

#include <iostream>
#include <vector>

#include "../fixlatest/NewOrderSingle.h"

namespace Mad {

	class Level {
	public:
		Level(uint64_t price)
			: m_Price(price), m_TotalVolume(0)
		{};
		
		uint64_t getPrice()			const { return m_Price; };
		uint64_t getTotalVolume()	const { return m_TotalVolume; };

		bool isEmpty() { return m_Orders.empty(); };

		void AddNewOrderSingle(const NewOrderSingle& order);

		friend std::ostream& operator<<(std::ostream& out, const Level& other);

	private:
		uint64_t m_Price;
		uint64_t m_TotalVolume;

		std::vector<NewOrderSingle> m_Orders;
	};

}