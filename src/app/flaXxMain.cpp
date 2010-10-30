#include "app/flaXxMain.h"

using namespace flaXx;

tr1::shared_ptr<FlaxxMain> instance = NULL;

FlaxxMain::FlaxxMain()
{}

tr1::shared_ptr<FlaxxMain> FlaxxMain::instance()
{
	if (instance == NULL)
		instance = new FlaxxMain();

    return instance;
}

FlaxxMain::main(int argc, char *argv[])
{
    // Kolla det som kommer från kommandoraden
    cmdParser.parse(argc, argv)

		// Hämta variabler och skapa rendering
		if (!cmdParser.help())
		{
			if (cmdParser.inFileSpecified())
				render = new Render(cmdParser.getInFile(),
									cmdParser.getOutFile());
			else
				render = new Render(cmdParser.getOutFile());
		}

    // TODO: Skicka options till renderingen
    render->setOptions(cmdParser.getOptions());

    // Rendera scenen
    render->render();

    // Spara scenen
    render->saveToFile();

}

