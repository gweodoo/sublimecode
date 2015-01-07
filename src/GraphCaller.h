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
#ifndef GRAPHCALLER_H
#define GRAPHCALLER_H
#include "Graph.h"
#include "Launcher.h"
#include "LauncherCscope.h"
#include "Configuration.h"
class GraphCaller:public Graph
{
public:
	
	~GraphCaller();
	Launcher* getLauncher();
	std::vector<Tag*>*  getFunctionsCalledBy(std::string name);
	std::vector<Tag*>* getFunctionsCallingThis(std::string name);
	std::vector<Tag*>* getFilesIncludedBy(std::string name);
	Tag* getTagByName(std::string name);
	int getCountFunctionApparition(std::string name);
	int getCountFunctionLength(std::string name);
	int getCountFunctionCalled(std::string name);
	int getCountFunctionCalling(std::string name);
	GraphCaller (Configuration * myConf);

private:
	Launcher* myLauncher;
	
	
};


#endif // GRAPHCALLER_H
