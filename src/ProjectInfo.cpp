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
#include "ProjectInfo.h"
#include <algorithm>
using namespace std;

ProjectInfo::ProjectInfo(Configuration *config){
	this->config = config;
}

void ProjectInfo::addFilesList ( std::vector< std::string > filesList ) {
	this->filesTree = filesList;
	//for(std::vector<std::string>::iterator it = filesTree.begin(); it != filesTree.end(); it++)
	//	cout << *it << endl;
}

bool ProjectInfo::analyzeSourcesTree() {
	string authors = "No authors found", type = "Cannot be termined";
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

	if(find(filesTree.begin(), filesTree.end(), "/AUTHORS") != filesTree.end())
		authors = "Somes authors";

	mapProjectInfo.insert(std::pair<string, string>("Project type", type));
	mapProjectInfo.insert(std::pair<string, string>("Authors", authors));

	for(std::map<std::string, std::string>::iterator it = mapProjectInfo.begin(); it != mapProjectInfo.end(); it++)
		cout << it->first << " : " << it->second << endl;
}
