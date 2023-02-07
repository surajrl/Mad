#include "Level.h"

namespace Mad {

	void Level::AddNewOrderSingle(const NewOrderSingle& order)
	{
		m_Orders.emplace_back(order.getClOrdID(), order.getTransactTime(), order.getPrice(), order.getOrderQtyData());
		m_TotalVolume += order.getOrderQtyData();
	};

	void Level::ExecuteOrder(const NewOrderSingle& newOrderSingle)
	{
		uint64_t qty = newOrderSingle.getOrderQtyData();
		auto it = m_Orders.begin();
		
		do 
		{
			if (qty > (*it).getQty())
			{
				qty -= (*it).getQty();
				it = m_Orders.erase(it);
			}
			else if (qty == (*it).getQty())
			{
				it = m_Orders.erase(it);
				break;
			}
			else
			{
				(*it).RemoveQty(qty);
				break;
			}
		} while (it != m_Orders.begin());

		m_TotalVolume -= newOrderSingle.getOrderQtyData();
	}

	std::ostream& operator<<(std::ostream& out, const Level& other)
	{
		out << "Total Volume: " << other.m_TotalVolume << "\tPrice: " << other.m_Price << std::endl;
		
		for (auto& order : other.m_Orders)
		{
			out << order.getClOrdID() << "\t" << order.getPrice() << "\t" << order.getQty() << "\t" << order.getTransactTime() << "\n";
		}

		return out;
	}

}