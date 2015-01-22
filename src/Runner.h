/***************************************************************************/
/*                                                                        */
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

#ifndef RUNNER_H
#define RUNNER_H

#include "Configuration.h"
#include "handler/SvnVcsHandler.h"
#include "handler/GitVcsHandler.h"
#include "handler/MercurialVcsHandler.h"
#include "handler/Tarbz2TarballHandler.h"
#include "handler/TargzTarballHandler.h"
#include "handler/ZipTarballHandler.h"

#include "stats/StatsParser.h"
#include "inclusiongraph/IncludeParser.h"

#include "GraphCaller.h"
#include "LauncherCTags.h"

#include "TagsParserImpl.h"
#include "TagsManagerImpl.h"

class Runner
{
private:
	GraphCaller * graphResolver;
	IncludeParser * includeResolver;
	Configuration * config;
	TagsManagerImpl * tagMan;

	std::vector<std::string> listFiles;
public:
	Runner(Configuration *config);
	void initEnvironment();
	void generateContents();
	void setListFiles(std::vector<std::string> list);
	std::vector< Tag* >* getFunctionsCalledByThisTag( Tag* cur );
	std::vector< Tag* >* getFunctionsCallingThisTag( Tag* cur );
	std::map<std::string, bool> getFilesIncludingThisFile(std::string path);
	std::map<std::string, bool> getFilesIncludedByThisFile(std::string path);

	/* Launcher CScope */
	int getFunctionLength(Tag * cur);

	/* TAG MANAGER */
	Tag* findSpecificTag ( std::string name, std::string filename, size_t line );
	std::vector<Tag*>* findTagsByType(tagType type);
	std::vector<Tag*>* getTagsByName(std::string name);
	std::vector<Tag*>* getTagsByFile(std::string filename);
	std::vector<std::string>* getTagNamesByType(tagType type);

	/* GETTERS */
	GraphCaller *  getGraphCaller() const;
	IncludeParser * getIncludeParser() const;
	TagsManagerImpl * getTagsManager() const;
};

#endif // RUNNER_H
