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
#include <QApplication>
using namespace std;

const char * const MainView::buildTypes[] = {"CalledGraph", "CallingGraph", "IncludedGraph", "InclusionGraph"};

MainView::MainView(Configuration *c, std::vector<std::string> fileList)
{
	ui = new Ui_MainView();
	ui->setupUi(this);
	ui->getCentralWidget()->show();
	waitingStart(); //Starts the spinner
	
	config = c;

	cssFile = QString::fromStdString(config->getRootPath())+"/style.css";
	cssHighlightFile = QString::fromStdString(config->getRootPath())+"/default.css";
	xslTag = QString::fromStdString(config->getRootPath()+"/transformSearchByTags.xsl");
	xslType = QString::fromStdString(config->getRootPath()+"/transformSearchByType.xsl");
	xslFile = QString::fromStdString(config->getRootPath()+"/transformSearchByFile.xsl");
	xslHighlight = QString::fromStdString(config->getRootPath()+"/transformHighlightFunction.xsl");
	statFile = QString::fromStdString(config->getRootPath()+"/statFile.html");
	
	for (int i=0; i<15; i++){
		ui->gettypeSelector()->addItem(tabTypeNames[i]);
	}
	
	for(vector<string>::iterator it = fileList.begin(); it != fileList.end(); it++){ //Adds the file paths on the file vector
		wordList.push_back(QString::fromStdString((*it).substr(config->getSourcesDir().size())));
	}
	
	if (ui->getRadioType()->isChecked()){
		ui->gettypeSelector()->setVisible(true);
	}
	
	fileSearchedVector = new std::vector<std::string>();
	
	this->show();
	
	cHTML = NULL;
	cjson = new CreateJson;
	runner = new Runner;
	runner->initEnvironment(config, fileList);
	QObject::connect(runner, SIGNAL(runnerChanged()), this, SLOT(onRunnerChanged()));
	runner->start(); //Configures tags mechanism
	
	//Initialize the different signals
	QObject::connect(ui->getResetButton(), SIGNAL(clicked()), this, SLOT(handleResetButton()));
	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(handlePushButton()));
	QObject::connect(ui->getRadioType(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getRadioName(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getRadioFile(), SIGNAL(clicked(bool)), this, SLOT(handlePushRadioType())); 
	QObject::connect(ui->getTabWidget(), SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int))); 
	QObject::connect(ui->getShortcutEnter(), SIGNAL(activated()), ui->getPushButton(), SLOT(click()));
	QObject::connect(ui->getTabWidget(), SIGNAL(currentChanged(int)), this, SLOT(changeTab(int)));
}

void MainView::generateStats()
{
	map_type_string map_project_info = runner->getProjectInfos();
 	vector_type_float vec_float_language = runner->getStatsAboutLanguages();
  	vector_type_int vec_int_stat_file = runner->getStatsPerFile();
	vector_type_int vec_int_language_header = runner->getStatsPerLanguage("C/C++ Header");
	vector_type_int vec_int_language_cplus = runner->getStatsPerLanguage("C++");
	MyJavaScriptOperations *myoperations = new MyJavaScriptOperations();
	
	for (map_type_string::const_iterator pos = map_project_info.begin(); pos != map_project_info.end(); pos++)
	{
		list_info.insert(QString::fromStdString(pos->first), QString::fromStdString(pos->second));
	}
	for (vector_type_float::const_iterator pos = vec_float_language.begin(); pos != vec_float_language.end(); pos++)
	{
		list_language.insert(QString::fromStdString(pos->first), pos->second);
	}
	for (vector_type_int::const_iterator pos = vec_int_stat_file.begin(); pos != vec_int_stat_file.end(); pos++)
	{
		list_tag.insert(QString::fromStdString(pos->first), pos->second);
	}
	for (vector_type_int::const_iterator pos = vec_int_language_header.begin(); pos != vec_int_language_header.end(); pos++)
	{
		list_header.insert(QString::fromStdString(pos->first), pos->second);
	}
	for (vector_type_int::const_iterator pos = vec_int_language_cplus.begin(); pos != vec_int_language_cplus.end(); pos++)
	{
		list_cplus.insert(QString::fromStdString(pos->first), pos->second);
	}
	myoperations->fillcplusList(list_cplus);
	myoperations->fillheaderList(list_header);
	myoperations->filllanguageList(list_language);
	myoperations->filltagList(list_tag);
	myoperations->fillinfoList(list_info);
	ui->getWebView()->page()->mainFrame()->addToJavaScriptWindowObject("myoperations", myoperations);
	ui->getWebView()->load(QUrl(statFile));
}

