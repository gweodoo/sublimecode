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

#ifndef CREATEJSON_H
#define CREATEJSON_H

#include <vector>
#include <QDebug>
#include <QVariant>
#include <QFile>
#include "tags/Tag.h"
#include "Graph.h"
#include "Configuration.h"
#include "inclusiongraph/IncludeParser.h"
#include <string>

class CreateJson {
	
public:
	static const char * const buildTypes[];
	explicit CreateJson(Configuration *c, Graph* myGraph);
	CreateJson(Configuration *c);
	~CreateJson();
	void TransformToJson(Tag * tag, std::string filepath, std::string buildType);
	void TransformToJson(std::string myPath, std::string filepath, IncludeParser * includeParser, std::string buildType);
	void buildItem(std::vector<Tag*> * tagVector, QTextStream * out, Graph * myGraph, std::string buildType, int nbIterator);
	void buildItem(Tag* tag, QTextStream * out, Graph * myGraph, std::string buildType, int nbIterator);
	void buildItem(std::map<std::string, bool> * mapOfFiles, QTextStream * out, IncludeParser * includeParser, std::string buildType, int nbIterator);
	
private:
	Configuration *config;
	Graph* myGraph;
};

#endif // CREATEJSON_H
