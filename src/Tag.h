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

#ifndef TAG_H
#define TAG_H

#include "Utils.h"

typedef enum tagType_e {
	TYPE_CLASS = 0,
	TYPE_DEFINE = 1,
	TYPE_ENUMERATOR = 2,
	TYPE_FUNCTION = 3,
	TYPE_FILE = 4,
	TYPE_ENUM = 5,
	TYPE_MEMBER = 6,
	TYPE_PROTO = 7,
	TYPE_STRUCT = 8,
	TYPE_TYPEDEF = 9,
	TYPE_UNION = 10,
	TYPE_VAR = 11,
	TYPE_ID = 12,
	TYPE_NAMESPACE = 13,
	TYPE_UNKNOWN = 14
} tagType;

extern const char* tabTypeNames[];
#define FIELD_ACCESS "access"
#define FIELD_FILE "file"
#define FIELD_KIND "kind"
#define FIELD_IMPL "implementation"
#define FIELD_INHE "inherits"
#define FIELD_SIGN "signature"
#define FIELD_CLASS "class"
#define FIELD_STRUCT "struct"

class Tag {
public:
	static const short NB_TAGS_TYPES = 15;
	static const std::string OUT_OF_SCOPE_TAG;
	
	virtual bool setName(std::string name) = 0;
	virtual bool setFileName(std::string fileName) = 0;
	virtual bool setLineNumber(size_t line) = 0;
	virtual bool setType(tagType type) = 0;
	virtual bool addInfoByKey(std::string key, std::string value) = 0;
	virtual std::string getName() const = 0;
	virtual std::string getFileName() const = 0;
	virtual size_t getLineNumber() const = 0;
	virtual tagType getType() const = 0;
	virtual std::string getInfoByKey(std::string key) const = 0;
	bool operator==(const Tag& t2);
	virtual void display() const = 0;

};

#endif
