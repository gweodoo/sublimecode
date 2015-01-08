/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QHeaderView>
#include <QPushButton>
#include <QTreeView>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
private: 
	QTreeView *treeView;
	QPushButton *pushButton;
	QPushButton *selectAll;
	QPushButton *deselectAll;

public:
	void setupUi(QDialog *Dialog);
	void retranslateUi(QDialog *Dialog);
	QTreeView *getTreeView();
	QPushButton *getPushButton();
	QPushButton *getSelectAll();
	QPushButton *getdeSelectAll();
};

QT_END_NAMESPACE

#endif // UI_DIALOG_H