#include "Controller.h"

using namespace oboy;

#include "oboylib/CrtDbgNew.h"

Controller::Controller()
{
	mIsEnabled = true;
	mIsConnected = false;
}

Controller::~Controller()
{
}

void Controller::setConnected(bool connected) 
{ 
	mIsConnected = connected; 
}

bool Controller::isConnected() 
{ 
	return mIsConnected; 
}

void Controller::setEnabled(bool enabled) 
{ 
	mIsEnabled = enabled; 
}

bool Controller::isEnabled() 
{ 
	return mIsEnabled && mIsConnected; 
}
