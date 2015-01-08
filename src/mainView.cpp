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

#include "mainView.h"
#include "ui_mainView.h"
#include "CreateHTML.h"
#include <QDebug>

MainView::MainView()
{
	ui = new Ui_MainView();
	this->resize(1200, 800);
    
	ui->setupUi(this);
	ui->getCentralWidget()->show();
	ui->getWebView()->load(QUrl("/home/ubuntu/Documents/home.html"));
		
	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(handlePushButton()));
}

MainView::MainView(QString file)
{
	ui = new Ui_MainView();
	this->resize(1200, 800);
    
	ui->setupUi(this);
	ui->getCentralWidget()->show();
	ui->getWebView()->setHtml(file);
	
	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(handlePushButton()));
}
/*
MainView::MainView(QString file, QWidget *parent)
{
	this->resize(1200, 800);
    
	ui.setupUi(this);
	ui.getCentralWidget()->show();
	ui.getWebView()->load(QUrl(file));
}
*/
MainView::~MainView()
{

}

void MainView::handlePushButton()
{
	qDebug() << ui->getLineEdit()->text();
	
	//Creation d'un XML test
	CreateHTML c;
	QString html;
	c.CreateXML();
	html = c.TransformToHTML();
	
	ui->getWebView()->setHtml(html);
	ui->getWebView()->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile("/home/ubuntu/Documents/SublimeCode/src/style.css"));
}
