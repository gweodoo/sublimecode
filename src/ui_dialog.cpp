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

#define RSZW(percent) (this->width*percent/100)
#define RSZH(percent) (this->height*percent/100)

void Ui_Dialog::setupUi(QDialog *Dialog)
    {
	QRect rect = QApplication::desktop()->screenGeometry();

        Dialog->setFixedSize(rect.width()*0.5, rect.height()*0.5);
	
	this->width = Dialog->width();
	this->height = Dialog->height();
	
	Dialog->move((rect.width() - this->width) /2, (rect.height() - this->height) /2);
	
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString("Dialog"));
        treeView = new QTreeView(Dialog);
        treeView->setObjectName(QString("treeView"));
        treeView->setGeometry(QRect(RSZW(3), RSZH(4), RSZW(94), RSZH(84)));

        selectAll = new QPushButton(Dialog);
        selectAll->setObjectName(QString("selectAll"));
	selectAll->setText("Select All");
        selectAll->setGeometry(QRect(RSZW(3), RSZH(91), RSZW(16), RSZH(6)));
	
	deselectAll = new QPushButton(Dialog);
        deselectAll->setObjectName(QString("deselectAll"));
	deselectAll->setText("Deselect All");
        deselectAll->setGeometry(QRect(RSZW(22), RSZH(91), RSZW(16), RSZH(6)));
	
	pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString("pushButton"));
	pushButton->setText("Finish");
        pushButton->setGeometry(QRect(RSZW(81), RSZH(91), RSZW(16), RSZH(6)));
	
        retranslateUi(Dialog);

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

