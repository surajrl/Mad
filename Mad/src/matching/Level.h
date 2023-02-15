#pragma once

#include <iostream>
#include <vector>

#include "../fixlatest/NewOrderSingle.h"

#include "Order.h"

namespace Mad {

	struct Level
	{
		Level(const Side& side, const uint64_t& price) : side(side), price(price), totalVolume(0) {};
		Level(const Side& side, const uint64_t& price, const uint64_t& qty) : side(side), price(price), totalVolume(qty) {};
		
		uint64_t price;
		uint64_t totalVolume;
		std::vector<LimitOrder> limitOrders;
		Side side;
	};

	struct LevelNode : public Level
	{
		LevelNode(const Level& level) : Level(level), parentLevelNode(nullptr), leftLevelNode(nullptr), rightLevelNode(nullptr) {};
		LevelNode(const Side& side, const uint64_t& price, const uint64_t& qty) : Level(side, price, qty), parentLevelNode(nullptr), leftLevelNode(nullptr), rightLevelNode(nullptr) {};
		
		LevelNode* parentLevelNode;
		LevelNode* leftLevelNode;
		LevelNode* rightLevelNode;
	};
}