#include <iostream>
#include "commandLineParser.h"

using namespace flaXx;

void CommandLineParser::parse(int argc, char *argv[])
{
    if (argc < 2)
		help = true;
	else
	{
		// Sätt namn för utfilen
		options->setOutFileName(argv[1]);

	}
}


void CommandLineParser::printHelp()
{
    std::cout << "flaXx is a Monte Carlo Ray Tracer.\n\n"
              << "Usage: \n"
              << "\t flaXx [infile] outfile [width] [height] [options]"
              << "\t Example: flaXx result.png 1280 1024" << std::endl;


}
