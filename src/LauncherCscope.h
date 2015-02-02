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
#include "tags/Tag.h"
#include "tags/TagsManager.h"
#include "FunctionGraph.h"

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
	
	/**
	* parse the output from a cscope command
	* and return a vector of Function Graph Object (functionName-fileName-call's line- signature)
	* @param[in] output the cscope's output to parse
	* @return a vector of FunctionGraph object containing the parsed cscope output
	*/
	std::vector<FunctionGraph*>* cscopeOutputParser(std::string output);
	/**
	* first step to get the right function definition for the calledFunction from CScope
	* get the global definitions found by Cscope
	* @param[in] nameOfFunction the name of the function to search the right definition on
	* @return list of definition found by cscope after being parsed
	*/
	std::vector<FunctionGraph*>* getGlobalDefinitionsFrom(std::string nameOfFunction);
	
	/**
	* step - 2
	* second step remove from the list the definition which are not function definitions and which are #define aliases
	* @param[in] listOfGlobalDefinitions the list of definitions on which we remove the not function output given by cscope
	* 
	*/
	void removeNotFunctionOutput(std::vector<FunctionGraph*>* listOfGlobalDefinitions);
	/**
	* step - 3
	* third step will look at the number of Argument and its type for each function graph
	* return a vector of vector. the vector contains the type of argument and a vector containing all the vector of type 
	* after this step we have two differents object: vector<FunctionGraph*>* containing the global definitions of the called function
	*						: vector<std::vector<std::string>*>* containing the list of argument type for each FunctionGraph
	* @param[in] listOfGlobalDefinitions the lift of definition to treat
	* @return a vector of vector containing the type of argument for each definition
	*/
	std::vector<std::vector<std::string>*>* getNumberOfArgumentAndTypeForFunction(std::vector<FunctionGraph*>* listOfGlobalDefinitions);
	/**
	* exemple  (const char *) -> (constchar*)
	* function here to parse a string composed af an argument and its type 
	* return the type only
	* @param[in] argumentAndTypeToParse the string to parse in order to get the type of argument
	* @return the type of the argument
	*/
	std::string getArgumentType(std::string  argumentAndTypeToParse)
	/**
	* function which makes the system calls in order to execute cscope
	* @param[in] command the number crreponsding to the command to execute, argument need by cscope
	* @param[in] command the argument describing the name need by cscope
	*/;
	std::string launchExternalTool(int command, std::string arg);
	/**
	* remove all space from a string
	* @param[in] stringToParse the string to remove the space from
	* @return the string whithout space
	*/
	std::string removeSpaceFromString(std::string stringToParse);
	/**
	* returns the list of variable's type for on function called
	* ["ml","md"] ----> ["int","void *"]
	* @param[in] calledFunctionToFind cscope's output's line to search the variable in
	* @return a vector of string containing all the type of variables
	*/
	std::vector<std::string>* getTypeForVariableUsedInFunctionCall(FunctionGraph* calledFunctionToFind);
	/**
	* returns the list of variable's name for on function called
	* example libvlc_media_list_add_media( ml, md) ----> ["ml","md"]
	* @param[in] callExpression the call expression to parse
	* @return vector of string corresponding to the name of each param in the call
	*/
	std::vector<std::string>* getVariablesNamesInFunctionCall(std::string callExpression);
	
	/**
	* remove the not matchings definition of a function towards the number of argument
	* if in the the list we have myFunction(var_1,var_2,var_3)
	* 			      myFunction(var_1,var_2)
	* 	and the number of argument is 2 we remove the first one
	* @param[in] calledFunctionToFind cscope's output's line to compare with
	* @param[in] listOfGlobalDefinitions the list of cscope's ouput to sort 
	*/
	void removeNotMatchingFunctionOnArgumentNumber(void* calledFunctionToFind, std::vector< FunctionGraph* >* listOfGlobalDefinitions, std::vector< std::vector< std::string >* >* listOfTypesforGlobalDefinitions, int arg);
	/**
	*in the case where we have the same definition for a function ( com from .h and .c  )
	* @param[in] listOfTypes vector of vector containing the list of type for each definition
	* @param[in] listOfGlobalDefinitions list of definitions to sort 
	*/
	void removeMatchesFromHAndC(std::vector<std::vector<std::string>*>* listOfTypes,std::vector<FunctionGraph*>* listOfGlobalDefinitions);
	
	/**
	* remove the .h function definition from the function called list
	* @param[in] listOfGlobalDefinitions list of function definition to sort
	* 
	*/
	void removeMatchesFromHAndC(std::vector<FunctionGraph*>* listOfGlobalDefinitions);
	/**
	* this function removes from the function called which do not belong to the function 
	* @param[in] lineStart the line where the function definition starts
	* @param[in] lineStop the line where the function definition stops
	* @param[in] listOfFunctionCalled the list of function definition to sort
	* @param[in] listOfFunctionCalled function definition to compare with
	*/
	void removeFromListFunctionNotBelonginToStackCall( int lineStart,int lineStop,std::vector<FunctionGraph*>* listOfFunctionCalled,void * functionAssociatedToTag,int argForSensOfUse);
	/**
	* check if the char is a valid one it means between a-zA-Z0-9
	* @param[in] caracterToTest the char to check
	* @return the boolean 
	*/
	bool isValidCaracter(char& caracterToTest);

	/**
	* return the number of variable used for the function call
	* @param[in] calledFunctionToFind cscope's output's line to search the variable in
	* @return the size of the list of variables
	*/
	int  getNumberOfVariableUsedInFunctionCall(FunctionGraph* calledFunctionToFind);
	/**
	* removes not matching function definition based on file Name et function line
	* @param[in] listOfGlobalDefinitions list of function definition to sort
	* @param[in] fileName the fine Name to compare with
	*/
	void removeNotConcernedDefinitionBasedOnFileName(std::vector< FunctionGraph* >* listOfGlobalDefinitions,std::string fileName);
	
	/**
	* removes not matching function definition base on line number
	* in case ov several definition with the same name of function , we take the neareast definition
	* @param[in] listOfGlobalDefinitions list of definitions to sort
	* @param[in] tagAssociatedToFunction the tag to compare with
	* @return the matching function definition
	*/
	FunctionGraph* removeNotConcernedDefinitionBaseInLineNumer(std::vector< FunctionGraph* >* listOfGlobalDefinitions, Tag* tagAssociatedToFunction);
	/**
	* utility function we replace the cscopeOutputParser in the case where we do not use Cscope
	* used for Object Style code 
	* it used in called and calling graphs ( 2 arguments )
	* in the first case we use the searched tag's fileName
	* in the second case we use the searched tag's Name
	* @param[in] output the ouput from the egrep command to parse
	* @param[in] arg
	* @return list Of Function as FunctionGraph Formatted output
	*/
	std::vector<FunctionGraph*>* egrepOutputParser(std::string output, std::string fileName, int arg);
	/**
	* utility function which checks if the string pass as an argument belongs to the language syntax
	* with the regex pattern we get [a-zA-Z0-9_]* *\\(.*\\)\" pattern
	* so we canget not wanted output as for(argumentExample) instead of myFunction1() , myFunction2() ...
	* @param[in] nameOfSymbolFound the string to check
	* @return the check result as a boolean
	**/
	bool isLanguageKey(std::string nameOfSymbolFound);
	/**
	* we have list of function as output when we look for a function definition place ( cscope may give lot of result )
	* we sort it on reading the function definition & couting the argument number 
	* compare the number of argument to the search tag one
	* this function is used in two cases one in caled function for non object and object style in called function 
	* in one case we have a Tag object and  in the other case we have a functionGraph object
	* @param[in] calledFunctionToFind  the tag we are comparaing with ( the tag for which we are looking for the definition)
	* @param[in] listOfGlobalDefinitions list of definition to sort in other to find the right definition
	* @param[in] listOfTypesforGlobalDefinitions the list of type as array for each definition in the list to sort
	* @param[in] arg the arg to as Object or non Object Style
	* @return the list od definition after sorting 
	* 
	* */
	std::vector<FunctionGraph*>* getFunctionNotMacthingOnArgumentNumber(void* calledFunctionToFind,std::vector<FunctionGraph*>* listOfGlobalDefinitions,std::vector<std::vector<std::string>*>* listOfTypesforGlobalDefinitions,int arg);
	/**
	* this function search and calculated the number of argument for a function in its definition
	* it's used generally by the launcCommandExternalTool arg 1 when we search for functions called list with egrep
	* @param[in] calledFunctionToFindCasted
	*@return the number of Variable 
	*/
	unsigned int getNumberOfVariableUsedInFunctionDefinition(Tag* calledFunctionToFindCasted);
	/**
	* utility function needed for creating the calling graph
	* it's used in the calling graph launchCommandExternalTool arg 2
	* after having  made an egrep on the searched tag 
	* we  remove from the output list (listOfCallingFunction) the name of matching a definition
	* @param[in] listOfCallingFunction the list of calling function to sort
	* 
	*/
	void removeFromListWhereTagNameIsDefinition(std::vector< FunctionGraph* >* listOfCallingFunction);
	/**
	* utility function needed in the calling graph
	* searching for the calling functions of a tag
	* we've get the list of each places ( so each files ) where the tag is called
	* for each files we get the the list of tag decalred in it
	* then with this list we'll look for the nearest position of each tag to find the good one
	* we store it as a map < key:nameOfFile , value:list of Tags in it >
	* @param[in] listOfFileWithListOfTagFunctionType the list of tag for each file
	* @param[in]  listOfCallingFunction the list of every calls of the searched tag
	* @return the list of caling Tag for every output
	* 
	* */
	std::vector< Tag* >* fullFilleWithListOftagForEachFile(std::map< std::string, std::vector< Tag* >* >* listOfFileWithListOfTagFunctionType, std::vector<FunctionGraph* >* listOfCallingFunction);
	/**
	* utility function used in calling graph function
	* we have the called function and the files where it's called
	* for each file where it appears we look for the tag for whom the definition start  is the nearest of the  called function
	* the neareast tag found is the callinf function
	* @param[in] listOfTagInfileMatchingCurrentOutputFunction the list of tag which might call the tag
	* @param[in] currentOutputFunction the output which contains the call of the tag (called one as it appears) which the parents are looked for 
	* @return list of the calling tags
	**/

	std::vector< Tag* >* getTagByNearestPositionFromFunctionOutput(std::vector< Tag* >* listOfTagInfileMatchingCurrentOutputFunction, FunctionGraph* currentOutputFunction);
	/**
	*used in calling graph creation for C++ code 
	* @param[in] listOfTagToReturn the list to fullFill
	* @param[in] listOfFunctionOutput the vector of calling 
	* 
	**/
	void fullfillListOfTagToReturn ( std::vector< Tag* >* listOfTagToReturn, std::vector< FunctionGraph* >* listOfFunctionOutput, Tag* tagAssociatedToFunction);
	/**
	* utility function needed in calling graph function
	* used in the case we do not use cscope in order to get the list of parent
	* we find the calling function ( as a tag ) in its file
	* and we are , line by line , looking for a call of the called function
	* @param[in] callingFunction function which might call the child ( called function )
	* @param[in] calledFunction function whom parents are searched
	* @return true if the function is truly one of the parent
	*/
	bool checkFunctionIsTrulyCallingThisFunction(Tag* callingFunction, Tag* calledFunction);
	/**
	* remove the tags which are the same than the parents one
	* @param[in] listOfTagToReturn the child list
	* @param[in] tagAssociatedToFunction the parent
	* 
	*/
	 void removeSameTagForCalling(std::vector< Tag* >* listOfTagToReturn, Tag* tagAssociatedToFunction);
	
