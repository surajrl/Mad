#include "Level.h"

namespace Mad {

	void Level::AddNewOrderSingle(const NewOrderSingle& order)
	{
		m_Orders.push_back(order);
		m_TotalVolume += order.getOrderQtyData();
	};

	std::ostream& operator<<(std::ostream& out, const Level& other)
	{
		out << "\t" << other.m_TotalVolume << "\t\t" << other.m_Price << std::endl;

		return out;
	}

}