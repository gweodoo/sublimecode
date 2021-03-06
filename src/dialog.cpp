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

#include "dialog.h"
#include "ui_dialog.h"
using namespace std;

Dialog::Dialog(Configuration *config, QWidget *parent) :
    QDialog(parent)
{
	ui = new Ui_Dialog();
	this->config = config;
	mpath = QString::fromUtf8(config->getSourcesDir().c_str());

	ui->setupUi(this);
	model = new CFileSystemModel();
	ui->getTreeView()->setModel(model); 
	ui->getTreeView()->setRootIndex(model->index(mpath));
	ui->getTreeView()->setColumnHidden(1, true);
	ui->getTreeView()->setColumnHidden(2, true);
	ui->getTreeView()->setColumnHidden(3, true);
	model->checkAllBoxes(mpath);
	QObject::connect(ui->getPushButton(), SIGNAL(clicked()), this, SLOT(Finish()));
	QObject::connect(ui->getSelectAll(), SIGNAL(clicked()), this, SLOT(SelectAll()));
	QObject::connect(ui->getdeSelectAll(), SIGNAL(clicked()), this, SLOT(DeSelectAll()));
}

Dialog::~Dialog()
{
	delete ui;
}

void Dialog::Finish()
{
	foreach (const QPersistentModelIndex &value, model->checkedIndexes)
	{
		QFileInfo fileInfo = model->filePath(value);
		if(fileInfo.isFile()) {
			string absolutePath = fileInfo.absolutePath().toStdString() + "/" + value.data().toString().toStdString();
			QString convrt = QString::fromStdString(absolutePath);
			string converti = convrt.toUtf8().data();
			fileList.push_back(converti);
		}
	}
	if(fileList.empty()){
			QMessageBox::warning(this, "No selected file", "You must select at least one item in the tree.\nPlease try again");
			return;
	}
	new MainView(this->config, fileList);
	this->hide();
}

void Dialog::SelectAll()
{
	updateCheckAllComboBox(mpath);
}

void Dialog::DeSelectAll()
{
	updateunCheckAllComboBox(mpath);
}

void Dialog::updateCheckAllComboBox(QString mpath)
{
	model->checkAllBoxes(mpath);
}

void Dialog::updateunCheckAllComboBox(QString mpath)
{
	model->uncheckAllBoxes(mpath);
}

void Dialog::closeEvent ( QCloseEvent* e ) {
    QDialog::closeEvent ( e );

	delete ui;
	delete model;
}
