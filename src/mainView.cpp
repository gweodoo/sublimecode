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
#include <QCompleter>
#include <QDirIterator>

MainView::MainView()
{
	ui = new Ui_MainView();
    
	ui->setupUi(this);
	ui->getCentralWidget()->show();
	ui->getWebView()->load(QUrl("/home/ubuntu/Documents/home.html"));
		
	//QPixmap bkgnd("../../resources/Black-lava-twitter-background.png");
	//bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	//QPalette palette;
	//palette.setBrush(QPalette::Background, bkgnd);
	//this->setPalette(palette);
	
	for (int i=0; i<15; i++){
		ui->gettypeSelector()->addItem(tabTypeNames[i]);
	}
// 	
 	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(handlePushButton()));
}

MainView::MainView(Configuration *c, std::vector<std::string> fileList)
{
	ui = new Ui_MainView();
		
	ui->setupUi(this);
	ui->getCentralWidget()->show();
	config = new Configuration(c->getSourcesDir(), c->getDestDir());
	
	QDirIterator it(QString::fromStdString(c->getSourcesDir()), QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext()) {
		relativePathToAnalyse = it.next().toStdString();
		allfileList.push_back(relativePathToAnalyse.substr(config->getSourcesDir().size(), relativePathToAnalyse.size()));
	}
	
	for (int i=0; i<15; i++){
		ui->gettypeSelector()->addItem(tabTypeNames[i]);
	}
	
	LauncherCTags launcher(config);
	for(vector<string>::iterator it = fileList.begin(); it != fileList.end(); it++){
		launcher.addPathToAnalyze(*it);
		pathToAnalyse = *it;
		wordList.push_back(QString::fromStdString(pathToAnalyse.substr(config->getSourcesDir().size(), pathToAnalyse.size())));
	}
	launcher.generateTagsFile();
	  
	QCompleter *completer = new QCompleter(wordList, this);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	//completer->set
	ui->getLineEdit()->setCompleter(completer);
	
// 	QPixmap bkgnd("../../resources/Black-lava-twitter-background.png");
// 	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
// 	QPalette palette;
// 	palette.setBrush(QPalette::Background, bkgnd);
// 	this->setPalette(palette);
	
	if (ui->getRadioType()->isChecked()){
		ui->gettypeSelector()->setVisible(true);
	}
	
	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(handlePushButton()));
	QObject::connect(ui->getRadioType(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getRadioName(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getRadioFile(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
}

MainView::~MainView()
{

}

void MainView::handlePushButton()
{/*
	this->tag = ui->getLineEdit()->text().toStdString();
	CreateHTML *c = new CreateHTML(config);
	QString html;
	
	if(ui->getRadioName()->isChecked()){
		c->createXMLSearchByTags(tag);
		html = c->TransformToHTML("../../myXLMSearchByTags.xml", "../../src/transformSearchByTags.xsl");
		ui->getWebView()->setHtml(html);
		ui->getWebView()->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile("../../src/style.css"));
	}
	else if (ui->getRadioType()->isChecked()){
		c->createXMLSearchByType(ui->gettypeSelector()->currentIndex());
		html = c->TransformToHTML("../../myXLMSearchByType.xml", "../../src/transformSearchByType.xsl");
		ui->getWebView()->setHtml(html);
		ui->getWebView()->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile("../../src/style.css"));
	}
	else if(ui->getRadioFile()->isChecked()){
		
	}*/
	
	
	//qDebug() << ui->getLineEdit()->text();
	
	//Creation d'un XML test
	//CreateHTML cHtml;
	//QString html;
	//cHtml.CreateXML();
	//html = cHtml.TransformToHTML();
	
	//CreateJson cjson;
	//cjson.TransformToJson();
	//ui->getWebView()->setHtml(html);
	//ui->getWebView()->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile("/home/ubuntu/Documents/SublimeCode/src/style.css"));
	ui->getWebView()->load(QUrl("/home/ubuntu/Documents/SublimeCode/src/callGraph.html"));
	
}

void MainView::handlePushRadioType()
{
	if(ui->getRadioType()->isChecked()==true)
	{
		ui->gettypeSelector()->setVisible(true);
		ui->getLineEdit()->setReadOnly(true);
	}
	else 
	{
		ui->gettypeSelector()->setVisible(false);
		ui->getLineEdit()->setReadOnly(false);
	}
}
