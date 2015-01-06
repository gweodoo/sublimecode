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

#include "TagImpl.h"
using namespace std;

TagImpl::TagImpl(std::string name, std::string fileName, std::string address, tagType type) {
	this->name = name;
	this->fileName = fileName;
	this->address = address;
	this->type = type;
}

bool TagImpl::setName(std::string name){
	this->name = name;
};
bool TagImpl::setFileName(std::string fileName){
	this->fileName = fileName;
	return true;
};
bool TagImpl::setAddress(std::string address){
	this->address = address;
	return true;
};
bool TagImpl::setType(tagType type){
	this->type = type;
	return true;
};
std::string TagImpl::getName() const{
	return name;
};
std::string TagImpl::getFileName() const{
	return fileName;
};
std::string TagImpl::getAddress() const{
	return address;
};
tagType TagImpl::getType() const{
	return type;
};
std::string TagImpl::getInfoByKey(std::string key)const{
	map<std::string, string>::const_iterator it = additionalInfo.find(key);
	if(it != additionalInfo.end())
		return it->second;
	return "";
};
bool TagImpl::addInfoByKey ( std::string key, string value ) {
	additionalInfo[key] = value;
	return true;
}


void TagImpl::display() const {
	cout
	<< "\tName = " << name<< endl
	<< "\tFileName = " << fileName<< endl
	<< "\tAddress = " << address<< endl
	<< "\tType = " << type<< endl;
	if(additionalInfo.size() > 0){
		cout << "\tAdditionnal : "<< endl;
		for(map<string,string>::const_iterator it = additionalInfo.begin(); it != additionalInfo.end(); it++)
			cout << "\t\t- " << it->first << " : " << it->second << endl;
	}
}