void MainView::closeEvent(QCloseEvent* e) {
	cjson->quit();
	runner->quit();
	delete cjson;
	delete runner;
	if (cHTML != NULL)
		delete cHTML;
	delete fileSearchedVector;
	delete ui;
	delete config;
	QMainWindow::closeEvent(e);
}

MainView::~MainView() {
}

QWebView *MainView::pageActuelle()
{
	return ui->getTabWidget()->currentWidget()->findChild<QWebView *>();
}

void MainView::onCjsonChanged()
{
	createNewGraphTab(QUrl(QString::fromStdString(config->getRootPath()) + "/callGraph.html"), filepath, display);
	
	waitingStop();
}

void MainView::onRunnerChanged()
{
	cHTML = new CreateHTML(config, runner);
	cjson->setRunner(runner);
	cjson->setConfiguration(config);
	QObject::connect(cjson, SIGNAL(cjsonChanged()), this, SLOT(onCjsonChanged()));
	generateStats();
	waitingStop();
}

void MainView::changeTab(int index) 
{
	if (ui->getTabWidget()->tabText(index).contains("Graph")) //A modifier
		ui->getLegendGroupBox()->setVisible(true);
	else 
		ui->getLegendGroupBox()->setVisible(false);
}

void MainView::closeTab(int index)
{
	if (index !=0){
		removeFileSearched(index);
		ui->getTabWidget()->removeTab(index);
		researchList.erase(researchList.begin() + index - 1);
	}
}

