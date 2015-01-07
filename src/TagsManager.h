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
#ifndef TAGSMANAGER_H
#define TAGSMANAGER_H

#include "Tag.h"

class TagsManager
{
public:
	virtual bool addTag(Tag* nw) = 0;
	virtual bool delTag(Tag* old) = 0;
	virtual Tag* findSpecificTag( std::string name, std::string filename, size_t line ) = 0;
	virtual  std::vector<Tag*>*  findTagsBy(tagType type) = 0;
	std::string hashTag(Tag* tag) const;
	std::string hashTag(std::string name, std::string filename, size_t line) const;
	virtual void display() const = 0;
	virtual bool isEmpty() const = 0;

};

#endif // TAGSMANAGER_H
