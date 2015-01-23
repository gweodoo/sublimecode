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

#ifndef LAUNCHERCSCOPE_H
#define LAUNCHERCSCOPE_H
#include "Configuration.h"
#include"Launcher.h"
#include "Tag.h"
#include "TagsManager.h"
#include "FunctionGraph.h"
#include "CscopeThreadObject.h"

void* FindFunctionDefinitionInThread(void* listOfCscopeOutput);
/**
 * class implementing the Launcher interface specificly to cscope
 */
class LauncherCscope: public  Launcher {

private :
	
	/**
	 * myTagManager - needed for searching specific tag given a function name and its line
	 * isLaunched - needed internally tin order to know if the cscope db is already constructed
	 * myConfiguration - need to know information about where sources are and the working directory
	 * 
	 */
	
	 TagsManager* myTagManager;
	 bool isLaunched;
	 Configuration* myConfiguration;
	 std::vector<Tag*>*listOfLastTagAsked ;
	 CscopeThreadObject* MyCscopeThreadObject;
	 /**
	  * need internally for parsing cscope output
	  */
	std::vector<FunctionGraph*>* cscopeOutputParser(std::string output);
	std::vector<FunctionGraph*>* getGlobalDefinitionsFrom(std::string nameOfFunction);
	void removeNotFunctionOutput(std::vector<FunctionGraph*>* listOfGlobalDefinitions);
	std::vector<std::vector<std::string>*>* getNumberOfArgumentAndTypeForFunction(std::vector<FunctionGraph*>* listOfGlobalDefinitions);
	std::string getArgumentType(std::string  argumentAndTypeToParse);
	std::string launchExternalTool(int command, std::string arg);
	std::string removeSpaceFromString(std::string stringToParse);
	std::vector<std::string>* getTypeForVariableUsedInFunctionCall(FunctionGraph* calledFunctionToFind);
	std::vector<std::string>* getVariablesNamesInFunctionCall(std::string callExpression);
	
	void removeNotMatchingFunctionOnArgumentNumber(FunctionGraph* calledFunctionToFind, std::vector< FunctionGraph* >* listOfGlobalDefinitions, std::vector< std::vector< std::string >* >* listOfTypesforGlobalDefinitions);
	void removeMatchesFromHAndC(std::vector<std::vector<std::string>*>* listOfTypes,std::vector<FunctionGraph*>* listOfGlobalDefinitions);
	void removeMatchesFromHAndC(std::vector<FunctionGraph*>* listOfGlobalDefinitions);
	void removeFromListFunctionNotBelonginToStackCall( int lineStart,int lineStop,std::vector<FunctionGraph*>* listOfFunctionCalled,Tag * functionAssociatedToTag);
	bool isValidCaracter(char& caracterToTest);

	int  getNumberOfVariableUsedInFunctionCall(FunctionGraph* calledFunctionToFind);
	 void removeNotConcernedDefinitionBasedOnFileName(std::vector< FunctionGraph* >* listOfGlobalDefinitions,std::string fileName);
	 FunctionGraph* removeNotConcernedDefinitionBaseInLineNumer(std::vector< FunctionGraph* >* listOfGlobalDefinitions, Tag* tagAssociatedToFunction);
	std::vector<FunctionGraph*>* egrepOutputParser(std::string output,std::string fileName);
	
	
public :
	
	 LauncherCscope(Configuration* myconfiguration,TagsManager* myTagManager);
	 bool initExternalTool();
	 bool closeExternalTool();
	 int getLineForEndOfFunctionDefinition(Tag* tagAssociatedToFunction);
	 
	 std::vector<Tag*>* launchCommandExternalTool(int command, Tag * tagAssociatedToFunction);
	 std::vector<std::string >* launchCommandExternalTool(int command, std::string  fileName);
	 int launchCommandExternalTool(Tag *tagAssociatedToFunction);
	 bool getIsLaunched();
	 CscopeThreadObject * getCscopeThreadObject();
	 void setCscopeThreadObject(CscopeThreadObject* threadObj);
	 	Tag * getTagFromFunctionGraphOutput(FunctionGraph* outputFunction);

};

#endif