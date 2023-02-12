#include "OrderBook.h"

namespace Mad {

	void OrderBook::AddLimitOrder(const LimitOrder& limitOrder)
	{
		uint64_t price = limitOrder.getPrice();
		uint64_t qty = limitOrder.getQty();

		switch (limitOrder.getSide())
		{
		case Side::BUY:
		{
			// Level not found so we need to add the level to the bids
			if (FindLevel(price, m_Bids) == nullptr)
			{
				Level newLevel(price);
				AddLevel(newLevel, m_Bids);
				m_BidsSize++;
			}

			LevelNode* levelNode = FindLevel(price, m_Bids);

			levelNode->limitOrders.push_back(limitOrder);
			levelNode->totalVolume += qty;
			m_TotalBids += qty;

			break;
		}
		case Side::SELL:
		{
			// Level not found so we need to add the level to the bids
			if (FindLevel(price, m_Asks) == nullptr)
			{
				Level newLevel(price);
				AddLevel(newLevel, m_Asks);
				m_AsksSize++;
			}

			LevelNode* levelNode = FindLevel(price, m_Asks);

			levelNode->limitOrders.push_back(limitOrder);
			levelNode->totalVolume += qty;
			m_TotalAsks+= qty;

			break;
		}
		default:
			std::cerr << "Unknown side\n";
			break;
		}
	}

	LevelNode* OrderBook::AddLevel(const Level& level, LevelNode* levelTree)
	{
		if (levelTree == nullptr)
		{
			// Creates the new level node
			levelTree = new LevelNode(level);

			if (m_Bids == nullptr) /* TODO: Check if the limit is a BUY or SELL */
			{
				m_Bids = levelTree;
			}
			else
			{
				/* TODO: The new level is not the root, so assign parent */
			}
		}
		else if (level.price < levelTree->price)
			levelTree->leftLevelNode = AddLevel(level, levelTree->leftLevelNode);
		else if (level.price >= levelTree->price)
			levelTree->rightLevelNode = AddLevel(level, levelTree->rightLevelNode);

		return levelTree;
	}

	LevelNode* OrderBook::FindLevel(const uint64_t& price, LevelNode* levelNode)
	{
		if (levelNode != nullptr)
		{
			if (price == levelNode->price)
				return levelNode;
			if (price < levelNode->price)
				return FindLevel(price, levelNode->leftLevelNode);
			else if (price >= levelNode->price)
				return FindLevel(price, levelNode->rightLevelNode);
			else
				return levelNode;
		}

		return nullptr;
	}


	LevelNode* OrderBook::BestBid(LevelNode* bids)
	{
		if (bids != nullptr)
		{
			if (bids->leftLevelNode == nullptr)
				return bids;
			else
				return BestBid(bids->leftLevelNode);
		}
		
		return nullptr;
	}
	
	LevelNode* OrderBook::BestAsk(LevelNode* asks)
	{
		if (asks != nullptr)
		{
			if (asks->rightLevelNode == nullptr)
				return asks;
			else
				return BestAsk(asks->rightLevelNode);
		}

		return nullptr;
	}
}