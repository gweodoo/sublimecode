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


#include "LauncherCTags.h"
using namespace std;

const std::string LauncherCTags::DEF_EXEC = "ctags";
const std::string LauncherCTags::GLOBAL_OPTIONS = "-Rn --c-kinds=+cdefgmnstuvx";

LauncherCTags::LauncherCTags (Configuration *config, std::vector<std::string> listPaths, string exe, string opts ) {
	this->pathExecutable = exe;
	this->listPaths = listPaths;
	this->config = config;
	if(opts != GLOBAL_OPTIONS)
		this->options = opts;

}

bool LauncherCTags::generateTagsFile() {
	std::string command = "", chainStr = "";
	int chainSize = 0;
	size_t i = 0;
	int ret;

	while(i < listPaths.size()){
		chainStr = "";
		chainSize = 0;
		while(chainSize < 100000 && i < listPaths.size()){
			chainStr += listPaths.at(i) + " ";
			chainSize +=listPaths.at(i).size();
			i++;
		}
		command = pathExecutable + options + " -a " + GLOBAL_OPTIONS + " -f " + config->getDestDir() + "/tags " + chainStr;
		ret = system(command.c_str());
		assert(ret != -1);
	}
	UNUSED(ret);
	return true;

}

void LauncherCTags::display() const {
	cout << "LAUNCHER CTAGS ------>" << endl
	<< "Executable : " << pathExecutable << endl
	<< "Extra opts : " << options << endl;
	if(!listPaths.empty())
		cout << "Paths to analyze :" << endl;
		for(vector<string>::const_iterator it = listPaths.begin(); it != listPaths.end(); it++)
			cout << "\t- " << *it <<endl;
	cout << "--------------------->" << endl;

}

std::string LauncherCTags::constructCommand() const {
	std::string command = pathExecutable + " " + options + " " + GLOBAL_OPTIONS;
	std::string path = " -f " + config->getDestDir() + "/tags " ;
	std::string list = "";

	for(vector<string>::const_iterator it = listPaths.begin(); it != listPaths.end(); it++)
		list += (*it) + " ";

	command += path + list;
	return command;
}
