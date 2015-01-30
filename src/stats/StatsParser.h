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
#ifndef CLOCPARSER_H
#define CLOCPARSER_H

#include "../Utils.h"
#include "StatsFileItem.h"
#include "StatsLanguageItem.h"
#include "../tags/TagsManager.h"

/**
 * StatsParser is the main stats handler for sublime code. It analyzes and
 * parse data from Cloc execution and store it in its own structure.
 */
class StatsParser {
private:
	std::vector<StatsLanguageItem*> tabLanguages; ///< list of project languages
	std::vector<StatsFileItem*> tabFiles;         ///< list of project sources files
	TagsManager* tagMan;                          ///< global TagsManager where tags are stored
	Configuration *config;                        ///< main configuration

public:
	/**
	 * default constructor
	 * \param[in] config main configuration
	 * \param[in] tagMan a pointer to the main tagsManager
	 */
	StatsParser( Configuration* config, TagsManager* tagMan );
	/**
	 * launch cloc and generate data from its output
	 */
	void load();
	///object displayer
	void display() const;
	/**
	 * STATS generator : get 10 files with the most lines of code for given language
	 * \param[in]  language the given to language to filter
	 * \return a vector (ordered) containing pair with the name of the files and number of code lines in it
	 */
	std::vector<std::pair<std::string, int > > getMostImplementedFilesPerLanguage( std::string language ) const;
	/**
	 * STATS generator : get 10 most present languages in the project
	 * \return a vector (ordered) containing the language and the number of languages belongs to it
	 */
	std::vector<std::pair<std::string, float> > getMostUsedLanguages() const;
	/**
	 * STATS generator : get 10 files with the most tags in it.
	 * \return a vector (ordered) containing pari with the name of the file and number of tags in it
	 */
	std::vector<std::pair<std::string, int > > getNbTagsPerFile() const;
	///default destructor
	~StatsParser();
};

#endif // CLOCPARSER_H
