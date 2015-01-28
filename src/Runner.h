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

/**
 * a runner is the main object representing model interaction. The application need to go through
 * this object to access to the model. Only one runner exists per application and is forwarded between
 * classes as a <b>Runner *</b>
 */
class Runner
{
private:
	Graph* graphResolver;               /// the model object which generate function callgraph system
	IncludeParser * includeResolver;    /// object model which generate file callgraph system
	Configuration * config;             /// current global configuration for the application
	TagsManagerImpl * tagMan;           /// the tagsManager shared by the whole model
	std::vector<std::string> listFiles; /// list of selected files (@see Dialog.h) by user
public:
	/**
	 * Main constructor
	 * \param[in] config the global configuration
	 */
	Runner(Configuration *config);
	/**
	 * Init environment, instanciate global objects from model.
	 */
	void initEnvironment();
	/**
	 * generate contents : fill tagsManager from TagsParser.
	 */
	void generateContents();
	/**
	 * After selected, store list of files the user wants to analyze.
	 * \param[in] list the strings vector contaings file paths
	 */
	void setListFiles(std::vector<std::string> list);
	/**
	 * EXECUTE MODEL : From The IncludeParser, generate childs for given file path.
	 * THIS FUNCTION FINDS FILES WHICH INCLUDES GIVEN FILES (i.e. #include "path")
	 * \param[in] path the file from which childs are generated
	 * \return a map with the file name and a boolean. True if file have really been found on filesystem. False otherwise
	 */
	std::map<std::string, bool> getFilesIncludingThisFile(std::string path);
	/**
	 * EXECUTE MODEL : From The IncludeParser, generate childs for given file path.
	 * THIS FUNCTION FINDS FILES INCLUDED IN THIS FILE (i.e. #include "*" in path)
	 * \param[in] path the file from which childs are generated
	 * \return a map with the file name and a boolean. True if file have really been found on filesystem. False otherwise
	 */
	std::map<std::string, bool> getFilesIncludedByThisFile(std::string path);
	/**
	 * Get size of function definition, from its definition start line to the end (from beginning '{' to '}')
	 * \param[in] cur the tag to measure
	 * \return the number of line
	 */
	int getFunctionLength(Tag * cur);
	/**
	 * EXECUTE MODEL : From The Graph, generate childs for given tag.
	 * THIS FUNCTION FINDS TAGS WHICH CALLS the GIVEN TAG (where "cur" is called)
	 * \param[in] cur from which childs are generated
	 * \return a vector with the associated childs as tags.
	 */
	std::vector< Tag* >* getFunctionsCalledByThisTag( Tag* cur );
	/**
	 * EXECUTE MODEL : From The Graph, generate childs for given tag.
	 * THIS FUNCTION FINDS TAGS CALLED IN GIVEN TAG (which tag are present in given tag definition)
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
	TagsManagerImpl * getTagsManager() const;
	/// global destructor
	~Runner();
};

#endif // RUNNER_H
