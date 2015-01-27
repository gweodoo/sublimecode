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

#include "VcsHandler.h"
using namespace std;

VcsHandler::VcsHandler(Configuration *config, std::string address, std::string branch) : Handler(config, address), curBranch(branch) {}

std::vector< std::string > VcsHandler::executeBranchesGetter(std::string command) {
	FILE * outputFile = popen(command.c_str(), "r");
	string output = "", cur ="";
	char buf[250];
	while(fgets(buf, 250, outputFile) != NULL)
		output += buf;

	stringstream flux(output);

	while(getline(flux, cur, '\n')){
		branchlist.push_back(cur);
	}
	return branchlist;
}

VcsHandler::~VcsHandler() {

    }