public :
	
	 LauncherCscope(Configuration* myconfiguration,TagsManager* myTagManager);
	/**
	* init Cscope as an external tool
	* @return true once initialized correctly
	*/
	 bool initExternalTool();
	/**
	* erase all the cscope files in the working directory
	* @return returnParam
	*/
	 bool closeExternalTool();
	/**
	* return the line for the end of function definition
	* to the associated Tag
	* @param[in] tagAssociatedToFunction the function to make the search on
	* @return the number of the line for definition's end
	**/
	int getLineForEndOfFunctionDefinition(Tag* tagAssociatedToFunction);
	/**
	* launch the external tool with the given command and parameter
	* the id of the command does not match the id given in the manual
	* @param[in] command the number corresponding to the executed command
	* @param[in] tagAssociatedToFunction the tag on which the search is done
	* @return  a list of Tag for the view
	* 
	*/
	std::vector<Tag*>* launchCommandExternalTool(int command, Tag * tagAssociatedToFunction);
	/**
	* calculate the length of the function passed in the tag
	* @param[in] tagAssociatedToFunction the taf on which the search is done
	* @return the length in line unit
	*/
	int launchCommandExternalTool(Tag *tagAssociatedToFunction);
	/**
	 * simple getter
	 * @areturn the property isLaunched
	 */
	bool getIsLaunched();
	/**
	* function which returns a tag corresponding to the functionGraph 
	* @param[in] outputFunction corresponds to a line from cscope output , on which one we do tasks
	* @return the tag matching the cscope output line
	*/
	Tag * getTagFromFunctionGraphOutput(FunctionGraph* outputFunction);

};

#endif
