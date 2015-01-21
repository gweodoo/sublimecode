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
#include <QDirIterator>
#include <QWebFrame>
#include "Graph.h"
#include "GraphCaller.h"
#include "CreateJson.h"
#include "ObjectTo.h"

MainView::MainView()
{
	ui = new Ui_MainView();
    
	ui->setupUi(this);
	ui->getCentralWidget()->show();
	
	for (int i=0; i<15; i++){
		ui->gettypeSelector()->addItem(tabTypeNames[i]);
	}
 	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(handlePushButton()));
	ui->getWebView()->load(QUrl("/home/ubuntu/Documents/SublimeCode/src/callGraph.html"));
}

MainView::MainView(Configuration *c, std::vector<std::string> fileList)
{
	ui = new Ui_MainView();
		
	ui->setupUi(this);
	ui->getCentralWidget()->show();
	//config = new Configuration(c->getSourcesDir(), c->getDestDir());//
	config = c;
	
	cHTML = new CreateHTML(config);
	
	cssFile = QString::fromStdString(config->getRootPath())+"/resources/style.css";
	xslTag = QString::fromStdString(config->getRootPath()+"/resources/transformSearchByTags.xsl");
	xslType = QString::fromStdString(config->getRootPath()+"/resources/transformSearchByType.xsl");
	xslFile = QString::fromStdString(config->getRootPath()+"/resources/transformSearchByFile.xsl");
	
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
		wordList.push_back(QString::fromStdString(pathToAnalyse.substr(config->getSourcesDir().size())));
	}
	launcher.generateTagsFile();
	  	
	if (ui->getRadioType()->isChecked()){
		ui->gettypeSelector()->setVisible(true);
	}
	
	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(handlePushButton()));
	QObject::connect(ui->getRadioType(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getRadioName(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getRadioFile(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getWebView()->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(slot_linkClicked(QUrl))); 
	QObject::connect(ui->getCallGraphButton(), SIGNAL(clicked(bool)), this, SLOT(generateCallGraph())); 

}

MainView::~MainView()
{
}

void MainView::slot_linkClicked(const QUrl& url)
{
	qDebug() << url;
	
	QString delimiter("///");
	QStringList elements = url.toString().split(delimiter);

	if (elements.at(0) == "CalledGraph")
	{
		generateCallGraph(elements.at(1), "Called");
	}
	else
	{
		if (elements.at(0) == "CallingGraph")
		{
			generateCallGraph(elements.at(1), "Calling");
		}
	}

	
}

bool exists(const char *fname)
{
    if( access( fname, F_OK ) != -1 ) {
    // file exists
	    return true;
    } else {
    // file doesn't exist
	    return false;
    }
}

void MainView::handlePushButton()
{
	this->tag = ui->getLineEdit()->text().toStdString();
	QString html;
	QString xmlFile;
		
	if(ui->getRadioName()->isChecked()){
		xmlFile = QString::fromStdString(config->getDestDir())+"/myXLMSearchByTags_"+QString::fromStdString(tag)+".xml";
		if(exists(xmlFile.toUtf8().data()) == false){
			cHTML->createXMLSearchByTags(tag);
		}
		html = cHTML->TransformToHTML(xmlFile, xslTag);
		ui->getWebView()->setHtml(html);
		ui->getWebView()->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile(cssFile));
	}
	else if (ui->getRadioType()->isChecked()){
		xmlFile = QString::fromStdString(config->getDestDir())+"/myXLMSearchByType_"+tabTypeNames[ui->gettypeSelector()->currentIndex()]+".xml";
		if(exists(xmlFile.toUtf8().data()) == false){
			cHTML->createXMLSearchByType(ui->gettypeSelector()->currentIndex());
		}
		html = cHTML->TransformToHTML(xmlFile, xslType);
		ui->getWebView()->setHtml(html);
		ui->getWebView()->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile(cssFile));
	}
	else if(ui->getRadioFile()->isChecked()){
		QString filename_modified = QString::fromStdString(tag);
		filename_modified.replace("/","_");
		xmlFile = QString::fromStdString(config->getDestDir())+"/myXLMSearchByFile_"+filename_modified+".xml";
		if(exists(xmlFile.toUtf8().data()) == false){
			cHTML->createXMLSearchByFile(tag);
		}
		html = cHTML->TransformToHTML(xmlFile , xslFile);
		ui->getWebView()->setHtml(html);
		ui->getWebView()->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile(cssFile));
	}
	//ui->getWebView()->load(QUrl("/home/ubuntu/Documents/home.html"));
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
	
	if(ui->getRadioFile()->isChecked()==true){
		completer = new QCompleter(wordList, this);
		completer->setCaseSensitivity(Qt::CaseInsensitive);
		completer->popup()->setStyleSheet("color : black");
		ui->getLineEdit()->setCompleter(completer);
		ui->getLineEdit()->setText("/");
	}
	else{
		completer = 0;
		ui->getLineEdit()->setCompleter(completer);
		ui->getLineEdit()->setText("");
	}
}

void MainView::generateCallGraph(QString number, std::string buildType)
{
	TagsManagerImpl tagMan(config);
	TagsParserImpl tagParse(&tagMan);
	tagParse.loadFromFile(config->getDestDir() + "/tags");
	TagsManager *myTagManager = &tagMan;
	Graph *myGraph = new GraphCaller(config, myTagManager);

	CreateJson * cjson = new CreateJson(config, myGraph);
	cjson->TransformToJson(cHTML->getList()->at(number.toInt() - 1), buildType);
	
	ObjectTo *objectTo = new ObjectTo(ui->getWebView());
	objectTo->setValue(ui->getWebView(), QString::fromStdString(config->getDestDir()) + "/callGraph.json");
	ui->getWebView()->setUrl(QUrl(QString::fromStdString(config->getRootPath()) + "resources/callGraph.html"));
	ui->getWebView()->show();
}
