#include "OBoy/Environment.h"
#include "Demo1.h"

int main(int argc, char* argv[])
{
	// initialize the platform:
	OBoy::Environment::instance()->init(
		Demo1::instance(),
		600, // width
		600, // height
		false, // fullscreen
		"demo1", // window title
		"demo1.dat", // persistence layer file name
		NULL); // no encryption

	// start the main loop
	OBoy::Environment::instance()->startMainLoop();

	// destroy the game:
	Demo1::destroy();

	// destroy the environment:
	OBoy::Environment::instance()->destroy();

	return 0;
}

