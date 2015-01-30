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


#define RSZW(percent) (this->width*percent/100)  ///< compute width in percent (resolution scale)
#define RSZH(percent) (this->height*percent/100) ///< compute height in percent (resolution scale)

QT_BEGIN_NAMESPACE
/**
 * Ui dialog is the displayer (window maker) for dialog view
 */
class Ui_Dialog
{
private: 
	QTreeView *treeView;      ///< sources tree displayer
	QPushButton *pushButton;  ///< finish button
	QPushButton *selectAll;   ///< checkAll button
	QPushButton *deselectAll; ///< uncheckAll button
	int width;                ///< window width
	int height;               ///< window height

public:
	///default destructor
	~Ui_Dialog();
	/**
	 * graphical initializer
	 * \param[in] Dialog the base class dialog, our container
	 */
	void setupUi(QDialog *Dialog);
	/**
	 * Translate buttons according to system language.
	 * \param[in] Dialog the base class dialog, our container
	 */
	void retranslateUi(QDialog *Dialog);
	/**
	 * sources tree qt object getter
	 * \return class member as pointer
	 */
	QTreeView *getTreeView();
	/**
	 * Finish button qt object getter
	 * \return class member as pointer
	 */
	QPushButton *getPushButton();
	/**
	 * selectAll button qt object getter
	 * \return class member as pointer
	 */
	QPushButton *getSelectAll();
	/**
	 * uncheck button qt object getter
	 * \return class member as pointer
	 */
	QPushButton *getdeSelectAll();
};

QT_END_NAMESPACE

#endif // UI_DIALOG_H
