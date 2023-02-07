#pragma once

#include <string>

#include "Message.h"
#include "FieldsTag.h"

namespace Mad {

	enum Side
	{
		BUY = 1,
		SELL
	};

	enum OrdType
	{
		MARKET = 1,
		LIMIT
	};

	class NewOrderSingle : public Message
	{
	public:
		NewOrderSingle(std::string message);

		std::string getClOrdID()		const { return m_ClOrdID; };
		std::string getSymbol()			const { return m_Symbol; };
		Side		getSide()			const { return m_Side; };
		std::string getTransactTime()	const { return m_TransactTime; };
		uint64_t	getOrderQtyData()	const { return m_OrderQtyData; };
		OrdType		getOrdType()		const { return m_OrdType; };
		uint64_t	getPrice()			const { return m_Price; };

		void setOrderQtyData(uint64_t orderQtyData) { m_OrderQtyData = orderQtyData; };

		friend std::ostream& operator<<(std::ostream& out, const NewOrderSingle& other);

	private:
		std::string m_ClOrdID;
		std::string m_Symbol;
		Side		m_Side;
		std::string m_TransactTime;
		uint64_t	m_OrderQtyData;
		OrdType		m_OrdType;
		uint64_t	m_Price;
	};

}
