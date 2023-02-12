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
			LevelNode* levelNode = FindLevel(price, m_Bids);

			if (levelNode == nullptr)
			{
				Level newLevel(price, qty);
				m_Bids = AddLevel(newLevel, m_Bids);
				
				m_Bids->limitOrders.push_back(limitOrder);
				m_TotalBids += qty;
			}
			else
			{
				levelNode->limitOrders.push_back(limitOrder);
				m_TotalBids += qty;
			}

			break;
		}
		case Side::SELL:
		{
			LevelNode* levelNode = FindLevel(price, m_Asks);
			if (levelNode == nullptr)
			{
				Level newLevel(price, qty);
				m_Asks = AddLevel(newLevel, m_Asks);

				m_Asks->limitOrders.push_back(limitOrder);
				m_TotalAsks += qty;
			}
			else
			{
				levelNode->limitOrders.push_back(limitOrder);
				m_TotalAsks += qty;
			}

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
			levelTree = new LevelNode(level);
			return levelTree;
		}
		else
		{
			if (level.price < levelTree->price)
				levelTree = AddLevel(level, levelTree->leftLevel);
			else if (level.price >= levelTree->price)
				levelTree = AddLevel(level, levelTree->rightLevel);

			return levelTree;
		}
	}

	LevelNode* OrderBook::FindLevel(const uint64_t& price, LevelNode* levelTree)
	{
		if (levelTree != nullptr)
		{
			if (price < levelTree->price)
				return FindLevel(price, levelTree->leftLevel);
			else if (price >= levelTree->price)
				return FindLevel(price, levelTree->rightLevel);
			else
				return levelTree;
		}

		return nullptr;
	}


	LevelNode* OrderBook::BestBid(LevelNode* bids)
	{
		if (bids != nullptr)
		{
			if (bids->leftLevel == nullptr)
				return bids;
			else
				return BestBid(bids->leftLevel);
		}
		
		return nullptr;
	}
	
	LevelNode* OrderBook::BestAsk(LevelNode* asks)
	{
		if (asks != nullptr)
		{
			if (asks->rightLevel == nullptr)
				return asks;
			else
				return BestAsk(asks->rightLevel);
		}

		return nullptr;
	}
}