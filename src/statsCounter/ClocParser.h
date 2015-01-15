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
#ifndef CLOCPARSER_H
#define CLOCPARSER_H
#include "../Utils.h"
#include "ClocLanguageItem.h"

class ClocParser {
private:
	std::vector<ClocLanguageItem*> tabLanguages;
public:
	void runWith(std::string path);
	void display() const;
	std::map<std::string, float> getRatioComments_Code() const;
	std::map<std::string, float> getRatioCode_Total() const;
};

#endif // CLOCPARSER_H
