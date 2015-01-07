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
#include "GraphCaller.h"

GraphCaller::GraphCaller( Configuration* myConf)


{
	if(myConf!=NULL){
		Launcher* myLauncher=new LauncherCscope(myConf);
		this->myLauncher=myLauncher;
	}
}	


std::vector<Tag*>* GraphCaller::getFunctionsCalledBy(std::string name){

	return this->myLauncher->launchCommandExternalTool(1,name);
	
}

std::vector< Tag* >* GraphCaller::getFunctionsCallingThis(std::string name)
{
	return this->myLauncher->launchCommandExternalTool(2,name);
}
std::vector< Tag* >* GraphCaller::getFilesIncludedBy(std::string name)
{
	return this->myLauncher->launchCommandExternalTool(3,name);
}
int GraphCaller::getCountFunctionApparition(std::string name)
{

}
int GraphCaller::getCountFunctionCalled(std::string name)
{

}
int GraphCaller::getCountFunctionCalling(std::string name)
{

}
int GraphCaller::getCountFunctionLength(std::string name)
{

}
Launcher* GraphCaller::getLauncher()
{
return this->myLauncher;
}

Tag* GraphCaller::getTagByName(std::string name)
{

}



GraphCaller::~GraphCaller()
{

}
