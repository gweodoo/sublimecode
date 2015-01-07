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
#include "CreateHTML.h"
#include <QtXml>
#include <QtCore>
#include <QDebug>
#include <QXmlQuery>

CreateHTML::CreateHTML(){}
CreateHTML::~CreateHTML(){}

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
	QFile file("/home/ubuntu/Documents/myXLM.xml");
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

QString CreateHTML::TransformToHTML()
{
	QString out;
	QXmlQuery query(QXmlQuery::XSLT20);
	query.setFocus(QUrl("/home/ubuntu/Documents/myXLM.xml"));
	query.setQuery(QUrl("/home/ubuntu/Documents/SublimeCode/src/transform.xsl"));
	query.evaluateTo(&out);
	qDebug() << out;
	//webview->setHtml(out);
	return out;
}
