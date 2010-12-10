/*
 * flaXx
 * Copyright (C) Albert Cervin <albert@nat0.se>, Nathalie Ek <nathalie@nat0.se> 2010
 * 
 * flaXx is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * flaXx is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include "commandLineParser.h"

using namespace flaXx;

void CommandLineParser::parse(int argc, char *argv[])
{
    if (argc < 2)
		help = true;
	else
	{
		// Set filename for outfile TODO: Proper command line parsing
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
