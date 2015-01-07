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


class LauncherCscope: public  Launcher {

private :
	 bool isLaunched;
	 Configuration* myConfiguration;
	 std::vector<Tag*>* cscopeOutputParser(std::string output);
	 std::string getPartFromString(std::string stringToSearchIn,int numberOfPar);
public :
	 LauncherCscope(Configuration* myconfiguration);
	 bool initExternalTool();
	 bool closeExternalTool();
	 std::vector<Tag*>* launchCommandExternalTool(int command, std::string arg);
	 bool getIsLaunched();
	 

};
#endif