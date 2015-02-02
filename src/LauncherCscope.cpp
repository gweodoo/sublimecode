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
#include "tags/Tag.h"
#include <ctime>
#include<sys/time.h>
#include<vector>



using namespace std;


LauncherCscope::LauncherCscope(Configuration* myconfiguration,TagsManager*myTagManager)
{
	this->myTagManager=myTagManager;
	this->myConfiguration=myconfiguration;
	this->isLaunched=false;

	
}

bool LauncherCscope::initExternalTool(){
	
	
	bool returnParam=false;
	if(this->isLaunched==true){
	
		returnParam=true;
	}
	else
	{
		
		string commandCscopeConstruct=string("cd ") +(string)this->myConfiguration->getSourcesDir() +string(" && cscope -bqRu ");
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

bool LauncherCscope::closeExternalTool()
{
	bool returnParam=false;
	string commandFileRemove_1=string("rm -rf ")+(string)this->myConfiguration->getDestDir()+string("/cscope* ");
	if(!system(commandFileRemove_1.c_str())==-1) returnParam=true ;
	return returnParam;
	
}

vector<Tag*>* LauncherCscope::launchCommandExternalTool(int command, Tag * tagAssociatedToFunction)
{
	vector<Tag*> *listOfTagToReturn=NULL;
	if(tagAssociatedToFunction!=NULL)
	{
		listOfTagToReturn=new vector<Tag*>();	
		/**
		* launch cscope and get the output
		*/
		if(command==1)
		{
			vector<FunctionGraph*>* listOfFunctionCalled=NULL;
			/**
			 * checking if c/c++
			 */
			unsigned  long int lastSlashPosition=tagAssociatedToFunction->getFileName().find_last_of("/");
			string fileNameWithoutPath=tagAssociatedToFunction->getFileName().substr(lastSlashPosition);
			unsigned long  int isC=fileNameWithoutPath.find(".c");
			if(isC!=string::npos)
			{
					unsigned  long int isCpp=fileNameWithoutPath.substr(isC).find("pp");
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
							listOfFunctionCalled=this->cscopeOutputParser(output);
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
							vector<FunctionGraph*>* listOfFunctionCalled=this->egrepOutputParser(output,tagAssociatedToFunction->getFileName(),1);
							//now we get the list of function called as if it was given by cscope
							int line_stop=this->getLineForEndOfFunctionDefinition(tagAssociatedToFunction);
							this->removeFromListFunctionNotBelonginToStackCall(tagAssociatedToFunction->getLineNumber(),this->getLineForEndOfFunctionDefinition(tagAssociatedToFunction),listOfFunctionCalled,tagAssociatedToFunction,1);
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
			delete listOfFunctionCalled;
			
		}
		if(command==2)
		{
			vector<FunctionGraph*>* listOfCallingFunction=NULL;
			string output=this->launchExternalTool(2,tagAssociatedToFunction->getName());
			listOfCallingFunction=this->cscopeOutputParser(output);
			
			unsigned  long int lastSlashPosition=tagAssociatedToFunction->getFileName().find_last_of("/");
			string fileNameWithoutPath=tagAssociatedToFunction->getFileName().substr(lastSlashPosition);
			unsigned long  int isC=fileNameWithoutPath.find(".c");			
			if(isC!=string::npos)
			{
					unsigned  long int isCpp=fileNameWithoutPath.substr(isC).find("pp");
					if(isCpp!=string::npos)
					{
						if(listOfCallingFunction->empty())
						{
							listOfCallingFunction=this->egrepOutputParser(this->launchExternalTool(4,tagAssociatedToFunction->getName()),tagAssociatedToFunction->getName(),2);
							this->removeMatchesFromHAndC(listOfCallingFunction);
							std::map<std::string,std::vector<Tag*>*>* listOfFileWithListOfTagFunctionType=new std::map<std::string,std::vector<Tag*>*>();
							this->removeFromListWhereTagNameIsDefinition(listOfCallingFunction);
							vector<Tag*>* tagToConcatenate=this->fullFilleWithListOftagForEachFile(listOfFileWithListOfTagFunctionType,listOfCallingFunction);
							listOfTagToReturn->insert(listOfTagToReturn->end(),tagToConcatenate->begin(),tagToConcatenate->end());
						}else
						{
							fullfillListOfTagToReturn(listOfTagToReturn,listOfCallingFunction,tagAssociatedToFunction);
						}
					}else 
					{
						fullfillListOfTagToReturn(listOfTagToReturn,listOfCallingFunction,tagAssociatedToFunction);
					}
			
					delete listOfCallingFunction;
			}
			
			this->removeSameTagForCalling(listOfTagToReturn,tagAssociatedToFunction);
		}
	}
		
	sort(listOfTagToReturn->begin(),listOfTagToReturn->end());
	listOfTagToReturn->erase(unique(listOfTagToReturn->begin(),listOfTagToReturn->end()),listOfTagToReturn->end());
	return listOfTagToReturn;
}

void LauncherCscope::fullfillListOfTagToReturn (vector<Tag*> *listOfTagToReturn,vector<FunctionGraph*>* listOfFunctionOutput,Tag * tagAssociatedToFunction)
{
	
	this->removeNotMatchingFunctionOnArgumentNumber(tagAssociatedToFunction,listOfFunctionOutput,NULL,2);
	for(unsigned int i=0;i<listOfFunctionOutput->size();i++)
	{
		if(!listOfFunctionOutput->at(i)->getTagName().empty())
		{
			
			vector<FunctionGraph*>* listOfGlobalDefinitions=this->cscopeOutputParser(this->launchExternalTool(0,listOfFunctionOutput->at(i)->getTagName()));
			
			
			this->removeMatchesFromHAndC(listOfGlobalDefinitions);
			this->removeNotFunctionOutput(listOfGlobalDefinitions);
			this->removeNotConcernedDefinitionBasedOnFileName(listOfGlobalDefinitions,listOfFunctionOutput->at(i)->getFileName());
			this->removeFromListFunctionNotBelonginToStackCall(0,0,listOfGlobalDefinitions,listOfFunctionOutput->at(i),2);
		
			if(listOfGlobalDefinitions->empty())
			{
				
				this->myTagManager->addTag(new Tag(listOfFunctionOutput->at(i)->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION));
				Tag *FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfFunctionOutput->at(i)->getTagName(),string("OutOfscope"),0);
				if(FunctionDefinitionTag!=NULL)listOfTagToReturn->push_back(FunctionDefinitionTag);
				
			}
			
			if(listOfGlobalDefinitions->size()==1)
			{
					//we can search for the tag directly now 
					Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfGlobalDefinitions->at(0)->getTagName(),listOfGlobalDefinitions->at(0)->getFileName(),listOfGlobalDefinitions->at(0)->getLine());
					if(FunctionDefinitionTag==NULL) FunctionDefinitionTag=new Tag(listOfFunctionOutput->at(0)->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION);
					
					if(FunctionDefinitionTag!=NULL){
						listOfTagToReturn->push_back(FunctionDefinitionTag);
						
						
					}
			}
			
			if(listOfGlobalDefinitions->size()>1)
			{
				FunctionGraph* singleDefinitionLeft=this->removeNotConcernedDefinitionBaseInLineNumer(listOfGlobalDefinitions,tagAssociatedToFunction);
				if(singleDefinitionLeft!=NULL)
				{
				Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(singleDefinitionLeft->getTagName(),singleDefinitionLeft->getFileName(),singleDefinitionLeft->getLine());
				if(FunctionDefinitionTag!=NULL)listOfTagToReturn->push_back(FunctionDefinitionTag);
				else {
					this->myTagManager->addTag(new Tag(singleDefinitionLeft->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION));
					Tag *FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfFunctionOutput->at(i)->getTagName(),string("OutOfscope"),0);
					if(FunctionDefinitionTag!=NULL)listOfTagToReturn->push_back(FunctionDefinitionTag);
				
				}
				}
			}
			
			delete listOfGlobalDefinitions;
			printf("\n\n");
		}
	}
}

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

