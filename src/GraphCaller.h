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
#include "TagsManager.h"
#include "Tag.h"
/**
 * Object Implementing the Graph interface specific to Cscope
 */
class GraphCaller:public Graph
{
public:
	/**
	 * constructor
	 */
	GraphCaller (Configuration * myConf,TagsManager*myTagManager);
	/**
	 * destructor
	 */
	~GraphCaller();
	/**
	 * getter
	 */
	Launcher* getLauncher();
	/**
	 * functions implementing the Graph Interface
	 */
	std::vector<Tag*>* getFunctionsCalledBy(Tag* name);
	std::vector<Tag*>* getFunctionsCallingThis(Tag* name);
	std::vector<Tag*>* getFilesIncludedBy(Tag* name);
	
	int getCountFunctionApparition(Tag* name);
	int getCountFunctionLength(Tag* name);
	int getCountFunctionCalled(Tag* name);
	int getCountFunctionCalling(Tag* name);
	

private:
	/**
	 * only attribute Launcher
	 */
	Launcher* myLauncher;
	
	
};


#endif // GRAPHCALLER_H