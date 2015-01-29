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
#include <QDebug>
#define RSZW(percent) (this->width*percent/100)
#define RSZH(percent) (this->height*percent/100)

void Ui_MainView::setupUi(QMainWindow *MainView)
{
	QRect rect = QApplication::desktop()->screenGeometry();

        MainView->setFixedSize(rect.width()*0.8, rect.height()*0.8);
	
	this->width = MainView->width();
	this->height = MainView->height();
	
	MainView->move((rect.width() - this->width) /2, (rect.height() - this->height) /2);
	
	if (MainView->objectName().isEmpty())
		MainView->setObjectName(QString("MainView"));
	centralWidget = new QWidget(MainView);
	centralWidget->setObjectName(QString("centralWidget"));
	
	leftWidget = new QWidget(centralWidget);
	leftWidget->setObjectName(QString("leftWidget"));
	leftWidget->setGeometry(QRect(0, 0, RSZW(28), RSZH(100)));
	

	tagGroupBox = new QGroupBox(leftWidget);
	tagGroupBox->setObjectName(QString("tagGroupBox"));
	tagGroupBox->setGeometry(QRect(RSZW(2), RSZH(3), RSZW(24), RSZH(26)));
	
	projectGroupBox = new QGroupBox(leftWidget);
	projectGroupBox->setObjectName(QString("projectGroupBox"));
	projectGroupBox->setGeometry(QRect(RSZW(2), RSZH(32), RSZW(24), RSZH(10)));
	
	lineEdit = new QLineEdit(tagGroupBox);
	lineEdit->setObjectName(QString("lineEdit"));
	lineEdit->setGeometry(QRect(RSZW(2), RSZH(4), RSZW(20), RSZH(4)));
	
	radio1 = new QRadioButton(tagGroupBox);
	radio1->setObjectName(QString("radio1"));
	radio1->setGeometry(QRect(RSZW(2), RSZH(8), RSZW(8), RSZH(4)));
	radio1->setText(": By Name");
	radio1->setChecked(true);
	
	radio2 = new QRadioButton(tagGroupBox);
	radio2->setObjectName(QString("radio2"));
	radio2->setGeometry(QRect(RSZW(2), RSZH(12), RSZW(8), RSZH(4)));
	radio2->setText(": By Type");
	
	radio3 = new QRadioButton(tagGroupBox);
	radio3->setObjectName(QString("radio3"));
	radio3->setGeometry(QRect(RSZW(2), RSZH(16), RSZW(8), RSZH(4)));
	radio3->setText(": By File");

	pushButton = new QPushButton(tagGroupBox);
	pushButton->setObjectName(QString("pushButton"));
	pushButton->setGeometry(QRect(RSZW(2), RSZH(20), RSZW(20), RSZH(4)));
	
	typeSelector = new QComboBox(tagGroupBox);
	typeSelector->setObjectName("typeSelector");
	typeSelector->setGeometry(QRect(RSZW(11), RSZH(12), RSZW(11), RSZH(4)));
	typeSelector->setVisible(false);
	
	resetButton = new QPushButton(projectGroupBox);
	resetButton->setObjectName(QString("resetButton"));
	resetButton->setGeometry(QRect(RSZW(2), RSZH(4), RSZW(20), RSZH(4)));
	
	tagGroupBox->raise();
	projectGroupBox->raise();
	
	rightWidget = new QWidget(centralWidget);
	rightWidget->setObjectName(QString("rightWidget"));
	rightWidget->setGeometry(QRect(RSZW(28), 0, RSZW(72), RSZH(100)));
	MainView->setCentralWidget(centralWidget);
	
	webView = new QWebView(rightWidget);
	webView->setGeometry(QRect(RSZW(0), RSZH(0), RSZW(71), RSZH(100)));
	webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
	webView->settings()->setObjectCacheCapacities(0,0,0);
	
	tabWidget = new QTabWidget(rightWidget);
	tabWidget->setGeometry(QRect(RSZW(0), RSZH(0), RSZW(71), RSZH(100)));
	tabWidget->addTab(webView, "Home");
	tabWidget->setTabsClosable(true);
	
	waitingMovie = new QMovie(":/mySpinner.gif");
	waitingLabel = new QLabel(centralWidget);
	waitingLabel->setFixedSize(200, 200);
	waitingLabel->move((this->width - waitingLabel->width()) /2, (this->height - waitingLabel->height()) /2);
	waitingLabel->setObjectName(QString("waitingWidget"));
	waitingLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	waitingLabel->setMovie (waitingMovie);
	waitingLabel->setVisible(false);

	enterShortcut = new QShortcut(QKeySequence("Return"), tagGroupBox);

	retranslateUi(MainView);
	MainView->setWindowTitle("Sublime Code");

	QMetaObject::connectSlotsByName(MainView);
}

void Ui_MainView::retranslateUi(QMainWindow *MainView)
{
	MainView->setWindowTitle(QApplication::translate("MainView", "MainView", 0));
	tagGroupBox->setTitle(QApplication::translate("MainView", "TAG", 0));
	projectGroupBox->setTitle(QApplication::translate("MainView", "PROJECT", 0));
	pushButton->setText(QApplication::translate("MainView", "Search", 0));
	resetButton->setText(QApplication::translate("MainView", "Open project", 0));
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

QTabWidget* Ui_MainView::getTabWidget()
{
	return this->tabWidget;
}

QShortcut* Ui_MainView::getShortcutEnter()
{
	return this->enterShortcut;
}

QPushButton* Ui_MainView::getResetButton() {
	return this->resetButton;
}

QLabel* Ui_MainView::getWaitingLabel()
{
	return this->waitingLabel;
}

Ui_MainView::~Ui_MainView() 
{
	delete webView;
	delete tabWidget;
	delete centralWidget;
}

QMovie* Ui_MainView::getWaitingMovie()
{
	return this->waitingMovie;
}
