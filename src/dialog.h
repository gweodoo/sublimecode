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
#include "ui_dialog.h"
#include "CFileSystemModel.h"
#include "mainView.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Configuration *config, QWidget *parent = 0);
    ~Dialog();
    Ui_Dialog *ui;

private:
    CFileSystemModel *model;
    QString mpath;
    std::vector<std::string> fileList;
    Configuration *config;
    QModelIndex *index;
    std::string absolutePath;

public slots:
	void Finish();
	void SelectAll();
	void DeSelectAll();
	void updateCheckAllComboBox(QString mpath);
	void updateunCheckAllComboBox(QString mpath);
	void closeEvent(QCloseEvent* e);
};

#endif // DIALOG_H
