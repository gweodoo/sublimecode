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
#include "Runner.h"
#include "Configuration.h"
#include "inclusiongraph/IncludeParser.h"
#include <string>
#include <QThread>

class CreateJson : public QThread
{
	Q_OBJECT
	
public:
	static const char * const buildTypes[]; //The different types of graphs
	
	/**
	 * Default constructor
	 */
	explicit CreateJson(QObject *parent = 0);
	
	/**
	 * Default destructor
	 */
	~CreateJson();
	
	/**
	 * Starts the thread
	 * Depending on the wanted type of graph launch the process 
	 */
	void run();
	
	/**
	 * Building the json file with a vector of tags (call graphs)
	 * \param[in] tagVector The vector of tags
	 * \param[in] out QTextStream to write in the file
	 * \param[in] buildType the wanted type of graph
	 * \param[in] nbIterator current number of iterations
	 */
	void buildItem(std::vector<Tag*> * tagVector, QTextStream * out, std::string buildType, int nbIterator);
	
	/**
	 * Building the json file with a tag (call graphs)
	 * \param[in] tag The tag
	 * \param[in] out QTextStream to write in the file
	 * \param[in] buildType the wanted type of graph
	 * \param[in] nbIterator current number of iterations
	 */
	void buildItem(Tag* tag, QTextStream * out, std::string buildType, int nbIterator);
	
	/**
	 * Building the json file with a map (include graphs)
	 * \param[in] tag The tag
	 * \param[in] out QTextStream to write in the file
	 * \param[in] buildType the wanted type of graph
	 * \param[in] nbIterator current number of iterations
	 */
	void buildItem(std::map<std::string, bool> * mapOfFiles, QTextStream * out, std::string buildType, int nbIterator);
	
	/**
	 * Setting current configuration
	 * \param[in] config The configuration
	 */
	void setConfiguration(Configuration * config);
	
	/**
	 * Setting current runner
	 * \param[in] runner The runner
	 */
	void setRunner(Runner * runner);
	
	/**
	 * Setting the needed parameters in order to generate the json for a call graph
	 * \param[in] tag The tag
	 * \param[in] filepath The path where the file will be created
	 * \param[in] buildType the wanted type of graph
	 */
	void setCallGraphParams(Tag * tag, std::string filepath, std::string buildType);
	void setIncludeGraphParams(std::string myPath, std::string filepath, std::string buildType);
	
private:
	Configuration *config; ///< The current configuration
	Runner * runner;       ///< The current runner
	Tag * tag;             ///< The current tag
	std::string filepath;  ///< The current filepath
	std::string buildType; ///< The current buildType
	std::string myPath;    ///< The current path
signals:
	/**
	 * Signal when the json process has finished
	 */
	void cjsonChanged();
	
};

#endif // CREATEJSON_H