std::vector<FunctionGraph*>* LauncherCscope::egrepOutputParser(std::string output,std::string fileName,int arg)
{
	
	vector<FunctionGraph*>* listOfCscopeOutput=new vector<FunctionGraph*>();
	stringstream outputAsStream(output);
	string readLine;
	while(getline(outputAsStream,readLine))
	{
		stringstream readLineAsStream(readLine);
		string part;
		FunctionGraph* newCscopeOutputLine=new FunctionGraph();
		if(arg==1)
		{
			//setting the line number
			getline(readLineAsStream,part,':');
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
		if(arg==2)
		{
			
			//setting the file address
			getline(readLineAsStream,part,' ');
			newCscopeOutputLine->setFileName(part);
			//setting the line number
			getline(readLineAsStream,part,' ');
			newCscopeOutputLine->setLine(atoi(part.c_str()));
			//setting the name of the tagAssociatedToFunction
			newCscopeOutputLine->setTagName(fileName);
			listOfCscopeOutput->push_back(newCscopeOutputLine);
			
			
		}
		
	}
	return listOfCscopeOutput;
}

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
		this->myTagManager->addTag(new Tag(outputFunction->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION));
			Tag *FunctionDefinitionTag=this->myTagManager->findSpecificTag(outputFunction->getTagName(),string("OutOfscope"),0);
			if(FunctionDefinitionTag!=NULL){
				delete listOfGlobalDefinition;
				return(FunctionDefinitionTag);
			}
		
	}
	// we have to find the right definition from the several we have
	else if(listOfGlobalDefinition->size()>1)
	{
		
	
		vector<vector<string>*>* listOFTypeForFunction=this->getNumberOfArgumentAndTypeForFunction(listOfGlobalDefinition);
		this->removeNotFunctionOutput(listOfGlobalDefinition);
		// getting rid of the .h and .c/c++ redundances ( the one in .h)
		listOfGlobalDefinition=this->getFunctionNotMacthingOnArgumentNumber(outputFunction,listOfGlobalDefinition,listOFTypeForFunction,1);
	
		this->removeMatchesFromHAndC(listOFTypeForFunction,listOfGlobalDefinition);
		if(listOfGlobalDefinition->size()==1)
		{
			//we can search for the tag directly now 
			Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfGlobalDefinition->at(0)->getTagName(),listOfGlobalDefinition->at(0)->getFileName(),listOfGlobalDefinition->at(0)->getLine());
			if(FunctionDefinitionTag!=NULL){
				delete listOfGlobalDefinition;
				return(FunctionDefinitionTag);
			}
		}
		else if(listOfGlobalDefinition->empty())
		{
	
			this->myTagManager->addTag(new Tag(outputFunction->getTagName(),string("OutOfscope"), 0, TYPE_FUNCTION));
			Tag *FunctionDefinitionTag=this->myTagManager->findSpecificTag(outputFunction->getTagName(),string("OutOfscope"),0);
			if(FunctionDefinitionTag!=NULL){
				delete listOfGlobalDefinition;
				return(FunctionDefinitionTag);
			}
				
		}
		else
		{
			
			Tag * FunctionDefinitionTag=this->myTagManager->findSpecificTag(listOfGlobalDefinition->at(0)->getTagName(),listOfGlobalDefinition->at(0)->getFileName(),listOfGlobalDefinition->at(0)->getLine());
			if(FunctionDefinitionTag!=NULL)
			{
				delete listOfGlobalDefinition;
				return (FunctionDefinitionTag);
			}
			/**
			*at this point we have differents function in the case of overloading for exemple 
			*then we have to identify which function is called thanks to the type of parameters
			*/
		}
		delete listOFTypeForFunction;
		
	}
		
	delete listOfGlobalDefinition;
	return NULL;
}
 

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
				commandToExecute=string("  egrep \"[a-zA-Z0-9_]* *\\(.*\\)\" -on  ")+arg;// +string("| awk -F: '{print $1\" \"$2}' ");
				break;
			case 4: 
				commandToExecute=string("  egrep \"")+arg+string("* *\\(.*\\)\" -onR  ")+this->myConfiguration->getSourcesDir()+string("| awk -F: '{print $1\" \"$2}' ");
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

