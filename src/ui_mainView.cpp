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

#include "ui_mainView.h"

void Ui_MainView::setupUi(QMainWindow *MainView)
{
	if (MainView->objectName().isEmpty())
		MainView->setObjectName(QString("MainView"));
	centralWidget = new QWidget(MainView);
	centralWidget->setObjectName(QString("centralWidget"));
	leftWidget = new QWidget(centralWidget);
	leftWidget->setObjectName(QString("leftWidget"));
	leftWidget->setGeometry(QRect(0, 0, 240, 800));
	leftWidget->setStyleSheet(QString("border-right: 1px solid gray;"));
	tagGroupBox = new QGroupBox(leftWidget);
	tagGroupBox->setObjectName(QString("tagGroupBox"));
	tagGroupBox->setGeometry(QRect(10, 10, 221, 151));
	radio1 = new QRadioButton(tagGroupBox);
	radio1->setObjectName(QString("radio1"));
	radio1->setGeometry(QRect(10, 55, 99, 27));
	radio1->setText(": By Name");
	radio2 = new QRadioButton(tagGroupBox);
	radio2->setObjectName(QString("radio2"));
	radio2->setGeometry(QRect(10, 75, 99, 27));
	radio2->setText(": By Type");
	typeSelector = new QComboBox(tagGroupBox);
	typeSelector->setObjectName("typeSelector");
	typeSelector->setGeometry(QRect(100, 75, 109, 27));
	typeSelector->setVisible(false);
	radio3 = new QRadioButton(tagGroupBox);
	radio3->setObjectName(QString("radio3"));
	radio3->setGeometry(QRect(10, 95, 99, 27));
	radio3->setText(": By File");
	radio1->setChecked(true);
	pushButton = new QPushButton(tagGroupBox);
	pushButton->setObjectName(QString("pushButton"));
	pushButton->setGeometry(QRect(60, 120, 99, 27));
	lineEdit = new QLineEdit(tagGroupBox);
	lineEdit->setObjectName(QString("lineEdit"));
	lineEdit->setGeometry(QRect(10, 30, 201, 27));
	otherGroupBox = new QGroupBox(leftWidget);
	otherGroupBox->setObjectName(QString("otherGroupBox"));
	otherGroupBox->setGeometry(QRect(10, 170, 221, 71));
	callGraphButton = new QPushButton(otherGroupBox);
	callGraphButton->setObjectName(QString("callGraphButton"));
	callGraphButton->setGeometry(QRect(10, 30, 201, 31));
	StatsGroupBox = new QGroupBox(leftWidget);
	StatsGroupBox->setObjectName(QString("StatsGroupBox"));
	StatsGroupBox->setGeometry(QRect(10, 250, 221, 151));
	stats1Button = new QPushButton(StatsGroupBox);
	stats1Button->setObjectName(QString("stats1Button"));
	stats1Button->setGeometry(QRect(10, 30, 201, 31));
	stats2Button = new QPushButton(StatsGroupBox);
	stats2Button->setObjectName(QString("stats2Button"));
	stats2Button->setGeometry(QRect(10, 70, 201, 31));
	stats3Button = new QPushButton(StatsGroupBox);
	stats3Button->setObjectName(QString("stats3Button"));
	stats3Button->setGeometry(QRect(10, 110, 201, 31));
	tagGroupBox->raise();
	otherGroupBox->raise();
	StatsGroupBox->raise();
	rightWidget = new QWidget(centralWidget);
	rightWidget->setObjectName(QString("rightWidget"));
	rightWidget->setGeometry(QRect(240, 0, 960, 800));
	MainView->setCentralWidget(centralWidget);
	menuBar = new QMenuBar(MainView);
	menuBar->setObjectName(QString("menuBar"));
	menuBar->setGeometry(QRect(0, 0, 1000, 25));
	menuFile = new QMenu(menuBar);
	menuFile->setObjectName(QString("menuFile"));
	menuEdit = new QMenu(menuBar);
	menuEdit->setObjectName(QString("menuEdit"));
	menuView = new QMenu(menuBar);
	menuView->setObjectName(QString("menuView"));
	MainView->setMenuBar(menuBar);
	webView = new QWebView(MainView);
	webView->setGeometry(QRect(240, 30, 980, 700));
	webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

	menuBar->addAction(menuFile->menuAction());
	menuBar->addAction(menuEdit->menuAction());
	menuBar->addAction(menuView->menuAction());

	MainView->setWindowTitle("Sublime Code");
	
	this->width = MainView->width();
	this->height = MainView->height();
	
	this->rect = QApplication::desktop()->screenGeometry();
 
	this->screenWidth = this->rect.width();
	this->screenHeight = this->rect.height();

        MainView->resize(screenWidth, screenHeight);
       
	retranslateUi(MainView);

	QMetaObject::connectSlotsByName(MainView);
}

void Ui_MainView::retranslateUi(QMainWindow *MainView)
{
	MainView->setWindowTitle(QApplication::translate("MainView", "MainView", 0));
	tagGroupBox->setTitle(QApplication::translate("MainView", "TAG", 0));
	pushButton->setText(QApplication::translate("MainView", "Search", 0));
	otherGroupBox->setTitle(QApplication::translate("MainView", "GRAPHS", 0));
	callGraphButton->setText(QApplication::translate("MainView", "Call Graph", 0));
	StatsGroupBox->setTitle(QApplication::translate("MainView", "STATS", 0));
	stats1Button->setText(QApplication::translate("MainView", "Stats1", 0));
	stats2Button->setText(QApplication::translate("MainView", "Stats2", 0));
	stats3Button->setText(QApplication::translate("MainView", "Stats3", 0));
	menuFile->setTitle(QApplication::translate("MainView", "File", 0));
	menuEdit->setTitle(QApplication::translate("MainView", "Edit", 0));
	menuView->setTitle(QApplication::translate("MainView", "View", 0));
}

QWidget * Ui_MainView::getCentralWidget()
{
	return this->centralWidget;
}

QWebView * Ui_MainView::getWebView()
{
	return this->webView;
}

QPushButton * Ui_MainView::getPushButton()
{
	return this->pushButton;
}

QLineEdit * Ui_MainView::getLineEdit()
{
	return this->lineEdit;
}

QRadioButton* Ui_MainView::getRadioName()
{
	return this->radio1;
}

QRadioButton* Ui_MainView::getRadioType()
{
	return this->radio2;
}

QRadioButton* Ui_MainView::getRadioFile()
{
	return this->radio3;
}

QComboBox* Ui_MainView::gettypeSelector()
{
	return this->typeSelector;
}
