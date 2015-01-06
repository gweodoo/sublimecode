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

#ifndef TAGIMPL_H
#define TAGIMPL_H

#include "Tag.h"
class TagImpl : public Tag
{
private:
	std::string name;
	std::string fileName;
	std::string address;
	tagType type;
	std::map<std::string, std::string> additionalInfo;
public:
	explicit TagImpl(std::string name, std::string fileName, std::string address, tagType type);
	virtual bool setName(std::string name);
	virtual bool setFileName(std::string fileName);
	virtual bool setAddress(std::string address);
	virtual bool setType(tagType type);
	virtual bool addInfoByKey(std::string key, std::string value);
	virtual std::string getName() const;
	virtual std::string getFileName() const;
	virtual std::string getAddress() const;
	virtual tagType getType() const;
	virtual std::string getInfoByKey(std::string key) const;
	virtual void display() const;
};

#endif // TAGIMPL_H
