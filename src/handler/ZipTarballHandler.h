/***************************************************************************/
/*                                                                        */
/* This file is part of Sublime Code.                                      */
/*                                                                         */
/* Sublime Code is free software: you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by    */
/* the Free Software Foundation, either version 3 of the License, or       */
/* (at your option) any later version.                                     */
/*                                                                         */
/* Sublime Code is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/* GNU General Public License for more details.                            */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with Sublime Code.  If not, see <http://www.gnu.org/licenses/>.   */
/*                                                                         */
/***************************************************************************/


#ifndef ZIPTARBALLHANDLER_H
#define ZIPTARBALLHANDLER_H

#include "TarballHandler.h"

/**
 * implements TarballHandler for zip tarball extraction tool
 */
class ZipTarballHandler :  public TarballHandler
{
public:
	/**
	 * default constructor for a ZIP tarball extraction project
	 * \param[in] config the current configuration
	 * \param[in] address the address where checking out the project
	 */
	ZipTarballHandler(Configuration *config, std::string address);
	bool getProject();
	virtual ~ZipTarballHandler();
};

#endif // ZIPTARBALLHANDLER_H
