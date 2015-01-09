/***************************************************************************/
/*                                                                        */
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

#include "FunctionGraph.h"

/**
 * classical constructor with attribute initialization parameters
 */
FunctionGraph::FunctionGraph(std::string fileName,std::string tagName,std::string signature,int line )
{

	this->fileName=fileName;
	this->tagName=tagName;
	this->line=line;
	this->signature=signature;
}

/**
 * classical constructor without attribute initialization
 */
FunctionGraph::~FunctionGraph()
{
	this->signature=std::string("");
}
/**
 * ---------------getters definition---------------------------
 */
std::string FunctionGraph::getFileName()
{
	return fileName;
}
int FunctionGraph::getLine()
{
	return line;
}
std::string FunctionGraph::getSignature()
{
	
	return this->signature;
}
std::string FunctionGraph::getTagName()
{
	return tagName;
}
/**
 * --------------setters definition----------------------------
 */
void FunctionGraph::setFileName(std::string fileName)
{
	this->fileName=fileName;
}
void FunctionGraph::setLine(int line)
{
	this->line=line;
}
void FunctionGraph::setTagName(std::string tagName)
{
	this->tagName=tagName;
}
FunctionGraph::FunctionGraph()
{
	
}
void FunctionGraph::setSignature(std::string signature)
{
	this->signature=signature;
}







