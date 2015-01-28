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

class LauncherCTags
{
private:
	std::string pathExecutable;
	std::string options;
	std::vector<std::string> listPaths;
	std::string filePath;
	Configuration* config;

	static const std::string DEF_EXEC;
	static const std::string GLOBAL_OPTIONS;

public:
	LauncherCTags(Configuration* config, std::vector<std::string> listPaths, std::string exe = "ctags", std::string opts = GLOBAL_OPTIONS);
	bool generateTagsFile();
	bool addPathToAnalyze(std::string filename);
	void display() const;
	std::string constructCommand() const;
};

#endif // LAUNCHERCTAGS_H