std::vector<FunctionGraph*>* LauncherCscope::getGlobalDefinitionsFrom(std::string nameOfFunction)
{
	vector<FunctionGraph*>* outputglobalDefinition=new vector<FunctionGraph*>();
	outputglobalDefinition=this->cscopeOutputParser(this->launchExternalTool(0,nameOfFunction));
	
	return outputglobalDefinition;
}


void LauncherCscope::removeNotFunctionOutput(std::vector<FunctionGraph*>* listOfGlobalDefinitions)
{
	if(listOfGlobalDefinitions!=NULL)
	{
		for(unsigned int i=0;i<listOfGlobalDefinitions->size();i++)
		{
			if(listOfGlobalDefinitions->at(i)->getSignature().find(";")!=std::string::npos||listOfGlobalDefinitions->at(i)->getSignature().find("#define")!=std::string::npos||listOfGlobalDefinitions->at(i)->getSignature().find("assert")!=std::string::npos) 
			{
				delete listOfGlobalDefinitions->at(i);
				listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+i);
				i--;
				
			}
		}
	}
}

std::vector<std::vector<std::string>*>* LauncherCscope::getNumberOfArgumentAndTypeForFunction(std::vector<FunctionGraph*>* listOfGlobalDefinitions)
{	
	vector<vector<string>*>* listOfArgumentAndType=new vector<vector<string>*>();
	if(listOfGlobalDefinitions!=NULL){
		for(unsigned int i=0;i<listOfGlobalDefinitions->size();i++)
		{
			vector<string>* listOfArgumentType=new vector<string>();
			string stringToParse=listOfGlobalDefinitions->at(i)->getSignature().substr(listOfGlobalDefinitions->at(i)->getSignature().find(listOfGlobalDefinitions->at(i)->getTagName()));
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

bool LauncherCscope::isValidCaracter(char& caracterToTest)
{
	int asciValue=(int)caracterToTest;
	if((asciValue>=65&&asciValue<=90)||(asciValue>=97&&asciValue<=122)||(asciValue>=48&&asciValue<=57)||asciValue==95)return true;
	else return false;
}


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
						delete listOfGlobalDefinitions->at(j);
						delete listOfTypes->at(j);
						listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+j);
						listOfTypes->erase(listOfTypes->begin()+j);
						i--;
					}
					if(listOfGlobalDefinitions->at(j)->getFileName().find(".h"))
					{
						delete listOfGlobalDefinitions->at(j);
						delete listOfTypes->at(j);
						listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+j);
						listOfTypes->erase(listOfTypes->begin()+j);
						j--;
					}
				}
				
				delete listOfTypeForFirstMatch;
				delete listOfTypeForSecondMatch;
			}
		}
	}
}

