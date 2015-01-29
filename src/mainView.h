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
#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include "ui_mainView.h"
#include <QString>
#include <QMessageBox>
#include "Configuration.h"
#include "CreateHTML.h"
#include <QCompleter>
#include "Runner.h"
#include <QThread>
#include <QCloseEvent>
#include "CreateJson.h"

class MainView : public QMainWindow
{
    Q_OBJECT

public:
	MainView(Configuration *c, std::vector<std::string> fileList);
	~MainView();
	
public slots:
	void handlePushButton();
	void handleResetButton();
	void handlePushRadioType();
	void slot_linkClicked(const QUrl &url);
	void generateGraph(int number, std::string buildType);
	void generateGraph(Tag * myTag, std::string buildType);
	void generateHighlightFunction(QString number);
	void closeTab(int index);
	QWebView *pageActuelle();
	void closeEvent(QCloseEvent* e);
	void createNewSearchTab(QString html);
	void createNewHighlightTab(QString html);
	void createNewGraphTab(QUrl html, string filename);
	void createHTMLFile(QString filename, QString html);
	QString readFile (const QString& filename);
	void onCjsonChanged();
	void onRunnerChanged();
	void waitingStart();
	void waitingStop();
	
private:
	Ui_MainView * ui;
	Configuration *config;
	std::vector<std::string> allfileList;
	std::vector<std::vector<Tag *>*> researchList;
	std::string tag;
	QStringList wordList;
	std::string pathToAnalyse;
	std::string relativePathToAnalyse;
	QCompleter *completer;
	QString cssFile;
	QString cssHighlightFile;
	QString xslTag;
	QString xslType;
	QString xslFile;
	QString xslHighlight;
	CreateHTML* cHTML;
	CreateJson * cjson;
	std::vector<Tag *>* list;
	QWebView *webViewSearch;
	Runner * runner;
	std::string filepath;
};

#endif // MAINVIEW_H
