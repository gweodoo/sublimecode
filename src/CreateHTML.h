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
#include "Runner.h"

/**
 * CreateHTML handles HTML files generation, which will be then displayed in Qt Webview
 */
class CreateHTML {

public:
	/**
	 * default constructor
	 * \param[in] c global configuration
	 * \param[in] runner the associated ruuner
	 */
	CreateHTML(Configuration *c, Runner *runner);
	/**
	 * count the number of "\n" present in a string, filled from a file
	 * \param[in] ifs string where file data are stored
	 * \return number of lines
	 */
	int getTotalLine(std::string ifs);
	/**
	 * generate XML file when user does a tag request on name
	 * \param[in] tag the tag name the user is looking for
	 */
	void createXMLSearchByTags(std::string tag);
	/**
	 * generate XML file when user does a tag request on specific type
	 * \param[in] type the tag type the user is looking for
	 */
	void createXMLSearchByType(int type);
	/**
	 * generate XML file when user does a tag request on specific file
	 * \param[in] filename the file the user is looking for
	 */
	void createXMLSearchByFile(std::string filename);
	/**
	 * Load tags and find where it is located in the associated file.
	 * Then, generate the related XML
	 * \param[in] tag the tag from which depends the highlightning
	 */
	void createListHighlightFunction( Tag* tag );
	/**
	 * set the current list with result from tagsByFile research
	 * \param[in] filename the file to look for
	 */
	void generateTagByFile(std::string filename);
	/**
	 * set the current list with result from tagsByType research
	 * \param[in] type the type to look for
	 */
	void generateTagByType(int type);
	/**
	 * set the current list with result from tagsByName research
	 * \param[in] tag the tag name to look for
	 */
	void generateTagByTag(std::string tag);
	/**
	 * Generate highlighted XML displayer , from 3 vectors, start of file, highlighted section and the end of file
	 * \param[in] beforeFunction the vector representing the start of the file
	 * \param[in] inFunction the vector representing the section to highlight
	 * \param[in] afterFunction the end of the file
	 */
	void createXMLHighlightFunction(std::vector<std::string> beforeFunction, std::vector<std::string> inFunction,std::vector<std::string> afterFunction);
	/**
	 * Apply XSL files to specific XML, in order to generate final HTML, then displayed in webview
	 * \param[in] fileXML the XML to display
	 * \param[in] fileXSL the XSL rules to parse the XML file
	 * \return the generated HTML
	 */
	QString TransformToHTML(QString fileXML, QString fileXSL);
	/**
	 * convert a string vector into one string
	 * \param[in] vector the vector to gather
	 * \return the merged string
	 */
	std::string stringFromVector(std::vector< std::string > vector);
	/**
	 * list of files fetched from model getter
	 * \return a vector containing list of tags matching with content
	 * \return an empty vector if no tags match
	 */
	std::vector<Tag *>* getList();
	/// default destructor
	~CreateHTML();

private:
	Configuration *config;                   ///< global configuration
	Runner *runner;                          ///< current runner
	std::vector<Tag *>* list;                ///< list which contains current data from model
	std::ostringstream ostr;                 ///< temporary object used to parse int->string
	std::vector<std::string> beforeFunction; ///< vector containing file lines before the highlighted section
	std::vector<std::string> inFunction;     ///< vector containing file lines in the highlighted section
	std::vector<std::string> afterFunction;  ///< vector containing file lines after the highlighted section
	/**
	 * Copy given file and replace space by "tabulation", to make file displaying smoother
	 * the file is copied in order to not corrupt source file
	 * \param[in] fileToCopy source file to copy
	 * \return the new modified file name
	 */
	std::string getFileCopied(std::string fileToCopy);
};

#endif
