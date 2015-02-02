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

#include "UI_mainwindow.h"
#include "ui_mainView.h"
#include <QInputDialog>

#define RSZW(percent) (this->width*percent/100)
#define RSZH(percent) (this->height*percent/100)

UI_MainWindow::UI_MainWindow(){
	centralWidget = NULL;
	directoryWidget = NULL;
	vcsWidget = NULL;
	archiveWidget = NULL;
	sourcesGroupBox = NULL;
	destinationGroupBox = NULL;
	tabs = NULL;
	browseSource = NULL;
	browseDest = NULL;
	browseArchive = NULL;
	Finish= NULL;
	lineEditSource= NULL;
	lineEditDest= NULL;
	lineEditVcs= NULL;
	lineEditArchive= NULL;
	lineEditBranch= NULL;
	labelBranch= NULL;
	comboBoxVcs= NULL;
	comboBoxArchive= NULL;
}
UI_MainWindow::~UI_MainWindow(){
	if(Finish != NULL) delete Finish;
	if(destinationGroupBox != NULL) delete destinationGroupBox;
	if(sourcesGroupBox != NULL) delete sourcesGroupBox;
	if(centralWidget != NULL) delete centralWidget;
}

const char * const UI_MainWindow::vcsTypes[] = {"CVS", "Git", "Mercurial", "SVN"};
const char * const UI_MainWindow::archiveTypes[] = {"Bzip", "Gzip", "Zip"};

void UI_MainWindow::setupUi(QMainWindow *MainWindow)
{	
	QRect rect = QApplication::desktop()->screenGeometry();

        MainWindow->setFixedSize(rect.width()*0.5, rect.height()*0.5);
	
	this->width = MainWindow->width();
	this->height = MainWindow->height();
	
	MainWindow->move((rect.width() - this->width) /2, (rect.height() - this->height) /2);

        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString("MainWindow"));
        this->centralWidget = new QWidget(MainWindow);
	this->centralWidget->setObjectName(QString("centralWidget"));
        MainWindow->setCentralWidget(this->centralWidget);
	
	sourcesGroupBox = new QGroupBox(centralWidget);
	sourcesGroupBox->setObjectName(QString("sourcesGroupBox"));
	sourcesGroupBox->setGeometry(QRect(RSZW(3), RSZH(12), RSZW(94), RSZH(38)));
	
	this->directoryWidget = new QWidget();
	this->lineEditSource = new QLineEdit(this->directoryWidget);
        this->lineEditSource->setObjectName(QString("lineEdit"));
        this->lineEditSource->setGeometry(QRect(RSZW(3), RSZH(8), RSZW(67), RSZH(6)));
	this->browseSource = new QPushButton(this->directoryWidget);
        this->browseSource->setObjectName(QString("Parcourir"));
	this->browseSource->setGeometry(QRect(RSZW(71), RSZH(8), RSZW(16), RSZH(6)));
	this->browseSource->setText(QString("Browse..."));
	
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
	this->browseArchive = new QPushButton(this->archiveWidget);
        this->browseArchive->setObjectName(QString("parcourirArchive"));
	this->browseArchive->setGeometry(QRect(RSZW(71), RSZH(8), RSZW(16), RSZH(6)));
	this->browseArchive->setText(QString("Browse..."));
	
   	this->tabs = new QTabWidget(this->sourcesGroupBox);
	this->tabs->setGeometry(QRect(RSZW(2), RSZH(7), RSZW(90), RSZH(28)));
  	this->tabs->addTab(this->directoryWidget,"Directory");  
	this->tabs->addTab(this->vcsWidget,"VCS");
	this->tabs->addTab(this->archiveWidget,"Archive");
	
	destinationGroupBox = new QGroupBox(centralWidget);
	destinationGroupBox->setObjectName(QString("destinationGroupBox"));
	destinationGroupBox->setGeometry(QRect(RSZW(3), RSZH(56), RSZW(94), RSZH(19)));

        this->lineEditDest = new QLineEdit(this->destinationGroupBox);
        this->lineEditDest->setGeometry(QRect(RSZW(5), RSZH(8), RSZW(67), RSZH(6)));
	this->browseDest = new QPushButton(this->destinationGroupBox);
	this->browseDest->setText(QString("Browse..."));
	this->browseDest->setGeometry(QRect(RSZW(73), RSZH(8), RSZW(16), RSZH(6)));
	
	this->Finish = new QPushButton(centralWidget);
        this->Finish->setGeometry(QRect(RSZW(76), RSZH(81), RSZW(21), RSZH(6)));
	this->Finish->setText(QString("Next"));
	
	waitingMovie = new QMovie(":/mySpinner.gif");
	waitingLabel = new QLabel(centralWidget);
	waitingLabel->setFixedSize(200, 200);
	waitingLabel->move((this->width - waitingLabel->width()) /2, (this->height - waitingLabel->height()) /2);
	waitingLabel->setObjectName(QString("waitingWidget"));
	waitingLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	waitingLabel->setMovie (waitingMovie);
	waitingLabel->setVisible(false);
	
        retranslateUi(MainWindow);
	MainWindow->setWindowTitle("Sublime Code");
	
        QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void UI_MainWindow::retranslateUi(QMainWindow *MainWindow)
{
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
	sourcesGroupBox->setTitle(QApplication::translate("MainWindow", "Sources project : ", 0));
	destinationGroupBox->setTitle(QApplication::translate("MainWindow", "Destination directory : ", 0));
	
	for (size_t i = 0; i < (sizeof(vcsTypes)/sizeof(*vcsTypes)); i++)
		this->comboBoxVcs->addItem(vcsTypes[i]);
	for (size_t i = 0; i < (sizeof(archiveTypes)/sizeof(*archiveTypes)); i++)
		this->comboBoxArchive->addItem(archiveTypes[i]);
} // retranslateUi

QLineEdit* UI_MainWindow::getLineEditSource()
{
	return this->lineEditSource;
}

QLineEdit* UI_MainWindow::getLineEditBranch()
{
	return this->lineEditBranch;
}

QLineEdit* UI_MainWindow::getLineEditDest()
{
	return this->lineEditDest;
}

QLineEdit* UI_MainWindow::getLineEditArchive()
{
	return this->lineEditArchive;
}

QPushButton* UI_MainWindow::getButtonBrowseSource()
{
	return this->browseSource;
}

QPushButton* UI_MainWindow::getButtonBrowseDest()
{
	return this->browseDest;
}

QPushButton* UI_MainWindow::getButtonBrowseArchive()
{
	return this->browseArchive;
}

QPushButton* UI_MainWindow::getFinish()
{	
	return this->Finish;
}

QTabWidget* UI_MainWindow::getQTabWidget()
{
	return this->tabs;
}

QLineEdit* UI_MainWindow::getLineEditVcs()
{
	return this->lineEditVcs;
}

QComboBox* UI_MainWindow::getComboBoxVcs()
{
	return this->comboBoxVcs;
}

QComboBox* UI_MainWindow::getComboBoxArchive()
{
	return this->comboBoxArchive;
}

QMovie* UI_MainWindow::getWaitingMovie()
{
	return this->waitingMovie;
}

QWidget * UI_MainWindow::getCentralWidget()
{
	return this->centralWidget;
}

QLabel* UI_MainWindow::getWaitingLabel()
{
	return this->waitingLabel;
}
