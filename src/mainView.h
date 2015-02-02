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
#include "MyJavaScriptOperations.h"

typedef std::vector<std::pair<std::string, float> > vector_type_float;
typedef std::vector<std::pair<std::string, int> > vector_type_int;
typedef std::map<std::string, std::string > map_type_string;

/**
 * Main view in sublimeCode. Display Qt manager and webview
 */
class MainView : public QMainWindow
{
    Q_OBJECT
private:
	/**
	 * check if a tab with given name is already opened
	 * \param[in] chain the tab title
	 * \return the tab index if exists
	 * \return -1 otherwise
	 */
	int checkAlreadyOpenedTab( string chain );

public:
	static const char * const buildTypes[]; ///< The different types of graphs
	
	/**
	 * Construtor of the main view
	 * \param[in] c The current configuration
	 * \param[in] fileList The list of the files that we want to analyze
	 */
	MainView(Configuration *c, std::vector<std::string> fileList);
	
	/**
	 * Default destructor
	 */
	~MainView();
	
public slots:
	/**
	 * Handling the search button depending on the type of demand
	 */
	void handlePushButton();
	
	/**
	 * Opens a message box, asks to close the current project and open anothor one
	 */
	void handleResetButton();
	
	/**
	 * Handle the radio button action
	 */
	void handlePushRadioType();
	
	/**
	 * Get the information from the webview and launch the corresponding process
	 * \param[in] url The given information
	 */
	void slot_linkClicked(const QUrl &url);
	
	/**
	 * Generates the graph with the index of the tab that has been clicked on
	 * \param[in] number index of the tab
	 * \param[in] buildType The building type
	 */
	void generateGraph(int number, std::string buildType);
	
	/**
	 * Generates the graph with a tag
	 * \param[in] myTag The given tag
	 * \param[in] buildType The building type
	 */
	void generateGraph(Tag * myTag, std::string buildType);
	
	/**
	 * Highlights a function in the webview
	 * \param[in] number index of the tab
	 */
	void generateHighlightFunction(QString number);
	
	/**
	 * Close a tab
	 * \param[in] index The tab index
	 */
	void closeTab(int index);
	
	/**
	 * Getting the current page
	 * \return QWebView The current page
	 */
	QWebView *pageActuelle();
	
	/**
	 * Elements destructor when closing
	 * \param[in] e the close event
	 */
	void closeEvent(QCloseEvent* e);
	
	/**
	 * Creates a new searching tab
	 * \param[in] html The html that will be shown on the webview
	 * \param[in] text text to display in tab
	 */
	void createNewSearchTab( QString html, string text );
	
	/**
	 * Creates a new hightlighting tab
	 * \param[in] html The html that will be shown on the webview
	 * \param[in] text text to display in tab
	 */
	void createNewHighlightTab(QString html,string text);
	
	/**
	 * Creates a new graph tab
	 * \param[in] html The html that will be shown on the webview
	 * \param[in] filepath The json file
	 * \param[in] text text to display in tab
	 */
	void createNewGraphTab( QUrl html, string filepath, string text );
	
	/**
	 * Creates the HTML file
	 * \param[in] filename The file created
	 * \param[in] html The content
	 */
	void createHTMLFile(QString filename, QString html);
	
	/**
	 * Reading the whole file
	 * \param[in] filename The name of the file
	 * \return QString The file read
	 */
	QString readFile (const QString& filename);
	
	/**
	 * When the json has been created, show the page on the webview
	 */
	void onCjsonChanged();
	
	/**
	 * When the runner has been created,sets needed information
	 */
	void onRunnerChanged();
	
	/**
	 * Start the spinner
	 */
	void waitingStart();
	
	/**
	 * Stop the spinner
	 */
	void waitingStop();
	/**
	 * stats generator call
	 */
	void generateStats();
	
private:
	Ui_MainView * ui;                              ///< The main view interface
	Configuration *config;                         ///< The current configuration
	std::vector<std::string> allfileList;          ///< The file list that we want to analyze
	std::vector<std::vector<Tag *>*> researchList; ///< The tab list
	std::string tag;                               ///< The current tag
	QStringList wordList;                          ///< The list of words for the word completer
	std::string pathToAnalyse;                     ///< The path that we want to analyze
	std::string relativePathToAnalyse;             ///< The relative path that we want to analyze
	QCompleter *completer;                         ///< The completer
	QString cssFile;                               ///< The global css file
	QString cssHighlightFile;                      ///< The hightlight css file
	QString xslTag;                                ///< The tag xsl file path
	QString xslType;                               ///< The type xsl file path
	QString xslFile;                               ///< The file xsl file path
	QString xslHighlight;                          ///< The highlight xsl file path
	QString statFile;                              ///< The stat html file path
	CreateHTML* cHTML;                             ///< The object to create the HTML file
	CreateJson * cjson;                            ///< The object to create the Json file
	QWebView *webViewSearch;                       ///< The searching web view
	Runner * runner;                               ///< The current runner
	std::string filepath;                          ///< The file path
	std::string display;                           ///< next displaying chain to insert in tab
	QVariantMap list_cplus;                        ///< stats list
	QVariantMap list_header;                       ///< stats list
	QVariantMap list_language;                     ///< stats list
	QVariantMap list_tag;                          ///< stats list
	QVariantMap list_info;                         ///< stats list
};

#endif // MAINVIEW_H
