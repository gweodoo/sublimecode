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







