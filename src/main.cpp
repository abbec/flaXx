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


#ifdef WIN32
	#include <memory>
#else
	#include <tr1/memory>
#endif

#include "app/flaXxMain.h"

int main(int argc,  char *argv[])
{
	// Create application instance
	std::tr1::shared_ptr<flaXx::FlaxxMain> instance(flaXx::FlaxxMain::instance());

	return instance->main(argc, argv);
}
