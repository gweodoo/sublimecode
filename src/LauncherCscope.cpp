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

using namespace std;


LauncherCscope::LauncherCscope(Configuration* myconfiguration)
{
this->myConfiguration=myconfiguration;
this->isLaunched=false;
}


bool LauncherCscope::initExternalTool(){
	
	if(this->isLaunched==true){
	
		return this->isLaunched;
	}
	else
	{
		string commandCscopeConstruct=string("cd ") +(string)this->myConfiguration->getSourcesDir() +string(" && cscope -bqk  ");
		string commandFileMove_1=string("mv ")+(string)this->myConfiguration->getSourcesDir()+string("/cscope.in.out ")+(string)this->myConfiguration->getDestDir();
		string commandFileMove_2=string("mv ")+(string)this->myConfiguration->getSourcesDir()+string("/cscope.out ")+(string)this->myConfiguration->getDestDir();
		string commandFileMove_3=string("mv ")+(string)this->myConfiguration->getSourcesDir()+string("/cscope.po.out ")+(string)this->myConfiguration->getDestDir();

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
void* LauncherCscope::launchCommandExternalTool(int command, std::string arg)
{

	void * responseToReturn=NULL;
	FILE * myCommandOutput=NULL;
	char buffer[256];
	string result="";
	
	if(!arg.empty()){
		switch(command)
		{
			/** list of the function called by**/
			case 1:
				string command=string("cd ")+this->myConfiguration->getDestDir()+string(" && cscope -d -L2 ")+arg;
				cout<<command<<endl;
				if((myCommandOutput=popen(command.c_str(),"r"))==NULL)perror("searching Called Function");
				
				while(!feof(myCommandOutput)){
				
					if(fgets(buffer,256,myCommandOutput)!=NULL){
					
						result+=buffer;
					}
				}
				cout<<result<<endl;	
				break;
				
			
		}
	}
		
}

bool LauncherCscope::getIsLaunched(){
	
	return this->isLaunched;
}

	