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

#include "TagsParserImpl.h"
using namespace std;

TagsParserImpl::TagsParserImpl(TagsManagerImpl* man) {
	myTagMan = man;
}

void TagsParserImpl::loadFromFile ( std::string inputFile ) {
	assert(inputFile != "");
	std::vector<string> tab;
	ifstream fileFd(inputFile.c_str());
	if(!fileFd.is_open())
		scError("File " << inputFile << " not Found !");

	string cur;
	std::string part;
	string name, filename;
	size_t line= 0;
	tagType type;

	while(getline(fileFd, cur, '\n')){

		if(cur[0] == '!') continue;
		stringstream ss(cur);

		while(getline(ss, part, '\t')){
			tab.push_back(part);
		}
		name = tab[0]; tab.erase(tab.begin());
		filename = tab[0]; tab.erase(tab.begin());

		line = atoi(tab[0].substr(0,tab[0].size() - 2).c_str()); tab.erase(tab.begin());
		type = identifyTypeFromFile(tab[0]); tab.erase(tab.begin());
		Tag* curTag = new TagImpl(name, filename, line, type);
		for(vector<string>::iterator it = tab.begin(); it != tab.end(); it++){
			int splitter = (*it).find(":");
			string key = (*it).substr(0, splitter);
			string value = (*it).substr(splitter+1, (*it).size());
			curTag->addInfoByKey(key, value);
		}
		myTagMan->addTag(curTag);
		tab.clear();
	}

}

tagType TagsParserImpl::identifyTypeFromFile ( string type ) {
	switch(type[0]){
		case 'c': return TYPE_CLASS;
		case 'd': return TYPE_DEFINE;
		case 'e': return TYPE_ENUMERATOR;
		case 'f': return TYPE_FUNCTION;
		case 'F': return TYPE_FILE;
		case 'g': return TYPE_ENUM;
		case 'm': return TYPE_MEMBER;
		case 'p': return TYPE_PROTO;
		case 's': return TYPE_STRUCT;
		case 't': return TYPE_TYPEDEF;
		case 'u': return TYPE_UNION;
		case 'v': return TYPE_VAR;
		case 'i': return TYPE_ID;
		case 'n': return TYPE_NAMESPACE;
		default: return TYPE_UNKNOWN;
	}
}

