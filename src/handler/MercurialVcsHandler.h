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

#ifndef MERCURIALVCSHANDLER_H
#define MERCURIALVCSHANDLER_H

#include "VcsHandler.h"

/**
 * Implements the version control system with Mercurial specification
 */
class MercurialVcsHandler : public VcsHandler
{
private:
	static const std::string DEFAULT_BRANCH; ///< default branch name for this vcs
public:
	/**
	 * default constructor for a Mercurial project
	 * \param[in] config the current configuration
	 * \param[in] address the address where checking out the project
	 * \param[in] branch a specific branch to checkout (default : DEFAULT_BRANCH}
	 */
	MercurialVcsHandler( Configuration* config, std::string address, std::string branch);
	virtual bool getProject ();
	virtual ~MercurialVcsHandler();
};

#endif // MERCURIALVCSHANDLER_H
