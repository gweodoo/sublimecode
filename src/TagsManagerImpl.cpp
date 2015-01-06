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
		hashtable.push_back(new map<size_t, Tag*>);
	}
}

Tag* TagsManagerImpl::findTag ( std::string name ) {
}

bool TagsManagerImpl::delTag ( Tag* old ) {
	hashtable[static_cast<short>(old->getType())]->erase(hashTag(old));
}

bool TagsManagerImpl::addTag ( Tag* nw ) {
	hashtable[static_cast<short>(nw->getType())]->insert(std::pair<size_t, Tag*>(hashTag(nw),nw));
}

void TagsManagerImpl::display() const {
	for(vector<std::map<size_t, Tag*>*>::const_iterator it = hashtable.begin(); it != hashtable.end(); it++){
		cout << " -------------- " << endl;
		for(map<size_t, Tag*>::const_iterator itmap = (*it)->begin(); itmap != (*it)->end(); itmap++){
			(*itmap).second->display();
		}
		cout << endl;
	}
}
