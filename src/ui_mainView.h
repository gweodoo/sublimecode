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

#ifndef UI_MAINVIEW_H
#define UI_MAINVIEW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGroupBox>
#include <QHeaderView>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QWidget>
#include <QWebView>
#include <QtGui/QDesktopWidget>
#include <QRadioButton>
#include <QComboBox>
#include <QShortcut>
#include <QLabel>
#include <QMovie>

QT_BEGIN_NAMESPACE

/**
 * Ui mainView is the displayer (window maker) for main view
 */
class Ui_MainView
{
public:
	static const char * const legendLabels[];
	///default destructor
	~Ui_MainView();    
	/**
	 * graphical initializer
	 * \param[in] MainView the base class MainView, our container
	 */
	void setupUi(QMainWindow *MainView);
	/**
	 * Translate buttons according to system language.
	 * \param[in] MainView the base class MainView, our container
	 */
	void retranslateUi(QMainWindow *MainView);
	/**
	 * Main widget qt object getter
	 * \return class member as pointer
	 */
	QWidget *getCentralWidget();
	/**
	 * Home webView qt object getter
	 * \return class member as pointer
	 */
	QWebView *getWebView();
	/**
	 * Search button qt object getter
	 * \return class member as pointer
	 */
	QPushButton * getPushButton();
	/**
	 * Open new project button qt object getter
	 * \return class member as pointer
	 */
	QPushButton * getResetButton();
	/**
	 * Tag line edit qt object getter
	 * \return class member as pointer
	 */
	QLineEdit * getLineEdit();
	/**
	 * Tag radio button qt object getter
	 * \return class member as pointer
	 */
	QRadioButton *getRadioName();
	/**
	 * Type radio button qt object getter
	 * \return class member as pointer
	 */
	QRadioButton *getRadioType();
	/**
	 * File radio button qt object getter
	 * \return class member as pointer
	 */	
	QRadioButton *getRadioFile();
	/**
	 * Tag type selector qt object getter
	 * \return class member as pointer
	 */
	QComboBox *gettypeSelector();
	/**
	 * Tab widget qt object getter
	 * \return class member as pointer
	 */
	QTabWidget *getTabWidget();
	/**
	 * Enter keybord shortcut qt object getter
	 * \return class member as pointer
	 */
	QShortcut *getShortcutEnter();
	/**
	 * Waiting spinner label qt object getter
	 * \return class member as pointer
	 */
	QLabel *getWaitingLabel();
	/**
	 * Waiting spinner movie qt object getter
	 * \return class member as pointer
	 */
	QMovie *getWaitingMovie();
	QGroupBox *getLegendGroupBox();
    
private:
	QComboBox *typeSelector;                   ///< tag type selector
	QWidget *centralWidget;                    ///< main widget 
	QWidget *leftWidget;                       ///< left widget
	QGroupBox *tagGroupBox;                    ///< tag search group box
	QGroupBox *projectGroupBox;                ///< open new project group box
	QPushButton *pushButton;                   ///< search button
	QGroupBox *legendGroupBox;
	QPushButton *resetButton;                  ///< open new project button
	QLineEdit *lineEdit;                       ///< get tag line edit
	QWidget *rightWidget;                      ///< right widget
	QWebView *webView;                         ///< home web view
	QRadioButton *radio1;                      ///< tag radio buttons
	QRadioButton *radio2;                      ///< type radio buttons
	QRadioButton *radio3;                      ///< file radio buttons
	QTabWidget *tabWidget;                     ///< tab widget
	QShortcut *enterShortcut;                  ///< keyboard enter shortcut
	int width;                                 ///< window width 
	int height;                                ///< window height
	QLabel *waitingLabel;                      ///< waiting spinner label
	QMovie *waitingMovie;                      ///< waiting spinner movie 
	QRadioButton *legendRadio0;
	QRadioButton *legendRadio1;
	QRadioButton *legendRadio2;
	QRadioButton *legendRadio3;
};

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H

