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

#ifndef CSCOPETHREADOBJECT_H
#define CSCOPETHREADOBJECT_H

#include "Tag.h"
#include "FunctionGraph.h"

class CscopeThreadObject
{
public:
CscopeThreadObject();


std::vector<std::vector<FunctionGraph*>*>* getListOfFunctionToAnalyze();
void setListOfFunctionToAnalyze(std::vector<std::vector<FunctionGraph*>*>* list);
std::vector<std::vector<Tag*>*>* getListOfTagAfterAnalyze();
void setListOfTagAfterAnalyze(std::vector<std::vector<Tag*>*>* list);
int getLastIndex();
void setLastIndex(int lastIndex);
std::vector<bool>* getListOfIndexDone();
void setListOfIndexDone(std::vector<bool>* listOfIndexDone);
void reInitializeObject();
void InitializeListOfIndexDoneWithNumber(int lengthToInitializeWith);

private :
	std::vector<std::vector<FunctionGraph*>*>*listOfFunctionToAnalyze;
	std::vector<std::vector<Tag*>*>* listOfTagAfterAnalyze;
	int lastIndex;
	std::vector<bool>* listOfIndexDone;

	

};
#endif // CSCOPETHREADOBJECT_H
