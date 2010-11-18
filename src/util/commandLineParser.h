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
