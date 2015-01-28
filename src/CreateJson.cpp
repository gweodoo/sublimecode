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

const char * const CreateJson::buildTypes[] = {"Called", "Calling", "IncludedGraph", "InclusionGraph"};
	
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
	
	if (buildType == "Called" || buildType == "Calling")
	{
		buildItem(tag, &out, buildType, 0);
	}
	else if (buildType == "IncludedGraph" || buildType == "InclusionGraph")
	{
		std::map<std::string, bool> myMap;
		myMap.insert(std::pair<string, bool>(myPath, true));
		buildItem(&myMap, &out, buildType, 0);
	}
	
	file.close();
	
	emit cjsonChanged();
}

void CreateJson::buildItem(std::map<std::string, bool> * mapOfFiles, QTextStream * out, std::string buildType, int nbIterator)
{
	qDebug() << mapOfFiles->size();
	
	std::map<std::string, bool> myMap;
	std::string nameValue;

	int wantedIterator = 3;
	
	if (nbIterator < wantedIterator)
	{
		int i = 0;
		qDebug() << nbIterator << " : " << i ;
		for(std::map<std::string, bool>::iterator it = mapOfFiles->begin(); it != mapOfFiles->end(); it++)
		{
			qDebug() << nbIterator << " : " << i << "    " << QString::fromStdString((*it).first);
			
			*out << "\n{";
			nameValue = (*it).first;
			
			if ((*it).second)
			{
				*out << "\"name\": \"" << QString::fromStdString(nameValue.erase(0, this->config->getSourcesDir().length())) << "\"";
			
				if (buildType == buildTypes[2])
					myMap = runner->getIncludeParser()->lookForIncludedGraph((*it).first);
				else if (buildType == buildTypes[3])
					myMap = runner->getIncludeParser()->lookForInclusionGraph((*it).first);
				
				if (!myMap.empty())
				{
					*out << ",\"children\": [";
					buildItem(&myMap, out, buildType, nbIterator + 1);
					*out << "]";
				}
				else 
				{
					if (nbIterator == 0)
						*out << ",\"children\": []";
				}
			}
			else 
			{
				*out << "\"name\": \"" << QString::fromStdString(nameValue) << "\"";
				*out << ",\"info\": \"Unresolved\"";
				*out << ",\"checked\": \"false\"";
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
	
	if (buildType == buildTypes[0])
		listOfFunctions = runner->getFunctionsCalledByThisTag(tag);
	else if (buildType == buildTypes[1])
		listOfFunctions = runner->getFunctionsCallingThisTag(tag);
	
	qDebug() << listOfFunctions->size();
	
	*out << "\n{";
	*out << "\"name\": \"" << QString::fromStdString(tag->getName()) << "\"," ;
	*out << "\"info\": \"" << QString::fromStdString(tag->getName()) << "\"," ;
	*out << "\"children\": [";
	buildItem(listOfFunctions, out, buildType, nbIterator + 1);
	*out << "]}";
}

void CreateJson::buildItem(std::vector<Tag*> * tagVector, QTextStream * out, std::string buildType, int nbIterator)
{
	qDebug() << tagVector->size();
	
	int wantedIterator = 3;
	
	if (nbIterator < wantedIterator)
	{
		int i = 0;
		
		for(vector<Tag*>::iterator it = tagVector->begin(); it != tagVector->end(); it++)
		{
			qDebug() << nbIterator << " : " << i << "    " << QString::fromStdString((*it)->getName()) << "    " 
			<< QString::fromStdString((*it)->getFileName());
			
			*out << "\n{";
			*out << "\"name\": \"" << QString::fromStdString((*it)->getName()) << "\"";

			if ((*it)->getFileName() != "OutOfscope")
			{
				stringstream ss;
				ss << (*it)->getLineNumber();
				string filename = (*it)->getFileName();
				*out << ",\"info\": \" In the file " << QString::fromUtf8(filename.c_str()) << " at line "
// 				*out << ",\"info\": \" In the file " << QString::fromStdString((*it)->getFileName()) << " at line "
				<< QString::fromStdString(ss.str())<< "\"";
				
				//if (nbIterator < (wantedIterator -1))
				//{
					vector<Tag*>* listOfFunctions = new std::vector<Tag*>();
					
					if (buildType == buildTypes[0]) 
						listOfFunctions = runner->getFunctionsCalledByThisTag(*it);
					else if (buildType == buildTypes[1])
						listOfFunctions = runner->getFunctionsCallingThisTag(*it);
					
					if (!listOfFunctions->empty())
					{
						*out << ",\"children\": [";
						buildItem(listOfFunctions, out, buildType, nbIterator + 1);
						*out << "]";
					}
				//}
			}
			else
			{
				*out << ",\"info\": \"" << QString::fromStdString((*it)->getFileName()) << "\"";
			}
			
			*out << "}";
			
			if (it+1 != tagVector->end())
			{
				*out << ",";
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
