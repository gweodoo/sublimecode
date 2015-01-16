/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

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
CreateJson::CreateJson()
{
	
}

CreateJson::~CreateJson()
{

}

void CreateJson::TransformToJson(Tag * tag)
{
	Configuration * myConf = new Configuration("/home/ubuntu/Téléchargements/vlc-2.1.5","/home/ubuntu/Téléchargements/");
	TagsManagerImpl *tagMan = new TagsManagerImpl(myConf);
	TagsManager*myTagManager = tagMan;
	Graph* myGraph = new GraphCaller(myConf,myTagManager);
	/*
	//Gerener le fichier
	LauncherCTags launcher(myConf);
	launcher.addPathToAnalyze("/home/ubuntu/Téléchargements/vlc-2.1.5");
	launcher.generateTagsFile();
	*/

	TagsParserImpl tagParse(tagMan);
	tagParse.loadFromFile("/home/ubuntu/Téléchargements/tags");
	
	Tag * testTag=new TagImpl("test_media_list",myConf->getSourcesDir()+string("/test/libvlc/media_list.c"),26,TYPE_FUNCTION);	
	
	//"libvlc_InternalInit"
	//"test_media_list"
	//"libvlc_InternalCreate" 
	//"vlc_mutex_init"
	
	QFile file("callGraph2.json");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	
	buildItem(testTag, &out, myGraph, 0);
	
	file.close();
}

void CreateJson::buildItem(Tag* tag, QTextStream * out, Graph * myGraph, int nbIterator)
{
	qDebug() << nbIterator << " : 0    " << QString::fromStdString(tag->getName()) << "    " << QString::fromStdString(tag->getFileName());
	
	vector<Tag*>* listOfFunctionCalled = myGraph->getFunctionsCalledBy(tag);

	qDebug() << listOfFunctionCalled->size();
	
	*out << "\n{";
	*out << "\"name\": \"" << QString::fromStdString(tag->getName()) << "\"," ;
	*out << "\"info\": \"" << QString::fromStdString(tag->getName()) << "\"," ;
	*out << "\"children\": [";
	buildItem(listOfFunctionCalled, out, myGraph, nbIterator + 1);
	*out << "]}";
}

void CreateJson::buildItem(std::vector<Tag*> * tagVector, QTextStream * out, Graph * myGraph, int nbIterator)
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
				*out << ",\"info\": \" In the file " << QString::fromStdString((*it)->getFileName()) << " at line "
				<< QString::fromStdString(ss.str())<< "\"";
				
				//if (nbIterator < (wantedIterator -1))
				//{
					vector<Tag*>* listOfFunctionCalled = myGraph->getFunctionsCalledBy(*it);
					
					if (!listOfFunctionCalled->empty())
					{
						*out << ",\"children\": [";
						buildItem(listOfFunctionCalled, out, myGraph, nbIterator + 1);
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
