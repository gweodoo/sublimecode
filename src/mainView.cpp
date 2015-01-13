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
// 	ui = new Ui_MainView();
//     
// 	ui->setupUi(this);
// 	ui->getCentralWidget()->show();
// 	ui->getWebView()->load(QUrl("/home/ubuntu/Documents/home.html"));
// 		
// 	QPixmap bkgnd("../../resources/Black-lava-twitter-background.png");
// 	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
// 	QPalette palette;
// 	palette.setBrush(QPalette::Background, bkgnd);
// 	this->setPalette(palette);
// 	
// 	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(handlePushButton()));
}

MainView::MainView(Configuration *c, std::vector<std::string> fileList)
{
	ui = new Ui_MainView();
		
	ui->setupUi(this);
	ui->getCentralWidget()->show();
	config = new Configuration(c->getSourcesDir(), c->getDestDir());
	myfileList = fileList;

	LauncherCTags launcher(config);
	for(vector<string>::iterator it = fileList.begin(); it != fileList.end(); it++){
		launcher.addPathToAnalyze(*it);
	}
	launcher.generateTagsFile();
	launcher.display();
	
	QPixmap bkgnd("../../resources/Black-lava-twitter-background.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);
	
	if (ui->getRadioType()->isChecked()){
		ui->gettypeSelector()->setVisible(true);
	}
	
	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(handlePushButton()));
}

MainView::~MainView()
{

}

void MainView::handlePushButton()
{
	this->tag = ui->getLineEdit()->text().toStdString();
	CreateHTML *c = new CreateHTML(config);
	QString html;
	
	if(ui->getRadioName()->isChecked()){
		c->createXMLSearchByTags(tag);
		html = c->TransformToHTML("/home/alexandre/Documents/SublimeCode/myXLMSearchByTags.xml", "/home/alexandre/Documents/SublimeCode/src/transformSearchByTags.xsl");
		ui->getWebView()->setHtml(html);
		ui->getWebView()->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile("/home/alexandre/Documents/SublimeCode/src/style.css"));
	}
	else if (ui->getRadioType()->isChecked()){
	}
	else if(ui->getRadioFile()->isChecked()){
		
	}
}
