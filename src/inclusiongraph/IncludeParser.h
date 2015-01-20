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

class IncludeParser {
private:

	Configuration *config;
	std::vector<std::string> listPaths;

	static const short NB_POSSIBLE_PATHS = 2;
	static const std::string tabInclusivePaths[];

	std::string getIncludedResult(std::string path) const;
	std::string runCommand(std::string startCommand, std::string endCommand) const;

	std::string getInclusionResult(std::string path) const;
	std::string findIncludeInProject(std::string filename) const;

	std::string findDirname(std::string name) const;
	std::string findBasename(std::string name) const;

public:
	IncludeParser(Configuration *config);
	std::map<std::string, bool> lookForIncludedGraph(std::string path) const;
	std::map<std::string, bool> lookForInclusionGraph(std::string path) const;

	void addPathToAnalyze(std::string path);
};

#endif // INCLUDEPARSER_H