std::string LauncherCscope::removeSpaceFromString(std::string stringToParse)
{
	string t ="";
	if(!stringToParse.empty())for(unsigned int i=0;i<stringToParse.length();i++)if(stringToParse.at(i)!=' ')t.push_back(stringToParse.at(i));
	return t;
}

std::vector<std::string>* LauncherCscope::getTypeForVariableUsedInFunctionCall(FunctionGraph* calledFunctionToFind)
{
	int positionOfFunctionName=calledFunctionToFind->getSignature().find(calledFunctionToFind->getTagName());
	string callExpressionwithOnlyFunctionNameAndParameters=calledFunctionToFind->getSignature().substr(positionOfFunctionName);
	std::vector<std::string>* variablesNames=this->getVariablesNamesInFunctionCall(callExpressionwithOnlyFunctionNameAndParameters);
	return variablesNames;
	
}

int LauncherCscope::getNumberOfVariableUsedInFunctionCall(FunctionGraph* calledFunctionToFind)
{
	int number=0;	
	std::vector<std::string>* variablesNames=this->getTypeForVariableUsedInFunctionCall(calledFunctionToFind);
	if(variablesNames!=NULL) number=variablesNames->size();
	delete variablesNames;
	return number;
}

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

void LauncherCscope::removeNotMatchingFunctionOnArgumentNumber(void* calledFunctionToFind,vector<FunctionGraph*>* listOfGlobalDefinitions,vector<vector<string>*>* listOfTypesforGlobalDefinitions,int arg)
{
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
				delete  listOfGlobalDefinitions->at(i);
				listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+i);
				i--;
			}
		}
	}
}

