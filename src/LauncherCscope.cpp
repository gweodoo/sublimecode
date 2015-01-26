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
#include<algorithm>
#include "LauncherCscope.h"
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include<iostream>
#include<string>
#include <list>
#include "FunctionGraph.h"
#include "TagImpl.h"
#include <ctime>
#include<sys/time.h>
#include<vector>



using namespace std;


LauncherCscope::LauncherCscope(Configuration* myconfiguration,TagsManager*myTagManager)
{
	this->myTagManager=myTagManager;
	this->myConfiguration=myconfiguration;
	this->isLaunched=false;
	this->MyCscopeThreadObject=new CscopeThreadObject();
	
}

/**
 * init Cscope as an external tool
 * @return true once initialized correctly
 */
bool LauncherCscope::initExternalTool(){
	
	
	bool returnParam=false;
	if(this->isLaunched==true){
	
		returnParam=true;
	}
	else
	{
		
		string commandCscopeConstruct=string("cd ") +(string)this->myConfiguration->getSourcesDir() +string(" && cscope -bqkRu ");
		string commandFileMove_1=string("mv ")+(string)this->myConfiguration->getSourcesDir()+string("/cscope.in.out ")+(string)this->myConfiguration->getDestDir();
		string commandFileMove_2=string("mv ")+(string)this->myConfiguration->getSourcesDir()+string("/cscope.out ")+(string)this->myConfiguration->getDestDir();
		string commandFileMove_3=string("mv ")+(string)this->myConfiguration->getSourcesDir()+string("/cscope.po.out ")+(string)this->myConfiguration->getDestDir();

		//scDebug("ConstructingCscope "<<commandCscopeConstruct);
		if(system(commandCscopeConstruct.c_str())==-1)
		{
			perror("Initializing Cscope");
		}
	
		if(system(commandFileMove_1.c_str())==-1)
		{
		
			perror("Moving file Cscope");
		}
		if(system(commandFileMove_2.c_str())==-1)
		{
		
			perror("Moving file Cscope");
		}
		if(system(commandFileMove_3.c_str())==-1)
		{
		
			perror("Moving file Cscope");
		}
		this->isLaunched=true;
		
		returnParam=true;
	}
	return returnParam;
}
/**
 * erase all the cscope files in the working directory
 * @return returnParam
 */
bool LauncherCscope::closeExternalTool()
{
	bool returnParam=false;
	string commandFileRemove_1=string("rm -rf ")+(string)this->myConfiguration->getDestDir()+string("/cscope* ");
	if(!system(commandFileRemove_1.c_str())==-1) returnParam=true ;
	return returnParam;
	
}

/**
 * launch the external tool with the given command and parameter
 * the id of the command does not match the id given in the manual
 * @param[in] command the number corresponding to the executed command
 * @param[in] tagAssociatedToFunction the tag on which the search is done
 * @return  a list of Tag for the view
 * 
 */

