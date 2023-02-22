#include "OrderBook.h"

namespace Mad {

	void OrderBook::AddLimitOrder(const LimitOrder& limitOrder)
	{
		uint64_t price = limitOrder.getPrice();
		uint64_t qty = limitOrder.getQty();

		switch (limitOrder.getSide())
		{
		case BUY:
		{
			if (FindLevel(price, m_Bids) == nullptr)
			{
				Level newLevel(BUY, price);
				AddLevel(newLevel, m_Bids, nullptr);
				m_BidsSize++;
			}

			LevelNode* levelNode = FindLevel(price, m_Bids);

			levelNode->limitOrders.push_back(limitOrder);
			levelNode->totalVolume += qty;
			m_TotalBidsVolume += qty;

			std::cout << "\t[ORDER {" + limitOrder.getClOrdID() + "}]\tADDED\t" << limitOrder.getSymbol() << " LIMIT " << "BID " << qty << " @ " << price << std::endl;

			break;
		}
		case SELL:
		{
			if (FindLevel(price, m_Asks) == nullptr)
			{
				Level newLevel(SELL, price);
				AddLevel(newLevel, m_Asks, nullptr);
				m_AsksSize++;
			}

			LevelNode* levelNode = FindLevel(price, m_Asks);

			levelNode->limitOrders.push_back(limitOrder);
			levelNode->totalVolume += qty;
			m_TotalAsksVolume+= qty;

			std::cout << "\t[ORDER {" + limitOrder.getClOrdID() + "} ]\tADDED\t" << limitOrder.getSymbol() << " LIMIT " << " ASK " << qty << " @ " << price << std::endl;

			break;
		}
		default:
			std::cerr << "Unknown side\n";
			break;
		}
	}

	void OrderBook::MatchMarketOrder(const MarketOrder& marketOrder)
	{
		uint64_t qty = marketOrder.getQty();

		switch (marketOrder.getSide())
		{
		case BUY:
		{
			if (m_BestAsk == nullptr)
			{
				std::cout << "\t[ MARKET ORDER{" + marketOrder.getClOrdID()+ "}]\tNOT FILLED" << std::endl;
				return;
			}

			while (!m_BestAsk->FillMarketOrder(marketOrder))
				m_BestAsk = UpdateBestAsk(m_Asks);

			m_TotalAsksVolume -= qty;

			break;
		}
		case SELL:
		{
			if (m_BestBid == nullptr)
			{
				std::cout << "\t[ MARKET ORDER {" + marketOrder.getClOrdID() + "} ]\tNOT FILLED" << std::endl;
				return;
			}

			while (!m_BestBid->FillMarketOrder(marketOrder))
				m_BestBid = UpdateBestBid(m_Bids);

			m_TotalBidsVolume -= qty;


			break;
		}
		default:
			break;
		}
	}

	LevelNode* OrderBook::AddLevel(const Level& level, LevelNode* currLevelNode, LevelNode* prevLevelNode)
	{
		if (currLevelNode == nullptr)
		{
			currLevelNode = new LevelNode(level);

			if (level.side == Side::BUY && m_Bids == nullptr)
			{
				m_Bids = currLevelNode;
			}
			else if (level.side == Side::SELL && m_Asks == nullptr)
			{
				m_Asks = currLevelNode;
			}
			else
			{
				currLevelNode->parentLevelNode = prevLevelNode;
			}
		}
		else if (level.price < currLevelNode->price)
			currLevelNode->leftLevelNode = AddLevel(level, currLevelNode->leftLevelNode, currLevelNode);
		else if (level.price >= currLevelNode->price)
			currLevelNode->rightLevelNode = AddLevel(level, currLevelNode->rightLevelNode, currLevelNode);

		/* Update best bid or best ask */
		if (level.side == Side::BUY)
		{
			if (m_BestBid == nullptr) m_BestBid = currLevelNode;
			else if (m_BestBid->price < level.price) m_BestBid = currLevelNode;
		}
		else if (level.side == Side::SELL)
		{
			if (m_BestAsk == nullptr) m_BestAsk = currLevelNode;
			else if (m_BestAsk->price > level.price) m_BestAsk = currLevelNode;
		}

		return currLevelNode;
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


	LevelNode* OrderBook::UpdateBestBid(LevelNode* bids)
	{
		if (bids != nullptr)
		{
			if (bids->rightLevelNode == nullptr)
				return bids;
			else
				return UpdateBestBid(bids->rightLevelNode);
		}
		
		return nullptr;
	}
	
	LevelNode* OrderBook::UpdateBestAsk(LevelNode* asks)
	{
		if (asks != nullptr)
		{
			if (asks->leftLevelNode== nullptr)
				return asks;
			else
				return UpdateBestAsk(asks->leftLevelNode);
		}

		return nullptr;
	}
}