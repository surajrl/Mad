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
			: m_Symbol(symbol), m_TotalBidsVolume(0), m_BidsSize(0), m_AsksSize(0), m_TotalAsksVolume(0), m_Bids(nullptr), m_Asks(nullptr), m_BestBid(nullptr), m_BestAsk(nullptr)
		{};
		
		~OrderBook()
		{
			delete m_Bids, m_Asks, m_BestBid, m_BestAsk;
		}

		const std::string& getSymbol() const { return m_Symbol; };
		
		const uint64_t& getTotalBidsVolume() const { return m_TotalBidsVolume; }
		const uint64_t& getTotalAsksVolume() const { return m_TotalAsksVolume; };
		
		void AddLimitOrder(const LimitOrder& limitOrder);
		void CancelLimitOrder(const LimitOrder& limitOrder) { std::cout << limitOrder.getClOrdID() << " canceled" << std::endl; };
		void MatchMarketOrder(const MarketOrder& marketOrder);

	private:
		std::string m_Symbol;

		LevelNode* m_Bids;	// Pointer to the root of the binary search tree containing the bids
		LevelNode* m_Asks;	// Pointer to the root of the binary search tree containing the asks

		LevelNode* m_BestBid;	// Pointer to the level node with the highest bid
		LevelNode* m_BestAsk;	// Pointer to the level node with the lowest ask

		uint64_t m_TotalBidsVolume;
		uint64_t m_TotalAsksVolume;

		uint64_t m_BidsSize;	// Amount of unique price levels in bids
		uint64_t m_AsksSize;	// Amount of unique price levels in asks

		LevelNode* AddLevel(const Level& level, LevelNode* currLevel, LevelNode* prevLevel);
		LevelNode* DeleteLevel(const Level& level) { /* TODO */ };
		LevelNode* FindLevel(const uint64_t& price, LevelNode* levelTree);

		LevelNode* UpdateBestBid(LevelNode* bids); // Returns the highest bid
		LevelNode* UpdateBestAsk(LevelNode* asks); // Returns the lowest ask
	};
}