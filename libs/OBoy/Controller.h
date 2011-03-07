#pragma once

#include "OBoyLib/Vector2.h"

namespace OBoy
{
	class Controller
	{
	public:

		Controller();
		virtual ~Controller();

		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();

		virtual void setConnected(bool connected);
		virtual bool isConnected();

	private:

		bool mIsEnabled;
		bool mIsConnected;

	};
}

