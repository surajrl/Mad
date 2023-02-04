#include "Message.h"

namespace Mad {

	Message::Message(std::string message) : m_MessageBody(message)
	{
		m_StandardHeader.BeginString = GetValueFromTag(8);
		RemoveFieldFromTag("8");

		m_StandardHeader.BodyLength = GetValueFromTag(9);
		RemoveFieldFromTag("9");

		m_StandardHeader.MsgType = GetValueFromTag(35);
		RemoveFieldFromTag("35");

		m_StandardHeader.SenderCompID = GetValueFromTag(49);
		RemoveFieldFromTag("49");

		m_StandardHeader.TargetCompID = GetValueFromTag(56);
		RemoveFieldFromTag("56");

		m_StandardHeader.MsgSeqNum = GetValueFromTag(34);
		RemoveFieldFromTag("34");

		m_StandardHeader.SendingTime = GetValueFromTag(52);
		RemoveFieldFromTag("52");

		m_StandardTrailer.CheckSum = GetValueFromTag(10);
		RemoveFieldFromTag("10");
	};

	int Message::MsgTypeToInt(std::string msgType)
	{
		if (msgType == "k")		return 0;
		if (msgType == "l")		return 1;
		if (msgType == "t")		return 2;
		if (msgType == "u")		return 3;
		if (msgType == "Q")		return 4;
		if (msgType == "BN")	return 5;
		if (msgType == "8")		return 6;
		if (msgType == "K")		return 7;
		if (msgType == "L")		return 8;
		if (msgType == "N")		return 9;
		if (msgType == "M")		return 10;
		if (msgType == "m")		return 11;
		if (msgType == "DJ")	return 12;
		if (msgType == "DK")	return 13;
		if (msgType == "AC")	return 14;
		if (msgType == "s")		return 15;
		if (msgType == "E")		return 16;
		if (msgType == "AB")	return 17;
		if (msgType == "D")		return 18;	// NewOrderSingle
		if (msgType == "9")		return 19;
		if (msgType == "G")		return 20;
		if (msgType == "F")		return 21;
		if (msgType == "BZ")	return 22;
		if (msgType == "CA")	return 23;
		if (msgType == "r")		return 24;
		if (msgType == "q")		return 25;
		if (msgType == "AF")	return 26;
		if (msgType == "H")		return 27;

		return -1;
	}

	std::string Message::GetValueFromTag(uint64_t tag)
	{
		std::string tagString = std::to_string(tag);
		size_t idx = getMessageBody().find(tagString + "=");
		if (idx != -1)
		{
			std::string field = getMessageBody().substr(idx, getMessageBody().find('\x01', idx) - idx);
			return field.substr(field.find('=') + 1);
		}

		return "";
	}

	void Message::RemoveFieldFromTag(std::string tag)
	{
		size_t idx = m_MessageBody.find(tag + "=");
		m_MessageBody.erase(idx, (m_MessageBody.find('\x01', idx) - idx) + 1);
	}
}