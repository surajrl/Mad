#include "pch.h"
#include "../../Mad/include/Mad.h"

struct MarketTest : testing::Test
{
	Mad::Market* myMarket;
	MarketTest() { myMarket = new Mad::Market(); };
	~MarketTest() { delete myMarket; };
};

TEST_F(MarketTest, AddLimitOrderTest) {

	std::time_t now = std::time(NULL);
	std::tm now_tm;
	gmtime_s(&now_tm, &now);
	char timestamp[42];
	std::strftime(timestamp, sizeof(timestamp), "%Y%m%d-%X", &now_tm);

	Mad::OrderBook myOrderBook("MSFT");
	Mad::LimitOrder buyLimitOrder("1", "MSFT", timestamp, 1000, Mad::BUY, 50);
	Mad::MarketOrder sellMarketOrder("2", "MSFT", timestamp, 100, Mad::SELL);
	
	myMarket->AddOrderBook(myOrderBook);
	myMarket->AddLimitOrder(buyLimitOrder);
	myMarket->MatchMarketOrder(sellMarketOrder);
}