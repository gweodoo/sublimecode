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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include "CreateHTML.h"
#include "mainView.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "UI_mainwindow1.h"

//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QMainWindow//, public QObject
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    UI_MainWindow1 *ui;
    
private:
    //Ui::MainWindow *ui;
    QString fileNameSource;
    QString fileNameSourceTest;
    QString fileNameDestination;
    QString fileNameDestinationTest;
    Configuration *config;
    
public slots:
     void Rechercher_Sources();
     void Rechercher_Destination();
     void Finish();
     bool exists(const char *fname);
};

#endif // MAINWINDOW_H