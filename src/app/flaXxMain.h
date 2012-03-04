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

#ifndef FLAXX_MAIN_H
#define FLAXX_MAIN_H

// The shared pointer is in another dir
// under msvc
#ifdef _MSC_VER
	#include <memory>
#else
	#include <tr1/memory>
#endif

#include "util/commandLineParser.h"
#include "render/render.h"

namespace flaXx
{


/** The application class containing the "real"
 * main method. */
class FlaxxMain
{
  public:
	/** The main method of the program */
    int main (int argc, char *argv[]);
	
	/** Method that returns an instance of the class if it exists.
	 * Otherwise it creates one and returns that. */
    static std::tr1::shared_ptr<FlaxxMain> instance();

  private:
    /** Private singleton-constructor */
    FlaxxMain();

    CommandLineParser cmdParser;
	std::tr1::shared_ptr<Render> render;

    /// Singleton instance
    static std::tr1::shared_ptr<FlaxxMain> inst;
};

} // namespace flaXx
#endif
