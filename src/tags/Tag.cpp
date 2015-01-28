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

#include "Tag.h"
using namespace std;

const char* tabTypeNames[] = {"CLASS", "DEFINE", "ENUMERATOR", "FUNCTION", "FILE", "ENUM", "MEMBER", "PROTO", "STRUCT", "TYPEDEF", "UNION", "VAR", "ID","NAMESPACE",  "UNKNOWN"};
const std::string OUT_OF_SCOPE_TAG = "OUT_OF_SCOPE";

Tag::Tag(std::string name, std::string fileName, size_t line, tagType type) {
	this->name = name;
	this->fileName = fileName;
	this->lineNumber = line;
	this->type = type;
}

void Tag::setName(std::string name){
	this->name = name;
}
void Tag::setFileName(std::string fileName){
	this->fileName = fileName;
}
void Tag::setLineNumber(size_t line){
	this->lineNumber = line;
}
void Tag::setType(tagType type){
	this->type = type;
}
std::string Tag::getName() const{
	return name;
}
std::string Tag::getFileName() const{
	return fileName;
}
size_t Tag::getLineNumber() const{
	return lineNumber;
}
tagType Tag::getType() const{
	return type;
}
std::string Tag::getInfoByKey(std::string key)const{
	map<std::string, string>::const_iterator it = additionalInfo.find(key);
	if(it != additionalInfo.end())
		return it->second;
	return "";
}
bool Tag::addInfoByKey ( std::string key, string value ) {
	additionalInfo[key] = value;
	return true;
}

void Tag::display() const {
	cout
	<< "\tName = " << name<< endl
	<< "\tFileName = " << fileName<< endl
	<< "\tLine number = " << lineNumber << endl
	<< "\tType = " << tabTypeNames[type]<< endl;
	if(additionalInfo.size() > 0){
		cout << "\tAdditionnal : "<< endl;
		for(map<string,string>::const_iterator it = additionalInfo.begin(); it != additionalInfo.end(); it++)
			cout << "\t\t- " << it->first << " : " << it->second << endl;
	}
}

std::string Tag::hashFileName() const {
	long filename = 0;
	std::stringstream ss;
	std::string tagToHash;

	ss << this->name << this->fileName << this->lineNumber;
	tagToHash = ss.str();

	for (size_t i = 0; i < tagToHash.length(); i++)
	{
		filename = filename + (tagToHash[i] * i);
	}

	ss.str("");
	ss.clear();
	ss << filename;
	return ss.str();
}

const std::map<std::string,std::string>& Tag::getAllInfo() const {
	return const_cast<const map<string,string>&>(additionalInfo);
}

Tag::~Tag() {
}
