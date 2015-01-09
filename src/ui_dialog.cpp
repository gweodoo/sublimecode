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
#include "ui_dialog.h"

void Ui_Dialog::setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString("Dialog"));
	Dialog->resize(600,500);
        treeView = new QTreeView(Dialog);
        treeView->setObjectName(QString("treeView"));
        treeView->setGeometry(QRect(10, 10, 581, 400));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString("pushButton"));
	pushButton->setText("Finish");
        pushButton->setGeometry(QRect(500, 430, 91, 27));
        selectAll = new QPushButton(Dialog);
        selectAll->setObjectName(QString("selectAll"));
	selectAll->setText("Select All");
        selectAll->setGeometry(QRect(10, 430, 91, 27));
	deselectAll = new QPushButton(Dialog);
        deselectAll->setObjectName(QString("deselectAll"));
	deselectAll->setText("Deselect All");
        deselectAll->setGeometry(QRect(100, 430, 91, 27));
        retranslateUi(Dialog);
	
	this->width = Dialog->width();
	this->height = Dialog->height();
	
	this->rect = QApplication::desktop()->screenGeometry();
 
	this->screenWidth = this->rect.width();
	this->screenHeight = this->rect.height();
 
	this->x = (this->screenWidth - this->width) /2;
	this->y = (this->screenHeight - this->height) /2;

	Dialog->move ( this->x, this->y );
        //Dialog->resize(screenWidth/2, screenHeight/2);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

void Ui_Dialog::retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        pushButton->setText(QApplication::translate("Dialog", "Finish", 0));
    } // retranslateUi
    
QPushButton* Ui_Dialog::getPushButton()
{
	return pushButton;
}

QPushButton* Ui_Dialog::getSelectAll()
{
	return selectAll;
}

QPushButton* Ui_Dialog::getdeSelectAll()
{
	return deselectAll;
}

QTreeView* Ui_Dialog::getTreeView()
{
	return treeView;
}

