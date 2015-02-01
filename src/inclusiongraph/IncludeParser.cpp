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

#include "IncludeParser.h"
#include <qfileinfo.h>
using namespace std;


const string IncludeParser::tabInclusivePaths[] = {"include/", "lib/"};

IncludeParser::IncludeParser(Configuration *config) : config(config) {}

std::map< std::string, bool > IncludeParser::lookForIncludedGraph ( std::string path ) const {
	std::string result = "", cur = "";
	std::map<std::string, bool>vec;
	size_t pos = 0;
	result = getIncludedResult(path);

	stringstream flux(result);
// 	cout << "RESULT = " << result << endl;
	while(getline(flux, cur, '\n')){
		pos = cur.find(":");
		string file = cur.substr(0, pos);
		string include = cur.substr(pos+1);
		size_t start = include.find("<"), end = 0;
// 		cout << file << " " << include << endl;
		if(start <= include.size()){
			end = include.find(">");
			include = include.substr(start+1, end - (start+1));
			string checkFile = config->getSourcesDir()+"/include/"+include;
			if(QFileInfo(QString(checkFile.c_str())).absolutePath() == QFileInfo(QString(path.c_str())).absolutePath()){
// 				cout << "Included in " << file << endl;
				vec.insert(std::pair<string, bool>(file, true));
			} else {
				checkFile = config->getSourcesDir()+"/lib/"+include;
				if(QFileInfo(QString(checkFile.c_str())).absolutePath() == QFileInfo(QString(path.c_str())).absolutePath()){
// 					cout << "Included in " << file << endl;
					vec.insert(std::pair<string, bool>(file, true));
				}

			}
		} else {
			start = include.find_first_of("\"");
			assert(start <= include.size());
			end = include.find_last_of("\"");
			include = include.substr(start+1, end - (start+1));
			string checkFile = findDirname(file)+"/"+include;

			if(QFileInfo(QString(checkFile.c_str())).absolutePath() == QFileInfo(QString(path.c_str())).absolutePath()){
// 				cout << "Included in " << file << endl;
				vec.insert(std::pair<string, bool>(file, true));
			}
		}
	}
	return vec;
}

map< string, bool > IncludeParser::lookForInclusionGraph ( string path ) const {
	std::string result = "", cur = "", pathInclude = "", include = "";
	std::map<std::string, bool> vec;
	size_t pos = 0;

	result = getInclusionResult(path);

	stringstream flux(result);
	while(getline(flux, cur, '\n')){
		pos = cur.find("<");
		if( pos < cur.size()){
			include = cur.substr(pos+1, cur.size()-1 - (pos+1));

		} else {
			pos = cur.find("\"");
			include = findDirname(path)+"/"+cur.substr(pos+1, cur.size()-1 - (pos+1));
		}
		pathInclude = findIncludeInProject(include);
		if( pathInclude == ""){
			vec.insert(std::pair<string, bool>(cur.substr(pos+1, cur.size()-1 - (pos+1)), false));
		} else {
			vec.insert(std::pair<string, bool>(pathInclude, true));
		}
	}

	return vec;
}

string IncludeParser::getInclusionResult ( string path ) const {
	string command="", result = "";
	const short MAX = 1024;
	char buf[MAX];

	command =  "egrep -o \"^ *# *include *(\\\"|<).*\\..*(\\\"|>)\" "+path;
	FILE * fd = popen(command.c_str(), "r");
	assert(fd != NULL);
	while(!feof(fd)){
		if(fgets(buf,MAX,fd)!=NULL){
			result.append(buf);
		}
	}
	return result;
}

string IncludeParser::getIncludedResult ( string path ) const {

	string command="", result = "";
	size_t pos = 0;
	const short MAX = 1024;
	char buf[MAX];
	path = findBasename(path);
	pos = path.find(".");
	string extension = path.substr(pos+1);
	if(extension != "h" && extension != "H" && extension != "hpp" && extension != "HPP") return "";
	if(pos < path.size())
		path.replace(pos, 1, "\\.");
	command =  "egrep -o \"^ *# *include *(\\\"|<)(.*/)*"+path+"(\\\"|>)\" -R "+config->getSourcesDir();
	FILE * fd = popen(command.c_str(), "r");
	assert(fd != NULL);
	while(!feof(fd)){
		if(fgets(buf,MAX,fd)!=NULL){
			result.append(buf);
		}
	}
// 	cout << "command = " << command << endl;
// 	cout << "result = " << result << endl;
	return result;
}

string IncludeParser::findDirname(std::string name) const {
	size_t last = name.find_last_of("/");
	if(last < name.size()){
		return name.substr(0,last);
	} else {
		return name;
	}
}


string IncludeParser::findBasename(std::string name) const {
	size_t last = name.find_last_of("/");
	if(last < name.size()){
		return name.substr(last+1);
	} else {
		return name;
	}
}

string IncludeParser::findIncludeInProject ( string filename ) const {
	if(filename[0] == '/'){
		if(access(filename.c_str(), F_OK) != -1)
			return filename;
	} else {
		for(int i = 0; i < NB_POSSIBLE_PATHS; i++){
			string checkFile = config->getSourcesDir()+"/"+tabInclusivePaths[i]+filename;
			if(access(checkFile.c_str(), F_OK) != -1){
				return checkFile;
			}
		}
	}

	return "";
}