vector<Tag*>* LauncherCscope::launchCommandExternalTool(int command, Tag * tagAssociatedToFunction)
{
	vector<Tag*> *listOfTagToReturn;
	if(tagAssociatedToFunction!=NULL)
	{
	listOfTagToReturn=new vector<Tag*>();	
		/**
		* launch cscope and get the output
		*/
		if(command==1)
		{
			/**
			 * checking if c/c++
			 */
			unsigned  int lastSlashPosition=tagAssociatedToFunction->getFileName().find_last_of("/");
			
			string fileNameWithoutPath=tagAssociatedToFunction->getFileName().substr(lastSlashPosition);
			
			unsigned  int isC=fileNameWithoutPath.find(".c");
			
			if(isC!=string::npos){
					unsigned  int isCpp=fileNameWithoutPath.substr(isC).find("pp");
					if(isCpp!=string::npos)
			{
				
				/**
				 *Cpp special treatement 
				 * checking is its a class method or not
				 */
				string isClassMethod=tagAssociatedToFunction->getInfoByKey("class");
				if(isClassMethod.empty())
				{
					
					/**
					 * we can deal with it like in C it's not an object method
					 */
					string output =this->launchExternalTool(1,tagAssociatedToFunction->getName());
					vector<FunctionGraph*>* listOfFunctionCalled=this->cscopeOutputParser(output);
					this->removeNotConcernedDefinitionBasedOnFileName(listOfFunctionCalled,tagAssociatedToFunction->getFileName());
				
					for(unsigned int i=0;i<listOfFunctionCalled->size();i++)
					{
				
						FunctionGraph* functToFind=listOfFunctionCalled->at(i);
						Tag* tag=this->getTagFromFunctionGraphOutput(functToFind);
						if(tag!=NULL)listOfTagToReturn->push_back(tag);
					}
				}
				else
				{
					/**
					 * we have to deal it for the C++ style object method
					 */
					
					string output =this->launchExternalTool(3,tagAssociatedToFunction->getFileName());
					vector<FunctionGraph*>* listOfFunctionCalled=this->egrepOutputParser(output,tagAssociatedToFunction->getFileName());
					//now we get the list of function called as if it was given by cscope
					this->removeFromListFunctionNotBelonginToStackCall(tagAssociatedToFunction->getLineNumber(),this->getLineForEndOfFunctionDefinition(tagAssociatedToFunction),listOfFunctionCalled,tagAssociatedToFunction);
					//now we have only the ouput matching to the tag associated function
					for(unsigned int i=0;i<listOfFunctionCalled->size();i++)
					{
				
						FunctionGraph* functToFind=listOfFunctionCalled->at(i);
						Tag* tag=this->getTagFromFunctionGraphOutput(functToFind);
						if(tag!=NULL)listOfTagToReturn->push_back(tag);
					}
					
					
					
				}
				
			}else if(isC!=string::npos)
			{
				
				/**
				 * C special treatement
				 */
				string output =this->launchExternalTool(1,tagAssociatedToFunction->getName());
				vector<FunctionGraph*>* listOfFunctionCalled=this->cscopeOutputParser(output);
				for(int p=0;p<listOfFunctionCalled->size();p++)
				{
					if(this->isLanguageKey(listOfFunctionCalled->at(p)->getTagName()))
					{
						listOfFunctionCalled->erase(listOfFunctionCalled->begin()+p);
					}
				}
				this->removeNotConcernedDefinitionBasedOnFileName(listOfFunctionCalled,tagAssociatedToFunction->getFileName());
			
				
				for(unsigned int i=0;i<listOfFunctionCalled->size();i++)
				{
			
					FunctionGraph* functToFind=listOfFunctionCalled->at(i);
					Tag* tag=this->getTagFromFunctionGraphOutput(functToFind);
					if(tag!=NULL)listOfTagToReturn->push_back(tag);
				}
				
			}
			else{}
			}
			
		
			
			
		}
		if(command==2)
		{
			vector<FunctionGraph*>* listOfCallingFunction=this->cscopeOutputParser(this->launchExternalTool(2,tagAssociatedToFunction->getName()));
			
			this->removeNotMatchingFunctionOnArgumentNumber(tagAssociatedToFunction,listOfCallingFunction,NULL,2);
			for(unsigned int i=0;i<listOfCallingFunction->size();i++)
			{
				if(!listOfCallingFunction->at(i)->getTagName().empty())
				{
					vector<FunctionGraph*>* listOfGlobalDefinitions=this->cscopeOutputParser(this->launchExternalTool(0,listOfCallingFunction->at(i)->getTagName()));
					this->removeMatchesFromHAndC(listOfGlobalDefinitions);
					this->removeNotFunctionOutput(listOfGlobalDefinitions);
					this->removeNotConcernedDefinitionBasedOnFileName(listOfGlobalDefinitions,listOfCallingFunction->at(i)->getFileName());
					this->removeFromListFunctionNotBelonginToStackCall(tagAssociatedToFunction->getLineNumber(),this->getLineForEndOfFunctionDefinition(tagAssociatedToFunction),listOfGlobalDefinitions,tagAssociatedToFunction);
					
					if(listOfGlobalDefinitions->empty())
					{
						
						this->myTagManager->addTag(new TagImpl(listOfCallingFunction->at(i)->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION));
						Tag *FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfCallingFunction->at(i)->getTagName(),string("OutOfscope"),0);
						if(FunctionDefinitionTag!=NULL)listOfTagToReturn->push_back(FunctionDefinitionTag);
						
					}
					if(listOfGlobalDefinitions->size()==1)
					{
							//we can search for the tag directly now 
							Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfGlobalDefinitions->at(0)->getTagName(),listOfGlobalDefinitions->at(0)->getFileName(),listOfGlobalDefinitions->at(0)->getLine());
							if(FunctionDefinitionTag==NULL) FunctionDefinitionTag=new TagImpl(listOfCallingFunction->at(0)->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION);
							if(FunctionDefinitionTag!=NULL)listOfTagToReturn->push_back(FunctionDefinitionTag);
					}
					if(listOfGlobalDefinitions->size()>1)
					{
						FunctionGraph* singleDefinitionLeft=this->removeNotConcernedDefinitionBaseInLineNumer(listOfGlobalDefinitions,tagAssociatedToFunction);
						if(singleDefinitionLeft!=NULL)
						{
						Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(singleDefinitionLeft->getTagName(),singleDefinitionLeft->getFileName(),singleDefinitionLeft->getLine());
						if(FunctionDefinitionTag!=NULL)listOfTagToReturn->push_back(FunctionDefinitionTag);
						else {
							this->myTagManager->addTag(new TagImpl(singleDefinitionLeft->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION));
							Tag *FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfCallingFunction->at(i)->getTagName(),string("OutOfscope"),0);
							if(FunctionDefinitionTag!=NULL)listOfTagToReturn->push_back(FunctionDefinitionTag);
						
						}
						}
					}
				}
			}
		}
		
	}
	sort(listOfTagToReturn->begin(),listOfTagToReturn->end());
	listOfTagToReturn->erase(unique(listOfTagToReturn->begin(),listOfTagToReturn->end()),listOfTagToReturn->end());
	return listOfTagToReturn;
}
/**
 * calculate the length of the function passed in the tag
 * @param[in] tagAssociatedToFunction the taf on which the search is done
 * @return the length in line unit
 */
int LauncherCscope::launchCommandExternalTool(Tag * tagAssociatedToFunction)
{

	int endOfFunctionDefinition=0;
	endOfFunctionDefinition=this->getLineForEndOfFunctionDefinition(tagAssociatedToFunction);
	if(endOfFunctionDefinition>0) endOfFunctionDefinition=endOfFunctionDefinition-tagAssociatedToFunction->getLineNumber();

return endOfFunctionDefinition;

	
}

