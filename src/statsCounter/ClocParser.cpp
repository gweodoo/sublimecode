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

#include "ClocParser.h"
using namespace std;

void ClocParser::runWith(std::string path){
	std::string command = "cloc --quiet --csv "+path, result="", cur="";
	FILE* fd = popen(command.c_str(), "r");
	const short MAX = 1024;
	char buf[MAX];
	assert(fd != NULL);
	while(!feof(fd)){

		if(fgets(buf,MAX,fd)!=NULL){

			result.append(buf);
		}
	}

	stringstream flux(result);
	while(getline(flux, cur, '\n')){
		if(cur.empty()) continue;
		cout << "\"" << cur << "\""<< endl;
		ClocLanguageItem* item = new ClocLanguageItem();
		item->fillFromString(cur);
		tabLanguages.push_back(item);
	}
}

void ClocParser::display() const {
	cout << "DISPLAYING Cloc Parser" <<endl;
	for(vector<ClocLanguageItem*>::const_iterator it = tabLanguages.begin(); it != tabLanguages.end(); it++){
		(*it)->display();
	}
}

map< string, float > ClocParser::getRatioCode_Total() const {
	map<string, float> res;
	for(vector<ClocLanguageItem*>::const_iterator it = tabLanguages.begin(); it != tabLanguages.end(); it++){
		size_t code = (*it)->getNbCodeLines();
		size_t total = code + (*it)->getNbBlankLines() + (*it)->getNbCommentLines();

		res.insert(std::pair<string,float>((*it)->getName(), (float)code/(float)total*100.0));
	}
	return res;
}

map< string, float > ClocParser::getRatioComments_Code() const {
	map<string, float> res;
	for(vector<ClocLanguageItem*>::const_iterator it = tabLanguages.begin(); it != tabLanguages.end(); it++){
		size_t code = (*it)->getNbCodeLines();
		size_t comments = (*it)->getNbCommentLines();

		res.insert(std::pair<string,float>((*it)->getName(), (float)comments/(float)code*100.0));
	}

	return res;
}


