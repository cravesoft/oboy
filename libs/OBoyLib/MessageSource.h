#pragma once

#include "Messenger.h"
#include <string>

namespace OBoyLib
{
	class MessageSource
	{
	public:

		MessageSource() {}
		virtual ~MessageSource() {}

		void sendMessage(std::string messageId, std::map<std::string,std::string> *params=NULL)
		{
			Messenger::instance()->sendMessage(messageId,this,params);
		}

	};
}
