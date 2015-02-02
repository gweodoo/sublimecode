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
	/**
	 * return the list of function called by the tag
	 * @param[in] tagAssociatedToFunction tag for which the list of function called is searched
	 * @return the list of called functions
	 **/
	virtual std::vector<Tag*>*  getFunctionsCalledBy(Tag * tagAssociatedToFunction)=0;
	/**
	 * return the list of function calling this tag
	 * @param[in] tagAssociatedToFunction tag for which the list of the calling function is searched
	 * @return the list of calling functions
	 * 
	 **/
	virtual std::vector<Tag*>* getFunctionsCallingThis(Tag * tagAssociatedToFunction)=0;
	/**
	 * calculater the end of a function definition
	 * @param[in] tagAssociatedToFunction the tag which definition's end is looked for
	 */
	virtual int getFunctionLength(Tag * tagAssociatedToFunction)=0;
	/**
	 * calsical destructor
	 **/
	virtual ~Graph(){};
	
};

#endif
