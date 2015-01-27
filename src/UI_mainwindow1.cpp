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

#include "UI_mainwindow1.h"
#include "ui_mainView.h"
#include <QInputDialog>

#define RSZW(percent) (this->width*percent/100)
#define RSZH(percent) (this->height*percent/100)

UI_MainWindow1::UI_MainWindow1(){
	centralWidget = NULL;
	directoryWidget = NULL;
	vcsWidget = NULL;
	archiveWidget = NULL;
	sourcesGroupBox = NULL;
	destinationGroupBox = NULL;
	tabs = NULL;
	Parcourir = NULL;
	Parcourir1 = NULL;
	parcourirArchive = NULL;
	Finish= NULL;
	lineEdit= NULL;
	lineEdit1= NULL;
	lineEditVcs= NULL;
	lineEditArchive= NULL;
	lineEditBranch= NULL;
	menuBar= NULL;
	mainToolBar= NULL;
	statusBar= NULL;
	labelBranch= NULL;
	comboBoxVcs= NULL;
	comboBoxArchive= NULL;
}
UI_MainWindow1::~UI_MainWindow1(){
	if(Finish != NULL) delete Finish;
	if(destinationGroupBox != NULL) delete destinationGroupBox;
	if(sourcesGroupBox != NULL) delete sourcesGroupBox;
	if(statusBar != NULL) delete statusBar;
	if(centralWidget != NULL) delete centralWidget;
	if(mainToolBar != NULL) delete mainToolBar;
	if(menuBar != NULL) delete menuBar;

}

const char * const UI_MainWindow1::vcsTypes[] = {"Cvs", "Git", "Mercurial", "Svn"};
const char * const UI_MainWindow1::archiveTypes[] = {"Tarbz2", "Targz", "Zip"};

