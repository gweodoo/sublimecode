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

TagsManagerImpl::TagsManagerImpl() {
	for(int i=0; i < Tag::NB_TAGS_TYPES; i++){
		hashtable.push_back(new multimap<size_t, Tag*>);
	}
}

std::vector<Tag*>* TagsManagerImpl::findSpecificTag ( std::string name ) {
	std::vector<Tag*>* vec = new std::vector<Tag*>;
	for(vector<std::multimap<size_t, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		std::pair<std::multimap<size_t,Tag*>::iterator, std::multimap<size_t,Tag*>::iterator> pair;
		pair = (*it)->equal_range(hashTag(name));
		for(multimap<size_t,Tag*>::iterator it = pair.first; it != pair.second; it++){
			vec->push_back(it->second);
		}
	}
	return vec;
}

std::vector<Tag*>* TagsManagerImpl::findTagsBy ( tagType type ) {
	std::vector<Tag*>* vec = new std::vector<Tag*>;
	for(vector<std::multimap<size_t, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		for(multimap<size_t, Tag*>::const_iterator itmap = (*it)->begin(); itmap != (*it)->end(); itmap++){
			Tag * cur = itmap->second;
			if(cur->getType() == type)
				vec->push_back(cur);
		}
	}
	return vec;
}

bool TagsManagerImpl::delTag ( Tag* old ) {
	hashtable[static_cast<short>(old->getType())]->erase(hashTag(old));
}

bool TagsManagerImpl::addTag ( Tag* nw ) {
	hashtable[static_cast<short>(nw->getType())]->insert(std::pair<size_t, Tag*>(hashTag(nw),nw));
	return true;

}

void TagsManagerImpl::display() const {
	for(vector<std::multimap<size_t, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		cout << " -------------- " << tabTypeNames[it - hashtable.begin()] << " -------------- " << endl;
		for(multimap<size_t, Tag*>::const_iterator itmap = (*it)->begin(); itmap != (*it)->end(); itmap++){
			(*itmap).second->display();
			cout << endl;
		}
	}
}
