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
#ifndef CLOCLANGUAGEITEM_H
#define CLOCLANGUAGEITEM_H

#include "../Utils.h"

/**
 * A StatsLanguageItem represents one stats language in the source code. This
 * item is generated from cloc by StatsParser and loaded into this object
 */
class StatsLanguageItem {
private:
	std::string name;      ///< the language name
	size_t nbFiles;        ///< number of files using this language
	size_t nbBlankLines;   ///< number of blank lines in files using this language
	size_t nbCommentLines; ///< number of comment lines in files using this language
	size_t nbCodeLines;    ///< number of code lines in files using this language

public:
	/// default constructor
	StatsLanguageItem();
	/**
	 * fill the current statsLanguageItem from data containing in comma-separated chain
	 * \param[in] chain the chain to split
	 */
	void fillFromString(std::string chain);
	/**
	 * language name getter
	 * \return the name as a string
	 */
	std::string getName() const;
	/**
	 * associated files number getter
	 * \return quantity as a size_t
	 */
	size_t getNbFiles() const;
	/**
	 * associates blank lines number getter
	 * \return quantity as a size_t
	 */
	size_t getNbBlankLines() const;
	/**
	 * associated commented lines number getter
	 * \return quantity as a size_t
	 */
	size_t getNbCommentLines() const;
	/**
	 * associated code lines number getter
	 * \return quantity as a size_t
	 */
	size_t getNbCodeLines() const;
	/// object displayer
	void display() const;
};

#endif // CLOCLANGUAGEITEM_H
