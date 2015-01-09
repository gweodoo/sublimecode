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

#include "FunctionGraph.h"
#include "GraphCaller.h"
#include "TagsManager.h"

GraphCaller::GraphCaller( Configuration* myConf,TagsManager*myTagManager)


{
	if(myConf!=NULL){
		Launcher* myLauncher=new LauncherCscope(myConf,myTagManager);
		this->myLauncher=myLauncher;
	}
}	


std::vector<Tag*>* GraphCaller::getFunctionsCalledBy(Tag * tagAssociatedToFunction){

	return this->myLauncher->launchCommandExternalTool(1,tagAssociatedToFunction);
	
}

std::vector<Tag*>* GraphCaller::getFunctionsCallingThis(Tag * tagAssociatedToFunction)
{
	return this->myLauncher->launchCommandExternalTool(2,tagAssociatedToFunction);
}
std::vector<Tag*>* GraphCaller::getFilesIncludedBy(Tag * tagAssociatedToFunction)
{
	return this->myLauncher->launchCommandExternalTool(7,tagAssociatedToFunction);
}
int GraphCaller::getCountFunctionApparition(Tag * tagAssociatedToFunction)
{

	
}
int GraphCaller::getCountFunctionCalled(Tag * tagAssociatedToFunction)
{

	return (this->myLauncher->launchCommandExternalTool(1,tagAssociatedToFunction))->size();
}
int GraphCaller::getCountFunctionCalling(Tag * tagAssociatedToFunction)
{
	return (this->myLauncher->launchCommandExternalTool(2,tagAssociatedToFunction))->size();
}
int GraphCaller::getCountFunctionLength(Tag * tagAssociatedToFunction)
{

}
Launcher* GraphCaller::getLauncher()
{
return this->myLauncher;
}





GraphCaller::~GraphCaller()
{

}
