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

#ifndef OBJECTTO_H
#define OBJECTTO_H

#include <QObject>
#include <QWebFrame>
#include <QWebView>
#include <QWebPage>

/**
 * Object forwarded to HTML files, in order to transfer data
 *
 * This object is used to transfer data from SublimeCode application to html
 * page, used by JS to display graphs.
 */
class ObjectTo : public QObject
{
    Q_OBJECT
public:
	/**
	 * main constructor
	 * \param[in] parent upstream accessor
	 */
	ObjectTo(QObject *parent);
	/**
	 * set attribute to transfer
	 * \param[in] view the view
	 * \param[in] objectValue the value to save
	 */
	void setValue(QWebView *view, QString objectValue);
    
public slots:
	/**
	 * get the associated value
	 * \return a QString as the value to send
	 */
	QString getValue();
    
private slots:
	///link the object to the javascript
	void attachObject();
    
private:
	QWebFrame *frame;     ///< the dependent view
	QString objectValue;  ///< value to transfer
};

#endif // OBJECTTO_H


