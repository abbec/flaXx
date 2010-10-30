#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

namespace flaXx{

class CommandLineParser
{

  public:
    CommandLineParser(int _argc, char *_argv[]):argc(_argc),
						argv(_argv){}
    tr1::shared_ptr<Options> getOptions(){ return options; }

    
		

  private:
    int argc;
    char *argv[];

    bool help;

    tr1::shared_ptr<Options> options;



};


}
