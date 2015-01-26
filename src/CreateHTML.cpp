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

#include <iostream>
#include <fstream> 
#include <sstream> 
#include "CreateHTML.h"
#include <QtXml>
#include <QtCore>
#include <QDebug>
#include <QXmlQuery>
#include <vector>  

CreateHTML::~CreateHTML(){}

CreateHTML::CreateHTML(Configuration* c, Runner *runner) : config(c), runner(runner) {}

void CreateHTML::generateTagByFile(string filename)
{
	list = runner->getTagsByFile(config->getSourcesDir()+filename);
}

void CreateHTML::generateTagByTag(string tag)
{
	list = runner->getTagsByName(tag);
}

void CreateHTML::generateTagByType(int type)
{
	list = runner->findTagsByType(static_cast<tagType>(type));
}

void CreateHTML::createXMLSearchByTags(string tag)
{	
	QFile file(QString::fromUtf8(config->getDestDir().c_str())+"/myXLMSearchByTags_"+QString::fromStdString(tag)+".xml"); 
	QDomDocument document;

	QDomElement root = document.createElement("SearchByTags");
	document.appendChild(root);

	for (size_t i=0; i<list->size(); i++)
	{
		QDomElement element = document.createElement("Tags");
		
		QDomElement element1 = document.createElement("Number");
		QDomElement element2 = document.createElement("Line");
	        QDomElement element3 = document.createElement("Path");
	        QDomElement element4 = document.createElement("Type");

		element.appendChild(element1);
		element.appendChild(element2);
		element.appendChild(element3);
		element.appendChild(element4);
		
		ostr << list->at(i)->getLineNumber();
		std::string lineNumberString = ostr.str();
		ostr.str("");
		ostr.clear();
		
		string converti = list->at(i)->getFileName();
		
		QDomText txt1 = document.createTextNode(QString::number(i+1));
		QDomText txt2 = document.createTextNode(QString::fromStdString(lineNumberString));
		QDomText txt3 = document.createTextNode(QString::fromStdString(converti.substr(config->getSourcesDir().size())));
		QDomText txt4 = document.createTextNode(QString::fromStdString(tabTypeNames[list->at(i)->getType()]));

		element1.appendChild(txt1);
		element2.appendChild(txt2);
		element3.appendChild(txt3);
		element4.appendChild(txt4);
		
		root.appendChild(element);
	}
	
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Open file failed";
	}
	else
	{
		QTextStream stream(&file);
		stream << document.toString();
		file.close();
		qDebug() << "Done";
	}
}

void CreateHTML::createXMLSearchByType(int type)
{	
	QFile file(QString::fromUtf8(config->getDestDir().c_str())+"/myXLMSearchByType_"+tabTypeNames[type]+".xml"); 
	QDomDocument document;
	
	QDomElement root = document.createElement("SearchByType");
	document.appendChild(root);

	for (size_t i=0; i<list->size(); i++)
	{
		QDomElement element = document.createElement("Type");
		
		QDomElement element1 = document.createElement("Number");
		QDomElement element2 = document.createElement("Line");
	        QDomElement element3 = document.createElement("Path");
	        QDomElement element4 = document.createElement("Name");

		element.appendChild(element1);
		element.appendChild(element2);
		element.appendChild(element3);
		element.appendChild(element4);
		
		ostr << list->at(i)->getLineNumber();
		std::string lineNumberString = ostr.str();
		ostr.str("");
		ostr.clear();
		
		string converti = list->at(i)->getFileName();
		
		QDomText txt1 = document.createTextNode(QString::number(i+1));
		QDomText txt2 = document.createTextNode(QString::fromStdString(lineNumberString));
		QDomText txt3 = document.createTextNode(QString::fromStdString(converti.substr(config->getSourcesDir().size())));
		QDomText txt4 = document.createTextNode(QString::fromStdString(list->at(i)->getName()));

		element1.appendChild(txt1);
		element2.appendChild(txt2);
		element3.appendChild(txt3);
		element4.appendChild(txt4);
		
		root.appendChild(element);
	}
	
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Open file failed";
	}
	else
	{
		QTextStream stream(&file);
		stream << document.toString();
		file.close();
		qDebug() << "Done";
	}
}

