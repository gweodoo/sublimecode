/*
 * Copyright 2015 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
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
