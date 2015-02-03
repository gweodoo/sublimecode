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

#include "StatsParser.h"
using namespace std;

StatsParser::StatsParser ( Configuration *config, TagsManager* tagMan ) : tagMan(tagMan), config(config) {}

void StatsParser::load(){
	string filename = config->getDestDir()+"/cloc_result";
	std::string command = "cloc --quiet --by-file-by-lang --csv "+config->getSourcesDir()+ " --report-file="+filename+" > /dev/null", result="", cur="";
	vector<string> header;
	bool first = false;
	int ret;
	ret = system(command.c_str());
	assert(ret != -1);
	ifstream flux(filename.c_str());
	while(getline(flux, cur, '\n')){
		if(cur.empty()) continue;
		map<string, int> splitLine = splitOn(cur, ',');
		if(splitLine.size() >= 6){
			first = !first;
			continue;
		}
		if(first){
			StatsFileItem* item = new StatsFileItem;
			item->fillFromString(cur);
			tabFiles.push_back(item);
		} else {

			StatsLanguageItem* item = new StatsLanguageItem;
			item->fillFromString(cur);
			tabLanguages.push_back(item);
		}
	}
	UNUSED(ret);
}

void StatsParser::display() const {
	cout << "DISPLAYING Cloc Parser" <<endl;
	for(vector<StatsLanguageItem*>::const_iterator it = tabLanguages.begin(); it != tabLanguages.end(); it++){
		(*it)->display();
	}

	for(vector<StatsFileItem*>::const_iterator it = tabFiles.begin(); it != tabFiles.end(); it++){
		(*it)->display();
	}
}

vector<std::pair<string, int> > StatsParser::getMostImplementedFilesPerLanguage(std::string language) const {
	int i = 0;
	const short MAX = 10;
	vector<std::pair<string, int> > vec;


	for(vector<StatsFileItem*>::const_iterator it = tabFiles.begin(); it != tabFiles.end() && i < MAX; it++){
		if((*it)->getLanguageName() == language){
			vec.push_back(make_pair((*it)->getFileName().substr(config->getSourcesDir().size()), (*it)->getNbCodeLines()));
			i++;
		}
	}
	return vec;
}

vector<std::pair<string, float> >  StatsParser::getMostUsedLanguages() const {
	int i = 0;
	const short MAX = 10;
	vector<std::pair<string, float> >  vec;
	for(vector<StatsLanguageItem*>::const_iterator it = tabLanguages.begin(); it != tabLanguages.end() && i < MAX; it++){
		vec.push_back(make_pair((*it)->getName(), (*it)->getNbCodeLines()+(*it)->getNbCommentLines()));
		i++;
	}
	return vec;
}

vector< pair< string, int > > StatsParser::getNbTagsPerFile() const {
	std::string command = "cut -f2 "+config->getDestDir()+"/tags | sort | uniq -c | sort -rn | awk '{printf(\"%s,%s\\n\",$2,$1)}'";
	string result = "", cur = "", cur2 = "";
	vector<std::pair<string, int> > vec;
	const short MAX = 256, MAX_TAGS = 10;
	short i = 0;
	char buf[MAX];

	FILE* fd = popen(command.c_str(), "r");
	while(!feof(fd)){
		if(fgets(buf,MAX,fd)!=NULL){
			result.append(buf);
		}
	}

	stringstream flux(result);
	while(getline(flux, cur, '\n') && i < MAX_TAGS){
		if(cur[0] != '/') continue;
		size_t pos = cur.find(",");
		size_t total = cur.size();
		size_t nb = atoi(cur.substr(pos+1, total - (pos+1)).c_str());
		string file = cur.substr(0, pos);
		vec.push_back(std::pair<string, int>(file.substr(config->getSourcesDir().size()), (int)nb));
		i++;
	}

	return vec;
}

StatsParser::~StatsParser() {
	for(vector<StatsLanguageItem*>::const_iterator it = tabLanguages.begin(); it != tabLanguages.end(); it++){
		delete (*it);
	}

	for(vector<StatsFileItem*>::const_iterator it = tabFiles.begin(); it != tabFiles.end(); it++){
		delete (*it);
	}

}

