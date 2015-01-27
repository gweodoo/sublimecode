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
#include <QWebHistory>
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

	cssFile = QString::fromStdString(config->getRootPath())+"/style.css";
	xslTag = QString::fromStdString(config->getRootPath()+"/transformSearchByTags.xsl");
	xslType = QString::fromStdString(config->getRootPath()+"/transformSearchByType.xsl");
	xslFile = QString::fromStdString(config->getRootPath()+"/transformSearchByFile.xsl");
	xslHighlight = QString::fromStdString(config->getRootPath()+"/transformHighlightFunction.xsl");
	
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

	QObject::connect(ui->getResetButton(), SIGNAL(clicked()), this, SLOT(handleResetButton()));
	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(handlePushButton()));
	QObject::connect(ui->getRadioType(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getRadioName(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getRadioFile(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	//QObject::connect(ui->getWebView()->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(slot_linkClicked(QUrl))); 
	QObject::connect(ui->getTabWidget(), SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int))); 
	QObject::connect(ui->getShortcutEnter(), SIGNAL(activated()), ui->getPushButton(), SLOT(click()));
	QObject::connect(ui->getTabWidget(), SIGNAL(currentChanged(int)), this, SLOT(changeTab(int)));
}

void MainView::closeEvent(QCloseEvent* e){
	QMainWindow::closeEvent(e);
	delete runner;
	delete config;
	delete cHTML;
	delete ui;
// 	delete cjson;
}

MainView::~MainView() {
}

QWebView *MainView::pageActuelle()
{
	return ui->getTabWidget()->currentWidget()->findChild<QWebView *>();
}

void MainView::changeTab(int index){
	//cout << index << endl;
}

void MainView::closeTab(int index)
{
	if (index !=0){
		ui->getTabWidget()->removeTab(index);
		researchList.erase(researchList.begin() + index - 1);
	}
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
	else if(elements.at(0) == "Path"){
		generateHighlightFunction(elements.at(1));
	}
}

bool exists(const char *fname)
{
    if( access( fname, F_OK ) != -1 ) {
	    return true;
    } else {
	    return false;
    }
}

void MainView::handleResetButton(){
	int reply = QMessageBox::question(this, "Open new project", "Would you close current opened project ?",QMessageBox::Yes|QMessageBox::No);

	if(reply){
		QApplication::exit(APPLICATION_REBOOT);
	}

}

void MainView::handlePushButton()
{
	this->tag = ui->getLineEdit()->text().toStdString();
	QString html;
	QString xmlFile;
		
	if(ui->getRadioName()->isChecked()){
		xmlFile = QString::fromUtf8(config->getDestDir().c_str())+"/myXLMSearchByTags_"+QString::fromStdString(tag)+".xml";
		cHTML->generateTagByTag(tag);
		if(exists(xmlFile.toUtf8().data()) == false){
			cHTML->createXMLSearchByTags(tag);
		}
 		html = cHTML->TransformToHTML(xmlFile, xslTag);
	}
	else if (ui->getRadioType()->isChecked()){
		xmlFile = QString::fromUtf8(config->getDestDir().c_str())+"/myXLMSearchByType_"+tabTypeNames[ui->gettypeSelector()->currentIndex()]+".xml";
		cHTML->generateTagByType(ui->gettypeSelector()->currentIndex());
		if(exists(xmlFile.toUtf8().data()) == false){
			cHTML->createXMLSearchByType(ui->gettypeSelector()->currentIndex());
		}
 		html = cHTML->TransformToHTML(xmlFile, xslType);
	}
	else if(ui->getRadioFile()->isChecked()){
		QString filename_modified = QString::fromStdString(tag);
		filename_modified.replace("/","_");
		xmlFile = QString::fromUtf8(config->getDestDir().c_str())+"/myXLMSearchByFile_"+filename_modified+".xml";
		cHTML->generateTagByFile(tag);
		if(exists(xmlFile.toUtf8().data()) == false){
			cHTML->createXMLSearchByFile(tag);
		}
		html = cHTML->TransformToHTML(xmlFile , xslFile);
	}

	researchList.push_back(cHTML->getList());
	createNewSearchTab(html);
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
	
	researchList.push_back(cHTML->getList());
	
	if (buildType == "Called" || buildType == "Calling")
		filepath = config->getDestDir() + "/" + buildType + "Graph_" + (researchList.at(ui->getTabWidget()->currentIndex() -1)->at(number.toInt() - 1))->hashFileName() + ".json";
	else if (buildType == "IncludedGraph" || buildType == "InclusionGraph")
		filepath = config->getDestDir() + "/" + buildType + "_" 
		+ (QString::fromStdString(this->tag).replace("/","_")).toStdString() + ".json";
	
	QFile file(QString::fromUtf8(filepath.c_str()));

	if(!file.exists())
	{
		if (buildType == "Called" || buildType == "Calling")
		{
			cjson = new CreateJson(config, runner->getGraphCaller());
			cjson->TransformToJson(researchList.at(ui->getTabWidget()->currentIndex() -1)->at(number.toInt() - 1), filepath, buildType);
		}
		else if (buildType == "IncludedGraph" || buildType == "InclusionGraph")
		{
			cjson = new CreateJson(config);
			cjson->TransformToJson(config->getSourcesDir() + this->tag, filepath, runner->getIncludeParser(), buildType);
		}
	}
	createNewGraphTab(QUrl(QString::fromStdString(config->getRootPath()) + "/callGraph.html"), filepath);
}

void MainView::generateHighlightFunction(QString number)
{
	QString xmlFile;
	QString html;
	std::string filename;
	xmlFile = QString::fromUtf8(config->getDestDir().c_str())+"/myXLMHighlightFunction.xml";

	researchList.push_back(cHTML->getList());
	QString ext = QString::fromStdString(researchList.at(ui->getTabWidget()->currentIndex())->at(number.toInt() - 1)->getFileName()).section('.',-1);
		
	if(ext!="js"){
		cHTML->createListHighlightFunction(researchList.at(ui->getTabWidget()->currentIndex())->at(number.toInt() - 1));
		html = cHTML->TransformToHTML(xmlFile , xslHighlight);
		createNewHighlightTab(html);
	}
	else {
		QMessageBox::information(this, "Warning", "Unsupported file format");
	}
}

void MainView::createNewSearchTab(QString html)
{
	ui->getTabWidget()->addTab(new QWebView, "Search");
	ui->getTabWidget()->setCurrentIndex(ui->getTabWidget()->count()-1);
	QWidget *w = ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex());
 	QWebView *webView = qobject_cast<QWebView *>(w);
	webView->setHtml(html);
	webView->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile(cssFile));
	QObject::connect(qobject_cast<QWebView *>(ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex()))->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(slot_linkClicked(QUrl)));
	qobject_cast<QWebView *>(ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex()))->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}


void MainView::createNewHighlightTab(QString html)
{
	ui->getTabWidget()->addTab(new QWebView, "Highlight");
	ui->getTabWidget()->setCurrentIndex(ui->getTabWidget()->count()-1);
	QWidget *w = ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex());
 	QWebView *webView = qobject_cast<QWebView *>(w);
	webView->setHtml(html);
	webView->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile(cssFile));
}

void MainView::createNewGraphTab(QUrl html, string filepath)
{
	ui->getTabWidget()->addTab(new QWebView, "Graph");
	ui->getTabWidget()->setCurrentIndex(ui->getTabWidget()->count()-1);
	QWidget *w = ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex());
	QWebView *webView = qobject_cast<QWebView *>(w);
	ObjectTo *objectTo = new ObjectTo(webView);
	objectTo->setValue(webView, QString::fromUtf8(filepath.c_str()));
	webView->setUrl(html);
	webView->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile(cssFile));
}

