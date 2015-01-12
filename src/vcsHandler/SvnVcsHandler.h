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

#ifndef SVNVCSHANDLER_H
#define SVNVCSHANDLER_H

#include "VcsHandler.h"

class SvnVcsHandler :  VcsHandler
{
public:
	SvnVcsHandler ( Configuration* config );
	virtual void checkoutBranch ( std::string branch );
	virtual void downloadFromAddress ( std::string address );
	virtual std::string getLastRevision() const;
	virtual std::vector<std::string>  getBranchesList();
};

#endif // SVNVCSHANDLER_H
