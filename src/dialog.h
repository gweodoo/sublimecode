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

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QCloseEvent>
#include "ui_dialog.h"
#include "CFileSystemModel.h"
#include "mainView.h"

/**
 * Dialog is object called to display sources tree to user.
 * Then, he can select paths he wants to analyze
 */
class Dialog : public QDialog
{
	Q_OBJECT

public:
	/**
	 * default constructor
	 * \param[in] config global configuration
	 * \param[in] parent upstream accessor
	 */
	explicit Dialog(Configuration *config, QWidget *parent = 0);
	///default destructor
	~Dialog();


private:
	Ui_Dialog *ui;                     ///< the graphical displayer
	CFileSystemModel *model;           ///< sources tree handler
	QString mpath;                     ///< root sources tree
	std::vector<std::string> fileList; ///< select list of files
	Configuration *config;             ///< current configuration
public slots:
	/**
	 * when click on "Finish", do some post-actions before running MainView
	 */
	void Finish();
	/**
	 * action to select all paths in sources tree
	 */
	void SelectAll();
	/**
	 * action to deselect all paths in sources tree
	 */
	void DeSelectAll();
	/**
	 * handler to check all paths in current tree
	 * \param[in] mpath current folder to check
	 */
	void updateCheckAllComboBox(QString mpath);
	/**
	 * handler to uncheck all paths in current tree
	 * \param[in] mpath current folder to uncheck
	 */
	void updateunCheckAllComboBox(QString mpath);
	/**
	 * Handler when close button is pressed
	 * \param[in] e the event
	 */
	void closeEvent(QCloseEvent* e);
};

#endif // DIALOG_H
