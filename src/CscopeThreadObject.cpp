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
#include "CscopeThreadObject.h"
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include<iostream>
#include<string>
#include <list>
#include "FunctionGraph.h"
#include "TagImpl.h"
using namespace std ;
CscopeThreadObject::CscopeThreadObject()
{
	this->lastIndex=0;
}
//list of Cscope output function to analyze
std::vector<std::vector<FunctionGraph*>*>* CscopeThreadObject::getListOfFunctionToAnalyze()
{
	if(this->listOfFunctionToAnalyze==NULL) this->listOfFunctionToAnalyze=new vector<vector<FunctionGraph*>*>();
	return this->listOfFunctionToAnalyze;
}
void CscopeThreadObject::setListOfFunctionToAnalyze(std::vector<std::vector<FunctionGraph*>*>* list)
{
	this->listOfFunctionToAnalyze=list;
}
//list of Tag to return after analyze
std::vector<std::vector<Tag*>*>* CscopeThreadObject::getListOfTagAfterAnalyze()
{
	if(this->listOfTagAfterAnalyze==NULL) this->listOfTagAfterAnalyze=new vector<vector<Tag*>*>();
	return this->listOfTagAfterAnalyze;
}
void CscopeThreadObject::setListOfTagAfterAnalyze(std::vector<std::vector<Tag*>*>*list)
{
	this->listOfTagAfterAnalyze=list;
}


int CscopeThreadObject::getLastIndex()
{
	return this->lastIndex;
}
void CscopeThreadObject::setLastIndex(int lastIndex)
{
		this->lastIndex=lastIndex;
}

vector<bool>* CscopeThreadObject::getListOfIndexDone()
{
	return this->listOfIndexDone;
}
void CscopeThreadObject::setListOfIndexDone(vector< bool >* listOfIndexDone)
{
	 this->listOfIndexDone=listOfIndexDone;
}

void CscopeThreadObject::reInitializeObject()
{
	this->listOfIndexDone=new vector<bool>();
	this->listOfTagAfterAnalyze=new vector<vector<Tag*>*>();
	this->listOfFunctionToAnalyze=new vector<vector<FunctionGraph*>*>();
	this->lastIndex=0;
}
void CscopeThreadObject::InitializeListOfIndexDoneWithNumber(int lengthToInitializeWith)
{
	this->listOfIndexDone=new vector<bool>();
	for(int i =0;i<lengthToInitializeWith;i++) this->listOfIndexDone->push_back(false);
}






