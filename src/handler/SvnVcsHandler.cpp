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

#include "SvnVcsHandler.h"
using namespace std;

SvnVcsHandler::SvnVcsHandler(Configuration *config) : VcsHandler(config) {}

void SvnVcsHandler::getProject ( std::string address ) {

	string workDir = config->getDestDir()+"/sources_project";
	//TODO check existing folder
	std::string command = "svn checkout "+address+"/trunk "+workDir;
	this->address = address;
	system(command.c_str());
}

std::vector<std::string>  SvnVcsHandler::getBranchesList() {
	std::string command = "svn ls "+address+"/branches";
	return VcsHandler::executeBranchesGetter(command);
}

