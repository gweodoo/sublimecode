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
/**
 * Enum handling possible types generated by CTags
 */
typedef enum tagType_e {
	TYPE_CLASS = 0,      ///< Represents a class type
	TYPE_DEFINE = 1,     ///< Represents a "define" type (macros)
	TYPE_ENUMERATOR = 2, ///< Represents a enumeration item type
	TYPE_FUNCTION = 3,   ///< Represents a function type
	TYPE_FILE = 4,       ///< Represents a file type
	TYPE_ENUM = 5,       ///< Represents a enum type
	TYPE_MEMBER = 6,     ///< Represents a member type (belong to a class or struct)
	TYPE_PROTO = 7,      ///< Represents a prototype type (tag from .h file for function)
	TYPE_STRUCT = 8,     ///< Represents a struct type
	TYPE_TYPEDEF = 9,    ///< Represents a typedef type (with an extra info : typeref)
	TYPE_UNION = 10,     ///< Represents a union type
	TYPE_VAR = 11,       ///< Represents a variable type
	TYPE_ID = 12,        ///< Represents a id type (not really used, for compatibility with web file (.css)
	TYPE_NAMESPACE = 13, ///< Represents a namespace type (especially for C++ support)
	TYPE_UNKNOWN = 14    ///< Represents a type which can't be hang up
} tagType;

extern const char* tabTypeNames[];  ///< Contains assiocated names to each type, according to its enum number
#define FIELD_ACCESS "access"       ///< access Key chain for additionnal info
#define FIELD_FILE "file"           ///< file Key chain for additionnal info (means tag is static to the file, no value required)
#define FIELD_KIND "kind"           ///< kind Key chain for additionnal info
#define FIELD_IMPL "implementation" ///< implementation Key chain for additionnal info
#define FIELD_INHE "inherits"       ///< inherits Key chain for additionnal info
#define FIELD_SIGN "signature"      ///< signature Key chain for additionnal info
#define FIELD_CLASS "class"         ///< class Key chain for additionnal info
#define FIELD_STRUCT "struct"       ///< struct Key chain for additionnal info

/**
 * A tag is the base manipulated object in SublimeCode. It represents a symbol in analyzed program. A tag can contains a lot of information:
 * - A name : it's the tag name, for example, for a function, it's its name
 * - A file name : references the tag by its filename in current tree
 * - A line number : defines where is located the tag definition in given file
 * - A tag type : According to previous enum, defines the tag type (function, class...)
 * - Additional infos : Constructed with a key-value map, additionnal infos contains miscellaneous data about the tag. For exeample, If the tag
 * 	is a member, a typical additionnal info is the reference tag : class, struct,... So the map item in this case could be key=class, value=foo
 *
 * In order to allow flexibility, a tag is an pure abstract class.
 */
class Tag {
public:
	static const short NB_TAGS_TYPES = 15;     ///< represents max number of possible tags
	static const std::string OUT_OF_SCOPE_TAG; ///< defines the global chain to identify "out of scope" tag (not in the project tree, like printf, malloc,...)
	
	/******** CONST ********/
	/**
	 * Get the tag name for current tag
	 * \return the name as a string
	 */
	virtual std::string getName() const = 0;
	/**
	 * Get the tag filename for current tag
	 * \return the filename as a string
	 */
	virtual std::string getFileName() const = 0;
	/**
	 * Get the tag line number for current tag
	 * \return the line number as a size_t
	 */
	virtual size_t getLineNumber() const = 0;
	/**
	 * Get the tag type for current tag
	 * \return the type as a tagType_e
	 */
	virtual tagType getType() const = 0;
	/**
	 * Get the associated value of the given key for current tag
	 * For example, the key class will return the referent class name if exist
	 * \return the value as a string
	 * \return empty string if key is not found.
	 */
	virtual std::string getInfoByKey(std::string key) const = 0;
	/// display the tag content in terminal
	virtual void display() const = 0;

	/****** NON-CONST ******/
	/**
	 * set tag name (should be deprecated, and replaced by constructor)
	 * \param[in] name the name used to set
	 */
	virtual void setName(std::string name) = 0;
	/**
	 * set tag filename (should be deprecated, and replaced by constructor)
	 * \param[in] fileName the name used to set
	 */
	virtual void setFileName(std::string fileName) = 0;
	/**
	 * set tag lineNumber (should be deprecated, and replaced by constructor)
	 * \param[in] line the name used to set
	 */
	virtual void setLineNumber(size_t line) = 0;
	/**
	 * set tag type (should be deprecated, and replaced by constructor)
	 * \param[in] type the name used to set
	 */
	virtual void setType(tagType type) = 0;
	/**
	 * set a key-value item to insert (should be deprecated, and replaced by constructor)
	 * \param[in] key the item key
	 * \param[in] value the item value
	 * \return true if set is ok
	 */
	virtual bool addInfoByKey(std::string key, std::string value) = 0;
};

#endif
