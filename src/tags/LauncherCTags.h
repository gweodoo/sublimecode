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

#ifndef LAUNCHERCTAGS_H
#define LAUNCHERCTAGS_H

#include "../Configuration.h"

/**
 * LauncherCTags represents module which generate "tags" file from ctags command
 */
class LauncherCTags
{
private:
	std::string pathExecutable;         ///< path to ctags program
	std::string options;                ///< user specific options
	std::vector<std::string> listPaths; ///< list of files to analyze
	Configuration* config;              ///< current configuration

	static const std::string DEF_EXEC;       ///< constant defining default ctags path
	static const std::string GLOBAL_OPTIONS; ///< constant defining default ctags options

public:
	/**
	 * main constructor
	 * \param[in] config current configuration as pointer
	 * \param[in] listPaths list of files to analyze
	 * \param[in] exe path to ctags (default = DEF_EXEC)
	 * \param[in] opts opts to ctags (default = GLOBAL_OPTIONS)
	 */
	LauncherCTags(Configuration* config, std::vector<std::string> listPaths, std::string exe = DEF_EXEC, std::string opts = GLOBAL_OPTIONS);
	/**
	 * Generate tags file from specified list of files
	 * \return True if succeeded
	 * \return False otherwise
	 */
	bool generateTagsFile();
	/// main object displayer
	void display() const;
	/**
	 * Construct specific command, from information stored in the object
	 * \return a string as the command to execute (system() call)
	 */
	std::string constructCommand() const;
};

#endif // LAUNCHERCTAGS_H
