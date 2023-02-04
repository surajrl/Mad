#pragma once

#include "../matching/Market.h"

#include "Message.h"
#include "NewOrderSingle.h"

namespace Mad {

	class FIXHandler
	{
	public:
		FIXHandler(Market market)
			: m_Market(market)
		{};

		void ProcessMessage(std::string message);

		void ProcessBidRequest() {};
		void ProcessBidResponse() {};
		void ProcessCrossOrderCancelReplaceRequest() {};
		void ProcessCrossOrderCancelRequest() {};
		void ProcessDontKnowTrade() {};
		void ProcessExecutionAck() {};
		void ProcessExecutionReport() {};
		void ProcessListCancelRequest() {};
		void ProcessListExecute() {};
		void ProcessListStatus() {};
		void ProcessListStatusRequest() {};
		void ProcessListStrikePrice() {};
		void ProcessMassOrder() {};
		void ProcessMassOrderAck() {};
		void ProcessMultilegOrderCancelReplace() {};
		void ProcessNewOrderCross() {};
		void ProcessNewOrderList() {};
		void ProcessNewOrderMultileg() {};
		void ProcessNewOrderSingle(std::string message);
		void ProcessOrderCancelReject() {};
		void ProcessOrderCancelReplaceRequest() {};
		void ProcessOrderCancelRequest() {};
		void ProcessOrderMassActionReport() {};
		void ProcessOrderMassActionRequest() {};
		void ProcessOrderMassCancelReport() {};
		void ProcessOrderMassCancelRequest() {};	
		void ProcessOrderMassStatusRequest() {};	
		void ProcessOrderStatusRequest() {};

	private:
		Market m_Market;
	};
	
}

