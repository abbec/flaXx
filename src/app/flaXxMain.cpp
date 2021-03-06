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
    // Parse command line arguments
    cmdParser.parse(argc, argv);

    // Fetch variables and create a render
    if (!cmdParser.helpRequested())
    {
        // Send options to the render
        render->setOptions(cmdParser.getOptions());

        // Render scene
        render->render();

        // Save render to file
        render->saveToFile();
    }
    else // If no or wrong arguments
        cmdParser.printHelp();

	return 0;
}
