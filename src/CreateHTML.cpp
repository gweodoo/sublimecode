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

CreateHTML::CreateHTML(){
}
CreateHTML::~CreateHTML(){}

CreateHTML::CreateHTML(Configuration* c)
{
	config = new Configuration(c->getSourcesDir(), c->getDestDir());
}

void CreateHTML::CreateHTMLfile(QString file)
{
	const char* fileChar;
	QByteArray ba = file.toLatin1();
	fileChar = ba.data();
	ofstream outfile (fileChar);
	CreateHTMLbase(fileChar);
}

void CreateHTML::CreateHTMLbase(const char* file)
{
	ofstream myfile;
	myfile.open(file);
	myfile << "<!DOCTYPE html>" << endl;
	myfile << "<html>" << endl;
	myfile << "<head>" << endl;
	myfile << "<title>Page Title</title>" << endl;
	myfile << "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">" << endl;
	myfile << "</head>" << endl;
	myfile << "<body>" << endl;
	myfile << "<p>AAAAAAAAAAAAAAAAAAAAAAAAAAA</p>" << endl;
	myfile << "</body>" << endl;
	myfile << "</html>" << endl;
	myfile.close();
}

void CreateHTML::CreateHTMLbegin(const char* file)
{
	ofstream myfile;
	myfile.open(file);
	myfile << "<!DOCTYPE html>" << endl;
	myfile << "<html>" << endl;
	myfile << "<head>" << endl;
	myfile << "<title>Page Title</title>" << endl;
	myfile << "</head>" << endl;
	myfile << "<body>" << endl;
	myfile.close();
}

void CreateHTML::CreateHTMLbody(const char* file)
{

}

void CreateHTML::CreateHTMLend(const char* file)
{
	ofstream myfile;
	myfile.open(file);
	myfile << "</body>" << endl;
	myfile << "</html>" << endl;
	myfile.close();
}


void CreateHTML::CreateXML()
{
	QFile file("/home/alexandre/Documents/myXLM.xml");
	QDomDocument document;

	QDomElement root = document.createElement("MyRowTiTi");
	document.appendChild(root);

	for(int i = 0; i < 5; i++)
	{
		QDomElement element = document.createElement("MyRowToTo");
		//element.setAttribute("Name", "MyRow number " + QString::number(i));
		//element.setAttribute("ID", QString::number(i));
		
		QDomElement element1 = document.createElement("Name");
		QDomElement element2 = document.createElement("ID");
		
		element.appendChild(element1);
		element.appendChild(element2);
		
		QDomText txt1 = document.createTextNode("Name : " + QString::number(i));
		QDomText txt2 = document.createTextNode("ID : " + QString::number(i));
		
		element1.appendChild(txt1);
		element2.appendChild(txt2);
		
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

void CreateHTML::createXMLSearchByTags(string tag)
{	
	QFile file("../../myXLMSearchByTags.xml");
	QDomDocument document;
	
	QDomElement root = document.createElement("SearchByTags");
	document.appendChild(root);
	
	this->myTagMan = new TagsManagerImpl(config);
	this->tpi = new TagsParserImpl(myTagMan);
	tpi->loadFromFile(config->getDestDir()+"/tags");
	list = myTagMan->getTagsByName(tag);

	for (int i=0; i<list->size(); i++)
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
		
		fileNameSubString = list->at(i)->getFileName().substr(config->getSourcesDir().size(), list->at(i)->getFileName().size());
		
		QDomText txt1 = document.createTextNode(QString::number(i+1));
		QDomText txt2 = document.createTextNode(QString::fromStdString(lineNumberString));
		QDomText txt3 = document.createTextNode(QString::fromStdString(fileNameSubString));
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


QString CreateHTML::TransformToHTML(QString fileXML, QString fileXSL)
{
	QString out;
	QXmlQuery query(QXmlQuery::XSLT20);
	query.setFocus(QUrl(fileXML));
	query.setQuery(QUrl(fileXSL));
	query.evaluateTo(&out);
	return out;
}