/**
 * simple getter 
 * @return a boolean translating 
 */

bool LauncherCscope::getIsLaunched()
{
	return this->isLaunched;
}


/**
 * parse the output from a cscope command
 * and return a vector of Function Graph Object (functionName-fileName-call's line- signature)
 * @param[in] output the cscope's output to parse
 * @return a vector of FunctionGraph object containing the parsed cscope output
 */
std::vector<FunctionGraph*>* LauncherCscope::cscopeOutputParser(std::string output)
{
	vector<FunctionGraph*>* listOfCscopeOutput=new vector<FunctionGraph*>();
	stringstream outputAsStream(output);
	string readLine;
	while(getline(outputAsStream,readLine))
	{
		stringstream readLineAsStream(readLine);
		string part;
		FunctionGraph* newCscopeOutputLine=new FunctionGraph();
		for(int i=0;i<3;i++)
		{
			getline(readLineAsStream,part,' ');
			switch(i){
			
				case 0:
					
					newCscopeOutputLine->setFileName(this->myConfiguration->getSourcesDir()+string("/")+part);
					break;
				case 1:
					newCscopeOutputLine->setTagName(part);
					break;
				case 2:
					newCscopeOutputLine->setLine(atoi(part.c_str()));
					break;
			}
		}
		while(getline(readLineAsStream,part,' '))
		{
			newCscopeOutputLine->setSignature(newCscopeOutputLine->getSignature().append(part));
			newCscopeOutputLine->getSignature().push_back(' ');
		}
		 listOfCscopeOutput->push_back(newCscopeOutputLine);
	}
	return listOfCscopeOutput;
}
/**
 * 
 */
std::vector<FunctionGraph*>* LauncherCscope::egrepOutputParser(std::string output,std::string fileName)
{
	
	vector<FunctionGraph*>* listOfCscopeOutput=new vector<FunctionGraph*>();
	stringstream outputAsStream(output);
	string readLine;
	while(getline(outputAsStream,readLine))
	{
		stringstream readLineAsStream(readLine);
		string part;
		FunctionGraph* newCscopeOutputLine=new FunctionGraph();
		//setting the line number
		getline(readLineAsStream,part,' ');
		newCscopeOutputLine->setLine(atoi(part.c_str()));
		//setting the signature ( function call here )
		while(getline(readLineAsStream,part,' '))
		{
			newCscopeOutputLine->setSignature(newCscopeOutputLine->getSignature().append(part));
			newCscopeOutputLine->getSignature().push_back(' ');
		}
		//setting the name of the function
		unsigned int positionOfFirstBracket=newCscopeOutputLine->getSignature().find_first_of("(");
		newCscopeOutputLine->setTagName(newCscopeOutputLine->getSignature().substr(0,positionOfFirstBracket));
		//setting the fileName
		newCscopeOutputLine->setFileName(fileName);
		
		if(this->isLanguageKey(newCscopeOutputLine->getTagName()))free(newCscopeOutputLine);
		else listOfCscopeOutput->push_back(newCscopeOutputLine);
		
		
	}
	return listOfCscopeOutput;
}
/**
 * function which returns a tag corresponding to the functionGraph 
 * @param[in] outputFunction corresponds to a line from cscope output , on which one we do tasks
 * @return the tag matching the cscope output line
 */
Tag  *LauncherCscope::getTagFromFunctionGraphOutput(FunctionGraph* outputFunction)
{

	vector<FunctionGraph*>* listOfGlobalDefinition=this->getGlobalDefinitionsFrom(outputFunction->getTagName());
	
	if(listOfGlobalDefinition->size()==1)
	{
		Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfGlobalDefinition->at(0)->getTagName(),listOfGlobalDefinition->at(0)->getFileName(),listOfGlobalDefinition->at(0)->getLine());
		if(FunctionDefinitionTag!=NULL)return(FunctionDefinitionTag);
		
	}
	// the function definition is out of cscope 
	else if(listOfGlobalDefinition->empty())
	{
		this->myTagManager->addTag(new TagImpl(outputFunction->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION));
			Tag *FunctionDefinitionTag=this->myTagManager->findSpecificTag(outputFunction->getTagName(),string("OutOfscope"),0);
			if(FunctionDefinitionTag!=NULL)return(FunctionDefinitionTag);
		
	}
	// we have to find the right definition from the several we have
	else if(listOfGlobalDefinition->size()>1)
	{
		
		vector<vector<string>*>* listOFTypeForFunction=this->getNumberOfArgumentAndTypeForFunction(listOfGlobalDefinition);
		this->removeNotFunctionOutput(listOfGlobalDefinition);
		// getting rid of the .h and .c/c++ redundances ( the one in .h)
		this->removeNotMatchingFunctionOnArgumentNumber(outputFunction,listOfGlobalDefinition,listOFTypeForFunction,1);
		this->removeMatchesFromHAndC(listOFTypeForFunction,listOfGlobalDefinition);
		if(listOfGlobalDefinition->size()==1)
		{
			//we can search for the tag directly now 
			Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfGlobalDefinition->at(0)->getTagName(),listOfGlobalDefinition->at(0)->getFileName(),listOfGlobalDefinition->at(0)->getLine());
			if(FunctionDefinitionTag!=NULL)return(FunctionDefinitionTag);
		}
		else if(listOfGlobalDefinition->empty())
		{
	
			this->myTagManager->addTag(new TagImpl(outputFunction->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION));
			Tag *FunctionDefinitionTag=this->myTagManager->findSpecificTag(outputFunction->getTagName(),string("OutOfscope"),0);
			if(FunctionDefinitionTag!=NULL)return(FunctionDefinitionTag);
		}
		else
		{
			
			
			Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfGlobalDefinition->at(0)->getTagName(),listOfGlobalDefinition->at(0)->getFileName(),listOfGlobalDefinition->at(0)->getLine());
			if(FunctionDefinitionTag!=NULL)return (FunctionDefinitionTag);
			/**
			*at this point we have differents function in the case of overloading for exemple 
			*then we have to identify which function is called thanks to the type of parameters
			*/
		}					
	}
				
	return NULL;
}
 
