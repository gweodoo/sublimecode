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

#ifndef GRAPH_H
#define GRAPH_H
#include "tags/Tag.h"

/**
 * calling/called graph for methods abstract interface
 */
class Graph {

public : 
	virtual std::vector<Tag*>*  getFunctionsCalledBy(Tag * tagAssociatedToFunction)=0;
	virtual std::vector<Tag*>* getFunctionsCallingThis(Tag * tagAssociatedToFunction)=0;
	virtual int getFunctionLength(Tag * tagAssociatedToFunction)=0;
	virtual ~Graph(){};
	
};

#endif
