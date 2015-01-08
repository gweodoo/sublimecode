#include "ui_dialog.h"

void Ui_Dialog::setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString("Dialog"));
        Dialog->resize(600, 500);
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