/**
 * function which makes the system calls in order to execute cscope
 * @param[in] command the number crreponsding to the command to execute, argument need by cscope
 * @param[in] command the argument describing the name need by cscope
 */
std::string LauncherCscope::launchExternalTool(int command, std::string arg)
{
	if(!this->isLaunched) this->initExternalTool();
	FILE * myCommandOutput=NULL;
	char buffer[256];
	string result="";
	string commandToExecute="";
	
	if(!arg.empty()){
		switch(command)
		{
			/** list of the function called by**/
			case -1:
				commandToExecute=string("cd ")+this->myConfiguration->getDestDir()+string(" && cscope -d -L0 ")+arg;
			break;
			case 0:
				commandToExecute=string("cd ")+this->myConfiguration->getDestDir()+string(" && cscope -d -L1 ")+arg;
			break;
			case 1:
				commandToExecute=string("cd ")+this->myConfiguration->getDestDir()+string(" && cscope -d -L2 ")+arg;
			break;
			case 2:
				commandToExecute=string("cd ")+this->myConfiguration->getDestDir()+string(" && cscope -d -L3 ")+arg;
			break;
			case 3:
				commandToExecute=string("  egrep \"[a-zA-Z0-9_]* *\\(.*\\)\" -on  ")+arg +string("| awk -F: '{print $1\" \"$2}' ");
				break;
			case 7:
				commandToExecute=string("cd ")+this->myConfiguration->getDestDir()+string(" && cscope -d -L8 ")+arg;
			break;
		}
		
			
			if((myCommandOutput=popen(commandToExecute.c_str(),"r"))==NULL)perror("searching Called Function");
			
			while(!feof(myCommandOutput)){
			
				if(fgets(buffer,256,myCommandOutput)!=NULL)
				{
					result.append(buffer);
				}
				
			}
			if(myCommandOutput) pclose(myCommandOutput);
		}
	return result;
}
/*
 * step - 1
 * first step to get the right function definition for the calledFunction from CScope
 * get the global definitions found by Cscope
 * 
 * @param[in] nameOfFunction the name of the function to search the right definition on
 * @return list of definition found by cscope after being parsed
 */
std::vector<FunctionGraph*>* LauncherCscope::getGlobalDefinitionsFrom(std::string nameOfFunction)
{
	vector<FunctionGraph*>* outputglobalDefinition=new vector<FunctionGraph*>();
	outputglobalDefinition=this->cscopeOutputParser(this->launchExternalTool(0,nameOfFunction));
	
	return outputglobalDefinition;
}

/**
 * step - 2
 * second step remove from the list the definition which are not function definitions and which are #define aliases
 * @param[in] listOfGlobalDefinitions the list of definitions on which we remove the not function output given by cscope
 * 
 */
void LauncherCscope::removeNotFunctionOutput(std::vector<FunctionGraph*>* listOfGlobalDefinitions)
{
	if(listOfGlobalDefinitions!=NULL)
	{
		for(unsigned int i=0;i<listOfGlobalDefinitions->size();i++)
		{
			if(listOfGlobalDefinitions->at(i)->getSignature().find(";")!=std::string::npos||listOfGlobalDefinitions->at(i)->getSignature().find("#define")!=std::string::npos||listOfGlobalDefinitions->at(i)->getSignature().find("assert")!=std::string::npos) 
			{
				listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+i);
				i--;
				
			}
		}
	}
}
/**
 * step - 3
 * third step will look at the number of Argument and its type for each function graph
 * return a vector of vector. the vector contains the type of argument and a vector containing all the vector of type 
 * after this step we have two differents object: vector<FunctionGraph*>* containing the global definitions of the called function
 *						: vector<std::vector<std::string>*>* containing the list of argument type for each FunctionGraph
 * @param[in] listOfGlobalDefinitions the lift of definition to treat
 * @return a vector of vector containing the type of argument for each definition
 */
