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

QT_BEGIN_NAMESPACE

class Ui_MainView
{
public:
	void setupUi(QMainWindow *MainView);
	void retranslateUi(QMainWindow *MainView);
	QWidget *getCentralWidget();
	QWebView *getWebView();
	QPushButton * getPushButton();
	QLineEdit * getLineEdit();
	QRadioButton *getRadioName();
	QRadioButton *getRadioType();
	QRadioButton *getRadioFile();
	QComboBox *gettypeSelector();
	QPushButton *getCallGraphButton();
    
private:
	QComboBox *typeSelector;
	QWidget *centralWidget;
	QWidget *leftWidget;
	QGroupBox *tagGroupBox;
	QPushButton *pushButton;
	QLineEdit *lineEdit;
	QGroupBox *otherGroupBox;
	QPushButton *callGraphButton;
	QGroupBox *StatsGroupBox;
	QPushButton *stats1Button;
	QPushButton *stats2Button;
	QPushButton *stats3Button;
	QWidget *rightWidget;
	QMenuBar *menuBar;
	QMenu *menuFile;
	QMenu *menuEdit;
	QMenu *menuView;
	QWebView *webView;
	QRadioButton *radio1, *radio2, *radio3;
	int width, height;
};

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H

