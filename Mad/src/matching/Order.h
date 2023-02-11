#pragma once

#include <iostream>
#include <string>

#include "../fixlatest/NewOrderSingle.h"

namespace Mad {

	class Order
	{
	public:
		Order(std::string clOrdID, std::string symbol, std::string transactTime, uint64_t qty, Side side)
			: m_ClOrdID(clOrdID), m_Symbol(symbol), m_TransactTime(transactTime), m_Qty(qty), m_Side(side)
		{};

		Order(const NewOrderSingle& newOrderSingle) :
			m_ClOrdID(newOrderSingle.getClOrdID()),
			m_Symbol(newOrderSingle.getSymbol()),
			m_TransactTime(newOrderSingle.getTransactTime()),
			m_Qty(newOrderSingle.getOrderQtyData()),
			m_Side(newOrderSingle.getSide())
		{};

		std::string getClOrdID()		const { return m_ClOrdID; };
		std::string	getSymbol()			const { return m_Symbol; };
		std::string getTransactTime()	const { return m_TransactTime; };
		uint64_t	getQty()			const { return m_Qty; };
		Side		getSide()			const { return m_Side; };

		void setQty(uint64_t qty) { m_Qty = qty; };
	
	private:
		std::string m_ClOrdID;
		std::string m_Symbol;
		std::string m_TransactTime;
		uint64_t	m_Qty;
		Side		m_Side;
	};

	class LimitOrder : public Order
	{
	public:
		LimitOrder(std::string clOrdID, std::string symbol, std::string transactTime, uint64_t qty, Side side, uint64_t price)
			: Order(clOrdID, symbol, transactTime, qty, side), m_Price(price)
		{};
		
		LimitOrder(const NewOrderSingle& newOrderSingle)
			: Order(newOrderSingle), m_Price(newOrderSingle.getPrice())
		{};
		
		uint64_t getPrice() const { return m_Price; };

	private:
		uint64_t m_Price;
	};

	class MarketOrder : public Order
	{
	public:
		MarketOrder(const NewOrderSingle& newOrderSingle)
			: Order(newOrderSingle)
		{};
	};

}

