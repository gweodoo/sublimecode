#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include "ui_mainView.h"
#include <QString>

class MainView : public QMainWindow
{
    Q_OBJECT

public:
	explicit MainView();
	explicit MainView(QString file);
	//explicit MainView(QString file, QWidget *parent = 0);
	~MainView();
	
public slots:
	void handlePushButton();

private:
	Ui_MainView * ui;
};

#endif // MAINVIEW_H
