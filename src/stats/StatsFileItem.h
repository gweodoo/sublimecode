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
#ifndef CLOCFILEITEM_H
#define CLOCFILEITEM_H

#include "../Utils.h"

/**
 * StatsFileItem represents a stats from Cloc, which loads stats from source
 * files in sources path. Specifically, StatsFileItem represents one file statistic,
 * its number of blank, comment or code lines.
 */
class StatsFileItem {
private:
	std::string filename;    ///< the file name where stats apply
	std::string languageName;///< file language
	size_t nbBlankLines;     ///< number of blank lines (spaces,tabs...)
	size_t nbCommentLines;   ///< number of commented lines (fully commented : comment + code = code line)
	size_t nbCodeLines;      ///< number of code lines in current file

public:
	///default constructor
	StatsFileItem();
	/**
	 * fill the current statsFileItem from data containing in comma-separated chain
	 * \param[in] chain the chain to split
	 */
	void fillFromString(std::string chain);
	/**
	 * file name getter
	 * \return file name as string
	 */
	std::string getFileName() const;
	/**
	 * language name getter
	 * \return language name as string
	 */
	std::string getLanguageName() const;
	/**
	 * blank lines number getter
	 * \return blank lines number as string
	 */
	size_t getNbBlankLines() const;
	/**
	 * commented lines number getter
	 * \return commented lines number as string
	 */
	size_t getNbCommentLines() const;
	/**
	 * code lines number getter
	 * \return code lines number as string
	 */
	size_t getNbCodeLines() const;
	///object displayer
	void display() const;
};

#endif // CLOCFILEITEM_H
