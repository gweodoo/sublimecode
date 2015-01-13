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

#include "Utils.h"
#include "mainView.h"
#include "mainwindow.h"
#include "CreateHTML.h"
#include <QApplication>
#include <QFile>
#include <QIODevice>
#include <QStyle>
#include "TagsManagerImpl.h"
#include "TagImpl.h"
#include "TagsParserImpl.h"
#include "LauncherCscope.h"
#include "LauncherCTags.h"
#include "Graph.h"
#include "GraphCaller.h"


using namespace std;

int main(int argc, char **argv){


	TagImpl tag1("tag1", "tag.c", 1034, TYPE_FUNCTION);
	TagImpl tag2("tag2", "tag.c", 66, TYPE_MEMBER);

	Configuration *myConf=new Configuration("/home/bak/Téléchargements/vlc-2.1.5","/home/bak/");
	
	TagsManagerImpl *tagMan=new TagsManagerImpl(myConf);

 LauncherCTags launcher(myConf);
   
        launcher.addPathToAnalyze("/home/bak/Téléchargements/vlc-2.1.5");
    launcher.generateTagsFile();
	TagsParserImpl tagParse(tagMan);
	tagParse.loadFromFile(myConf->getDestDir()+string("/tags"));
	
   
	//tagMan.display();
	//tagMan.findSpecificTag("OMX_MARKTYPE", "modules/codec/omxil/OMX_Types.h", 297)->display();
	//tagMan.findSpecificTag("test_init","test/libvlc/test.h",73)->display();
	//Configuration *myConf=new Configuration("/home/bak/Téléchargements/vlc-2.1.5","/home/bak/");
	
	TagsManager*myTagManager=tagMan;
	Graph* myGraph=new GraphCaller(myConf,myTagManager);
	Tag * testTag=new TagImpl("test_media_list",myConf->getSourcesDir()+string("/test/libvlc/media_list.c"),26,TYPE_FUNCTION); 
	
	//Tag * testTag=new TagImpl("libvlc_release",myConf->getSourcesDir()+string("/lib/core.c"),90,TYPE_FUNCTION);
	vector<Tag*>* listOfFunctionCalled=myGraph->getFunctionsCalledBy(testTag);
	for(int i=0;i<listOfFunctionCalled->size();i++)
	{
		
	
			vector<Tag*>*listOfFunctionCalled_2=myGraph->getFunctionsCalledBy(listOfFunctionCalled->at(i));
			
			for(int j=0;j<listOfFunctionCalled_2->size();j++)
			{  
				cout<<"function test_media_list -- " <<listOfFunctionCalled->at(i)->getName()<< " -- "<< listOfFunctionCalled_2->at(j)->getName()<<endl;
				
				
					//vector<Tag*>*listOfFunctionCalled_3=myGraph->getFunctionsCalledBy(listOfFunctionCalled_2->at(j));
					
				
				
			}
		
	}
	//cout<<" should be assert :"<<listOfFunctionCalled->at(8)<<endl;
	
	/*cout<< "size of list of  calling this function  :" <<listOfFunctionCalled->size()<<endl;
	for(int i=0;i<listOfFunctionCalled->size();i++)
	{
		cout<<"function Name "<< listOfFunctionCalled->at(i)->getName()<<endl;
	}*/
	//	myGraph->getCountFunctionCalled("Blow_up");
	//scDebug("size listOFFunctionCalled"<<listOfFunctionCalled->size());
	for(int i=0;i<listOfFunctionCalled->size();i++){ 
		cout<<"tagName : "<<listOfFunctionCalled->at(i)->getName()<<"type : "<<listOfFunctionCalled->at(i)->getFileName()<<endl;
	}
	/*MainWindow w;
	w.show();

	return a.exec();*/

}
