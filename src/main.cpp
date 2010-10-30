#include "app/flaXxMain.h"


int main(int argc,  char *argv[])
{
	// Skapa instans av programmet
	instance = flaXx::FlaxxMain::instance();

	return instance->main(argc, argv);
}
