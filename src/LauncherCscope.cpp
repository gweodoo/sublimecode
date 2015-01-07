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





bool LauncherCscope::initExternalTool(){
	
	if(this->isLaunched==true){
	
		return this->isLaunched;
	}
	else
	{
		if(system("cd /../ && cscope -b -q -k")==-1)
		{
			perror("Initializing cscope");
		}
	}
}
void* LauncherCscope::launchCommandExternalTool(int command, std::string arg)
{

}

bool LauncherCscope::getIsLaunched(){
	
	return this->isLaunched;
}

	