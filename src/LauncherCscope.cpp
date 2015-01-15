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

#include "LauncherCscope.h"
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include<iostream>
#include<string>
#include <list>
#include "FunctionGraph.h"
#include "TagImpl.h"

using namespace std;


LauncherCscope::LauncherCscope(Configuration* myconfiguration,TagsManager*myTagManager)
{
	this->myTagManager=myTagManager;
	this->myConfiguration=myconfiguration;
	this->isLaunched=false;
	this->myTagIdentifier=new TagIdentifier();
}


bool LauncherCscope::initExternalTool(){
	
	
	if(this->isLaunched==true){
	
		return this->isLaunched;
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
		return true;
	}
}

bool LauncherCscope::closeExternalTool()
{
	string commandFileRemove_1=string("rm -rf ")+(string)this->myConfiguration->getDestDir()+string("/cscope* ");
	if(system(commandFileRemove_1.c_str())==-1) perror("closing External Tool");
	else return true;
	
}

/**
 * launch the external tool with the given command and parameter
 * the id of the command does not match the id given in the manual
 * return a list of Tag for the view
 * 
 */

vector<Tag*>* LauncherCscope::launchCommandExternalTool(int command, Tag * tagAssociatedToFunction)
{
	FunctionGraph*fc=new FunctionGraph(myConfiguration->getSourcesDir()+string("/lib/media.c"),string("vlc_path2uri"),string("char *mrl = vlc_path2uri( path, NULL );"),342);

	if(tagAssociatedToFunction!=NULL)
	{
	vector<Tag*> *listOfTagToReturn=new vector<Tag*>();	
		/**
		* launch cscope and get the output
		*/
	
		if(command==1)
		{
			string output =this->launchExternalTool(1,tagAssociatedToFunction->getName());
			vector<FunctionGraph*>* listOfFunctionCalled=this->cscopeOutputParser(output);
			//this->removeFromListFunctionNotBelonginToStackCall(tagAssociatedToFunction->getLineNumber(),this->getLineForEndOfFunctionDefinition(tagAssociatedToFunction),listOfFunctionCalled,tagAssociatedToFunction);
			//cout<<"size of function call list  before parsing :" <<tagAssociatedToFunction->getName()<<" befor parsing is : "<<listOfFunctionCalled->size()<<endl;
			
			for(int i=0;i<listOfFunctionCalled->size();i++)
			{
				
				FunctionGraph* functToFind=listOfFunctionCalled->at(i);
				//cout<<" getiing definition for "<< functToFind->getTagName()<<endl;
				Tag* tag=this->getTagFromFunctionGraphOutput(functToFind);
				if(tag!=NULL)listOfTagToReturn->push_back(tag);
				//cout<<" i "<<i<<" size of list listOfTagToReturn "<<listOfTagToReturn->size()<<endl;
				
				
				//cout<<"size of global definition for :" <<tagAssociatedToFunction->getName()<<"  after parsing is : "<<listOfGlobalDefinition->size()<<endl;
			}
			//cout<<" list listOfTagToReturn "<<listOfTagToReturn->size()<<endl;
			return listOfTagToReturn;
			//cout<<"size of function call list  for :" <<tagAssociatedToFunction->getName()<<" after parsing is : "<<listOfTagToReturn->size()<<endl;
			
		}
		if(command=2)
		{
			vector<FunctionGraph*>* listOfCallingFunction=this->cscopeOutputParser(this->launchExternalTool(2,tagAssociatedToFunction->getName()));
			for(int i=0;i<listOfCallingFunction->size();i++)
			{
				vector<FunctionGraph*>* listOfGlobalDefinitions=this->cscopeOutputParser(this->launchExternalTool(2,listOfCallingFunction->at(i)->getTagName()));
			
				this->removeMatchesFromHAndC(listOfGlobalDefinitions);
				this->removeNotFunctionOutput(listOfGlobalDefinitions);
				this->removeNotConcernedDefinitionBasedOnFileName(listOfGlobalDefinitions,tagAssociatedToFunction);
				if(listOfGlobalDefinitions->empty())
				{
					Tag *FunctionDefinitionTag=new TagImpl(listOfCallingFunction->at(i)->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION);
					if(FunctionDefinitionTag!=NULL)listOfTagToReturn->push_back(FunctionDefinitionTag);
				}
				if(listOfGlobalDefinitions->size()==1)
				{
						//we can search for the tag directly now 
						Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfGlobalDefinitions->at(0)->getTagName(),listOfGlobalDefinitions->at(0)->getFileName(),listOfGlobalDefinitions->at(0)->getLine());
						if(FunctionDefinitionTag==NULL) FunctionDefinitionTag=new TagImpl(listOfCallingFunction->at(i)->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION);
						if(FunctionDefinitionTag!=NULL)listOfTagToReturn->push_back(FunctionDefinitionTag);
				}
				if(listOfGlobalDefinitions->size()>1)
				{
					FunctionGraph* singleDefinitionLeft=this->removeNotConcernedDefinitionBaseInLineNumer(listOfGlobalDefinitions,tagAssociatedToFunction);
					Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(singleDefinitionLeft->getTagName(),singleDefinitionLeft->getFileName(),singleDefinitionLeft->getLine());
					if(FunctionDefinitionTag!=NULL)listOfTagToReturn->push_back(FunctionDefinitionTag);
					
					
					
				}
				
				
			}
		}
		
		return listOfTagToReturn;
	}
	else return new vector<Tag*>();
}