void MainView::slot_linkClicked(const QUrl& url)
{
	QString delimiter("///");
	QStringList elements = url.toString().split(delimiter);
	
	if(elements.at(0).contains("Graph") || elements.at(0).contains("file"))
	{
		waitingStart();
	}

	if ((elements.at(0) == buildTypes[0]) || (elements.at(0) == buildTypes[1]))
		generateGraph(elements.at(1).toInt(), elements.at(0).toStdString());
	else if ((elements.at(0) == buildTypes[2]) || (elements.at(0) == buildTypes[3])) {
		setCurrentFileSearched();
		generateGraph(0, elements.at(0).toStdString());
	}
	else if(elements.at(0) == "Path")
		generateHighlightFunction(elements.at(1));
	else if (elements.at(0).contains("file"))
	{
		if (elements.at(1).toStdString() == buildTypes[0] || elements.at(1).toStdString() == buildTypes[1]) //If call graphs
		{
			researchList.push_back(cHTML->getList());
			Tag * myTag = runner->findSpecificTag(elements.at(2).toStdString(), elements.at(3).toStdString(), elements.at(4).toInt());
			generateGraph(myTag, elements.at(1).toStdString());
		}
		else if (elements.at(1).toStdString() == buildTypes[2] || elements.at(1).toStdString() == buildTypes[3]) //If include graph
		{
			this->tag = elements.at(2).toStdString();
			generateGraph(0, elements.at(1).toStdString());
		}
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

	if(reply == QMessageBox::Yes) {
		QApplication::exit(APPLICATION_REBOOT);
	}
}

void MainView::handlePushButton()
{
	this->tag = ui->getLineEdit()->text().toStdString();
	QString html;
	QString xmlFile;
	string display;
	
	if(ui->getRadioName()->isChecked()){
		xmlFile = QString::fromUtf8(config->getDestDir().c_str())+"/myXLMSearchByTags_"+QString::fromStdString(tag)+".xml";
		cHTML->generateTagByTag(tag);
		if(exists(xmlFile.toUtf8().data()) == false){
			cHTML->createXMLSearchByTags(tag);
		}
 		html = cHTML->TransformToHTML(xmlFile, xslTag);
		display="Search : "+tag;
	}
	else if (ui->getRadioType()->isChecked()){
		xmlFile = QString::fromUtf8(config->getDestDir().c_str())+"/myXLMSearchByType_"+tabTypeNames[ui->gettypeSelector()->currentIndex()]+".xml";
		cHTML->generateTagByType(ui->gettypeSelector()->currentIndex());
		if(exists(xmlFile.toUtf8().data()) == false){
			cHTML->createXMLSearchByType(ui->gettypeSelector()->currentIndex());
		}
 		html = cHTML->TransformToHTML(xmlFile, xslType);ui->getWaitingMovie()->stop();
		ui->getWaitingLabel()->setVisible(false);
		display="Search : "+string(tabTypeNames[ui->gettypeSelector()->currentIndex()]);
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
		display = "Search : "+tag;
	}
	researchList.push_back(cHTML->getList());
	createNewSearchTab(html, display);
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

void MainView::generateGraph(int number, std::string buildType)
{
	Tag * myTag = NULL;
	
	researchList.push_back(cHTML->getList());
	if (buildType == buildTypes[0] || buildType == buildTypes[1]) //If call graph
		myTag = researchList.at(ui->getTabWidget()->currentIndex() -1)->at(number - 1);
	generateGraph(myTag, buildType);
}

void MainView::generateGraph(Tag * myTag, std::string buildType)
{
	display = "";

	if (buildType == buildTypes[0])
		display = "Called : " + myTag->getName()+"()";
	else if (buildType == buildTypes[1])
		display = "Calling : " + myTag->getName()+"()";
	else if (buildType == buildTypes[2])
			display = "Included : "+tag;
	else if (buildType == buildTypes[3])
		display = "Including : "+tag;

	if (buildType == buildTypes[0] || buildType == buildTypes[1]){ //If call graph
		filepath = config->getDestDir() + "/" + buildType + "_" + myTag->hashFileName() + ".json";
	}
	else if (buildType == buildTypes[2] || buildType == buildTypes[3]){ //If include graph
		filepath = config->getDestDir() + "/" + buildType + "_"
		+ (QString::fromStdString(this->tag).replace("/","_")).toStdString() + ".json";
	}
	QFile file(QString::fromUtf8(filepath.c_str()));

	if(!file.exists())
	{
		if (buildType == buildTypes[0] || buildType == buildTypes[1]) //If call graph
		{
			cjson->setRunner(runner);
			cjson->setCallGraphParams(myTag, filepath, buildType);
		}
		else if (buildType == buildTypes[2] || buildType == buildTypes[3]) //If include graph
		{
			cjson->setIncludeGraphParams(config->getSourcesDir() + this->tag, filepath, buildType);
		}
		cjson->start();
	}
	else
	{
		createNewGraphTab(QUrl(QString::fromStdString(config->getRootPath()) + "/callGraph.html"), filepath, display);
		
		waitingStop();
	}
}

void MainView::generateHighlightFunction(QString number)
{
	QString xmlFile;
	QString html;
	std::string filename;
	Tag * cur;
	std::string chain = "";
	xmlFile = QString::fromUtf8(config->getDestDir().c_str())+"/myXLMHighlightFunction.xml";

	researchList.push_back(cHTML->getList());
	cur = researchList.at(ui->getTabWidget()->currentIndex()-1)->at(number.toInt() - 1);
	QString ext = QString::fromStdString(cur->getFileName()).section('.',-1);
	if(ext!="js"){
		cHTML->createListHighlightFunction(cur);
		html = cHTML->TransformToHTML(xmlFile , xslHighlight);
		chain = "File : " + cur->getFileName().substr(config->getSourcesDir().size());
		createNewHighlightTab(html, chain);
	}
	else {
		QMessageBox::information(this, "Warning", "Unsupported file format");
	}
}

void MainView::createNewSearchTab(QString html, string text)
{
	int index = 0;
	index = checkAlreadyOpenedTab(text);
	
	if(index >= 0 && index < ui->getTabWidget()->count()){
		ui->getTabWidget()->setCurrentIndex(index);
	} else {
		ui->getTabWidget()->addTab(new QWebView, QString::fromStdString(text));
		ui->getTabWidget()->setCurrentIndex(ui->getTabWidget()->count()-1);
		QWidget *w = ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex());
		QWebView *webView = qobject_cast<QWebView *>(w);
		webView->setHtml(html);
		webView->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile(cssFile));
		QObject::connect(qobject_cast<QWebView *>(ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex()))->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(slot_linkClicked(QUrl)));
		qobject_cast<QWebView *>(ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex()))->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
	
		fileSearchedVector->push_back(this->tag);
	}
}


