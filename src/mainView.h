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
#include "LauncherCTags.h"
#include "TagsManagerImpl.h"
#include "Tag.h"
#include "CreateHTML.h"
#include <QCompleter>
#include "CreateHTML.h"

class MainView : public QMainWindow
{
    Q_OBJECT

public:
	explicit MainView();
	MainView(Configuration *c, std::vector<std::string> fileList);
	~MainView();
	
public slots:
	void handlePushButton();
	void handlePushRadioType();
	void slot_linkClicked(const QUrl &url);
	void generateCallGraph(QString number, std::string buildType);
	void generateHighlightFunction(QString number);

private:
	Ui_MainView * ui;
	Configuration *config;
	std::vector<std::string> allfileList;
	std::string tag;
	QStringList wordList;
	std::string pathToAnalyse;
	std::string relativePathToAnalyse;
	QCompleter *completer;
	QString cssFile;
	QString xslTag;
	QString xslType;
	QString xslFile;
	QString xslHighlight;
	CreateHTML *cHTML;
	TagsParserImpl *tpi;
	TagsManagerImpl *myTagMan;
	std::vector<Tag *>* list;
};

#endif // MAINVIEW_H
