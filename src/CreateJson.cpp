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

#include "CreateJson.h"
#include <QDebug>
#include <QVariant>
#include <QFile>
#include "Configuration.h"
#include "tags/TagsManager.h"
#include <unistd.h>
#include <string>

using namespace std;

const char * const CreateJson::buildTypes[] = {"CalledGraph", "CallingGraph", "IncludedGraph", "InclusionGraph"};
	
CreateJson::CreateJson(QObject *parent) :
	QThread(parent)
{
	
}

CreateJson::~CreateJson()
{

}

void CreateJson::run()
{
	cout << myPath << endl;
	QFile file(QString::fromUtf8(filepath.c_str()));
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	
	if (buildType == buildTypes[0] || buildType == buildTypes[1]) //If it is a call graph
	{
		buildItem(tag, &out, buildType, 0);
	}
	else if (buildType == buildTypes[2] || buildType == buildTypes[3]) //If it is a include graph
	{
		std::map<std::string, bool> myMap;
		myMap.insert(std::pair<string, bool>(myPath, true)); //insert the first path
		buildItem(&myMap, &out, buildType, 0);
	}
	
	file.close();
	
	emit cjsonChanged(); //The json file has been created
}

void CreateJson::buildItem(std::map<std::string, bool> * mapOfFiles, QTextStream * out, std::string buildType, int nbIterator)
{
	qDebug() << mapOfFiles->size();
	
	std::map<std::string, bool> myMap;
	std::string nameValue;

	int wantedIterator = 3; //The number of iteration that will be shown on the graph
	
	if (nbIterator < wantedIterator) //While the current number of iteration is under the wanted one
	{
		int i = 0;
		qDebug() << nbIterator << " : " << i ;
		for(std::map<std::string, bool>::iterator it = mapOfFiles->begin(); it != mapOfFiles->end(); it++) //for each element of the map
		{
			qDebug() << nbIterator << " : " << i << "    " << QString::fromStdString((*it).first);
			
			*out << "\n{";
			nameValue = (*it).first;
			
			if ((*it).second) //If we have the information on the data
			{
				*out << "\"name\": \"" << QString::fromStdString(nameValue.erase(0, this->config->getSourcesDir().length())) << "\"";
			
				if (buildType == buildTypes[2]) //IncludedGraph
					myMap = runner->getFilesIncludedByThisFile((*it).first);
				else if (buildType == buildTypes[3]) //InclusionGraph
					myMap = runner->getFilesIncludingThisFile((*it).first);
				
				if (!myMap.empty()) //If there is no more child
				{
					*out << ",\"children\": [";
					buildItem(&myMap, out, buildType, nbIterator + 1);
					*out << "]";
				}
				else 
				{
					if (nbIterator == 0)
						*out << ", \"children\": []";
				}
			}
			else //If it is not resolved
			{
				*out << "\"name\": \"" << QString::fromStdString(nameValue) << "\"";
				*out << ", \"infofile\": \"Unresolved\"";
				*out << ", \"checked\": \"false\"";
			}
			
			*out << "}";
			
			if (i < mapOfFiles->size()-1)
			{
				*out << ",";
			}
			i++;
		}
	}
}

void CreateJson::buildItem(Tag* tag, QTextStream * out, std::string buildType, int nbIterator)
{

	qDebug() << nbIterator << " : 0    " << QString::fromStdString(tag->getName()) << "    " << QString::fromStdString(tag->getFileName());
	
	vector<Tag*>* listOfFunctions = new std::vector<Tag*>();
	
	if (buildType == buildTypes[0]) //CalledGraph
		listOfFunctions = runner->getFunctionsCalledByThisTag(tag);
	else if (buildType == buildTypes[1]) //CallingGraph
		listOfFunctions = runner->getFunctionsCallingThisTag(tag);
	
	qDebug() << listOfFunctions->size();
	
	*out << "\n{";
	*out << "\"name\": \"" << QString::fromStdString(tag->getName()) << "\", " ;
	stringstream ss;
	ss << tag->getLineNumber();
	string filename = tag->getFileName();
	*out << "\"infofile\": \"" << QString::fromUtf8(filename.c_str()) << "\", ";
	*out << "\"infoline\": \"" << QString::fromStdString(ss.str()) << "\", ";
	*out << "\"children\": [";
	buildItem(listOfFunctions, out, buildType, nbIterator + 1); //Continue with the tag's children
	*out << "]}";
}

void CreateJson::buildItem(std::vector<Tag*> * tagVector, QTextStream * out, std::string buildType, int nbIterator)
{
	qDebug() << tagVector->size();
	
	int wantedIterator = 3;
	
	if (nbIterator < wantedIterator)
	{
		int i = 0;
		
		for(vector<Tag*>::iterator it = tagVector->begin(); it != tagVector->end(); it++) //For each element of the tag vector
		{
			qDebug() << nbIterator << " : " << i << "    " << QString::fromStdString((*it)->getName()) << "    " 
			<< QString::fromStdString((*it)->getFileName());
			
			*out << "\n{";
			*out << "\"name\": \"" << QString::fromStdString((*it)->getName()) << "\"";

			if ((*it)->getFileName() != "OutOfscope") //If it is not out of our scope and we can find where it is
			{
				stringstream ss; //Used to transfor our size_t to string
				ss << (*it)->getLineNumber();
				string filename = (*it)->getFileName();
				*out << ", \"infofile\": \"" << QString::fromUtf8(filename.c_str()) << "\"";
				*out << ", \"infoline\": \"" << QString::fromStdString(ss.str()) << "\"";

// 				if (nbIterator+1 < wantedIterator)
// 				{
					vector<Tag*>* listOfFunctions = NULL;
					
					if (buildType == buildTypes[0]) //CalledGraph
						listOfFunctions = runner->getFunctionsCalledByThisTag(*it);
					else if (buildType == buildTypes[1]) //CallingGraph
						listOfFunctions = runner->getFunctionsCallingThisTag(*it);

					assert(listOfFunctions != NULL);
					if (!listOfFunctions->empty()) //If it has children
					{
						*out << ",\"children\": [";
						buildItem(listOfFunctions, out, buildType, nbIterator + 1); //Continue
						*out << "]";
					}
// 				}
			}
			else //If it is out of our scope
			{
				*out << ", \"infofile\": \"" << QString::fromStdString((*it)->getFileName()) << "\"";
			}
			
			*out << "}";
			
			if (it+1 != tagVector->end()) //If not the last one
			{
				*out << ", ";
			}
			
			i++;
		}
	}
}

void CreateJson::setConfiguration(Configuration * config)
{
	this->config = config;
}

void CreateJson::setRunner(Runner * Runner)
{
	this->runner = Runner;
}

void CreateJson::setCallGraphParams(Tag * tag, std::string filepath, std::string buildType)
{
	this->tag = tag;
	this->filepath = filepath;
	this->buildType = buildType;
}

void CreateJson::setIncludeGraphParams(std::string myPath, std::string filepath, std::string buildType)
{
	this->myPath = myPath;
	this->filepath = filepath;
	this->buildType = buildType;
}
