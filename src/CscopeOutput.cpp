#include "CscopeOutput.h"

CscopeOutput::CscopeOutput(std::string fileName,std::string tagName,std::string signature,int line )
{

	this->fileName=fileName;
	this->tagName=tagName;
	this->line=line;
	this->signature=signature;
}

CscopeOutput::~CscopeOutput()
{

}
std::string CscopeOutput::getFileName()
{
	return fileName;
}
int CscopeOutput::getLine()
{
	return line;
}
std::string CscopeOutput::getSignature()
{
	return signature;
}
std::string CscopeOutput::getTagName()
{
	return tagName;
}
void CscopeOutput::setFileName(std::string fileName)
{
this->fileName=fileName;
}
void CscopeOutput::setLine(int line)
{
this->line=line;
}
void CscopeOutput::setTagName(std::string tagName)
{
this->tagName=tagName;
}
CscopeOutput::CscopeOutput()
{

}
void CscopeOutput::setSignature(std::string signature)
{
this->signature=signature;
}







