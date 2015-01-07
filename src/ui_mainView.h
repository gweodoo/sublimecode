#ifndef UI_MAINVIEW_H
#define UI_MAINVIEW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGroupBox>
#include <QHeaderView>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QWidget>
#include <QWebView>
#include <QtGui/QDesktopWidget>

QT_BEGIN_NAMESPACE

class Ui_MainView
{
public:
	void setupUi(QMainWindow *MainView);
	void retranslateUi(QMainWindow *MainView);
	QWidget *getCentralWidget();
	QWebView *getWebView();
	QPushButton * getPushButton();
	QLineEdit * getLineEdit();
    
private:
	QWidget *centralWidget;
	QWidget *leftWidget;
	QGroupBox *tagGroupBox;
	QPushButton *pushButton;
	QLineEdit *lineEdit;
	QGroupBox *otherGroupBox;
	QPushButton *callGraphButton;
	QGroupBox *StatsGroupBox;
	QPushButton *stats1Button;
	QPushButton *stats2Button;
	QPushButton *stats3Button;
	QWidget *rightWidget;
	QMenuBar *menuBar;
	QMenu *menuFile;
	QMenu *menuEdit;
	QMenu *menuView;
	QWebView *webView;
};

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H

