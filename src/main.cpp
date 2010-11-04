#include <tr1/memory>

#include "app/flaXxMain.h"

int main(int argc,  char *argv[])
{
    // Skapa instans av programmet
	std::tr1::shared_ptr<flaXx::FlaxxMain> instance(flaXx::FlaxxMain::instance());

    return instance->main(argc, argv);
}
