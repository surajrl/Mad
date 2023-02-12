#pragma once

#include <iostream>
#include <vector>

#include "../fixlatest/NewOrderSingle.h"

#include "Order.h"

namespace Mad {

	struct Level
	{
		Level(const uint64_t& price) : price(price), totalVolume(0) {};
		Level(const uint64_t& price, const uint64_t& qty) : price(price), totalVolume(qty) {};
		
		uint64_t price;
		uint64_t totalVolume;	
		std::vector<LimitOrder> limitOrders;
	};

	struct LevelNode : public Level
	{
		LevelNode(const Level& level) : Level(level), parentLevelNode(nullptr), leftLevelNode(nullptr), rightLevelNode(nullptr) {};
		LevelNode(const uint64_t& price, const uint64_t& qty) : Level(price, qty), parentLevelNode(nullptr), leftLevelNode(nullptr), rightLevelNode(nullptr) {};
		
		LevelNode* parentLevelNode;
		LevelNode* leftLevelNode;
		LevelNode* rightLevelNode;
	};
}