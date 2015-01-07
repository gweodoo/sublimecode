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


std::vector<FunctionGraph*>* GraphCaller::getFunctionsCalledBy(std::string name){

	return this->myLauncher->launchCommandExternalTool(1,name);
	
}

std::vector<FunctionGraph*>* GraphCaller::getFunctionsCallingThis(std::string name)
{
	return this->myLauncher->launchCommandExternalTool(2,name);
}
std::vector<FunctionGraph*>* GraphCaller::getFilesIncludedBy(std::string name)
{
	return this->myLauncher->launchCommandExternalTool(7,name);
}
int GraphCaller::getCountFunctionApparition(std::string name)
{

	
}
int GraphCaller::getCountFunctionCalled(std::string name)
{

	return (this->myLauncher->launchCommandExternalTool(1,name))->size();
}
int GraphCaller::getCountFunctionCalling(std::string name)
{
	return (this->myLauncher->launchCommandExternalTool(2,name))->size();
}
int GraphCaller::getCountFunctionLength(std::string name)
{

}
Launcher* GraphCaller::getLauncher()
{
return this->myLauncher;
}





GraphCaller::~GraphCaller()
{

}
