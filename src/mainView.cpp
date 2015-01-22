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
#include <QDebug>
#include <QDirIterator>
#include <QWebFrame>
#include "GraphCaller.h"
#include "CreateJson.h"
#include "ObjectTo.h"

MainView::MainView(Configuration *c, std::vector<std::string> fileList)
{
	ui = new Ui_MainView();
		
	ui->setupUi(this);
	ui->getCentralWidget()->show();
	config = c;
	runner = new Runner(config);

	cssFile = QString::fromStdString(config->getRootPath())+"/resources/style.css";
	xslTag = QString::fromStdString(config->getRootPath()+"/resources/transformSearchByTags.xsl");
	xslType = QString::fromStdString(config->getRootPath()+"/resources/transformSearchByType.xsl");
	xslFile = QString::fromStdString(config->getRootPath()+"/resources/transformSearchByFile.xsl");
	xslHighlight = QString::fromStdString(config->getRootPath()+"/resources/transformHighlightFunction.xsl");
	
	for (int i=0; i<15; i++){
		ui->gettypeSelector()->addItem(tabTypeNames[i]);
	}
	
	for(vector<string>::iterator it = fileList.begin(); it != fileList.end(); it++){
		wordList.push_back(QString::fromStdString((*it).substr(config->getSourcesDir().size())));
	}

	if (ui->getRadioType()->isChecked()){
		ui->gettypeSelector()->setVisible(true);
	}

	runner->setListFiles(fileList);
	runner->generateContents();

	cHTML = new CreateHTML(config, runner);

	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(handlePushButton()));
	QObject::connect(ui->getRadioType(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getRadioName(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getRadioFile(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getWebView()->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(slot_linkClicked(QUrl))); 
	QObject::connect(ui->getTabWidget(), SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int))); 
	QObject::connect(ui->getShortcutEnter(), SIGNAL(activated()), ui->getPushButton(), SLOT(click())); 
}

MainView::~MainView()
{
}

void MainView::closeTab(int index)
{
	if (index !=0)
		ui->getTabWidget()->removeTab(index);
}

void MainView::slot_linkClicked(const QUrl& url)
{	
	QString delimiter("///");
	QStringList elements = url.toString().split(delimiter);

	if (elements.at(0) == "CalledGraph")
		generateGraph(elements.at(1), "Called");
	else if (elements.at(0) == "CallingGraph")
		generateGraph(elements.at(1), "Calling");
	else if (elements.at(0) == "IncludedGraph")
		generateGraph("0", elements.at(0).toStdString());
	else if (elements.at(0) == "InclusionGraph")
		generateGraph("0", elements.at(0).toStdString());
	else if(elements.at(0) == "Path")
		generateHighlightFunction(elements.at(1));
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
	QWebView *webViewSearch = new QWebView();

	if(ui->getRadioName()->isChecked()){
		xmlFile = QString::fromStdString(config->getDestDir())+"/myXLMSearchByTags_"+QString::fromStdString(tag)+".xml";
		if(exists(xmlFile.toUtf8().data()) == false){

			cHTML->createXMLSearchByTags(tag);
		}
 		html = cHTML->TransformToHTML(xmlFile, xslTag);
	}
	else if (ui->getRadioType()->isChecked()){
		xmlFile = QString::fromStdString(config->getDestDir())+"/myXLMSearchByType_"+tabTypeNames[ui->gettypeSelector()->currentIndex()]+".xml";
		if(exists(xmlFile.toUtf8().data()) == false){
			cHTML->createXMLSearchByType(ui->gettypeSelector()->currentIndex());
		}
 		html = cHTML->TransformToHTML(xmlFile, xslType);
	}
	else if(ui->getRadioFile()->isChecked()){
		QString filename_modified = QString::fromStdString(tag);
		filename_modified.replace("/","_");
		xmlFile = QString::fromStdString(config->getDestDir())+"/myXLMSearchByFile_"+filename_modified+".xml";
		if(exists(xmlFile.toUtf8().data()) == false){
			cHTML->createXMLSearchByFile(tag);
		}
		html = cHTML->TransformToHTML(xmlFile , xslFile);
	}
	
	ui->getWebView()->setHtml(html);
	ui->getWebView()->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile(cssFile));
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

void MainView::generateGraph(QString number, std::string buildType)
{
	CreateJson * cjson;
	std::string filepath;
	
	if (buildType == "Called" || buildType == "Calling")
		filepath = config->getDestDir() + "/" + buildType + "Graph_" + (cHTML->getList()->at(number.toInt() - 1))->hashFileName() + ".json";
	else if (buildType == "IncludedGraph" || buildType == "InclusionGraph")
		filepath = config->getDestDir() + "/" + buildType + "_" + "numeroHashedInclude" + ".json";
	
	QFile file(QString::fromStdString(filepath));
	
	if(!file.exists())
	{
		if (buildType == "Called" || buildType == "Calling")
		{
			
			cjson = new createJson(config, runner->getGraphCaller());
			cjson->TransformToJson(cHTML->getList()->at(number.toInt() - 1), filepath, buildType);
		}
		else if (buildType == "IncludedGraph" || buildType == "InclusionGraph")
		{
			cjson = new CreateJson(config);
			cjson->TransformToJson(config->getSourcesDir() + this->tag, filepath, includeParser, buildType);
		}
	}
	
	ObjectTo *objectTo = new ObjectTo(ui->getWebView());
	objectTo->setValue(ui->getWebView(), QString::fromStdString(filepath));
	ui->getWebView()->setUrl(QUrl(QString::fromStdString(config->getRootPath()) + "resources/callGraph.html"));
	ui->getWebView()->show();
}

void MainView::generateHighlightFunction(QString number)
{
	QString xmlFile;
	QString html;
	std::string filename;
	xmlFile = QString::fromStdString(config->getDestDir())+"/myXLMHighlightFunction.xml";
	
	QWebView *webViewHighlight = new QWebView();
		
	QString ext = QString::fromStdString(cHTML->getList()->at(number.toInt() - 1)->getFileName()).section('.',-1);
	
	if(ext!="js"){
		cHTML->createListHighlightFunction(cHTML->getList()->at(number.toInt() - 1));
		html = cHTML->TransformToHTML(xmlFile , xslHighlight);
		ui->getTabWidget()->addTab(webViewHighlight, "Highlight");
		webViewHighlight->setHtml(html);
		webViewHighlight->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile(cssFile));
	}
	else {
		QMessageBox::information(this, "Warning", "Unsupported file format");
	}
}

