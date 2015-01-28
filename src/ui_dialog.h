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
#include <QDesktopWidget>
#include <QLabel>
#include <QMovie>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
private: 
	QTreeView *treeView;
	QPushButton *pushButton;
	QPushButton *selectAll;
	QPushButton *deselectAll;
	int width, height;

public:
	~Ui_Dialog();
	void setupUi(QDialog *Dialog);
	void retranslateUi(QDialog *Dialog);
	QTreeView *getTreeView();
	QPushButton *getPushButton();
	QPushButton *getSelectAll();
	QPushButton *getdeSelectAll();
};

QT_END_NAMESPACE

#endif // UI_DIALOG_H
