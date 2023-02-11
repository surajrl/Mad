#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

#include "../fixlatest/NewOrderSingle.h"

#include "Level.h"

namespace Mad {

	class OrderBook {
	public:
		OrderBook(const std::string& symbol)
			: m_Symbol(symbol), m_TotalBidsVolume(0), m_TotalAsksVolume(0)
		{};

		const std::string& getSymbol() const { return m_Symbol; };
		
		const uint64_t& getTotalBidsVolume() const { return m_TotalBidsVolume; }
		const uint64_t& getTotalAsksVolume() const { return m_TotalAsksVolume; };
		
		const Level& getBidLevel(const uint64_t priceLevel)	const { return m_Bids.at(priceLevel); };
		const Level& getaAskLevel(const uint64_t priceLevel) const { return m_Asks.at(priceLevel); };

		const Level& BestBid() const { return m_Bids.at(*std::max_element(m_BidPrices.begin(), m_BidPrices.end())); }
		const Level& BestAsk() const { return m_Asks.at(*std::min_element(m_AskPrices.begin(), m_AskPrices.end())); }

		void AddLimitOrder(const LimitOrder& limitOrder);
		void CancleLimitOrder(const LimitOrder& limitOrder) { std::cout << limitOrder.getClOrdID() << " canceled" << std::endl; };
		void ExecuteMarketOrder(const MarketOrder& marketOrder);

		friend std::ostream& operator<<(std::ostream& out, const OrderBook& other);

	private:
		std::string m_Symbol;

		std::unordered_map<uint64_t, Level> m_Bids;
		std::unordered_map<uint64_t, Level> m_Asks;

		std::vector<uint64_t> m_BidPrices;
		std::vector<uint64_t> m_AskPrices;

		uint64_t m_TotalBidsVolume;
		uint64_t m_TotalAsksVolume;
	};
}