std::vector<std::vector<std::string>*>* LauncherCscope::getNumberOfArgumentAndTypeForFunction(std::vector<FunctionGraph*>* listOfGlobalDefinitions)
{	
	vector<vector<string>*>* listOfArgumentAndType=new vector<vector<string>*>();
	if(listOfGlobalDefinitions!=NULL){
		for(unsigned int i=0;i<listOfGlobalDefinitions->size();i++)
		{
			vector<string>* listOfArgumentType=new vector<string>();
			string stringToParse=listOfGlobalDefinitions->at(i)->getSignature();
			/**
			 **get the number of Argument
			 * get the arguments as String
			 */
			unsigned int positionOpeningbracket=0;
			unsigned int positionEndingbracket=0;
			
			positionOpeningbracket=stringToParse.find_first_of("(");
			positionEndingbracket=stringToParse.find_last_of(")");
			/**
			 * case where the ouput of cscope is truncate because of grep, the ")" symbol is not found
			 */
			if(positionEndingbracket==string::npos) positionEndingbracket=stringToParse.size()-1;
			string stringParameters="";
			if(positionEndingbracket-positionOpeningbracket==1) stringParameters="";
			else stringParameters=stringToParse.substr(positionOpeningbracket+1,positionEndingbracket-positionOpeningbracket-1);

			//parse the argument
			bool argumentPresent=false;
			int numberOfArgument=0;
			int positionPrecedentComma=0;
			int positionFollowingComma=0;
			if(!stringParameters.empty()){
				
				for(unsigned int j=0;j<stringParameters.length();j++)
				{
					if(stringParameters.at(j)!=' ')
					{	
						argumentPresent=true;
						j=stringParameters.length();
					}
				}
				if(argumentPresent){
					
					//start with the opening bracket as the first comma
					positionPrecedentComma=positionOpeningbracket;
					bool argFoundIsLast=false;
					do
					{
						
						
						string argumentWithType="";
						unsigned long int  pos=0;
					
						pos=stringToParse.find(',',positionPrecedentComma+1);
						
						// if we don't find any comma it means we have reached the end of parameters or have only one parameter
						if((pos==string::npos)) 
						{
							argFoundIsLast=true;
							positionFollowingComma=positionEndingbracket;
							argumentWithType=stringToParse.substr(positionPrecedentComma+1,positionFollowingComma-positionPrecedentComma-1);
						}
						else{
							positionFollowingComma=pos;
							argumentWithType=stringToParse.substr(positionPrecedentComma+1,positionFollowingComma-positionPrecedentComma-1);
							positionPrecedentComma=positionFollowingComma;
						}
						
						string typeOfTheArgument=this->getArgumentType(argumentWithType);
						listOfArgumentType->push_back(typeOfTheArgument);
						numberOfArgument++;
					}while(argFoundIsLast==false);
				}
			}else
			{
				listOfArgumentType->push_back("");
			}
		listOfArgumentAndType->push_back(listOfArgumentType);
		}
	}

	return listOfArgumentAndType;
}
/**
 * exemple  (const char *) -> (constchar*)
 * function here to parse a string composed af an argument and its type 
 * return the type only
 * @param[in] argumentAndTypeToParse the string to parse in order to get the type of argument
 * @return the type of the argument
 */
std::string LauncherCscope::getArgumentType(std::string  argumentAndTypeToParse)
{
	string NameOfArgument;
	string typeOfArgument="";
	string stringOfArgumentToParse="";
	bool rootArgumentFound=false;
	bool firstCharacterForRootNameFoud=false;
	int posFirstCaracterNameArgument=0;
	for( int i=(argumentAndTypeToParse.length()-1);i>=0;i--)
	{	if(rootArgumentFound==false)
		{	if(firstCharacterForRootNameFoud==false)
			{	if(this->isValidCaracter(argumentAndTypeToParse.at(i)))
				{	firstCharacterForRootNameFoud=true;
					NameOfArgument.push_back(argumentAndTypeToParse.at(i));
				}
			}else
			{	if(this->isValidCaracter(argumentAndTypeToParse.at(i)))
				{	NameOfArgument.push_back((argumentAndTypeToParse.at(i)));
				}
				else
				{	rootArgumentFound=true;
					posFirstCaracterNameArgument=i;
					break;
				}	
			}
		}
	}
	stringOfArgumentToParse=argumentAndTypeToParse.substr(0,posFirstCaracterNameArgument);
	typeOfArgument=(this->removeSpaceFromString(stringOfArgumentToParse));
	return typeOfArgument;
}
/**
 * check if the char is a valid one it means between a-zA-Z0-9
 * @param[in] caracterToTest the char to check
 * @return the boolean 
 */
bool LauncherCscope::isValidCaracter(char& caracterToTest)
{
	int asciValue=(int)caracterToTest;
	if((asciValue>=65&&asciValue<=90)||(asciValue>=97&&asciValue<=122)||(asciValue>=48&&asciValue<=57)||asciValue==95)
	{
		return true;
	}else
	{
		return false;
	}
}

/**
 *in the case where we have the same definition for a function ( com from .h and .c  )
 * @param[in] listOfTypes vector of vector containing the list of type for each definition
 * @param[in] listOfGlobalDefinitions list of definitions to sort 
 */
