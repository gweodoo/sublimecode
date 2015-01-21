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

class ObjectTo : public QObject
{
    Q_OBJECT
public:
    ObjectTo(QObject *parent);
    void setValue(QWebView *view, QString objectValue);
    
public slots:
    QString getValue();
    
private slots:
    void attachObject();
    
private:
    QWebFrame *frame;
    QString objectValue;
};

#endif // OBJECTTO_H


