#include "Order.h"

namespace Mad {

	void Order::RemoveQty(uint64_t qtyToRemove)
	{
		m_Qty -= qtyToRemove;
	}

}