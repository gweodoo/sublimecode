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

#include "mainwindow.h"
#include "dialog.h"
#include "Utils.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
	
    ui = new UI_MainWindow1();
    ui->setupUi(this);

//     QPixmap bkgnd("../../resources/Black-lava-twitter-background.png");
//     bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
//     QPalette palette;
//     palette.setBrush(QPalette::Background, bkgnd);
//     this->setPalette(palette);
        
    QObject::connect(ui->getParcourir(), SIGNAL(clicked()), this, SLOT(Rechercher_Sources()));
    QObject::connect(ui->getParcourir1(), SIGNAL(clicked()), this, SLOT(Rechercher_Destination()));
    QObject::connect(ui->getParcourirArchive(), SIGNAL(clicked()), this, SLOT(Rechercher_Destination()));
    QObject::connect(ui->getFinish(), SIGNAL(clicked()), this, SLOT(Finish()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Rechercher_Sources()
{
	fileNameSource = QFileDialog::getExistingDirectory(this, tr("Choose a Directory"),"/home");
	ui->getLineEdit()->setText(fileNameSource);
}

void MainWindow::Rechercher_Destination()
{
	fileNameDestination = QFileDialog::getExistingDirectory(this, tr("Choose or Create a Directory"),"/home");
	ui->getLineEdit1()->setText(fileNameDestination);	
}

void MainWindow::Rechercher_Archive()
{
	fileNameArchive = QFileDialog::getExistingDirectory(this, tr("Choose or Create a Directory"),"/home");
	ui->getLineEditArchive()->setText(fileNameArchive);	
}

bool MainWindow::exists(const char *fname)
{
    if( access( fname, F_OK ) != -1 ) {
    // file exists
	    return true;
    } else {
    // file doesn't exist
	    return false;
    }
}


void MainWindow::Finish()
{
	fileNameSourceTest = ui->getLineEdit()->text();
	fileNameDestinationTest = ui->getLineEdit1()->text();
	if(fileNameDestination=="")
		fileNameDestination = "Sources";
	else fileNameDestination = fileNameDestination + "/Sources";
	if (QDir().exists(fileNameDestination)){
		QDir().remove(fileNameDestination);
	}
	QDir().mkdir(fileNameDestination);
	
	QMessageBox qmb;
	QMessageBox qmb2;
	if(fileNameSourceTest==""){
		qmb.setText("Remplir les sources du projet");
		qmb.exec();
	}
	else {
 		if(exists(fileNameSource.toLatin1().data()) == true)
 		{
// 		if(fileNameDestinationTest==""){
// 			fileNameDestination=fileNameDestination+"/home.html";
// 		}
// 		else fileNameDestination=fileNameDestination+"/home.html";
// 		CreateHTML *c = new CreateHTML();
// 		c->CreateHTMLfile(fileNameDestination);
// 	        if(fileNameDestinationTest==""){
// 			fileNameDestinationTest="Sources/style.css";
// 		}
// 		else fileNameDestinationTest=fileNameDestinationTest+"/Sources/style.css";
// 		if (QFile::exists(fileNameDestinationTest))
// 		{
// 			QFile::remove(fileNameDestinationTest);
// 		}
// 		QFile::copy("../../src/style.css", fileNameDestinationTest);
		config = new Configuration(fileNameSourceTest.toStdString(), fileNameDestination.toStdString());
		Dialog *w = new Dialog(config);
		w->show();
		this->hide();
		}
		else {
			qmb2.setText("Le fichier source n'existe pas");
			qmb2.exec();
		}
	}
}


