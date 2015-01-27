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

#ifndef PARSING_H
#define PARSING_H

#include "Utils.h"
#include "Tag.h"

/**
 * A tag parser loads a "tags" file generated by CTags and fills the associated tagsManager.
 */
class TagsParser {

public:
	/**
	 * this function opens the file and load, line by line, all its contents
	 * \param[in] inputFile the path where is located the "tags" file
	 */
	virtual void loadFromFile(std::string inputFile) = 0;
	/**
	 * tag type is read as a string from file. TagParser need to be convert it as a
	 * enum (@see Tag.h). this function run a switch-case to determine good enum member the tag is.
	 * \param[in] type the type as a string (actually a simple char, but a string is read from file)
	 * \return the associated tagType value (@see Tag.h)
	 */
	virtual tagType identifyTypeFromFile(std::string type) = 0;
};

#endif
