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

#include "Runner.h"

Runner::Runner(Configuration *config) : config(config) {
	initEnvironment();
}

Runner::~Runner() {
	delete this->tagMan;
	delete this->graphResolver;
	delete this->includeResolver;
}

void Runner::initEnvironment() {
	this->tagMan = new TagsManager(config);
}

void Runner::generateContents() {
	LauncherCTags launcher(config, listFiles);
	TagsParserImpl parser(tagMan);

	launcher.generateTagsFile();

	parser.loadFromFile(config->getDestDir()+"/tags");
	this->graphResolver = new GraphCaller(config, tagMan);
	this->includeResolver = new IncludeParser(config, listFiles);
}

void Runner::setListFiles ( std::vector< std::string > list ) {
	listFiles = list;
}

std::map< std::string, bool > Runner::getFilesIncludedByThisFile ( std::string path ) {
	return this->includeResolver->lookForInclusionGraph(path);
}

std::map< std::string, bool > Runner::getFilesIncludingThisFile ( std::string path ) {
	return this->includeResolver->lookForIncludedGraph(path);
}

std::vector< Tag* >* Runner::getFunctionsCalledByThisTag ( Tag* cur ) {
	return this->graphResolver->getFunctionsCalledBy(cur);
}

std::vector< Tag* >* Runner::getFunctionsCallingThisTag ( Tag* cur ) {
	return this->graphResolver->getFunctionsCallingThis(cur);
}

Tag* Runner::findSpecificTag ( std::string name, std::string filename, size_t line ) {
	return this->tagMan->findSpecificTag(name, filename, line);
}

std::vector< Tag* >* Runner::findTagsByType ( tagType type ) {
	return this->tagMan->findTagsByType(type);
}

std::vector< Tag* >* Runner::getTagsByFile ( std::string filename ) {
	return this->tagMan->getTagsByFile(filename);
}
std::vector< Tag* >* Runner::getTagsByName ( std::string name ) {
	return this->tagMan->getTagsByName(name);
}

std::vector< std::string >* Runner::getTagNamesByType ( tagType type ) {
	return this->tagMan->getTagNamesByType(type);
}

Graph* Runner::getGraph() const {
	return graphResolver;
}

IncludeParser* Runner::getIncludeParser() const {
	return includeResolver;
}

TagsManager* Runner::getTagsManager() const {
	return tagMan;
}

int Runner::getFunctionLength ( Tag* cur ) {
	return this->graphResolver->getFunctionLength(cur);
}
