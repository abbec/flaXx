#include "app/flaXxMain.h"

using namespace flaXx;

std::tr1::shared_ptr<FlaxxMain> FlaxxMain::inst;

FlaxxMain::FlaxxMain():render(new Render())
{}

std::tr1::shared_ptr<FlaxxMain> FlaxxMain::instance()
{
    if (!inst)
        inst = std::tr1::shared_ptr<FlaxxMain>(new FlaxxMain());

    return inst;
}

int FlaxxMain::main(int argc, char *argv[])
{
    // Kolla det som kommer från kommandoraden
    cmdParser.parse(argc, argv);

    // Hämta variabler och skapa rendering
    if (!cmdParser.helpRequested())
    {
        // Skicka options till renderingen
        render->setOptions(cmdParser.getOptions());

        // Rendera scenen
        render->render();

        // Spara scenen
        render->saveToFile();
    }
    else
        cmdParser.printHelp();
}