void UI_MainWindow1::setupUi(QMainWindow *MainWindow)
{	
	QRect rect = QApplication::desktop()->screenGeometry();

        MainWindow->setFixedSize(rect.width()*0.5, rect.height()*0.5);
	
	this->width = MainWindow->width();
	this->height = MainWindow->height();
	
	MainWindow->move((rect.width() - this->width) /2, (rect.height() - this->height) /2);

        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString("MainWindow"));
	//MainWindow->resize(600, 350);
        this->menuBar = new QMenuBar(MainWindow);
	this->menuBar->setObjectName(QString("menuBar"));
        MainWindow->setMenuBar(this->menuBar);
        this->mainToolBar = new QToolBar(MainWindow);
	this->mainToolBar->setObjectName(QString("mainToolBar"));
        MainWindow->addToolBar(this->mainToolBar);
        this->centralWidget = new QWidget(MainWindow);
	this->centralWidget->setObjectName(QString("centralWidget"));
        MainWindow->setCentralWidget(this->centralWidget);
        this->statusBar = new QStatusBar(MainWindow);
	this->statusBar->setObjectName(QString("statusBar"));
        MainWindow->setStatusBar(this->statusBar);
	
	sourcesGroupBox = new QGroupBox(MainWindow);
	sourcesGroupBox->setObjectName(QString("sourcesGroupBox"));
	//sourcesGroupBox->setGeometry(QRect(20, 20, 560, 150));
	sourcesGroupBox->setGeometry(QRect(RSZW(3), RSZH(12), RSZW(94), RSZH(38)));
	
	this->directoryWidget = new QWidget();
	this->lineEdit = new QLineEdit(this->directoryWidget);
        this->lineEdit->setObjectName(QString("lineEdit"));
        this->lineEdit->setGeometry(QRect(RSZW(3), RSZH(8), RSZW(67), RSZH(6)));
	this->Parcourir = new QPushButton(this->directoryWidget);
        this->Parcourir->setObjectName(QString("Parcourir"));
	this->Parcourir->setGeometry(QRect(RSZW(71), RSZH(8), RSZW(16), RSZH(6)));
	this->Parcourir->setText(QString("Browse..."));
	
	this->vcsWidget = new QWidget();
	this->comboBoxVcs = new QComboBox(this->vcsWidget);
	this->comboBoxVcs->setObjectName(QString("comboBoxVcs"));
	this->comboBoxVcs->setGeometry(QRect(RSZW(3), RSZH(4), RSZW(16), RSZH(6)));
	this->lineEditVcs = new QLineEdit(this->vcsWidget);
        this->lineEditVcs->setObjectName(QString("lineEditVcs"));
        this->lineEditVcs->setGeometry(QRect(RSZW(20), RSZH(4), RSZW(67), RSZH(6)));
	this->labelBranch = new QLabel(this->vcsWidget);
	this->labelBranch->setText("Branch : ");
	this->labelBranch->setGeometry(QRect(RSZW(4), RSZH(12), RSZW(15), RSZH(6)));
	this->lineEditBranch = new QLineEdit(this->vcsWidget);
        this->lineEditBranch->setObjectName(QString("lineEditBranch"));
        this->lineEditBranch->setGeometry(QRect(RSZW(20), RSZH(12), RSZW(67), RSZH(6)));
	
	this->archiveWidget = new QWidget();
	this->comboBoxArchive = new QComboBox(this->archiveWidget);
	this->comboBoxArchive->setObjectName(QString("comboBoxArchive"));
	this->comboBoxArchive->setGeometry(QRect(RSZW(3), RSZH(8), RSZW(16), RSZH(6)));
	this->lineEditArchive = new QLineEdit(this->archiveWidget);
        this->lineEditArchive->setObjectName(QString("lineEditArchive"));
        this->lineEditArchive->setGeometry(QRect(RSZW(20), RSZH(8), RSZW(50), RSZH(6)));
	this->parcourirArchive = new QPushButton(this->archiveWidget);
        this->parcourirArchive->setObjectName(QString("parcourirArchive"));
	this->parcourirArchive->setGeometry(QRect(RSZW(71), RSZH(8), RSZW(16), RSZH(6)));
	this->parcourirArchive->setText(QString("Browse..."));
	
   	this->tabs = new QTabWidget(this->sourcesGroupBox);
	this->tabs->setGeometry(QRect(RSZW(2), RSZH(7), RSZW(90), RSZH(28)));
  	this->tabs->addTab(this->directoryWidget,"Directory");  
	this->tabs->addTab(this->vcsWidget,"VCS");
	this->tabs->addTab(this->archiveWidget,"Archive");
	
	destinationGroupBox = new QGroupBox(MainWindow);
	destinationGroupBox->setObjectName(QString("destinationGroupBox"));
	destinationGroupBox->setGeometry(QRect(RSZW(3), RSZH(56), RSZW(94), RSZH(19)));

        this->lineEdit1 = new QLineEdit(this->destinationGroupBox);
        this->lineEdit1->setGeometry(QRect(RSZW(5), RSZH(8), RSZW(67), RSZH(6)));
	this->Parcourir1 = new QPushButton(this->destinationGroupBox);
	this->Parcourir1->setText(QString("Browse..."));
	this->Parcourir1->setGeometry(QRect(RSZW(73), RSZH(8), RSZW(16), RSZH(6)));
	
	this->Finish = new QPushButton(MainWindow);
        this->Finish->setGeometry(QRect(RSZW(76), RSZH(81), RSZW(21), RSZH(6)));
	this->Finish->setText(QString("Next"));
	
        retranslateUi(MainWindow);
	MainWindow->setWindowTitle("Sublime Code");
	
        QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void UI_MainWindow1::retranslateUi(QMainWindow *MainWindow)
{
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
	sourcesGroupBox->setTitle(QApplication::translate("MainWindow", "Sources project : ", 0));
	destinationGroupBox->setTitle(QApplication::translate("MainWindow", "Destination directory : ", 0));
	
	for (size_t i = 0; i < (sizeof(vcsTypes)/sizeof(*vcsTypes)); i++)
		this->comboBoxVcs->addItem(vcsTypes[i]);
	for (size_t i = 0; i < (sizeof(archiveTypes)/sizeof(*archiveTypes)); i++)
		this->comboBoxArchive->addItem(archiveTypes[i]);
} // retranslateUi

QLineEdit* UI_MainWindow1::getLineEdit()
{
	return this->lineEdit;
}

QLineEdit* UI_MainWindow1::getLineEditBranch()
{
	return this->lineEditBranch;
}

QLineEdit* UI_MainWindow1::getLineEdit1()
{
	return this->lineEdit1;
}

QLineEdit* UI_MainWindow1::getLineEditArchive()
{
	return this->lineEditArchive;
}

QPushButton* UI_MainWindow1::getParcourir()
{
	return this->Parcourir;
}

QPushButton* UI_MainWindow1::getParcourir1()
{
	return this->Parcourir1;
}

QPushButton* UI_MainWindow1::getParcourirArchive()
{
	return this->parcourirArchive;
}

QPushButton* UI_MainWindow1::getFinish()
{	
	return this->Finish;
}

QTabWidget* UI_MainWindow1::getQTabWidget()
{
	return this->tabs;
}

QLineEdit* UI_MainWindow1::getLineEditVcs()
{
	return this->lineEditVcs;
}

QComboBox* UI_MainWindow1::getComboBoxVcs()
{
	return this->comboBoxVcs;
}

QComboBox* UI_MainWindow1::getComboBoxArchive()
{
	return this->comboBoxArchive;
}