void MainView::createNewHighlightTab(QString html, string text)
{
	ui->getTabWidget()->addTab(new QWebView, QString::fromStdString(text));
	ui->getTabWidget()->setCurrentIndex(ui->getTabWidget()->count()-1);
	QWidget *w = ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex());
	QWebView *webView = qobject_cast<QWebView *>(w);
	webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
	createHTMLFile(QString::fromUtf8(config->getRootPath().c_str())+"/highlightFunction.html", html);
	webView->load(QUrl(QString::fromUtf8(config->getRootPath().c_str())+"/highlightFunction.html"));
}

void MainView::createHTMLFile(QString filename, QString html)
{
	QFile file(filename);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	out << html;
	file.close();
}

QString MainView::readFile (const QString& filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
// 	qDebug() << stream.readAll();
        return stream.readAll();
    }
    return "";
}

void MainView::createNewGraphTab(QUrl html, string filepath, string text)
{
	ui->getTabWidget()->addTab(new QWebView, QString::fromStdString(text));
	ui->getTabWidget()->setCurrentIndex(ui->getTabWidget()->count()-1);
	QWidget *w = ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex());
	QWebView *webView = qobject_cast<QWebView *>(w);
	ObjectTo *objectTo = new ObjectTo(webView);
	objectTo->setValue(webView, QString::fromUtf8(filepath.c_str()));
	webView->setUrl(html);
	webView->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile(cssFile));
	QObject::connect(qobject_cast<QWebView *>(ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex()))->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(slot_linkClicked(QUrl)));
	qobject_cast<QWebView *>(ui->getTabWidget()->widget(ui->getTabWidget()->currentIndex()))->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}

void MainView::waitingStart()
{
	ui->getCentralWidget()->setEnabled(false);
	ui->getWaitingMovie()->start();
	ui->getWaitingLabel()->setVisible(true);
}

void MainView::waitingStop()
{
	ui->getCentralWidget()->setEnabled(true);
	ui->getWaitingMovie()->stop();
	ui->getWaitingLabel()->setVisible(false);
}

int MainView::checkAlreadyOpenedTab( string chain ) {
	for(int i = 0; i < ui->getTabWidget()->count(); i++){
		if(chain == ui->getTabWidget()->tabText(i).toStdString())
			return i;
	}
	return -1;
}

void MainView::setCurrentFileSearched()
{
	int cpt = -1;
	for(int i = 0; i < ui->getTabWidget()->count(); i++) {
		if (ui->getTabWidget()->tabText(i).contains("Search") && i <= ui->getTabWidget()->currentIndex())
			cpt++;
	}
	
	if (cpt >= 0)
		this->tag = fileSearchedVector->at(cpt);
}

void MainView::removeFileSearched(int index)
{
	if (ui->getTabWidget()->tabText(index).contains("Search"))
	{
		int cpt = -1;
		for(int i = 0; i < ui->getTabWidget()->count(); i++) {
			if (ui->getTabWidget()->tabText(i).contains("Search") && i <= ui->getTabWidget()->currentIndex())
				cpt++;
		}
		
		if (cpt >= 0)
			fileSearchedVector->erase(fileSearchedVector->begin() + cpt);
	}
}
