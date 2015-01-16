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
	int getFunctionLength(Tag * tagAssociatedToFunction);
	std::vector<std::string>* getFilesIncludedBy(std::string name);
	
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
