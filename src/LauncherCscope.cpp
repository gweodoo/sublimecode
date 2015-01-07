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
#include "CscopeOutput.h"

using namespace std;


LauncherCscope::LauncherCscope(Configuration* myconfiguration,TagsManager*myTagManager)
{
	this->myTagManager=myTagManager;
	this->myConfiguration=myconfiguration;
	this->isLaunched=false;
}


bool LauncherCscope::initExternalTool(){
	
	scDebug("Start initExternalTool");
	if(this->isLaunched==true){
	
		return this->isLaunched;
	}
	else
	{
		string commandCscopeConstruct=string("cd ") +(string)this->myConfiguration->getSourcesDir() +string(" && cscope -bqkR ");
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
 * 
 */
vector<Tag*>* LauncherCscope::launchCommandExternalTool(int command, std::string arg)
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
			case 1:
				commandToExecute=string("cd ")+this->myConfiguration->getDestDir()+string(" && cscope -d -L2 ")+arg;
			break;
			case 2:
				commandToExecute=string("cd ")+this->myConfiguration->getDestDir()+string(" && cscope -d -L3 ")+arg;
			break;
			case 3:
				commandToExecute=string("cd ")+this->myConfiguration->getDestDir()+string(" && cscope -d -L8 ")+arg;
			break;
		}
		if(command==1||command==2||command==3){
		
			if((myCommandOutput=popen(commandToExecute.c_str(),"r"))==NULL)perror("searching Called Function");
			
			while(!feof(myCommandOutput)){
			
				if(fgets(buffer,256,myCommandOutput)!=NULL){
				
					result.append(buffer);
				}
				
			}
			if(myCommandOutput) pclose(myCommandOutput);
			
			return this->cscopeOutputParser(result);
							
			
		}
		
	}
	
		
}

bool LauncherCscope::getIsLaunched(){
	
	return this->isLaunched;
}

std::vector<Tag*>* LauncherCscope::cscopeOutputParser(std::string output){

	vector<CscopeOutput*>* listOfCscopeOutput=new vector<CscopeOutput*>();
	
	this->listOfLastTagAsked=new vector<Tag*>();
	stringstream outputAsStream(output);
	string readLine;
	while(getline(outputAsStream,readLine)){
	
		
		stringstream readLineAsStream(readLine);
		string part;
		int count=0;
		CscopeOutput* newCscopeOutputLine=new CscopeOutput();
		while(getline(readLineAsStream,part,' ')){
				
	
			
			switch(count){
			
				
				case 0:
					newCscopeOutputLine->setFileName(part);
					break;
				case 1:
					newCscopeOutputLine->setTagName(part);
					break;
				case 2:
					newCscopeOutputLine->setLine(atoi(part.c_str()));
					break;
				case 3:
					newCscopeOutputLine->setSignature(part);
					break;
					
				
			}
			count++;
		}
		count=0;
		listOfCscopeOutput->push_back(newCscopeOutputLine);
	}
	for(int i=0;i<listOfCscopeOutput->size();i++)
	{
	

		Tag* myNewTag=this->myTagManager->findSpecificTag(listOfCscopeOutput->at(i)->getTagName(),listOfCscopeOutput->at(i)->getFileName(),listOfCscopeOutput->at(i)->getLine());
		if(myNewTag!=NULL) this->listOfLastTagAsked->push_back(myNewTag);
		
	}
	
	return this->listOfLastTagAsked;
		
	
}

	