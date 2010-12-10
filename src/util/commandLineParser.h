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

#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include <tr1/memory>

#include "util/options.h"

namespace flaXx {

class CommandLineParser
{

  public:
    CommandLineParser(): help(false), options(new Options()) {}

	std::tr1::shared_ptr<Options> getOptions() { return options; }

    void parse(int argc, char *argv[]);

    bool helpRequested() { return help; }

    void printHelp();


  private:

    bool help;

	std::tr1::shared_ptr<Options> options;

};


}
#endif
