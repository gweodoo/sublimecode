/***************************************************************************/
/*                                                                         */
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

#ifndef UI_MAINWINDOW1_H
#define UI_MAINWINDOW1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QDesktopWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QComboBox>

QT_BEGIN_NAMESPACE

class UI_MainWindow1
{
private: 
    QWidget *centralWidget;
    QWidget *directoryWidget;
    QWidget *vcsWidget;
    QWidget *archiveWidget;
    QGroupBox *sourcesGroupBox;
    QGroupBox *destinationGroupBox;
    QTabWidget *tabs;
    QPushButton *Parcourir;
    QPushButton *Parcourir1;
    QPushButton *parcourirArchive;
    QPushButton *Finish;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit1;
    QLineEdit *lineEditVcs;
    QLineEdit *lineEditArchive;
    QLineEdit * lineEditBranch;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QLabel *labelBranch;
    QLabel *labelParcourir;
    QLabel *labelParcourir1;
    int width, height;
    int screenWidth, screenHeight;
    int x, y;
    QRect rect;
    QComboBox *comboBoxVcs;
    QComboBox *comboBoxArchive;

public:
    static const char * const vcsTypes[];
    static const char * const archiveTypes[];
    explicit UI_MainWindow1();
    ~UI_MainWindow1();
    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);
    QLineEdit *getLineEdit();
    QLineEdit *getLineEdit1();
    QLineEdit *getLineEditArchive();
    QPushButton *getParcourir();
    QPushButton *getParcourir1();
    QPushButton *getParcourirArchive();
    QPushButton *getFinish();
};

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
