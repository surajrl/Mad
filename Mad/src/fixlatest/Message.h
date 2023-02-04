#pragma once

#include <iostream>
#include <string>

namespace Mad {

	struct StandardHeader
	{
		std::string BeginString;			// Tag 8 - Required
		std::string BodyLength;				// Tag 9 - Required
		std::string MsgType;				// Tag 35 - Required
		std::string ApplVerID;
		std::string ApplExtID;
		std::string CstmApplVerID;
		std::string SenderCompID;			// Tag 49 - Required
		std::string TargetCompID;			// Tag 56 - Required
		std::string OnBehalfOfCompID;
		std::string DeliverToCompID;
		std::string MsgSeqNum;				// Tag 34 - Required
		std::string SenderSubID;		
		std::string SenderLocationID;
		std::string TargetSubID;
		std::string TargetLocationID;
		std::string OnBehalfOfSubID;
		std::string OnBehalfOfLocationID;
		std::string DeliverToSubID;
		std::string DeliverToLocationID;
		std::string PossDupFlag;
		std::string PossResend;
		std::string SendingTime;			// Tag 52 - Required
		std::string OrigSendingTime;
		std::string XmlDataLen;
		std::string XmlData;
		std::string MessageEncoding;
		std::string LastMsgSeqNumProcessed;
		// Component HopGrp
	};

	struct StandardTrailer
	{
		std::string CheckSum;
	};

	class Message {
	public:
		Message(std::string message);

		std::string getMessageBody() { return m_MessageBody; };

		StandardHeader getStandardHeader() const { return m_StandardHeader; };
		StandardTrailer getStandardTrailer() const { return m_StandardTrailer; };

		static int MsgTypeToInt(std::string msgType);
		std::string GetValueFromTag(uint64_t tag);
		void RemoveFieldFromTag(std::string tag);

	private:
		StandardHeader m_StandardHeader;
		std::string m_MessageBody;
		StandardTrailer m_StandardTrailer;


	};

}
