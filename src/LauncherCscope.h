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
#include "TagIdentifier.h"

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
	 TagIdentifier* myTagIdentifier;
	 TagsManager* myTagManager;
	 bool isLaunched;
	 Configuration* myConfiguration;
	 std::vector<Tag*>*listOfLastTagAsked ;
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
	int getLineForEndOfFunctionDefinition(Tag* tagAssociatedToFunction);
	void removeNotMatchingFunctionOnArgumentNumber(FunctionGraph* calledFunctionToFind, std::vector< FunctionGraph* >* listOfGlobalDefinitions, std::vector< std::vector< std::string >* >* listOfTypesforGlobalDefinitions);
	void removeMatchesFromHAndC(std::vector<std::vector<std::string>*>* listOfTypes,std::vector<FunctionGraph*>* listOfGlobalDefinitions);
	void removeMatchesFromHAndC(std::vector<FunctionGraph*>* listOfGlobalDefinitions);
	void removeFromListFunctionNotBelonginToStackCall( int lineStart,int lineStop,std::vector<FunctionGraph*>* listOfFunctionCalled,Tag * functionAssociatedToTag);
	bool isValidCaracter(char& caracterToTest);
	Tag * getTagFromFunctionGraphOutput(FunctionGraph* outputFunction);
	int  getNumberOfVariableUsedInFunctionCall(FunctionGraph* calledFunctionToFind);
	 void removeNotConcernedDefinitionBasedOnFileName(std::vector< FunctionGraph* >* listOfGlobalDefinitions,Tag * tagAssociatedToFunction);
	 FunctionGraph* removeNotConcernedDefinitionBaseInLineNumer(std::vector< FunctionGraph* >* listOfGlobalDefinitions, Tag* tagAssociatedToFunction);
	
	
	
public :
	
	 LauncherCscope(Configuration* myconfiguration,TagsManager* myTagManager);
	 bool initExternalTool();
	 bool closeExternalTool();
	 std::vector<Tag*>* launchCommandExternalTool(int command, Tag * tagAssociatedToFunction);
	 bool getIsLaunched();
	 

};
#endif