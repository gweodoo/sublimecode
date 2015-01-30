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
	void fillcplusList(QVariantMap list_cplus);
	void fillheaderList(QVariantMap list_header);
	void filllanguageList(QVariantMap list_language);
	void filltagList(QVariantMap list_tag);
	void fillinfoList(QVariantMap list_info);
	Q_INVOKABLE QVariantMap getcpluslistToJavaScript();
	Q_INVOKABLE QVariantMap getheaderlistToJavaScript();
	Q_INVOKABLE QVariantMap getlanguagelistToJavaScript();
	Q_INVOKABLE QVariantMap gettaglistToJavaScript();
	Q_INVOKABLE QVariantMap getinfolistToJavaScript();

private:
	QVariantMap listcplusToJavaScript;
	QVariantMap listheaderToJavaScript;
	QVariantMap listlanguageToJavaScript;
	QVariantMap listtagToJavaScript;
	QVariantMap listinfoToJavaScript;
};

#endif // MYJAVASCRIPTOPERATIONS_H
