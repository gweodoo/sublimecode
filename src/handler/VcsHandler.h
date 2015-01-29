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

class VcsHandler : public Handler
{
protected:
	std::vector<std::string> branchlist;
	std::string curBranch;
public:
	VcsHandler(Configuration *config, std::string address, std::string branch);
	virtual bool getProject() = 0;
	virtual std::vector<std::string>  getBranchesList() = 0;
	std::vector< std::string > executeBranchesGetter(std::string command);
	virtual ~VcsHandler();
};

#endif // VCSHANDLER_H
