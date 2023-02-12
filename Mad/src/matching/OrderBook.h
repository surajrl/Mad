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
			: m_Symbol(symbol), m_TotalBids(0), m_BidsSize(0), m_AsksSize(0), m_TotalAsks(0), m_Bids(nullptr), m_Asks(nullptr)
		{};

		const std::string& getSymbol() const { return m_Symbol; };
		
		const uint64_t& getTotalBidsVolume() const { return m_TotalBids; }
		const uint64_t& getTotalAsksVolume() const { return m_TotalAsks; };
		
		void AddLimitOrder(const LimitOrder& limitOrder);
		void CancelLimitOrder(const LimitOrder& limitOrder) { std::cout << limitOrder.getClOrdID() << " canceled" << std::endl; };
		void ExecuteMarketOrder(const MarketOrder& marketOrder) { /* TODO */ };

		void Print(LevelNode* root) const
		{
			if (root != NULL)
			{
				Print(root->leftLevelNode);
				std::cout << "Price: " << root->price << "\tTotal Volume: " << root->totalVolume << std::endl;
				std::cout << "Number of Orders: " << root->limitOrders.size() << std::endl;
				for (auto & order : root->limitOrders)
				{
					std::cout << order.getClOrdID() << "\t" << order.getTransactTime() << "\t" << order.getQty() << std::endl;
				}
				Print(root->rightLevelNode);
			}
		}

		friend std::ostream& operator<<(std::ostream& out, const OrderBook& other)
		{
			if (other.m_Bids != nullptr)
			{
				out << "Total Bids Volume: " << other.m_TotalBids << std::endl;
				other.Print(other.m_Bids);
			}
			
			if (other.m_Asks != nullptr)
			{
				out << "Total Asks Volume: " << other.m_TotalAsks << std::endl;
				other.Print(other.m_Asks);
			}
			
			return out;
		};

	private:
		std::string m_Symbol;

		LevelNode* m_Bids;	// Pointer to the root of the binary search tree containing the bids
		LevelNode* m_Asks;	// Pointer to the root of the binary search tree containing the asks

		uint64_t m_TotalBids;
		uint64_t m_TotalAsks;

		uint64_t m_BidsSize;	// Amount of unique price levels in bids
		uint64_t m_AsksSize;	// Amount of unique price levels in asks

		LevelNode* AddLevel(const Level& level, LevelNode* levelTree);
		LevelNode* DeleteLevel(const Level& level) { /* TODO */ };
		LevelNode* FindLevel(const uint64_t& price, LevelNode* levelTree);
		LevelNode* BestBid(LevelNode* bids);									// Returns the highest bid
		LevelNode* BestAsk(LevelNode* asks);									// Returns the lowest ask

	};
}