void LauncherCscope::removeMatchesFromHAndC(std::vector<std::vector<std::string>*>* listOfTypes,std::vector<FunctionGraph*>* listOfGlobalDefinitions)
{	/**
	 * we iterate on the global definition vector
	 */
	for(unsigned int i=0;i<listOfGlobalDefinitions->size();i++)
	{
		string name=listOfGlobalDefinitions->at(i)->getTagName();
		/**
		 * compare each global definition to the other
		 */
		for(unsigned int j=0;j<listOfGlobalDefinitions->size();j++)
		{
			/**
			 * if two identical name have matched ( and is not the same line )
			 * we compare the parameters type between global definitions
			 */
			if((j!=i)&&(listOfGlobalDefinitions->at(j)->getTagName().compare(listOfGlobalDefinitions->at(i)->getTagName())))
			{	unsigned int numberOfMatchingParameterType=0;
				vector<string >* listOfTypeForFirstMatch=listOfTypes->at(i);
				vector<string >* listOfTypeForSecondMatch=listOfTypes->at(j);
				for(unsigned int p=0;p<listOfTypeForFirstMatch->size();p++)
				{	if(listOfTypeForFirstMatch->at(p).compare(listOfTypeForSecondMatch->at(p)))
					{	
						numberOfMatchingParameterType++;
					}
				}
				//if the two definitions are identical we remove One of them
				if(numberOfMatchingParameterType==listOfTypeForFirstMatch->size())
				{
					// ( we remove the i-th or j-th  ? )
					// check the one who comme from .h
					if(listOfGlobalDefinitions->at(i)->getFileName().find(".h"))
					{
						listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+j);
						listOfTypes->erase(listOfTypes->begin()+j);
						i--;
					}
					if(listOfGlobalDefinitions->at(j)->getFileName().find(".h"))
					{
						listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+j);
						listOfTypes->erase(listOfTypes->begin()+j);
						j--;
					}
				}
			}
		}
	}
}
/**
 * remove all space from a string
 * @param[in] stringToParse the string to remove the space from
 * @return the string whithout space
 */
std::string LauncherCscope::removeSpaceFromString(std::string stringToParse)
{
	string t ="";
	if(!stringToParse.empty())
	{
		for(unsigned int i=0;i<stringToParse.length();i++)
		{
			if(stringToParse.at(i)!=' ')
			{
				t.push_back(stringToParse.at(i));
			}
		}
	}
	return t;
}
/**
 * returns the list of variable's type for on function called
 * ["ml","md"] ----> ["int","void *"]
 * @param[in] calledFunctionToFind cscope's output's line to search the variable in
 * @return a vector of string containing all the type of variables
 */
std::vector<std::string>* LauncherCscope::getTypeForVariableUsedInFunctionCall(FunctionGraph* calledFunctionToFind)
{
	int positionOfFunctionName=calledFunctionToFind->getSignature().find(calledFunctionToFind->getTagName());
	
	string callExpressionwithOnlyFunctionNameAndParameters=calledFunctionToFind->getSignature().substr(positionOfFunctionName);
	
	std::vector<std::string>* variablesNames=this->getVariablesNamesInFunctionCall(callExpressionwithOnlyFunctionNameAndParameters);
	return variablesNames;
	
}
/**
 * return the number of variable used for the function call
 * @param[in] calledFunctionToFind cscope's output's line to search the variable in
 * @return the size of the list of variables
 */
int LauncherCscope::getNumberOfVariableUsedInFunctionCall(FunctionGraph* calledFunctionToFind)
{
	int number=0;	
	std::vector<std::string>* variablesNames=this->getTypeForVariableUsedInFunctionCall(calledFunctionToFind);
	if(variablesNames!=NULL) number=variablesNames->size();
	return number;
	
}
/**
 * returns the list of variable's name for on function called
 * example libvlc_media_list_add_media( ml, md) ----> ["ml","md"]
 * @param[in] callExpression the call expression to parse
 * @return vector of string corresponding to the name of each param in the call
 */
std::vector<std::string>* LauncherCscope::getVariablesNamesInFunctionCall(string callExpression)
{
	bool endreached=false;
	
	vector<string>* listOfVariableName=new vector<string>();
	int positionOpeningbracket=callExpression.find_first_of("(");
	
	int positionEndingbracket=callExpression.find_last_of(")");
	int positionPrecedentComma=positionOpeningbracket;
	unsigned long int positionFollowingComma=0;
	do
	{
			positionFollowingComma=callExpression.find(",",positionPrecedentComma+1);
			if(positionFollowingComma==string::npos)
			{
				endreached=true;
				positionFollowingComma=positionEndingbracket;
			}
			string variableName=callExpression.substr(positionPrecedentComma+1,positionFollowingComma-positionPrecedentComma-1);
			listOfVariableName->push_back(variableName);
			positionPrecedentComma=positionFollowingComma;
	}
	while(!endreached);
	
	return listOfVariableName;
	
}

/**
 * remove the not matchings definition of a function towards the number of argument
 * if in the the list we have myFunction(var_1,var_2,var_3)
 * 			      myFunction(var_1,var_2)
 * 	and the number of argument is 2 we remove the first one
 * @param[in] calledFunctionToFind cscope's output's line to compare with
 * @param[in] listOfGlobalDefinitions the list of cscope's ouput to sort 
 */
