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
	Configuration *config;              /// default global configuration
	std::vector<std::string> listPaths; /// list of selected paths

	static const short NB_POSSIBLE_PATHS = 2;     /// nb possible extra paths for inclusions
	static const std::string tabInclusivePaths[]; /// tab with possible extra paths

	/**
	 * Start
	 */
	std::string getIncludedResult(std::string path) const;

	std::string getInclusionResult(std::string path) const;
	std::string findIncludeInProject(std::string filename) const;

	std::string findDirname(std::string name) const;
	std::string findBasename(std::string name) const;

public:
	IncludeParser(Configuration *config, std::vector<std::string> list);
	std::map<std::string, bool> lookForIncludedGraph(std::string path) const;
	std::map<std::string, bool> lookForInclusionGraph(std::string path) const;
	bool checkInclusionGraphChild(std::string path) const;
	bool checkIncludedGraphChild(std::string path) const;

	void addPathToAnalyze(std::string path);
};

#endif // INCLUDEPARSER_H
