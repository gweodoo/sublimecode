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
