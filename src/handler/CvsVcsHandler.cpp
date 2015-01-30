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

#include "CvsVcsHandler.h"

const std::string CvsVcsHandler::DEFAULT_BRANCH = "master";

bool CvsVcsHandler::getProject () {
	std::string command;

	if(curBranch.empty()) curBranch = DEFAULT_BRANCH;

	command = "cvs -Q -d "+address+ " checkout -d "+config->getDestDir()+"/sources_project "+curBranch;
// 	std::cout << command << std::endl;
	int ret = system(command.c_str());
	assert(ret != -1);
	return (WEXITSTATUS(ret) == 0);
}

CvsVcsHandler::CvsVcsHandler ( Configuration* config, std::string address, std::string branch)  : VcsHandler(config, address, branch) {}

CvsVcsHandler::~CvsVcsHandler() {}

