#pragma once


#include <iostream>
#include <string>

namespace Mad {

	class Order
	{
	public:
		Order(std::string clOrdID, std::string transactTime, uint64_t price, uint64_t qty)
			: m_ClOrdID(clOrdID), m_TransactTime(transactTime), m_Price(price), m_Qty(qty)
		{};

		std::string getClOrdID()		const { return m_ClOrdID; };
		std::string getTransactTime()	const { return m_TransactTime; };
		uint64_t	getPrice()			const { return m_Price; };
		uint64_t	getQty()			const { return m_Qty; };

		void RemoveQty(uint64_t qtyToRemove);

	private:
		std::string m_ClOrdID;
		std::string m_TransactTime;
		uint64_t	m_Price;
		uint64_t	m_Qty;
	};

}

