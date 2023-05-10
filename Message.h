#pragma once
#include "User.h"

class Message
{
public:
	Message(const std::string& sender, const std::string& recipient, const std::string& text) : _sender(sender), _recipient(recipient), _text(text) {}
	const std::string& GetSender() const {return _sender;}
	const std::string& GetRecipient() const {return _recipient;}
	const std::string& GetText() const {return _text;}

private:
	std::string _sender;
	std::string _recipient;
	std::string _text;
};