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

#include "MercurialVcsHandler.h"
using namespace std;

const std::string MercurialVcsHandler::DEFAULT_BRANCH = "default";

MercurialVcsHandler::MercurialVcsHandler(Configuration *config, std::string address, std::string branch) : VcsHandler(config, address, branch) {}

bool MercurialVcsHandler::getProject () {
	std::string command;

	if(curBranch.empty()) curBranch = DEFAULT_BRANCH;
	command = "hg clone "+address+"#"+curBranch+" "+config->getDestDir()+"/sources_project";
	int ret = system(command.c_str());
	assert(ret != -1);
	return (WEXITSTATUS(ret) == 0);

}

std::vector<std::string> MercurialVcsHandler::getBranchesList() {
	std::string command = "hg -R "+config->getDestDir()+"/sources_project branches | cut -f1 -d\" \"";
	return VcsHandler::executeBranchesGetter(command);
}

MercurialVcsHandler::~MercurialVcsHandler() {

    }

