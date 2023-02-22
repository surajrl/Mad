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

		const std::string&	getClOrdID()		const { return m_ClOrdID; };
		const std::string&	getSymbol()			const { return m_Symbol; };
		const std::string&	getTransactTime()	const { return m_TransactTime; };
		const uint64_t&		getQty()			const { return m_Qty; };
		const Side&			getSide()			const { return m_Side; };

		void Reduce(const uint64_t qtyToReduce) const
		{
			if (qtyToReduce > m_Qty)
			{
				std::cerr << "qtyToReduce > m_Qty" << std::endl;
				return;
			}

			m_Qty -= qtyToReduce;
		};

		void Fill() const
		{
			m_Qty = 0;
			std::cout << "\t[ORDER {" + m_ClOrdID + "}]\tFILLED" << std::endl;
		};

		void PartiallyFill(const uint64_t qtyToReduce) const
		{
			if (qtyToReduce > m_Qty)
			{
				std::cerr << "qtyToReduce > m_Qty" << std::endl;
				return;
			}

			m_Qty -= qtyToReduce;
			std::cout << "\t[ORDER {" + m_ClOrdID + "}]\tPARTIALLY FILLED" << std::endl;

		}

	private:
		std::string		m_ClOrdID;
		std::string		m_Symbol;
		std::string		m_TransactTime;
		mutable uint64_t		m_Qty;
		Side			m_Side;
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
		MarketOrder(std::string clOrdID, std::string symbol, std::string transactTime, uint64_t qty, Side side)
			: Order(clOrdID, symbol, transactTime, qty, side)
		{};
		MarketOrder(const NewOrderSingle& newOrderSingle)
			: Order(newOrderSingle)
		{};
	};

}