std::vector<FunctionGraph*>* LauncherCscope::getFunctionNotMacthingOnArgumentNumber(void* calledFunctionToFind,std::vector<FunctionGraph*>* listOfGlobalDefinitions,vector<vector<string>*>* listOfTypesforGlobalDefinitions,int arg)
{
	vector<FunctionGraph*>* newListOfGlobalDefinition=new vector<FunctionGraph*>();
	if(arg==1)
	{
		FunctionGraph*calledFunctionToFindCasted=(FunctionGraph*)calledFunctionToFind;
		unsigned int numberOfArgument=this->getNumberOfVariableUsedInFunctionCall(calledFunctionToFindCasted);
		for(int i=0;i<listOfTypesforGlobalDefinitions->size();i++){
		
			if((listOfTypesforGlobalDefinitions->at(i)->size())!=numberOfArgument) {
				
				if(listOfGlobalDefinitions->size()>i) newListOfGlobalDefinition->push_back(listOfGlobalDefinitions->at(i));
			
				
			}
		}
		
	}
	return newListOfGlobalDefinition;
}

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
		bool weAreInComment=false;
		/**
		 * skip the n-first line before function definition
		 */
		for(unsigned int i=1;i<tagAssociatedToFunction->getLineNumber();i++) 
		{
			getline(stream,currentLine);
		
		}
		bool functionNameAlreadyRead=false;
		bool endOfFunctionFound=false;
		bool weAreInString=false;
		/**
		 * looking for brace brackets
		 * case division in order to find the first brace bracket
		 */
		do
		{
				if(currentLine.find(" /*")!=string::npos||currentLine.find("/*")!=string::npos||currentLine.find("  /*")!=string::npos||currentLine.find("#if")!=string::npos||currentLine.find("#ifdef")!=string::npos)weAreInComment=true;
				
				if(weAreInComment==0){
					if(numberOfLine==0)
					{
						getline(stream,currentLine);
						functionInitialPos=currentLine.find(tagAssociatedToFunction->getName());
						
						for(unsigned int p=functionInitialPos;p<currentLine.length();p++)
						{
							if(currentLine.at(p)==(char)34)
							{
								if(p>0)
								{
									if(currentLine.at(p-1)!=(char)39&&currentLine.at(p-1)!=(char)49&&currentLine.at(p-1)!=(char)47)
									{
										if(weAreInString==true) weAreInString=false;
										else weAreInString=true;
									}
								}
							}
							if(currentLine.at(p)=='{'&&weAreInString==false)
							{	if(p>0)
								{
									if(currentLine.at(p-1)!='\''&&currentLine.at(p-1)!='"'&&currentLine.at(p-1)!='='&&currentLine.at(p-1)!=(char)39)
									{
										niveauBraceBracket++;
										firstBraceBracketAlreyFound=true;
									}
								}
								else
								{
									niveauBraceBracket++;
									firstBraceBracketAlreyFound=true;
								}
							}if(currentLine.at(p)=='}'&&weAreInString==false)
							{
								if(p>0)
								{
									if(currentLine.at(p-1)!='\''&&currentLine.at(p-1)!='"'&&currentLine.at(p-1)!='='&&currentLine.at(p-1)!=(char)39)
									{
												niveauBraceBracket--;
									}
								}
								else{
									niveauBraceBracket--;
								}
							}
							
						}
						functionNameAlreadyRead=true;
					}
					else
					{
					
						for(unsigned int p=0;p<currentLine.length();p++)
						{	
							if(currentLine.at(p)==(char)34)
							{
								if(p>0){
								
									if(currentLine.at(p-1)!=(char)39&&currentLine.at(p-1)!=(char)49&&currentLine.at(p-1)!=(char)47)
									{
										if(weAreInString==true) weAreInString=false;
										else weAreInString=true;
									}
								}
							}
							if(currentLine.at(p)=='{'&&weAreInString==false)
							{	if(p>0)
								{
								
									if(currentLine.at(p-1)!='\''&&currentLine.at(p-1)!='"'&&currentLine.at(p-1)!='='&&currentLine.at(p-1)!=(char)39)
									{
										niveauBraceBracket++;
										firstBraceBracketAlreyFound=true;
									}
								}else{
										niveauBraceBracket++;
										firstBraceBracketAlreyFound=true;
								}
							}if(currentLine.at(p)=='}'&&weAreInString==false)
							{
								if(p>0)
								{
									if(currentLine.at(p-1)!='\''&&currentLine.at(p-1)!='"'&&currentLine.at(p-1)!='='&&currentLine.at(p-1)!=(char)39)niveauBraceBracket--;
								}else
									niveauBraceBracket--;
								}
							}
						}
					}
					
				}
			if(currentLine.find(" */")!=string::npos||currentLine.find("*/")!=string::npos||currentLine.find("  */")!=string::npos||currentLine.find("#endif")!=string::npos)weAreInComment=false;
				
			
			if(functionNameAlreadyRead==true&&niveauBraceBracket==0&&firstBraceBracketAlreyFound)endOfFunctionFound=true;
			numberOfLine++;
			
		}while(endOfFunctionFound==false&&getline(stream,currentLine));
	
		if(niveauBraceBracket==0)numberOfEndLine=numberOfLine+tagAssociatedToFunction->getLineNumber()-1;
		else numberOfEndLine=tagAssociatedToFunction->getLineNumber();
		
	}	
	 return numberOfEndLine;
}