void CreateHTML::createXMLSearchByFile(string filename)
{
	QString filename_modified = QString::fromStdString(filename);
	filename_modified.replace("/","_");
	QFile file(QString::fromUtf8(config->getDestDir().c_str())+"/myXLMSearchByFile_"+filename_modified+".xml"); 
	QDomDocument document;
	
	QDomElement root = document.createElement("SearchByFile");
	document.appendChild(root);

	for (size_t i=0; i<list->size(); i++)
	{
		QDomElement element = document.createElement("File");
		
		QDomElement element1 = document.createElement("Number");
		QDomElement element2 = document.createElement("Line");
	        QDomElement element3 = document.createElement("Name");
	        QDomElement element4 = document.createElement("Type");

		element.appendChild(element1);
		element.appendChild(element2);
		element.appendChild(element3);
		element.appendChild(element4);
		
		ostr << list->at(i)->getLineNumber();
		std::string lineNumberString = ostr.str();
		ostr.str("");
		ostr.clear();
				
		QDomText txt1 = document.createTextNode(QString::number(i+1));
		QDomText txt2 = document.createTextNode(QString::fromStdString(lineNumberString));
		QDomText txt3 = document.createTextNode(QString::fromStdString(list->at(i)->getName()));
		QDomText txt4 = document.createTextNode(QString::fromStdString(tabTypeNames[list->at(i)->getType()]));

		element1.appendChild(txt1);
		element2.appendChild(txt2);
		element3.appendChild(txt3);
		element4.appendChild(txt4);
		
		root.appendChild(element);
	}
	
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Open file failed";
	}
	else
	{
		QTextStream stream(&file);
		stream << document.toString();
		file.close();
		qDebug() << "Done";
	}
}

int CreateHTML::getTotalLine(std::string content)
{
	int lines_count = 1;
	for(size_t i=0; i<content.length(); i++){
		if(content.at(i) == '\n'){
			lines_count++;
		}
	}
	return lines_count;
}

void CreateHTML::createListHighlightFunction(Tag* tag)
{
	beforeFunction.clear();
	inFunction.clear();
	afterFunction.clear();
	
	std::string line;
	int lines_count = 1;
		
	std::ifstream ifs1(tag->getFileName().c_str());
	std::string content((std::istreambuf_iterator<char>(ifs1)),(std::istreambuf_iterator<char>()));
	
	int TotalLine = getTotalLine(content);
	int BeginLineFunction = tag->getLineNumber();
	int EndLineFunction = tag->getLineNumber() + runner->getFunctionLength(tag);
	
	std::ifstream ifs(tag->getFileName().c_str());
	
	while(std::getline(ifs, line)){
		if(lines_count>0 && lines_count<BeginLineFunction){
			beforeFunction.push_back(line+"\n");
		}
		else if (lines_count>=BeginLineFunction && lines_count<=EndLineFunction){
			inFunction.push_back(line+"\n");
		}
		else if(lines_count>EndLineFunction && lines_count<=TotalLine){
			afterFunction.push_back(line+"\n");
		}
		lines_count++;
	}
	createXMLHighlightFunction(beforeFunction, inFunction, afterFunction);
}

string CreateHTML::stringFromVector(vector< string > vector)
{
	std::ostringstream oss;

	if (!vector.empty())
	{
		std::copy(vector.begin(), vector.end()-1,std::ostream_iterator<string>(oss, ""));
		oss << vector.back();
	}

	return oss.str();
}

void CreateHTML::createXMLHighlightFunction(vector< string > beforeFunction, vector< string > inFunction, vector< string > afterFunction)
{	
	QFile file(QString::fromUtf8(config->getDestDir().c_str())+"/myXLMHighlightFunction.xml"); 
	QDomDocument document;
	
	QDomElement root = document.createElement("HighlightFunction");
	document.appendChild(root);
	
	QDomElement element = document.createElement("Highlight");

	QDomElement element1 = document.createElement("BeforeFunction");
	QDomElement element2 = document.createElement("InFunction");
	QDomElement element3 = document.createElement("AfterFunction");
	
	element.appendChild(element1);
	element.appendChild(element2);
	element.appendChild(element3);
	
	QDomText txt1 = document.createTextNode(QString::fromStdString(stringFromVector(beforeFunction)));
	QDomText txt2 = document.createTextNode(QString::fromStdString(stringFromVector(inFunction)));
	QDomText txt3 = document.createTextNode(QString::fromStdString(stringFromVector(afterFunction)));

	element1.appendChild(txt1);
	element2.appendChild(txt2);
	element3.appendChild(txt3);
	
	root.appendChild(element);
	
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Open file failed";
	}
	else
	{	
		QTextStream stream(&file);
		stream << document.toString();
		file.close();
		qDebug() << "Done";
	}
}

QString CreateHTML::TransformToHTML(QString fileXML, QString fileXSL)
{
	QString out;
	QXmlQuery query(QXmlQuery::XSLT20);
	query.setFocus(QUrl(fileXML));
	query.setQuery(QUrl(fileXSL));
	query.evaluateTo(&out);
	return out;
}

std::vector<Tag *>* CreateHTML::getList()
{
	return this->list;
}
