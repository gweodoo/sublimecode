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
#ifndef FUNCTIONGRAPH_H
#define FUNCTIONGRAPH_H

#include"Utils.h"

/**
 * Represents a Line output given by cscope;
 * it's composed of:
 * 			- output name
 * 			- output file name
 * 			- output line number
 * 			- output signature 
 * 				it can be the signature of the function if it's a definition or the expression of a function call 
 */

class FunctionGraph
{
public:
	/**
	 * simple constructor with 4 parts initialization
	 * @param[in] fileName the file Name for the matching output
	 * @param[in] tagName the name of the function output
	 * @param[in] signature the expression
	 * @param[in] line the line where the expression is localisez
	 * 
	 */
	FunctionGraph(std::string fileName,std::string tagName,std::string signature,int line );
	/**
	 * simple constructir
	 */
	FunctionGraph();
	/**
	 * simple destructor
	 * 
	 **/
	~FunctionGraph();
	/**
	* classical getter for fileName-tagName-Line-Signature
	*/
	std::string getFileName();
	std::string getTagName();
	std::string getSignature();
	int getLine();
	/**
	* classical setter for fileName-tagName-Line-Signature
	*/
	void setFileName(std::string fileName);
	void setTagName(std::string tagName);
	void setSignature(std::string signature);
	void setLine(int line);

private:
	/**
	 * Needs 4 attributes Cscope always giving as output fileName-tagName-Line-Signature
	 */
	std::string fileName;
	std::string tagName;
	std::string signature;
	int line;

};

#endif // FUNCTIONGRAPH_H
