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

#ifndef LAUNCHER_H
#define LAUNCHER_H
#include"Utils.h"
#include "tags/Tag.h"
#include "FunctionGraph.h"
/**
 * main interface for an external tool launcher
 */
class Launcher {

public :
	virtual bool initExternalTool()=0;
	virtual bool closeExternalTool()=0;
	virtual std::vector<Tag*>* launchCommandExternalTool(int command, Tag * tagAssociatedToFunction)=0;
	
	virtual int launchCommandExternalTool(Tag *tagAssociatedToFunction)=0;
};

#endif
