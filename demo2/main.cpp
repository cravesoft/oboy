#include "OBoy/Environment.h"
#include "Demo2.h"

int main(int argc, char* argv[])
{
	// initialize the platform:
	oboy::Environment::instance()->init(
		Demo2::instance(),
		1024, // width
		768, // height
		false, // fullscreen
		"demo2", // window title
		"demo2.dat", // persistence layer file name
		NULL); // no encryption

	// start the main loop
	oboy::Environment::instance()->startMainLoop();

	// destroy the game:
	Demo2::destroy();

	// destroy the environment:
	oboy::Environment::instance()->destroy();

	return 0;
}

