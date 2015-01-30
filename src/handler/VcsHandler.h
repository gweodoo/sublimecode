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
#ifndef VCSHANDLER_H
#define VCSHANDLER_H

#include "Handler.h"

/**
 * Abstract class which add some specific information about version control systems specifications
 */
class VcsHandler : public Handler
{
protected:
	std::string curBranch; ///< vcs specific attribute : branch to checkout
public:
	/**
	 * default constructor for a version control system project
	 * \param[in] config the current configuration
	 * \param[in] address the address where checking out the project
	 * \param[in] branch a specific branch to checkout (default : DEFAULT_BRANCH}
	 */
	VcsHandler(Configuration *config, std::string address, std::string branch);
	virtual bool getProject() = 0;
	virtual ~VcsHandler();
};

#endif // VCSHANDLER_H
