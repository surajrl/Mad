#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "../fixlatest/NewOrderSingle.h"

#include "Level.h"

namespace Mad {

	class OrderBook {
	public:
		OrderBook(const std::string& symbol)
			: m_Symbol(symbol)
		{};

		std::string getSymbol() const { return m_Symbol; };

		void AddNewOrderSingle(NewOrderSingle& newOrderSingle);

		friend std::ostream& operator<<(std::ostream& out, const OrderBook& other);

	private:
		std::string m_Symbol;

		std::unordered_map<uint64_t, Level> m_Bids;
		std::unordered_map<uint64_t, Level> m_Asks;
	};

}