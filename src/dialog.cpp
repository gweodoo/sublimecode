#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QString file, QWidget *parent) :
    QDialog(parent)
{
    ui = new Ui_Dialog();
    QString mpath = file;
    ui->setupUi(this);
    model = new CFileSystemModel();
    ui->getTreeView()->setModel(model); 
    ui->getTreeView()->setRootIndex(model->index(mpath));
    ui->getTreeView()->setColumnHidden(1, true);
    ui->getTreeView()->setColumnHidden(2, true);
    ui->getTreeView()->setColumnHidden(3, true);
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
     qDebug() << value.data().toString();
   
   MainView *w = new MainView();
   w->show();
   this->hide();
}

void Dialog::SelectAll()
{
	qDebug() << "toto";
}

void Dialog::DeSelectAll()
{
	qDebug() << "tata";
}

void Dialog::updateCheckAllComboBox()
{
// 	m_d->m_ignoreChange = true;
// 	unsigned checkedCount = checkedFilesCount();
// 	if (checkedCount == 0)
// 	m_d->m_ui.checkAllCheckBox->setCheckState(Qt::Unchecked);
// 	else if (checkedCount == m_d->m_ui.fileView->model()->rowCount())
// 	m_d->m_ui.checkAllCheckBox->setCheckState(Qt::Checked);
// 	else
// 	m_d->m_ui.checkAllCheckBox->setCheckState(Qt::PartiallyChecked);
// 	
// 	m_d->m_ignoreChange = false;
}

