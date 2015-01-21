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

#include "StatsFileItem.h"
using namespace std;

StatsFileItem::StatsFileItem(){
	this->filename = "";
	this->languageName = "";
	this->nbBlankLines = 0;
	this->nbCommentLines = 0;
	this->nbCodeLines = 0;
}

void StatsFileItem::fillFromString(std::string chain){
	stringstream flux(chain);
	string cur;
	vector<string> vec;
	while(getline(flux, cur, ',')){
		vec.push_back(cur);
	}
	languageName = vec[0].c_str();
	filename = vec[1].c_str();
	nbBlankLines = atoi(vec[2].c_str());
	nbCommentLines = atoi(vec[3].c_str());
	nbCodeLines = atoi(vec[4].c_str());
}
std::string StatsFileItem::getFileName() const{
	return filename;
}
std::string StatsFileItem::getLanguageName() const{
	return languageName;
}
size_t StatsFileItem::getNbBlankLines() const{
	return nbBlankLines;
}
size_t StatsFileItem::getNbCommentLines() const{
	return nbCommentLines;
}
size_t StatsFileItem::getNbCodeLines() const{
	return nbCodeLines;
}

void StatsFileItem::display() const {
	cout << "FILE = " << filename << endl
	<< "LANGUAGE = " << languageName<< endl
	<< "NB BLANK = " << nbBlankLines<< endl
	<< "NB COMME = " << nbCommentLines<< endl
	<< "NB CODE  = " << nbCodeLines<< endl;

}
