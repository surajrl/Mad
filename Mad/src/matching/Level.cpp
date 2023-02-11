#include "Level.h"

namespace Mad {

	void Level::AddLimitOrder(const LimitOrder& limitOrder) const
	{
		m_LimitOrders.emplace_back(limitOrder);
		m_TotalVolume += limitOrder.getQty();
	};

	std::ostream& operator<<(std::ostream& out, const Level& other)
	{
		out <<
			"Price Level: " << other.m_Price << "\t" <<
			"Total Volume: " << other.m_TotalVolume << "\t" <<
			"\n";

		if (other.m_LimitOrders.size() != 0)
			out << "ClOrdID" << "\t\t\t" << "TransactTime" << "\t\t" << "Qty" << "\t" << "Price" << "\n";
		for (auto& limitOrder : other.m_LimitOrders)
		{
			out << limitOrder.getClOrdID() << "\t" << limitOrder.getTransactTime() << "\t" << limitOrder.getQty() << "\t" << limitOrder.getPrice() << "\n";
		}

		return out;
	}

}