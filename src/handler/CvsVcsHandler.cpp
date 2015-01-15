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

void CvsVcsHandler::getProject ( std::string address ) {
	std::string command = "cvs checkout -d "+ config->getDestDir()+"/sources_cvs "+address;
	this->address = address;
	scError("Not implemented");
	system(command.c_str());
}

CvsVcsHandler::CvsVcsHandler ( Configuration* config )  : VcsHandler(config) {}

std::vector<std::string>  CvsVcsHandler::getBranchesList(){
	std:: string command = "ls -l";

	scError("Not implemented");
	return VcsHandler::executeBranchesGetter(command);
}

