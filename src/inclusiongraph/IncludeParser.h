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

#ifndef INCLUDEPARSER_H
#define INCLUDEPARSER_H

#include "../Utils.h"
#include "../Configuration.h"

/**
 * The includeParser generates inclusions graphs for sublimeCode.
 */
class IncludeParser {
private:
	Configuration *config;              ///< default global configuration

	static const short NB_POSSIBLE_PATHS = 2;     ///< nb possible extra paths for inclusions
	static const std::string tabInclusivePaths[]; ///< tab with possible extra paths

	/**
	 * launch the command to get all files where "path" is included, i.e. find where
	 * current file is included in whole project
	 * \param[in] path the file to look look for
	 * \return the result as a string : the grep output
	 */
	std::string getIncludedResult(std::string path) const;
	/**
	 * launch the command to get all files included in given file i.e. find which files are
	 * pointed by \#include pattern found in "path"
	 * \param[in] path the file to analyze
	 * \return the result as a string : the grep output
	 */
	std::string getInclusionResult(std::string path) const;
	/**
	 * From a specific file name, check if this file exists in project tree
	 * \param[in] filename the file to check
	 * \return absolute path corresponding to the filename
	 * \return empty string if file doesn't exist
	 */
	std::string findIncludeInProject(std::string filename) const;
	/**
	 * Isolate a path from the file name and return the path
	 * \param[in] name the file name
	 * \return the dirname where this file is stored
	 */
	std::string findDirname(std::string name) const;
	/**
	 * Isolate a path from the file name and return the file name
	 * \param[in] name the file name
	 * \return the basename for the given path
	 */
	std::string findBasename(std::string name) const;
public:
	/**
	 * default constructor
	 * \param[in] config current global configuration
	 */
	IncludeParser(Configuration *config);
	/**
	 * MAIN FUNCTION : look for files where path is included
	 * \param[in] path the file to check for include
	 * \return a map containing the file which does the include (string) and check on existency (true/false)
	 */
	std::map<std::string, bool> lookForIncludedGraph(std::string path) const;
	/**
	 * MAIN FUNCTION : look for files called as \#include in given path
	 * \param[in] path the file to check for include
	 * \return a map containing the file which does the include (string) and check on existency (true/false)
	 */
	std::map<std::string, bool> lookForInclusionGraph(std::string path) const;
};

#endif // INCLUDEPARSER_H
