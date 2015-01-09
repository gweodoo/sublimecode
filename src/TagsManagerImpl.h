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

#ifndef TAGSMANAGERIMPL_H
#define TAGSMANAGERIMPL_H

#include "TagsManager.h"
#include "Configuration.h"
using namespace std;

class TagsManagerImpl :  public TagsManager
{
private:
	Configuration* config;
	std::vector<std::map<std::string, Tag*>* > hashtable;
public:
	TagsManagerImpl(Configuration *config);
	virtual Tag* findSpecificTag ( std::string name, std::string filename, size_t line );
	virtual std::vector<Tag*>* findTagsByType(tagType type);
	virtual bool delTag ( Tag* old );
	virtual bool addTag ( Tag* nw );
	virtual void display() const;
	virtual bool isEmpty() const;
	virtual std::vector<Tag*>* getTagsByName(std::string name);
	virtual std::vector<Tag*>* getTagsByFile(std::string filename);
	virtual std::vector<std::string>* getTagNamesByType(tagType type);
};

#endif // TAGSMANAGERIMPL_H
