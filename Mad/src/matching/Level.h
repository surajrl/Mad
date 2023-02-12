#pragma once

#include <iostream>
#include <vector>

#include "../fixlatest/NewOrderSingle.h"

#include "Order.h"

namespace Mad {

	struct Level
	{
		Level(const uint64_t& price, const uint64_t& qty) : price(price), totalVolume(qty) {};
		
		uint64_t price;					
		uint64_t totalVolume;	
		std::vector<LimitOrder> limitOrders;
	};

	struct LevelNode : public Level
	{
		LevelNode(const Level& level) : Level(level), leftLevel(nullptr), rightLevel(nullptr) {};
		LevelNode(const uint64_t& price, const uint64_t& qty) : Level(price, qty), leftLevel(nullptr), rightLevel(nullptr) {};
		
		LevelNode* leftLevel;
		LevelNode* rightLevel;
	};
}