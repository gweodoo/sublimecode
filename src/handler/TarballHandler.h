/***************************************************************************/
/*                                                                         */
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
#ifndef TARBALLHANDLER_H
#define TARBALLHANDLER_H

#include "Handler.h"

/**
 * Abstract class which add specific informations about project fetching with
 * tarball extraction tools
 */
class TarballHandler :  public Handler
{
protected:
	std::string executable; ///< path to executable for this tarball extractor
public:
	/**
	 * default constructor for a tarball extraction project
	 * \param[in] config the current configuration
	 * \param[in] address the address where checking out the project
	 */
	TarballHandler ( Configuration* config, std::string address );
	virtual bool getProject() = 0;
	virtual ~TarballHandler();
};

#endif // TARBALLHANDLER_H
