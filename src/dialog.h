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
    explicit Dialog(QString file, QWidget *parent = 0);
    ~Dialog();
    Ui_Dialog *ui;

private:
    CFileSystemModel *model;

public slots:
	void Finish();
	void SelectAll();
	void DeSelectAll();
	void updateCheckAllComboBox();
};

#endif // DIALOG_H