void LauncherCscope::removeNotMatchingFunctionOnArgumentNumber(void* calledFunctionToFind,vector<FunctionGraph*>* listOfGlobalDefinitions,vector<vector<string>*>* listOfTypesforGlobalDefinitions,int arg)
{
	if(arg==1)
	{
		FunctionGraph*calledFunctionToFindCasted=(FunctionGraph*)calledFunctionToFind;
		unsigned int numberOfArgument=this->getNumberOfVariableUsedInFunctionCall(calledFunctionToFindCasted);
		for(unsigned int i=0;i<listOfGlobalDefinitions->size();i++)
		{
	
			if((listOfTypesforGlobalDefinitions->at(i)->size())!=numberOfArgument)
			{
				listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+i);
				i--;
			}
		}
		
	}
	if(arg==2)
	{
		Tag*calledFunctionToFindCasted=(Tag*)calledFunctionToFind;
		// getting the number of argument of the tag defintion
		unsigned int numberOfArgument=this-> getNumberOfVariableUsedInFunctionDefinition(calledFunctionToFindCasted);
		//now comparing with the list of function calling
		// here the argument is listOfglabDefinitions but its in fact list Of the function call 
		for(int i=0;i<listOfGlobalDefinitions->size();i++)
		{
			string call=listOfGlobalDefinitions->at(i)->getSignature().substr(listOfGlobalDefinitions->at(i)->getSignature().find(calledFunctionToFindCasted->getName()));
			vector<string>* variablesNames=this->getVariablesNamesInFunctionCall(call);
			if((variablesNames->size())!=numberOfArgument)
			{
				listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+i);
				i--;
			}
		}
		
		
		
	}
	
}

/**
 * return the line for the end of function definition
 * to the associated Tag
 * @param[in] tagAssociatedToFunction the function to make the search on
 * @return the number of the line for definition's end
 */
int LauncherCscope::getLineForEndOfFunctionDefinition(Tag* tagAssociatedToFunction)
{
	ifstream stream(tagAssociatedToFunction->getFileName().c_str());
	int numberOfEndLine=0;
	if(stream!=0){
		string currentLine;
		int numberOfLine=0;
		int niveauBraceBracket=0;
		int functionInitialPos=0;
		bool firstBraceBracketAlreyFound=false;
		/**
		 * skip the n-first line beforde function definition
		 */
		for(unsigned int i=1;i<tagAssociatedToFunction->getLineNumber();i++) 
		{
			getline(stream,currentLine);
		}
		bool functionNameAlreadyRead=false;
		bool endOfFunctionFound=false;
		/**
		 * looking for brace brackets
		 * case division in order to find the first brace bracket
		 */
		do
		{
			if(numberOfLine==0)
			{
				getline(stream,currentLine);
				functionInitialPos=currentLine.find(tagAssociatedToFunction->getName());
				
				for(unsigned int p=functionInitialPos;p<currentLine.length();p++)
				{
					
					if(currentLine.at(p)=='{')
					{
						niveauBraceBracket++;
						firstBraceBracketAlreyFound=true;
					}if(currentLine.at(p)=='}')niveauBraceBracket--;
				}
				functionNameAlreadyRead=true;
			}
			else
			{
				getline(stream,currentLine);
				
				for(unsigned int p=0;p<currentLine.length();p++)
				{	if(currentLine.at(p)=='{')
					{
						firstBraceBracketAlreyFound=true;
						niveauBraceBracket++;
					}
					if(currentLine.at(p)=='}')niveauBraceBracket--;
				}
			}
			if(functionNameAlreadyRead==true&&niveauBraceBracket==0&&firstBraceBracketAlreyFound)endOfFunctionFound=true;
			numberOfLine++;
		}while(endOfFunctionFound==false);
	
		numberOfEndLine=numberOfLine+tagAssociatedToFunction->getLineNumber()-1;
	}	
	 return numberOfEndLine;
}
/**
 * this function removes from the function called which do not belong to the function 
 * @param[in] lineStart the line where the function definition starts
 * @param[in] lineStop the line where the function definition stops
 * @param[in] listOfFunctionCalled the list of function definition to sort
 * @param[in] listOfFunctionCalled function definition to compare with
 */
void LauncherCscope::removeFromListFunctionNotBelonginToStackCall(int lineStart,int lineStop, vector<FunctionGraph*>* listOfFunctionCalled,Tag * functionAssociatedToTag)
{
		for(unsigned int i=0;i<listOfFunctionCalled->size();i++)
		{
		
			if((listOfFunctionCalled->at(i)->getLine()>=lineStop)||(listOfFunctionCalled->at(i)->getLine()<=lineStart)||(listOfFunctionCalled->at(i)->getFileName().compare(functionAssociatedToTag->getFileName())!=0))
			{	
				listOfFunctionCalled->erase(listOfFunctionCalled->begin()+i);
				i--;
			}
		}
}
/**
 * remove the .h function definition from the function called list
 * @param[in] listOfGlobalDefinitions list of function definition to sort
 * 
 */
void LauncherCscope::removeMatchesFromHAndC(std::vector<FunctionGraph*>* listOfGlobalDefinitions)
{
	for(unsigned int i=0;i<listOfGlobalDefinitions->size();i++)
	{
		if(listOfGlobalDefinitions->at(i)->getFileName().find(".h")!=string::npos) {
			listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+i);
			i--;
		}
	}
}
/**
 * removes not matching function definition based on file Name et function line
 * @param[in] listOfGlobalDefinitions list of function definition to sort
 * @param[in] fileName the fine Name to compare with
 */
void LauncherCscope::removeNotConcernedDefinitionBasedOnFileName(std::vector< FunctionGraph* >* listOfGlobalDefinitions, std::string  fileName)
{
	
	for(unsigned int i=0;i<listOfGlobalDefinitions->size();i++)
	{
		
		if((listOfGlobalDefinitions->at(i)->getFileName().find(fileName)==string::npos))
		{
			listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+i);
			i--;
		}
	}
}

