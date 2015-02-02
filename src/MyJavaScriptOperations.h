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

#ifndef MYJAVASCRIPTOPERATIONS_H
#define MYJAVASCRIPTOPERATIONS_H

#include <QWebView>
#include <QVariant>

using namespace std;
///simplify stats object handling with typeref
typedef std::vector<std::pair<std::string, float> > vector_type_float;
///simplify stats object handling with typeref
typedef std::vector<std::pair<std::string, int> > vector_type_int;

/**
 * Object handling Javascript displaying on front page, about stats
 */
class MyJavaScriptOperations : public QObject {
	Q_OBJECT
public:
	/**
	 * function filling the listcplusToJavaScript 
	 * \param[in] list_cplus the list of stats about C++ (name of the file and number of code lines)
	 */
	void fillcplusList(QVariantMap list_cplus);
	/**
	 * function filling the listheaderToJavaScript 
	 * \param[in] list_header the list of stats about headers (name of the file and number of code lines)
	 */
	void fillheaderList(QVariantMap list_header);
	/**
	 * function filling the listlanguageToJavaScript 
	 * \param[in] list_language the list of stats about programming language (name of language and number of code lines)
	 */
	void filllanguageList(QVariantMap list_language);
	/**
	 * function filling the listtagToJavaScript 
	 * \param[in] list_tag the list of stats about tags in files (name of the file and number of tags)
	 */
	void filltagList(QVariantMap list_tag);
	/**
	 * function filling the listinfoToJavaScript 
	 * \param[in] list_info the list of project infos (name of the information and information)
	 */
	void fillinfoList(QVariantMap list_info);
	///function exposing the of stats about C++ to the Javascript file
	Q_INVOKABLE QVariantMap getcpluslistToJavaScript();
	///function exposing the of stats about header to the Javascript file
	Q_INVOKABLE QVariantMap getheaderlistToJavaScript();
	///function exposing the of stats about programming languages to the Javascript file
	Q_INVOKABLE QVariantMap getlanguagelistToJavaScript();
	///function exposing the of stats about tags to the Javascript file
	Q_INVOKABLE QVariantMap gettaglistToJavaScript();
	///function exposing the of stats about project info to the Javascript file
	Q_INVOKABLE QVariantMap getinfolistToJavaScript();

private:
	QVariantMap listcplusToJavaScript;      ///< QVariantMap of C++ stats transmitted to JavaScript
	QVariantMap listheaderToJavaScript;     ///< QVariantMap of header stats transmitted to JavaScript
	QVariantMap listlanguageToJavaScript;   ///< QVariantMap of language stats transmitted to JavaScript
	QVariantMap listtagToJavaScript;        ///< QVariantMap of tags stats transmitted to JavaScript
	QVariantMap listinfoToJavaScript;       ///< QVariantMap of project info stats transmitted to JavaScript
};

#endif // MYJAVASCRIPTOPERATIONS_H
