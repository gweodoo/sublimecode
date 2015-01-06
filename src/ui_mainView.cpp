#include "ui_mainView.h"

void Ui_MainView::setupUi(QMainWindow *MainView)
{
	if (MainView->objectName().isEmpty())
		MainView->setObjectName(QString("MainView"));
	MainView->setFixedSize(1200, 800);
	centralWidget = new QWidget(MainView);
	centralWidget->setObjectName(QString("centralWidget"));
	leftWidget = new QWidget(centralWidget);
	leftWidget->setObjectName(QString("leftWidget"));
	leftWidget->setGeometry(QRect(0, 0, 240, 800));
	leftWidget->setStyleSheet(QString("border-right: 1px solid gray"));
	tagGroupBox = new QGroupBox(leftWidget);
	tagGroupBox->setObjectName(QString("tagGroupBox"));
	tagGroupBox->setGeometry(QRect(10, 10, 221, 111));
	pushButton = new QPushButton(tagGroupBox);
	pushButton->setObjectName(QString("pushButton"));
	pushButton->setGeometry(QRect(60, 70, 99, 27));
	lineEdit = new QLineEdit(tagGroupBox);
	lineEdit->setObjectName(QString("lineEdit"));
	lineEdit->setGeometry(QRect(10, 30, 201, 27));
	otherGroupBox = new QGroupBox(leftWidget);
	otherGroupBox->setObjectName(QString("otherGroupBox"));
	otherGroupBox->setGeometry(QRect(10, 130, 221, 71));
	callGraphButton = new QPushButton(otherGroupBox);
	callGraphButton->setObjectName(QString("callGraphButton"));
	callGraphButton->setGeometry(QRect(10, 30, 201, 31));
	StatsGroupBox = new QGroupBox(leftWidget);
	StatsGroupBox->setObjectName(QString("StatsGroupBox"));
	StatsGroupBox->setGeometry(QRect(10, 210, 221, 151));
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
	webView->setGeometry(QRect(240, 0, 960, 800));

	menuBar->addAction(menuFile->menuAction());
	menuBar->addAction(menuEdit->menuAction());
	menuBar->addAction(menuView->menuAction());

	MainView->setWindowTitle("Sublime Code");
	
	MainView->setWindowTitle("Sublime Code");
	MainView->move (((QApplication::desktop()->screenGeometry().width() - MainView->width()) /2), 
			((QApplication::desktop()->screenGeometry().height() - MainView->height()) /2));
       
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
