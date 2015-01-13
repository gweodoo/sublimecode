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

LauncherCTags::LauncherCTags (Configuration *config, std::vector<std::string>* listPaths, string exe, string opts ) {
	this->pathExecutable = exe;
	this->listPaths = listPaths;
	this->config = config;
	if(opts != GLOBAL_OPTIONS)
		this->options = opts;

	if(listPaths == NULL)
		this->listPaths = new vector<string>;
}

bool LauncherCTags::generateTagsFile() {
	//int ret= system("ctags -Rn -f /home/alexandre/Documents/tags /home/alexandre/Documents/vlc-2.1.5");
	int ret = system(constructCommand().c_str());
	
	cout << "size : " << constructCommand().size() << endl;
	if(ret == -1) return false;
	cout << WEXITSTATUS(ret) << endl;
	return WEXITSTATUS(ret) == 0 ? true : false;
}

bool LauncherCTags::addPathToAnalyze ( string path ) {
	listPaths->push_back(path);
	return true;
}

void LauncherCTags::display() const {
	cout << "LAUNCHER CTAGS ------>" << endl
	<< "Executable : " << pathExecutable << endl
	<< "Extra opts : " << options << endl;
	if(!listPaths->empty())
		cout << "Paths to analyze :" << endl;
		for(vector<string>::iterator it = listPaths->begin(); it != listPaths->end(); it++)
			cout << "\t- " << *it <<endl;
	cout << "--------------------->" << endl;

}

std::string LauncherCTags::constructCommand() const {
	std::string command = pathExecutable + " " + options + " " + GLOBAL_OPTIONS;
	std::string path = " -f " + config->getDestDir() + "/tags " ;
	std::string list = "";

	for(vector<string>::iterator it = listPaths->begin(); it != listPaths->end(); it++)
		list += (*it) + " ";

	command += path + list;
	return command;
}