void LauncherCscope::removeFromListFunctionNotBelonginToStackCall(int lineStart,int lineStop, vector<FunctionGraph*>* listOfFunctionCalled,void * functionAssociatedToTag,int argForSensOfUse)
{
			if( argForSensOfUse==1)
			{
				Tag * tagAssociatedToFunction=(Tag*)functionAssociatedToTag;
				for(unsigned int i=0;i<listOfFunctionCalled->size();i++)
				{
			
					if((listOfFunctionCalled->at(i)->getLine()>=lineStop)||(listOfFunctionCalled->at(i)->getLine()<=lineStart)||(listOfFunctionCalled->at(i)->getFileName().compare(tagAssociatedToFunction->getFileName())!=0))
					{	
						delete listOfFunctionCalled->at(i);
						listOfFunctionCalled->erase(listOfFunctionCalled->begin()+i);
						i--;
					}
				}
			}
			if( argForSensOfUse==2)
			{
				for(unsigned int i=0;i<listOfFunctionCalled->size();i++)
				{
					FunctionGraph* functionGraphAssociatedToFunction=(FunctionGraph*)functionAssociatedToTag;
					FunctionGraph* currentDef=listOfFunctionCalled->at(i);
					Tag* myTag=this->myTagManager->findSpecificTag(currentDef->getTagName(),currentDef->getFileName(),currentDef->getLine());
					if(myTag==NULL)
					{
						delete listOfFunctionCalled->at(i);
						listOfFunctionCalled->erase(listOfFunctionCalled->begin()+i);
						i--;
					}else{
						int lineStartForDefinition=currentDef->getLine();
						int lineStopForDefinition=this->getLineForEndOfFunctionDefinition(myTag);
					
						if(functionGraphAssociatedToFunction->getLine()<lineStartForDefinition||functionGraphAssociatedToFunction->getLine()>lineStopForDefinition||functionGraphAssociatedToFunction->getFileName().compare(currentDef->getFileName())!=0)
						{
								delete listOfFunctionCalled->at(i);
								listOfFunctionCalled->erase(listOfFunctionCalled->begin()+i);
								i--;
						}
					}
				}
			}	
}
void LauncherCscope::removeMatchesFromHAndC(std::vector<FunctionGraph*>* listOfGlobalDefinitions)
{
	for(vector<FunctionGraph*>::iterator it = listOfGlobalDefinitions->begin(); it != listOfGlobalDefinitions->end();){
		assert((*it)!=NULL);
		if((*it)->getFileName().find(".c")==string::npos)
		{
			delete *it;
			listOfGlobalDefinitions->erase(it);
		}else
		{
			it = it+1 ;
		}
	}
}

void LauncherCscope::removeNotConcernedDefinitionBasedOnFileName(std::vector< FunctionGraph* >* listOfGlobalDefinitions, std::string  fileName)
{
	
	for(unsigned int i=0;i<listOfGlobalDefinitions->size();i++)
	{
		if((listOfGlobalDefinitions->at(i)->getFileName().find(fileName)==string::npos))
		{
			delete listOfGlobalDefinitions->at(i);
			listOfGlobalDefinitions->erase(listOfGlobalDefinitions->begin()+i);
			i--;
		}
	}
}

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
	||nameOfSymbolFound.compare("defined")==0||nameOfSymbolFound.compare("#define")==0
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
		}while(firstBraceBracketAlreyFound==false);
	}
	string callExpressionwithOnlyFunctionNameAndParameters=listOfArgument;
	std::vector<std::string>* variablesNames=this->getVariablesNamesInFunctionCall(callExpressionwithOnlyFunctionNameAndParameters);
	numberOfVariable=variablesNames->size();
	delete variablesNames;
	return numberOfVariable;
	
}

