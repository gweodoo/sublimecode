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
#include "TagsManagerImpl.h"
#include "Graph.h"
#include "GraphCaller.h"
#include "TagImpl.h"
#include <unistd.h>
#include "TagsParserImpl.h"
#include "LauncherCTags.h"
#include <string>

using namespace std;

const char * const CreateJson::buildTypes[] = {"Called", "Calling", "IncludedGraph", "InclusionGraph"};

CreateJson::CreateJson(Configuration *c, Graph* myGraph)
{
	//config = new Configuration(c->getSourcesDir(), c->getDestDir());
	this->config = c;
	this->myGraph = myGraph;
}

CreateJson::CreateJson(Configuration *c)
{
	this->config = c;
}


CreateJson::~CreateJson()
{

}

void CreateJson::TransformToJson(Tag * tag, std::string filepath, std::string buildType)
{/*
	TagsManagerImpl *tagMan = new TagsManagerImpl(config);
	TagsManager*myTagManager = tagMan;
	Graph* myGraph = new GraphCaller(config,myTagManager);
*/
	
/*
	TagsParserImpl tagParse(tagMan);
	tagParse.loadFromFile(config->getDestDir() + "/tags");
	qDebug() << QString::fromStdString(config->getDestDir()) + "/tags";
	
		
	//Gerener le fichier
	LauncherCTags launcher(config);
	launcher.addPathToAnalyze(config->getSourcesDir());
	launcher.generateTagsFile();
	*/
	//Tag * testTag=new TagImpl("test_media_list",myConf->getSourcesDir()+string("/test/libvlc/media_list.c"),26,TYPE_FUNCTION);	
	
	//"libvlc_InternalInit"
	//"test_media_list"
	//"libvlc_InternalCreate" 
	//"vlc_mutex_init"
	QFile file(QString::fromUtf8(filepath.c_str()));
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	
	buildItem(tag, &out, myGraph, buildType, 0);
	
	file.close();
}

void CreateJson::TransformToJson(std::string myPath, std::string filepath, IncludeParser * includeParser, std::string buildType)
{
	QFile file(QString::fromUtf8(filepath.c_str()));
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	
	std::map<std::string, bool> myMap;
	myMap.insert(std::pair<string, bool>(myPath, true));
	
	buildItem(&myMap, &out, includeParser, buildType, 0);
	
	file.close();
}

void CreateJson::buildItem(std::map<std::string, bool> * mapOfFiles, QTextStream * out, IncludeParser * includeParser, std::string buildType, int nbIterator)
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
					myMap = includeParser->lookForIncludedGraph((*it).first);
				else if (buildType == buildTypes[3])
					myMap = includeParser->lookForInclusionGraph((*it).first);
				
				if (!myMap.empty())
				{
					*out << ",\"children\": [";
					buildItem(&myMap, out, includeParser, buildType, nbIterator + 1);
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

void CreateJson::buildItem(Tag* tag, QTextStream * out, Graph * myGraph, std::string buildType, int nbIterator)
{

	qDebug() << nbIterator << " : 0    " << QString::fromStdString(tag->getName()) << "    " << QString::fromStdString(tag->getFileName());
	
	vector<Tag*>* listOfFunctions = new std::vector<Tag*>();
	
	if (buildType == buildTypes[0])
		listOfFunctions = myGraph->getFunctionsCalledBy(tag);
	else if (buildType == buildTypes[1])
		listOfFunctions = myGraph->getFunctionsCallingThis(tag);
	
	qDebug() << listOfFunctions->size();
	
	*out << "\n{";
	*out << "\"name\": \"" << QString::fromStdString(tag->getName()) << "\"," ;
	*out << "\"info\": \"" << QString::fromStdString(tag->getName()) << "\"," ;
	*out << "\"children\": [";
	buildItem(listOfFunctions, out, myGraph, buildType, nbIterator + 1);
	*out << "]}";
}

void CreateJson::buildItem(std::vector<Tag*> * tagVector, QTextStream * out, Graph * myGraph, std::string buildType, int nbIterator)
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
						listOfFunctions = myGraph->getFunctionsCalledBy(*it);
					else if (buildType == buildTypes[1])
						listOfFunctions = myGraph->getFunctionsCallingThis(*it);
					
					if (!listOfFunctions->empty())
					{
						*out << ",\"children\": [";
						buildItem(listOfFunctions, out, myGraph, buildType, nbIterator + 1);
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
