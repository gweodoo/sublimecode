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
//         MainWindow->resize(screenWidth/4, screenHeight/4);
	
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString("MainWindow"));
	MainWindow->resize(400, 300);
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
        this->Parcourir = new QPushButton(this->centralWidget);
        this->Parcourir->setObjectName(QString("Parcourir"));
	this->Parcourir->setGeometry(QRect(300, 50, 91, 27));
	this->Parcourir->setText(QString("Parcourir..."));
        this->lineEdit = new QLineEdit(this->centralWidget);
        this->lineEdit->setObjectName(QString("lineEdit"));
        this->lineEdit->setGeometry(QRect(10, 50, 281, 27));
	this->labelParcourir = new QLabel(this->centralWidget);
	this->labelParcourir->setGeometry(QRect(10, 27, 281, 27));
	this->labelParcourir->setText("Sources du projet :");
	this->Parcourir1 = new QPushButton(this->centralWidget);
        this->Parcourir1->setGeometry(QRect(300, 150, 91, 27));
	this->Parcourir1->setText(QString("Parcourir..."));
        this->lineEdit1 = new QLineEdit(this->centralWidget);
        this->lineEdit1->setGeometry(QRect(10, 150, 281, 27));
	this->labelParcourir1 = new QLabel(this->centralWidget);
	this->labelParcourir1->setGeometry(QRect(10, 127, 281, 27));
	this->labelParcourir1->setText("Dossier de destination :");
	this->Finish = new QPushButton(this->centralWidget);
        this->Finish->setGeometry(QRect(300, 220, 91, 27));
	this->Finish->setText(QString("Suivant"));
        retranslateUi(MainWindow);
	MainWindow->setWindowTitle("Sublime Code");
	
        QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void UI_MainWindow1::retranslateUi(QMainWindow *MainWindow)
{
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
} // retranslateUi

QLineEdit* UI_MainWindow1::getLineEdit()
{
	return this->lineEdit;
}

QLineEdit* UI_MainWindow1::getLineEdit1()
{
	return this->lineEdit1;
}

QPushButton* UI_MainWindow1::getParcourir()
{
	return this->Parcourir;
}

QPushButton* UI_MainWindow1::getParcourir1()
{
	return this->Parcourir1;
}

QPushButton* UI_MainWindow1::getFinish()
{	
	return this->Finish;
}
