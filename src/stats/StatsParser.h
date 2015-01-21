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
#include "../TagsManagerImpl.h"

class StatsParser {
private:
	std::vector<StatsLanguageItem*> tabLanguages;
	std::vector<StatsFileItem*> tabFiles;
	TagsManager* tagMan;
	Configuration *config;

	StatsLanguageItem const * findLanguage(std::string name) const;
public:
	StatsParser( Configuration* config, TagsManager* tagMan );
	void loadFrom(std::string path);
	void display() const;
	vector< pair< string, int > > getMostImplementedFilesPerLanguage( string language ) const;
	std::vector<std::pair<std::string, float> > getMostUsedLanguages() const;
	vector< pair< string, int > > getNbTagsPerFile() const;
};

#endif // CLOCPARSER_H
