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

#include "GitVcsHandler.h"
using namespace std;

GitVcsHandler::GitVcsHandler(Configuration *config) : VcsHandler(config) {}

void GitVcsHandler::getProject ( std::string address ) {
	std::string command = "git clone "+address+" "+config->getDestDir()+"/sources_git";
	this->address = address;
	system(command.c_str());
}

std::vector<std::string>  GitVcsHandler::getBranchesList() {
	std::string command = "git --git-dir "+config->getDestDir()+"/sources_git/.git branch --list | rev | cut -f1 -d" " | rev";
	return VcsHandler::executeBranchesGetter(command);

}
