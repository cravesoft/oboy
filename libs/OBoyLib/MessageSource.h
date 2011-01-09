#pragma once

#include "Messenger.h"
#include <string>

namespace oboylib
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
