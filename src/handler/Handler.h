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

#ifndef HANDLER_H
#define HANDLER_H

#include "../Utils.h"
#include "../Configuration.h"

/**
 * the handler catches sources project gathering. The easy way is the simple
 * directory already on file system. But SublimeCode can interact directly with
 * some version control system as Git, Svn, Mercurial... This base class defines
 * generic methods handling project fetching.
 */
class Handler
{
protected:
	Configuration *config;  /// current global configuration
	std::string address;    /// where project is located
public:
	/**
	 * default constructor
	 * \param[in] config current config
	 * \param[in] address where project is located
	 */
	Handler(Configuration *config, std::string address);
	/**
	 * fetch project from address
	 * \return True if project fetching succeeded
	 * \return False otherwise
	 */
	virtual bool getProject() = 0;
	/**
	 * fetch different revision of the project.
	 * \return string vector containing multiple project's revision.
	 */
	virtual std::vector<std::string>  getBranchesList() = 0;
	///default destructor
	virtual ~Handler();
};

#endif // HANDLER_H
