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
#include "StatsProjectInfo.h"
#include <algorithm>
using namespace std;

StatsProjectInfo::StatsProjectInfo(Configuration *config,  std::vector< std::string > filesList ) : config(config) {
	this->config = config;
	for(std::vector<string>::iterator it = filesList.begin(); it != filesList.end(); it++){
		filesTree.push_back(it->substr(config->getSourcesDir().size()));
	}

}

void StatsProjectInfo::analyzeSourcesTree() {
	string authors = "No authors found", type = "Cannot be termined", file = "";
	stringstream buf;
	for(std::vector<string>::iterator it = filesTree.begin(); it != filesTree.end(); it++){
		if((*it) == "/Makefile.in" || (*it) == "/Makefile.am" || (*it) == "/configure.ac"){
			//AUTOTOOLS PROJECT
			type="AutoTools";
			break;
		} else if((*it) == "/SConstruct"){
			//SCons PROJECT
			type="SCons";
			break;
		} else if((*it) == "/CMakeLists.txt"){
			//CMAKE PROJECT
			type="CMake";
			break;
		}	else if((*it) == "/configure"){
			//CONFIGURE PROJECT
			type = "Configure &amp;&amp; make &amp;&amp; make install";
			break;
		} else if((*it) == "/Makefile"){
			//MAKE PROJECT
			type = "Make";
			break;
		}
	}
	vector<string>::iterator t = find(filesTree.begin(), filesTree.end(), "/AUTHORS");
	if(t != filesTree.end())
		file = *t;

	mapProjectInfo.insert(std::pair<string, string>("Project type", type));

	mapProjectInfo.insert(std::pair<string, string>("Authors", listOfAuthors(file)));

	buf.clear();buf << filesTree.size();
	mapProjectInfo.insert(std::pair<string, string>("Number of files", buf.str()));
}

map< string, string > StatsProjectInfo::getProjectInfo() const {
	return mapProjectInfo;
}

std::string StatsProjectInfo::listOfAuthors(std::string filename){
	filename = config->getSourcesDir() + filename;
	ifstream file(filename.c_str());
	std::string cur = "", result = "";
	while(std::getline(file, cur, '\n')){
		result += cur + "/";
	}
	return result;
}

