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

#ifndef FILESYSTEMPARSER_H
#define FILESYSTEMPARSER_H

#include "../Utils.h"
#include "../Configuration.h"

/**
 * StatsProjectInfo provides global informations about project like the type
 * (builder used), authors (if found), ...
 */
class StatsProjectInfo
{
private:
	Configuration *config;                             ///< global configuration pointer
	std::vector<std::string> filesTree;                ///< list of selected files
	std::map<std::string ,std::string> mapProjectInfo; ///< map containing list of extracted data

	/**
	 * read a file depicted as "AUTHORS" one and extract each line as an author name
	 * \param[in] filename "AUTHORS" file path
	 * \return string to print authors
	 */
	std::string listOfAuthors(std::string filename);
public:
	/**
	 * Default constructor
	 * \param[in] config global configuration
	 * \param[in] filesList list of selected files
	 */
	StatsProjectInfo(Configuration *config, std::vector<std::string> filesList);
	/**
	 * Start sources tree data extraction
	 */
	void analyzeSourcesTree();
	/**
	 * return filled map by analyzeSourcesTree() function.
	 * \warning need to be called AFTER analyzeSourcesTree() (or map will be empty)
	 * \return the filled map
	 */
	std::map<std::string,std::string> getProjectInfo() const;
};

#endif // FILESYSTEMPARSER_H
