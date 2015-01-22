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
#ifndef CREATEHTML_H
#define CREATEHTML_H
#include <QString>
#include <QtXml>
#include <QtCore>
#include <QDebug>
#include <QXmlQuery>
#include "Configuration.h"
#include "LauncherCTags.h"
#include "Runner.h"

using namespace std;

class CreateHTML {

public:
	explicit CreateHTML();
	~CreateHTML();
        CreateHTML(Configuration *c, Runner *runner);
	
	int getTotalLine(std::string ifs);
	void createXMLSearchByTags(string tag);
	void createXMLSearchByType(int type);
	void createXMLSearchByFile(string filename);
	void createListHighlightFunction( Tag* tag );
	void createXMLHighlightFunction(std::vector<std::string> beforeFunction, std::vector<std::string> inFunction,std::vector<std::string> afterFunction);
	QString TransformToHTML(QString fileXML, QString fileXSL);
	std::string stringFromVector(vector< string > vector);
	
	std::vector<Tag *>* getList();

private:
	Configuration *config;
	Runner *runner;
	std::vector<Tag *>* list;
	std::ostringstream ostr;
	std::string fileNameSubString;
	std::vector<std::string> beforeFunction;
	std::vector<std::string> inFunction;
	std::vector<std::string> afterFunction;
};

#endif
