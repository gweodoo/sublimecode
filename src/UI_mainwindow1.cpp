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

UI_MainWindow1::UI_MainWindow1(){}
UI_MainWindow1::~UI_MainWindow1(){}

const char * const UI_MainWindow1::vcsTypes[] = {"Cvs", "Git", "Mercurial", "Svn"};
const char * const UI_MainWindow1::archiveTypes[] = {"Tarbz2", "Targz", "Zip"};

void UI_MainWindow1::setupUi(QMainWindow *MainWindow)
{	
	this->rect = QApplication::desktop()->screenGeometry();
 
	this->screenWidth = this->rect.width();
	this->screenHeight = this->rect.height();
	
	this->width = MainWindow->width();
	this->height = MainWindow->height();
	
	this->x = (this->screenWidth - this->width) /2;
	this->y = (this->screenHeight - this->height) /2;

	MainWindow->move ( this->x, this->y );
        MainWindow->resize(screenWidth/4, screenHeight/4);

        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString("MainWindow"));
	MainWindow->resize(600, 350);
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
	sourcesGroupBox->setGeometry(QRect(20, 20, 560, 150));
	
	this->directoryWidget = new QWidget();
	this->lineEdit = new QLineEdit(this->directoryWidget);
        this->lineEdit->setObjectName(QString("lineEdit"));
        this->lineEdit->setGeometry(QRect(10, 25, 430, 27));
	this->Parcourir = new QPushButton(this->directoryWidget);
        this->Parcourir->setObjectName(QString("Parcourir"));
	this->Parcourir->setGeometry(QRect(445, 25, 80, 27));
	this->Parcourir->setText(QString("Parcourir..."));
	
	this->vcsWidget = new QWidget();
	this->comboBoxVcs = new QComboBox(this->vcsWidget);
	this->comboBoxVcs->setObjectName(QString("comboBoxVcs"));
	this->comboBoxVcs->setGeometry(QRect(10, 10, 120, 27));
	this->lineEditVcs = new QLineEdit(this->vcsWidget);
        this->lineEditVcs->setObjectName(QString("lineEditVcs"));
        this->lineEditVcs->setGeometry(QRect(140, 10, 385, 27));
	this->labelBranch = new QLabel(this->vcsWidget);
	this->labelBranch->setText("Branch : ");
	this->labelBranch->setGeometry(QRect(15, 40, 110, 27));
	this->lineEditBranch = new QLineEdit(this->vcsWidget);
        this->lineEditBranch->setObjectName(QString("lineEditBranch"));
        this->lineEditBranch->setGeometry(QRect(140, 40, 385, 27));
	
	this->archiveWidget = new QWidget();
	this->comboBoxArchive = new QComboBox(this->archiveWidget);
	this->comboBoxArchive->setObjectName(QString("comboBoxArchive"));
	this->comboBoxArchive->setGeometry(QRect(10, 25, 120, 27));
	this->lineEditArchive = new QLineEdit(this->archiveWidget);
        this->lineEditArchive->setObjectName(QString("lineEditArchive"));
        this->lineEditArchive->setGeometry(QRect(140, 25, 295, 27));
	this->parcourirArchive = new QPushButton(this->archiveWidget);
        this->parcourirArchive->setObjectName(QString("parcourirArchive"));
	this->parcourirArchive->setGeometry(QRect(445, 25, 80, 27));
	this->parcourirArchive->setText(QString("Parcourir..."));
	
   	this->tabs = new QTabWidget(this->sourcesGroupBox);
	this->tabs->setGeometry(QRect(10, 25, 540, 110));
  	this->tabs->addTab(this->directoryWidget,"Directory");  
	this->tabs->addTab(this->vcsWidget,"VCS");
	this->tabs->addTab(this->archiveWidget,"Archive");
	
	destinationGroupBox = new QGroupBox(MainWindow);
	destinationGroupBox->setObjectName(QString("destinationGroupBox"));
	destinationGroupBox->setGeometry(QRect(20, 190, 560, 65));

        this->lineEdit1 = new QLineEdit(this->destinationGroupBox);
        this->lineEdit1->setGeometry(QRect(20, 25, 430, 27));
	this->Parcourir1 = new QPushButton(this->destinationGroupBox);
	this->Parcourir1->setText(QString("Parcourir..."));
	this->Parcourir1->setGeometry(QRect(455, 25, 80, 27));
	
	this->Finish = new QPushButton(MainWindow);
        this->Finish->setGeometry(QRect(475, 275, 105, 27));
	this->Finish->setText(QString("Suivant"));
	
        retranslateUi(MainWindow);
	MainWindow->setWindowTitle("Sublime Code");
	
        QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void UI_MainWindow1::retranslateUi(QMainWindow *MainWindow)
{
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
	sourcesGroupBox->setTitle(QApplication::translate("MainWindow", "Sources du projet : ", 0));
	destinationGroupBox->setTitle(QApplication::translate("MainWindow", "Dossier de destination : ", 0));
	
	for (int i = 0; i < (sizeof(vcsTypes)/sizeof(*vcsTypes)); i++)
		this->comboBoxVcs->addItem(vcsTypes[i]);
	for (int i = 0; i < (sizeof(archiveTypes)/sizeof(*archiveTypes)); i++)
		this->comboBoxArchive->addItem(archiveTypes[i]);
} // retranslateUi

QLineEdit* UI_MainWindow1::getLineEdit()
{
	return this->lineEdit;
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
