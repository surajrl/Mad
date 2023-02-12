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
			: m_Symbol(symbol), m_TotalBids(0), m_TotalAsks(0), m_Bids(nullptr), m_Asks(nullptr)
		{};

		const std::string& getSymbol() const { return m_Symbol; };
		
		const uint64_t& getTotalBidsVolume() const { return m_TotalBids; }
		const uint64_t& getTotalAsksVolume() const { return m_TotalAsks; };
		
		void AddLimitOrder(const LimitOrder& limitOrder);
		void CancelLimitOrder(const LimitOrder& limitOrder) { std::cout << limitOrder.getClOrdID() << " canceled" << std::endl; };
		void ExecuteMarketOrder(const MarketOrder& marketOrder) { /* TODO */ };

		friend std::ostream& operator<<(std::ostream& out, const OrderBook& other)
		{
			if (other.m_Bids != nullptr)
			{
				out << other.m_Bids->price << std::endl;
				out << other.m_TotalBids << std::endl;
			}
			
			if (other.m_Asks != nullptr)
			{
				out << other.m_Asks->price << std::endl;
				out << other.m_TotalAsks << std::endl;
			}
			
			return out;
		};

	private:
		std::string m_Symbol;

		LevelNode* m_Bids;	// Binary tree containing the bids the current LevelNode is the last entered node
		LevelNode* m_Asks;	// Binary tree containing the asks the current LevelNode is the last entered node

		uint64_t m_TotalBids;
		uint64_t m_TotalAsks;

		LevelNode* AddLevel(const Level& level, LevelNode* levelTree);
		LevelNode* DeleteLevel(const Level& level) { /* TODO */ };
		LevelNode* FindLevel(const uint64_t& price, LevelNode* levelTree);
		LevelNode* BestBid(LevelNode* bids);									// Returns the highest bid
		LevelNode* BestAsk(LevelNode* asks);									// Returns the lowest ask

	};
}