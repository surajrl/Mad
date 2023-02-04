#pragma once

#include <string>
#include <vector>

#include "../fixlatest/NewOrderSingle.h"

#include "Level.h"

namespace Mad {

	class OrderBook {
	public:
		OrderBook(std::string symbol)
			: m_Symbol(symbol)
		{};

		std::string getSymbol() const { return m_Symbol; };

		void AddNewOrderSingle(const NewOrderSingle& newOrderSingle);

		friend std::ostream& operator<<(std::ostream& out, const OrderBook& other);

	private:
		std::string m_Symbol;

		std::vector<Level> m_Bids;
		std::vector<Level> m_Asks;
	};

}