/**
 * removes not matching function definition base on line number
 * in case ov several definition with the same name of function , we take the neareast definition
 * @param[in] listOfGlobalDefinitions list of definitions to sort
 * @param[in] tagAssociatedToFunction the tag to compare with
 * @return the matching function definition
 */
FunctionGraph* LauncherCscope::removeNotConcernedDefinitionBaseInLineNumer(std::vector< FunctionGraph* >* listOfGlobalDefinitions, Tag* tagAssociatedToFunction)
{

	FunctionGraph* funcToReturn=NULL;
	
	if(listOfGlobalDefinitions!=NULL)
	{
		int max=0;
		int lineNumber=0;
		lineNumber=tagAssociatedToFunction->getLineNumber();
		for(unsigned int i=0;i<listOfGlobalDefinitions->size();i++)
		{
			FunctionGraph* currentDef=listOfGlobalDefinitions->at(i);
			lineNumber=currentDef->getLine();
			if(max<lineNumber)
			{
				max=lineNumber;
				funcToReturn=currentDef;
			}
		}
	}
	 return funcToReturn;
}
CscopeThreadObject* LauncherCscope::getCscopeThreadObject()
{
	return this->MyCscopeThreadObject;
}
bool LauncherCscope::isLanguageKey(std::string nameOfSymbolFound)
{
	bool isLanguageKey=false;
	if(nameOfSymbolFound.compare("for")==0||nameOfSymbolFound.compare("if")==0||nameOfSymbolFound.compare("at")==0||nameOfSymbolFound.compare("while")==0||nameOfSymbolFound.compare("else")==0
		||nameOfSymbolFound.compare("find_last_of")==0||nameOfSymbolFound.compare("push_back")==0||nameOfSymbolFound.compare("")==0
	||nameOfSymbolFound.compare("find_last_of")==0||nameOfSymbolFound.compare("pop_back")==0||nameOfSymbolFound.compare("substr")==0
	||nameOfSymbolFound.compare("find")==0||nameOfSymbolFound.compare("erase")==0||nameOfSymbolFound.compare("compare")==0
		||nameOfSymbolFound.compare("stream")==0||nameOfSymbolFound.compare("isstream")==0||nameOfSymbolFound.compare("find_first_of")==0
	||nameOfSymbolFound.compare("size")==0||nameOfSymbolFound.compare("length")==0||nameOfSymbolFound.compare("string")==0
	||nameOfSymbolFound.compare("switch")==0||nameOfSymbolFound.compare("exec")==0||nameOfSymbolFound.compare("printf")==0||nameOfSymbolFound.compare("system")==0
	||nameOfSymbolFound.compare("defined")==0
	) isLanguageKey=true;
	return isLanguageKey;
}
unsigned int LauncherCscope::getNumberOfVariableUsedInFunctionDefinition(Tag* calledFunctionToFindCasted)
{
ifstream stream(calledFunctionToFindCasted->getFileName().c_str());
	int numberOfVariable=0;
	string listOfArgument="";
	if(stream!=0){
		string currentLine;
		int numberOfLine=0;
		int niveauBraceBracket=0;
		int functionInitialPos=0;
		bool firstBraceBracketAlreyFound=false;
		/**
		 * skip the n-first line beforde function definition
		 */
		for(unsigned int i=1;i<calledFunctionToFindCasted->getLineNumber();i++) 
		{
			getline(stream,currentLine);
		}
		bool functionNameAlreadyRead=false;
		bool cursorIsInComment=false;
		bool signatureclosingBraceBracketFound=false;
		
		/**
		 * looking for brace brackets
		 * case division in order to find the first brace bracket
		 */
		do
		{
			getline(stream,currentLine);
			
			if(currentLine.find("/*")!=string::npos)
			{
				cursorIsInComment=true;
			}
			if(currentLine.find("*/")!=string::npos)
			{
				cursorIsInComment=false;
			}
			
			if(!cursorIsInComment||currentLine.find("//")==string::npos){
				unsigned long int namePosition=currentLine.find(calledFunctionToFindCasted->getName());
				if(namePosition!=string::npos)
				{
					functionNameAlreadyRead=true;
					currentLine=currentLine.substr(namePosition);
					
				}
				if(functionNameAlreadyRead==true)
				{
					if(currentLine.find_first_of("{")!=string::npos)
					{
						for(unsigned int p=functionInitialPos;p<currentLine.length();p++)
						{
							if(currentLine.at(p)=='{')
							{
								firstBraceBracketAlreyFound=true;
								listOfArgument.append(currentLine.substr(0,p));
								break;
							}
						}	
					}
					else{
						listOfArgument.append(currentLine);
					}
				}

				
			}
		
			
		}while(firstBraceBracketAlreyFound==false);
	
		
		
	}
	int positionOfFunctionName=listOfArgument.find(calledFunctionToFindCasted->getName());
	
	string callExpressionwithOnlyFunctionNameAndParameters=listOfArgument;
	std::vector<std::string>* variablesNames=this->getVariablesNamesInFunctionCall(callExpressionwithOnlyFunctionNameAndParameters);
	numberOfVariable=variablesNames->size();

	return numberOfVariable;
	
}
