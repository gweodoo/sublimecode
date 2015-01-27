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

/**
 * A tag manager gathers all loaded tags from the project and store them in a organized structure.
 * In this case, it's a vector of vectors. The first one sorts tags by type, and second one by alphabetical order.
 * basic command are available : add, del, display, empty?,...
 * some research routines are also available, in order to find tags according starting information we have.
 */
class TagsManager
{
public:
	/**
	 * Add a tag in the tag manager
	 * \param[in] nw the new tag to push
	 * \return true if successes, false otherwise
	 */
	virtual bool addTag(Tag* nw) = 0;
	/**
	 * remove a tag in the tag manager
	 * \param[in] nw the new tag to delete
	 * \return true if successes, false otherwise
	 */
	virtual bool delTag(Tag* old) = 0;
	/**
	 * a specific tag is unique thanks to his name, the file name and the line number it is defined.
	 * This method looks for the unique tag matching with given information.
	 * \param[in] name the tag name
	 * \param[in] filename the file name
	 * \param[in] line the line
	 * \return a tag pointer if successes, <b>NULL</b> otherwise
	 */
	virtual Tag* findSpecificTag( std::string name, std::string filename, size_t line ) = 0;
	/**
	 * get all tags according to specific tag, i.e. returns one vector from tag manager
	 * \param[in] type the type to look for
	 * \return a vector pointer, empty or not, according to tag type
	 */
	virtual  std::vector<Tag*>*  findTagsByType(tagType type) = 0;
	/**
	 * help tagsManager to sort its tag with an unique key. This function generate, from data a tag,
	 * a unique hash as a string : name:filename:line
	 * \param[in] tag the tag which need its unique key.
	 * \return the hash chain
	 */
	std::string hashTag(Tag* tag) const;
	/**
	 * generate hash chain from basics types (called by others ones. @see std::string hashTag(Tag* tag) const)
	 * \param[in] name the tag name
	 * \param[in] filename the tag filename
	 * \param[in] line the line
	 */
	std::string hashTag(std::string name, std::string filename, size_t line) const;
	/**
	 * display tagsManager contents to standard output
	 */
	virtual void display() const = 0;
	/**
	 * check if tagsManager is empty
	 * \return true if empty, false otherwise
	 */
	virtual bool isEmpty() const = 0;
	/**
	 * look for tags, according tag name. The name is not a unique key, so multiple matches can occur.
	 * \param[in] name the tag name to find.
	 * \return a pointer Tag pointer vector, containing tag information for given name
	 */
	virtual std::vector<Tag*>* getTagsByName(std::string name) = 0;
	/**
	 * looks for tags, according to file inclusion. List all tags gathered in the same given filename
	 * \param[in] filename the path where extract tags
	 * \return a pointer tag pointer vector, containing tag information for given file
	 */
	virtual std::vector<Tag*>* getTagsByFile(std::string filename) = 0;
	/**
	 * list tags for a given type (FUNCTION, CLASS,...)
	 * \param[in] type the given type as a enum (@see Tag.h)
	 * \return a pointer tag pointer vector, containing tag information for given type)
	 */
	virtual std::vector<std::string>* getTagNamesByType(tagType type) = 0;
};

#endif // TAGSMANAGER_H
