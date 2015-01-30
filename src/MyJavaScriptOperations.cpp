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

#include <QWebView>
#include "MyJavaScriptOperations.h"

void MyJavaScriptOperations::fillcplusList(QVariantMap list_cplus)
{
	listcplusToJavaScript = list_cplus;
}

void MyJavaScriptOperations::fillheaderList(QVariantMap list_header)
{
	listheaderToJavaScript = list_header;
}

void MyJavaScriptOperations::filllanguageList(QVariantMap list_language)
{
	listlanguageToJavaScript = list_language;
}

void MyJavaScriptOperations::filltagList(QVariantMap list_tag)
{
	listtagToJavaScript = list_tag;
}

void MyJavaScriptOperations::fillinfoList(QVariantMap list_info)
{
	listinfoToJavaScript = list_info;
}

QVariantMap MyJavaScriptOperations::getcpluslistToJavaScript()
{
	return listcplusToJavaScript;
}

QVariantMap MyJavaScriptOperations::getheaderlistToJavaScript()
{
	return listheaderToJavaScript;
}

QVariantMap MyJavaScriptOperations::getlanguagelistToJavaScript()
{
	return listlanguageToJavaScript;
}

QVariantMap MyJavaScriptOperations::gettaglistToJavaScript()
{
	return listtagToJavaScript;
}

QVariantMap MyJavaScriptOperations::getinfolistToJavaScript()
{
	return listinfoToJavaScript;
}