bool LauncherCscope::getIsLaunched(){
	
	return this->isLaunched;
}
/**
 * parse the output from a cscope command
 * and return a vector of Function Graph Object (functionName-fileName-call's line- signature)
 */
std::vector<FunctionGraph*>* LauncherCscope::cscopeOutputParser(std::string output){
	
	
	vector<FunctionGraph*>* listOfCscopeOutput=new vector<FunctionGraph*>();
	stringstream outputAsStream(output);
	string readLine;
	while(getline(outputAsStream,readLine)){
	
		
		stringstream readLineAsStream(readLine);
		string part;
		//int count=0;
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
 * function which return a tag corresponding to the functionGraph 
 */
Tag  *LauncherCscope::getTagFromFunctionGraphOutput(FunctionGraph* outputFunction)
{

	vector<FunctionGraph*>* listOfGlobalDefinition=this->getGlobalDefinitionsFrom(outputFunction->getTagName());
				
				
				//cout<<" list Of Global Definition for " <<outputFunction->getTagName()<<" is : "<< listOfGlobalDefinition->size()<<endl;
				// we have found the function directly can look for the tag
				
				
				if(listOfGlobalDefinition->size()==1)
				{
					Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfGlobalDefinition->at(0)->getTagName(),listOfGlobalDefinition->at(0)->getFileName(),listOfGlobalDefinition->at(0)->getLine());
				
					if(FunctionDefinitionTag!=NULL)return(FunctionDefinitionTag);
					
				}
				// the function definition is out of cscope 
				else if(listOfGlobalDefinition->empty())
				{
					Tag *FunctionDefinitionTag=new TagImpl(outputFunction->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION);
					return (FunctionDefinitionTag);
			
					
				}
				// we have to find the right definition from the several we have
				else if(listOfGlobalDefinition->size()>1)
					
					
				{
					//cout << " size superior à 1 "<<endl;
			
					
					//getting list of type and parameters for each global definition;
					vector<vector<string>*>* listOFTypeForFunction=this->getNumberOfArgumentAndTypeForFunction(listOfGlobalDefinition);
					
					this->removeNotFunctionOutput(listOfGlobalDefinition);
					//cout <<" size of global definition before removing argument number and HC is "<<listOfGlobalDefinition->size()<<endl; 
					// getting rid of the .h and .c/c++ redundances ( the one in .h)
					this->removeNotMatchingFunctionOnArgumentNumber(outputFunction,listOfGlobalDefinition,listOFTypeForFunction);
					this->removeMatchesFromHAndC(listOFTypeForFunction,listOfGlobalDefinition);
					
					//cout <<" size of global definition after removing argument number and HC is "<<listOfGlobalDefinition->size()<<endl;
					
					
					
					if(listOfGlobalDefinition->size()==1)
					{
						//we can search for the tag directly now 
						Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfGlobalDefinition->at(0)->getTagName(),listOfGlobalDefinition->at(0)->getFileName(),listOfGlobalDefinition->at(0)->getLine());
						if(FunctionDefinitionTag!=NULL)return(FunctionDefinitionTag);
					}
					else if(listOfGlobalDefinition->empty())
					{
						Tag *FunctionDefinitionTag=new TagImpl(outputFunction->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION);
						return (FunctionDefinitionTag);
					}
					else{
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
 * 
 */
std::string LauncherCscope::launchExternalTool(int command, std::string arg){

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
			case 7:
				commandToExecute=string("cd ")+this->myConfiguration->getDestDir()+string(" && cscope -d -L8 ")+arg;
			break;
		}
		
			//vector<CscopeOutput*>* listOfCscopeOutput;
			//this->listOfLastTagAsked=new vector<Tag*>();
		
			if((myCommandOutput=popen(commandToExecute.c_str(),"r"))==NULL)perror("searching Called Function");
			
			while(!feof(myCommandOutput)){
			
				if(fgets(buffer,256,myCommandOutput)!=NULL){
				
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
 * 
 */
void LauncherCscope::removeNotFunctionOutput(std::vector<FunctionGraph*>* listOfGlobalDefinitions)
{
	if(listOfGlobalDefinitions!=NULL)
	{
		for(int i=0;i<listOfGlobalDefinitions->size();i++)
		{
			if(listOfGlobalDefinitions->at(i)->getSignature().find(";")!=std::string::npos||listOfGlobalDefinitions->at(i)->getSignature().find("#define")!=std::string::npos||listOfGlobalDefinitions->at(i)->getSignature().find("assert")!=std::string::npos) 
			{
				//cout<<"removing "<<listOfGlobalDefinitions->at(i)->getSignature()<<endl;
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
 */
std::vector<std::vector<std::string>*>* LauncherCscope::getNumberOfArgumentAndTypeForFunction(std::vector<FunctionGraph*>* listOfGlobalDefinitions)
{

	vector<vector<string>*>* listOfArgumentAndType=new vector<vector<string>*>();
	if(listOfGlobalDefinitions!=NULL){
		for(int i=0;i<listOfGlobalDefinitions->size();i++)
		{
			vector<string>* listOfArgumentType=new vector<string>();
			string stringToParse=listOfGlobalDefinitions->at(i)->getSignature();
			/**
			 **get the number of Argument
			 */
			//get the arguments as String
			int positionOpeningbracket=0;
			int positionEndingbracket=0;
			
			positionOpeningbracket=stringToParse.find_first_of("(");
			positionEndingbracket=stringToParse.find_last_of(")");
			
			if(positionEndingbracket==string::npos) positionEndingbracket=stringToParse.size()-1;
			//cout<<"positon of ending bracket"<< positionEndingbracket<<endl;
			string stringParameters="";
			if(positionEndingbracket-positionOpeningbracket==1) stringParameters="";
			else stringParameters=stringToParse.substr(positionOpeningbracket+1,positionEndingbracket-positionOpeningbracket-1);

		
			//cout<<"parameters : "<<stringParameters<<endl;
			//parse the argument
			bool argumentPresent=false;
			int numberOfArgument=0;
			int positionPrecedentComma=0;
			int positionFollowingComma=0;
			if(!stringParameters.empty()){
				
				for(int j=0;j<stringParameters.length();j++)
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
						int pos=0;
					
						pos=stringToParse.find(',',positionPrecedentComma+1);
						
						
						// if we don't find any comma it means we have reached the end of parameters or have only one parameter
						if((pos==string::npos)) 
						{
							//cout<<"reach the end of argumentandType list"<<endl;
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
 */
std::string LauncherCscope::getArgumentType(std::string  argumentAndTypeToParse)
{

	
	string NameOfArgument;
	string stringOfArgumentToParse="";
	bool rootArgumentFound=false;
	bool firstCharacterForRootNameFoud=false;
	int posFirstCaracterNameArgument=0;
	for(int i=(argumentAndTypeToParse.length()-1);i>=0;i--)
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
	
	return(this->removeSpaceFromString(stringOfArgumentToParse));
}
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
 *in the case where we have the same definition for a function ( com from .h and .c  
 */

void LauncherCscope::removeMatchesFromHAndC(std::vector<std::vector<std::string>*>* listOfTypes,std::vector<FunctionGraph*>* listOfGlobalDefinitions)
{
	/**
	 * we iterate on the global definition vector
	 */
	for(int i=0;i<listOfGlobalDefinitions->size();i++)
	{
		string name=listOfGlobalDefinitions->at(i)->getTagName();
		/**
		 * compare each global definition to the other
		 */
		for(int j=0;j<listOfGlobalDefinitions->size();j++)
		{
			/**
			 * if two identical name have matched ( and is not the same line )
			 * we compare the parameters type between global definitions
			 */
			if((j!=i)&&(listOfGlobalDefinitions->at(j)->getTagName().compare(listOfGlobalDefinitions->at(i)->getTagName())))
			{	int numberOfMatchingParameterType=0;
				vector<string >* listOfTypeForFirstMatch=listOfTypes->at(i);
				vector<string >* listOfTypeForSecondMatch=listOfTypes->at(j);
				for(int p=0;p<listOfTypeForFirstMatch->size();p++)
				{	if(listOfTypeForFirstMatch->at(p).compare(listOfTypeForSecondMatch->at(p)))
					{	numberOfMatchingParameterType++;
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
					}
					if(listOfGlobalDefinitions->at(j)->getFileName().find(".h"))
					{
						listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+j);
						listOfTypes->erase(listOfTypes->begin()+j);
					}
					
				}
				
			}
		}
	}
	
}

std::string LauncherCscope::removeSpaceFromString(std::string stringToParse)
{
	
	string t ="";
	if(!stringToParse.empty())
	{
		for(int i=0;i<stringToParse.length();i++)
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
 */
std::vector<std::string>* LauncherCscope::getTypeForVariableUsedInFunctionCall(FunctionGraph* calledFunctionToFind)
{
	std::vector<std::string>* variablesNames=this->getVariablesNamesInFunctionCall(calledFunctionToFind->getSignature());
	/*for(int i=0;i<variablesNames->size();i++)
	{
		string output=this->launchExternalTool(-1,variablesNames->at(i));
		std::vector<FunctionGraph*>* symbolFoundforThisVariableName= this->cscopeOutputParser(output);
		
		
		
	}*/
	return variablesNames;
	
}
/**
 * return the number of variable used for the function call
 */
int LauncherCscope::getNumberOfVariableUsedInFunctionCall(FunctionGraph* calledFunctionToFind)
{
	
	std::vector<std::string>* variablesNames=this->getVariablesNamesInFunctionCall(calledFunctionToFind->getSignature());

	return variablesNames->size();
}
/**
 * returns the list of variable's name for on function called
 * example libvlc_media_list_add_media( ml, md) ----> ["ml","md"]
 */
std::vector<std::string>* LauncherCscope::getVariablesNamesInFunctionCall(string callExpression)
{

	bool endreached=false;
	
	vector<string>* listOfVariableName=new vector<string>();
	int positionOpeningbracket=callExpression.find_first_of("(");
	
	int positionEndingbracket=callExpression.find_last_of(")");
	int positionPrecedentComma=positionOpeningbracket;
	int positionFollowingComma=0;
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
 */
void LauncherCscope::removeNotMatchingFunctionOnArgumentNumber(FunctionGraph* calledFunctionToFind,vector<FunctionGraph*>* listOfGlobalDefinitions,vector<vector<string>*>* listOfTypesforGlobalDefinitions)
{
	int numberOfArgument=this->getNumberOfVariableUsedInFunctionCall(calledFunctionToFind);
	for(int i=0;i<listOfGlobalDefinitions->size();i++)
	{
		if((listOfTypesforGlobalDefinitions->at(i)->size())!=numberOfArgument)
		{
			listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+i);
		}
	}
	
}

/**
 * return the line for the end of function definition
 * to the associated Tag
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
		for(int i=1;i<tagAssociatedToFunction->getLineNumber();i++) 
		{
			
			getline(stream,currentLine);
			cout<<" line read is "<<currentLine<<endl;
		}
		bool functionNameAlreadyRead=false;
		bool endOfFunctionFound=false;
		do
		{
			if(numberOfLine==0)
			{
				getline(stream,currentLine);
				functionInitialPos=currentLine.find(tagAssociatedToFunction->getName());
				
				for(int p=functionInitialPos;p<currentLine.length();p++)
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
				
				for(int p=0;p<currentLine.length();p++)
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
 */
void LauncherCscope::removeFromListFunctionNotBelonginToStackCall(int lineStart,int lineStop, vector<FunctionGraph*>* listOfFunctionCalled,Tag * functionAssociatedToTag)
{
		for(int i=0;i<listOfFunctionCalled->size();i++)
		{
			
			if((listOfFunctionCalled->at(i)->getLine()>>lineStop)||(listOfFunctionCalled->at(i)->getLine()<<lineStart)||(listOfFunctionCalled->at(i)->getFileName().compare(functionAssociatedToTag->getFileName())))
			{
				listOfFunctionCalled->erase(listOfFunctionCalled->begin()+i);
				i--;
			}
				
		}
}
/**
 * remove the .h function definition from the function called list
 */
void LauncherCscope::removeMatchesFromHAndC(std::vector<FunctionGraph*>* listOfGlobalDefinitions)
{
		
	
	for(int i=0;i<listOfGlobalDefinitions->size();i++)
	{
			
		if(listOfGlobalDefinitions->at(i)->getFileName().find(".h")!=string::npos) {
			listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+i);
			
			i--;
			
		}
			
		}
}

/**
 * removes not matching function definition based on file Name et function line
 */
void LauncherCscope::removeNotConcernedDefinitionBasedOnFileName(std::vector< FunctionGraph* >* listOfGlobalDefinitions, Tag* tagAssociatedToFunction)
{
	
	for(int i=0;i<listOfGlobalDefinitions->size();i++)
	{
		if((listOfGlobalDefinitions->at(i)->getFileName().compare(tagAssociatedToFunction->getFileName()))!=1||(listOfGlobalDefinitions->at(i)->getLine()>tagAssociatedToFunction->getLineNumber()))
		{
			listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+i);
			i--;
		}
		
	}
}
/**
 * removes not matching function definition base on line number
 */
FunctionGraph* LauncherCscope::removeNotConcernedDefinitionBaseInLineNumer(std::vector< FunctionGraph* >* listOfGlobalDefinitions, Tag* tagAssociatedToFunction)
{

	if(listOfGlobalDefinitions!=NULL)
	{
			
		int max=0;
		int count =0;
		int lineNumber=0;
		do
		{
			FunctionGraph* currentDef=listOfGlobalDefinitions->at(count);
			lineNumber=currentDef->getLine();
			if(max<currentDef->getLine())
			{
				max=currentDef->getLine();
			}
			
			
			count++;
		}while(lineNumber<tagAssociatedToFunction->getLineNumber());
	
		return listOfGlobalDefinitions->at(count-1);
	}
	else return NULL;
}

//void LauncherCscope::removeDouble