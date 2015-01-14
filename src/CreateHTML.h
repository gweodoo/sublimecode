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
#include "Configuration.h"
#include "LauncherCTags.h"
#include "TagsParserImpl.h"
#include "TagsManagerImpl.h"

using namespace std;

class CreateHTML {

public:
	explicit CreateHTML();
	~CreateHTML();
        CreateHTML(Configuration *c);
	void CreateHTMLfile(QString file);
	void CreateHTMLbase(const char* file);

	void CreateHTMLbegin(const char* file);
	void CreateHTMLbody(const char* file);
	void CreateHTMLend(const char* file);

	void CreateXML();
	void createXMLSearchByTags(string tag);
	void createXMLSearchByType(int type);
	QString TransformToHTML(QString fileXML, QString fileXSL);

private:
	Configuration *config;
	TagsParserImpl *tpi;
	TagsManagerImpl *myTagMan;
	std::vector<Tag *>* list;
	std::ostringstream ostr;
	std::string fileNameSubString;
};

#endif