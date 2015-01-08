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

#include "TagsManagerImpl.h"

TagsManagerImpl::TagsManagerImpl(Configuration *config) {
	this->config = config;
	for(int i=0; i < Tag::NB_TAGS_TYPES; i++){
		hashtable.push_back(new map<string, Tag*>);
	}
}

Tag* TagsManagerImpl::findSpecificTag ( std::string name, std::string filename, size_t line ) {
	//scDebug("name:"<<name <<" fileName :"<<filename << " line : "<<line);
	for(vector<map<string, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		map<string,Tag*>::iterator itmap = (*it)->find(hashTag(name, filename, line));
		if(itmap != (*it)->end())
			return (itmap->second);
	}
	return NULL;
}

std::vector<Tag*>* TagsManagerImpl::findTagsBy ( tagType type ) {
	std::vector<Tag*>* vec = new std::vector<Tag*>;
	for(map<string, Tag*>::const_iterator it = hashtable[type]->begin(); it != hashtable[type]->end(); it++){
		vec->push_back(it->second);
	}
	return vec;
}

bool TagsManagerImpl::delTag ( Tag* old ) {
	hashtable[static_cast<short>(old->getType())]->erase(hashTag(old));
	return true;
}

bool TagsManagerImpl::addTag ( Tag* nw ) {
	hashtable[static_cast<short>(nw->getType())]->insert(std::pair<string, Tag*>(hashTag(nw),nw));
	return true;
}

void TagsManagerImpl::display() const {
	for(vector<map<string, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		cout << " -------------- " << tabTypeNames[it - hashtable.begin()] << " -------------- " << endl;
		for(map<string, Tag*>::const_iterator itmap = (*it)->begin(); itmap != (*it)->end(); itmap++){
			(*itmap).second->display();
			cout << endl;
		}
	}
}

bool TagsManagerImpl::isEmpty() const {
	for(vector<map<string, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		if(!(*it)->empty())
			return false;
	}
	return true;
}

std::vector< Tag* >* TagsManagerImpl::getTagsByName ( string name ) {
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

