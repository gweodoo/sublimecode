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

class StatsLanguageItem {
private:
	std::string name;
	size_t nbFiles;
	size_t nbBlankLines;
	size_t nbCommentLines;
	size_t nbCodeLines;

public:
	StatsLanguageItem();
	void fillFromString(std::string chain);
	std::string getName() const;
	size_t getNbFiles() const;
	size_t getNbBlankLines() const;
	size_t getNbCommentLines() const;
	size_t getNbCodeLines() const;
	void display() const;
};

#endif // CLOCLANGUAGEITEM_H