void LauncherCscope::removeFromListWhereTagNameIsDefinition(std::vector< FunctionGraph* >* listOfCallingFunction)
{
	for(vector<FunctionGraph*>::iterator it = listOfCallingFunction->begin(); it != listOfCallingFunction->end();){
		assert((*it)!=NULL);
		if (this->myTagManager->findSpecificTag((*it)->getTagName(),(*it)->getFileName(),(*it)->getLine())==NULL)it= it+1; 
		else listOfCallingFunction->erase(it);
	}
	
}

std::vector<Tag*>* LauncherCscope::fullFilleWithListOftagForEachFile(std::map< string, std::vector< Tag* >* >* listOfFileWithListOfTagFunctionType,std::vector< FunctionGraph* >*listOfCallingFunction )
{
	std::vector<Tag*>* listOfTagToReturn=new std::vector<Tag*>();

	for(int i=0;i<listOfCallingFunction->size();i++)
	{
		FunctionGraph* currentOutputFunction=listOfCallingFunction->at(i);
		std::map<std::string,std::vector<Tag*>*>::iterator listOfTagForFile=listOfFileWithListOfTagFunctionType->find(currentOutputFunction->getFileName());
		std::pair<std::string,std::vector<Tag*>*> myPair;
		if(listOfTagForFile==listOfFileWithListOfTagFunctionType->end())
		{
			std::vector<Tag*>* listOfTag=this->myTagManager->getTagsByTypeAndFile(currentOutputFunction->getFileName(),TYPE_FUNCTION);
			myPair.first=currentOutputFunction->getFileName();
			myPair.second=listOfTag;
			listOfFileWithListOfTagFunctionType->insert(myPair);
		}
		else
		{
			myPair=*listOfTagForFile;
		}
		std::vector<Tag*>* listOfTagToconcat=this->getTagByNearestPositionFromFunctionOutput(myPair.second,currentOutputFunction);
		listOfTagToReturn->insert(listOfTagToReturn->end(),listOfTagToconcat->begin(),listOfTagToconcat->end());
	}
	return listOfTagToReturn;
}

std::vector<Tag*>* LauncherCscope::getTagByNearestPositionFromFunctionOutput(std::vector< Tag* >* listOfTagInfileMatchingCurrentOutputFunction, FunctionGraph* currentOutputFunction)
{
	std::vector< Tag* >* listOfTagToReturn=new std::vector< Tag* >();
	
	for(int i=0;i<listOfTagInfileMatchingCurrentOutputFunction->size();i++)
	{
		Tag * currTag=listOfTagInfileMatchingCurrentOutputFunction->at(i);
		int lineStartTag=currTag->getLineNumber();
		int lineStopTag=this->getLineForEndOfFunctionDefinition(currTag);
		if(lineStartTag<currentOutputFunction->getLine()&&lineStopTag>currentOutputFunction->getLine()) listOfTagToReturn->push_back(currTag);
		
	}
	return listOfTagToReturn;
}

bool LauncherCscope::checkFunctionIsTrulyCallingThisFunction(Tag* callingFunction, Tag* calledFunction)
{
	
	int lineStop=this->getLineForEndOfFunctionDefinition(callingFunction);
	bool callf=false;
	ifstream stream(callingFunction->getFileName().c_str());
	if(stream!=0){
		string currentLine;
		int currentLineNumber=0;
		/**
		 * skip the n-first line beforde function definition
		 */
		for(unsigned int i=1;i<callingFunction->getLineNumber();i++) 
		{
			getline(stream,currentLine);
		}
		do {
			
			if(currentLine.find(calledFunction->getName())!=string::npos){
				callf=true;
				break;
				
			}
			currentLineNumber++;
		}while(getline(stream,currentLine)||currentLineNumber<lineStop);
	}
		return callf;
}

void LauncherCscope::removeSameTagForCalling(std::vector< Tag* >* listOfTagToReturn, Tag* tagAssociatedToFunction)
{
	for(vector<Tag*>::iterator it = listOfTagToReturn->begin(); it != listOfTagToReturn->end();){
		if((((std::string)(*it)->getName()).compare(tagAssociatedToFunction->getName()))==0&&(((std::string)(*it)->getFileName()).compare(tagAssociatedToFunction->getFileName()))==0
		&&(((int)(*it)->getLineNumber())==tagAssociatedToFunction->getLineNumber()))
		{
			listOfTagToReturn->erase(it);
		}else{
			it=it+1;
		}
	}
}

