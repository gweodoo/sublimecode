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

#include "inclusiongraph/IncludeParser.h"

#include "GraphCaller.h"

#include "tags/LauncherCTags.h"
#include "tags/TagsParser.h"
#include "tags/TagsManager.h"
#include "stats/StatsParser.h"
#include "stats/StatsProjectInfo.h"

#include <QThread>

/**
 * a runner is the main object representing model interaction. The application need to go through
 * this object to access to the model. Only one runner exists per application and is forwarded between
 * classes as a <b>Runner *</b>
 */
class Runner : public QThread
{
	Q_OBJECT
	
private:
	Graph* graphResolver;               /// the model object which generate function callgraph system
	IncludeParser * includeResolver;    /// object model which generate file callgraph system
	Configuration * config;             /// current global configuration for the application
	TagsManager * tagMan;               /// the tagsManager shared by the whole model
	StatsParser * statsResolver;        /// Stats generator for the home page
	StatsProjectInfo * projectInfo;     /// projects mains stats for home page
	std::vector<std::string> listFiles; /// list of selected files (@see Dialog.h) by user
public:
	/**
	 * default constructor
	 * \param[in] parent a QObject needed to make runner threaded.
	 */
	explicit Runner(QObject *parent = 0);
	/**
	 * set global class members
	 * \param[in] config global current configuration
	 * \param[in] list list of selected files
	 */
	void initEnvironment(Configuration *config, std::vector< std::string > list);
	/**
	 * As a thread, start project analysis
	 */
	void run();
	/**
	 * EXECUTE MODEL : From The IncludeParser, generate childs for given file path.
	 * THIS FUNCTION FINDS FILES INCLUDED IN THIS FILE (i.e. #include "*" in path)
	 * \param[in] path the file from which childs are generated
	 * \return a map with the file name and a boolean. True if file have really been found on filesystem. False otherwise
	 */
	std::map<std::string, bool> getFilesIncludedByThisFile(std::string path);
	/**
	 * EXECUTE MODEL : From The IncludeParser, generate childs for given file path.
	 * THIS FUNCTION FINDS FILES WHERER THIS FILE IS INCLUDED (i.e. #include "path")
	 * \param[in] path the file from which childs are generated
	 * \return a map with the file name and a boolean. True if file have really been found on filesystem. False otherwise
	 */

	std::map< std::string, bool > getFilesIncludingThisFile ( std::string path );

	/* Launcher CScope */
	/**
	 * Get size of function definition, from its definition start line to the end (from beginning '{' to '}')
	 * \param[in] cur the tag to measure
	 * \return the number of line
	 */
	int getFunctionLength(Tag * cur);

	/* TAG MANAGER */
	/**
	 * EXECUTE MODEL : From The Graph, generate childs for given tag.
	 * THIS FUNCTION FINDS TAGS CALLED IN GIVEN TAG (which tag are present in given tag definition)
	 * \param[in] cur from which childs are generated
	 * \return a vector with the associated childs as tags.
	 */
	std::vector< Tag* >* getFunctionsCalledByThisTag( Tag* cur );
	/**
	 * EXECUTE MODEL : From The Graph, generate childs for given tag.
	 * THIS FUNCTION FINDS TAGS WHICH CALLS the GIVEN TAG (where "cur" is called)
	 * \param[in] cur from which childs are generated
	 * \return a vector with the associated childs as tags.
	 */
	std::vector< Tag* >* getFunctionsCallingThisTag( Tag* cur );
	/**
	 * retrieve a tag, according to its main information : name, filename and file definition
	 * \param[in] name the tag name
	 * \param[in] filename the tag filename
	 * \param[in] line the tag definition line
	 * \return a tag pointer if the tag exists in tag manager
	 * \return NULL otherwise
	 */
	Tag* findSpecificTag ( std::string name, std::string filename, size_t line );
	/**
	 * retrieve tags according to a specific type
	 * \param[in] type the given type
	 * \return a tag pointer vector pointer if type exists
	 * \return NULL otherwise
	 */
	std::vector<Tag*>* findTagsByType(tagType type);
	/**
	 * retrieve tags according to a specific type, results are string array.
	 * \param[in] type the given type
	 * \return a tag vector pointer if at least one tag matches.
	 * \return NULL otherwise
	 */
	std::vector<std::string>* getTagNamesByType(tagType type);
	/**
	 * retrieve tags according to a specific name
	 * \param[in] name the given name
	 * \return a tag pointer vector pointer if at least one tag matches
	 * \return NULL otherwise
	 */
	std::vector<Tag*>* getTagsByName(std::string name);
	/**
	 * retrieve tags according to a specific file
	 * \param[in] filename the given filename
	 * \return a tag pointer vector pointer if file exists
	 * \return NULL otherwise
	 */
	std::vector<Tag*>* getTagsByFile(std::string filename);
	/**
	 * getter on graph class member
	 * \deprecated
	 * \return a Graph pointer
	 */
	Graph*  getGraph() const;
	/**
	 * Getter on IncludeParser class member
	 * \deprecated
	 * \return IncludeParser pointer
	 */
	IncludeParser * getIncludeParser() const;
	/**
	 * Getter on current tag manager
	 * \deprecated
	 * \return a TagsManager pointer
	 */
	TagsManager* getTagsManager() const;
	/**
	 * get statistics for front page. Get 10 most code-filled file for given language
	 * \param[in] language the language to analyze
	 * \return vector (ordered) of key(string,int), representing the file and its code lines number
	 */
	std::vector<std::pair<std::string, int > > getStatsPerLanguage( std::string language ) const;
	/**
	 * get most present languages
	 * \return a vector (ordered) of pair(string,float) representing the language name and the number of code lines about it
	 */
	std::vector<std::pair<std::string, float> > getStatsAboutLanguages() const;
	/**
	 * get statistics for front page. Get 10 most tags definition-filled files
	 * \return vector (ordered) of key(string,int), representing the file and its tags number
	 */
	std::vector<std::pair<std::string, int > > getStatsPerFile() const;
	/**
	 * Get global infos about the project. The rsult is a map of strings, which contains the type of value (authors...) and the value
	 * \return a strings map with a (key;value) combination for each data
	 */
	std::map< std::string, std::string > getProjectInfos() const;
	/// global destructor
	~Runner();
	
signals:
	void runnerChanged();
	
};

#endif // RUNNER_H
