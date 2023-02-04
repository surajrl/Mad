#include "NewOrderSingle.h"

namespace Mad {

	NewOrderSingle::NewOrderSingle(std::string message) : Message(message)
	{
		m_ClOrdID = GetValueFromTag(FIX::ClOrdID);
		m_Symbol = GetValueFromTag(FIX::Symbol);

		m_Side = (Side)atoi(GetValueFromTag(FIX::Side).c_str());

		m_TransactTime = GetValueFromTag(FIX::TransactTime);

		// OrderQtyData could be one of 38, 152 or 516
		int orderQtyDataValues[3] = {
			FIX::OrderQty,
			FIX::CashOrderQty,
			FIX::OrderPercent
		};

		for (int i = 0; i < 3; i++)
		{
			if (GetValueFromTag(orderQtyDataValues[i]) != "")
			{
				m_OrderQtyData = atoi(GetValueFromTag(orderQtyDataValues[i]).c_str());
				break;
			}
		}

		m_OrdType = (OrdType)atoi(GetValueFromTag(FIX::OrdType).c_str());

		if (m_OrdType == OrdType::LIMIT)
		{
			m_Price = atoi(GetValueFromTag(FIX::Price).c_str());
		}
	};

	std::ostream& operator<<(std::ostream& out, const NewOrderSingle& other)
	{
		out << "ClOrdID: " << other.m_ClOrdID << "\t" << "TransactTime: " << other.m_TransactTime << "\t" << "OrderQty: " << other.m_OrderQtyData << "\t" << "Price: " << other.m_Price;

		return out;
	}
}