#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include "ui_mainView.h"
#include <QString>

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QString file, QWidget *parent = 0);
    ~MainView();

private:
	Ui_MainView ui;
};

#endif // MAINVIEW_H
