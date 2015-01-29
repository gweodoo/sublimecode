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

#include "TagsManager.h"
using namespace std;

TagsManager::TagsManager(Configuration *config) {
	this->config = config;
	for(int i=0; i < Tag::NB_TAGS_TYPES; i++){
		hashtable.push_back(new map<string, Tag*>);
	}
}

Tag* TagsManager::findSpecificTag ( std::string name, std::string filename, size_t line ) {
	//scDebug("name:"<<name <<" fileName :"<<filename << " line : "<<line);
	for(vector<map<string, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		map<string,Tag*>::iterator itmap = (*it)->find(hashTag(name, filename, line));
		if(itmap != (*it)->end())
			return (itmap->second);
	}
	return NULL;
}

std::vector<Tag*>* TagsManager::findTagsByType ( tagType type ) {
	std::vector<Tag*>* vec = new std::vector<Tag*>;
	for(map<string, Tag*>::const_iterator it = hashtable[type]->begin(); it != hashtable[type]->end(); it++){
		vec->push_back(it->second);
	}
	return vec;
}

bool TagsManager::delTag ( Tag* old ) {
	hashtable[static_cast<short>(old->getType())]->erase(hashTag(old));
	return true;
}

bool TagsManager::addTag ( Tag* nw ) {
	hashtable[static_cast<short>(nw->getType())]->insert(std::pair<string, Tag*>(hashTag(nw),nw));
	return true;
}

void TagsManager::display() const {
	for(vector<map<string, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		cout << " -------------- " << tabTypeNames[it - hashtable.begin()] << " -------------- " << endl;
		for(map<string, Tag*>::const_iterator itmap = (*it)->begin(); itmap != (*it)->end(); itmap++){
			(*itmap).second->display();
			cout << endl;
		}
	}
}

bool TagsManager::isEmpty() const {
	for(vector<map<string, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		if(!(*it)->empty())
			return false;
	}
	return true;
}

std::vector< Tag* >* TagsManager::getTagsByName ( string name ) {
	std::vector<Tag *>* list = new vector<Tag*>;
	for(vector<map<string, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		for(map<string, Tag*>::const_iterator itmap = (*it)->begin(); itmap != (*it)->end(); itmap++){
			if(itmap->second->getName() == name){
				list->push_back(itmap->second);
			}
		}
	}
	return list;
}

std::vector< Tag* >* TagsManager::getTagsByFile ( string filename ) {
	std::vector<Tag *>* list = new vector<Tag*>;
	for(vector<map<string, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		for(map<string, Tag*>::const_iterator itmap = (*it)->begin(); itmap != (*it)->end(); itmap++){
			if(itmap->second->getFileName() == filename){
				list->push_back(itmap->second);
			}
		}
	}
	return list;
}

vector< string >* TagsManager::getTagNamesByType ( tagType type ) {
	vector<Tag*>* vec = findTagsByType(type);
	vector<string>* list = new vector<string>;
	for(vector<Tag*>::iterator it = vec->begin(); it != vec->end(); it++)
		list->push_back((*it)->getName());

	return list;
}

TagsManager::~TagsManager() {
	for(vector<map<string, Tag*>*>::iterator it = hashtable.begin(); it != hashtable.end(); it++){
		for(map<string, Tag*>::iterator itmap = (*it)->begin(); itmap != (*it)->end(); itmap++){
			delete itmap->second;
			(*it)->erase(itmap);
		}
		delete *it;
	}
}

std::string TagsManager::hashTag(Tag* tag) const{
	return hashTag(tag->getName(), tag->getFileName(), tag->getLineNumber());
}

std::string TagsManager::hashTag(std::string name, std::string filename, size_t line) const{
	stringstream ss;
	ss << filename << ":" << line << ":" << name;
	return ss.str();
}

std::vector< Tag* >* TagsManager::getTagsByTypeAndFile ( string file, tagType type ) {
	std::vector<Tag*>* vec = findTagsByType(type);
	for(vector<Tag*>::iterator it = vec->begin(); it != vec->end();){
		it = ((*it)->getFileName() == file) ? it+1 : vec->erase(it);
	}
	return vec;
}

