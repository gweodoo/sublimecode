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

#include "StatsLanguageItem.h"
using namespace std;

StatsLanguageItem::StatsLanguageItem(){
	this->name = "";
	this->nbFiles = 0;
	this->nbBlankLines = 0;
	this->nbCommentLines = 0;
	this->nbCodeLines = 0;
}

void StatsLanguageItem::fillFromString(std::string chain){
	stringstream flux(chain);
	string cur;
	vector<string> vec;
	while(getline(flux, cur, ',')){
		vec.push_back(cur);
	}
	nbFiles = atoi(vec[0].c_str());
	name = vec[1].c_str();
	nbBlankLines = atoi(vec[2].c_str());
	nbCommentLines = atoi(vec[3].c_str());
	nbCodeLines = atoi(vec[4].c_str());
}
std::string StatsLanguageItem::getName() const{
	return name;
}
size_t StatsLanguageItem::getNbFiles() const{
	return nbFiles;
}
size_t StatsLanguageItem::getNbBlankLines() const{
	return nbBlankLines;
}
size_t StatsLanguageItem::getNbCommentLines() const{
	return nbCommentLines;
}
size_t StatsLanguageItem::getNbCodeLines() const{
	return nbCodeLines;
}

void StatsLanguageItem::display() const {
	cout << "LANGUAGE = " << name << endl
	<< "NB FILES = " << nbFiles<< endl
	<< "NB BLANK = " << nbBlankLines<< endl
	<< "NB COMME = " << nbCommentLines<< endl
	<< "NB CODE  = " << nbCodeLines<< endl;

}
