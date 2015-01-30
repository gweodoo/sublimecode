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
#include <qinputdialog.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(NULL)
{
	if(! (checkCommandExistency("ctags", true) && checkCommandExistency("cscope", true) && checkCommandExistency("cloc", true))){
		QMessageBox::critical(this, "Dependency issue", "Some dependencies aren't resolved.\n Check for dependency:\n\t- CTags\n\t- CScope\n\t- Cloc\n\nAdd then to your PATH environment");
		exit(1);
	}
	ui = new UI_MainWindow1();
	ui->setupUi(this);
   
	QObject::connect(ui->getParcourir(), SIGNAL(clicked()), this, SLOT(Rechercher_Sources()));
	QObject::connect(ui->getParcourir1(), SIGNAL(clicked()), this, SLOT(Rechercher_Destination()));
	QObject::connect(ui->getParcourirArchive(), SIGNAL(clicked()), this, SLOT(Rechercher_Archive()));
	QObject::connect(ui->getFinish(), SIGNAL(clicked()), this, SLOT(Finish()));
	
	handlerThread = new HandlerThread;
}

MainWindow::~MainWindow() {}

void MainWindow::Rechercher_Sources()
{
	fileNameSource = QFileDialog::getExistingDirectory(this, tr("Choose a Directory"),"~");
	ui->getLineEdit()->setText(fileNameSource);
}

bool MainWindow::removeDir(QString file)
{
	const char *convert_dest = file.toUtf8().constData();
	std::string str_dest(convert_dest);
	string commandFileRemove_1=string("rm -rf ")+str_dest;
	if(system(commandFileRemove_1.c_str())==-1) {
		perror("closing Error");
		return false;
	}
	else return true;
	
}

void MainWindow::Rechercher_Destination()
{
	QMessageBox::StandardButton reply;
	bool ok;
	fileNameDestination = QFileDialog::getExistingDirectory(this, tr("Choose or Create a Directory"),"~");
	QString fileNameDestinationRoot = fileNameDestination;
	ui->getLineEdit1()->setText(fileNameDestination);

	if(fileNameDestination=="")
		fileNameDestination = "SublimeCode_build";
	else fileNameDestination = fileNameDestination + "/SublimeCode_build";
	if (QDir().exists(fileNameDestination)){
		reply = QMessageBox::question(this, "Existing build folder", "The folder SublimeCode_build already exists. Do you want to delete it?",QMessageBox::Yes|QMessageBox::No);
		if (reply == QMessageBox::Yes)
		{
			removeDir(fileNameDestination);
			QDir().mkdir(fileNameDestination);
		}
		else {
			fileNameDestination = QInputDialog::getText(this, tr("Set the file destination name"), tr("File Name : "), QLineEdit::Normal, "", &ok);
			if(ok && !fileNameDestination.isEmpty()){
				fileNameDestination = fileNameDestinationRoot+"/"+fileNameDestination;
				QDir().mkdir(fileNameDestination);
			}
			else if (ok && fileNameDestination.isEmpty()){
				QMessageBox::warning(this, "Empty field", "Build folder name cannot be empty !");
				ui->getLineEdit1()->setText("");
			}
			else if (!ok){
				ui->getLineEdit1()->setText("");
			}
		}
	}
	else {
		QDir().mkdir(fileNameDestination);
	}
}

void MainWindow::Rechercher_Archive()
{
	fileNameArchive = QFileDialog::getOpenFileName(this, "Please select an Archive file","~", "*.zip *.tar.gz *.tar.bz2");
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
	int currentTab = ui->getQTabWidget()->currentIndex();
	fileNameDestinationTest = ui->getLineEdit1()->text();

	handler = NULL;
	Dialog *dialog = NULL;
	QFileInfo fileInfoSource;
	QFileInfo fileInfoDestination;
	fileInfoDestination = fileNameDestination;
	
	const char *convert_dest = fileInfoDestination.canonicalFilePath().toUtf8().constData();
	if(exists(convert_dest) == false){
		QMessageBox::critical(this, "Build issue", "Unable to find your specified build folder", QMessageBox::Ok);
		return;
	}
	std::string str_dest(convert_dest);

	switch (currentTab){
		case 0 :
		{
			fileNameSourceTest = ui->getLineEdit()->text();

			if(fileNameSourceTest==""){
				QMessageBox::critical(this, "Empty field", "Please provide project sources", QMessageBox::Ok);
				break;
			}

			if(exists(fileNameSource.toUtf8().data()) == true){
				fileInfoSource = fileNameSourceTest;
				const char *convert_source = fileInfoSource.canonicalFilePath().toUtf8().constData();
				std::string str_source(convert_source);
				config = new Configuration(str_source, str_dest);
				dialog = new Dialog(config);
				dialog->show();
				this->hide();
			}
			else QMessageBox::critical(this, "Project issue", "Unable to load sources project\nCheck path you provide", QMessageBox::Ok);
			break;
		}
		case 1 :
		{
			fileNameSourceTest = ui->getLineEditVcs()->text();
			branchNameSource = ui->getLineEditBranch()->text();

			if(fileNameSourceTest==""){
				QMessageBox::critical(this, "Empty field", "Please provide project sources", QMessageBox::Ok);
				break;
			}
			int currentVcs = ui->getComboBoxVcs()->currentIndex();
			fileInfoSource = fileNameSourceTest;
			const char *convert_source = fileInfoSource.canonicalFilePath().toUtf8().constData();
			std::string str_source(convert_source);
			config = new Configuration(str_source, str_dest);
			switch (currentVcs){
				case 0 :
					handler = new CvsVcsHandler(config,fileNameSourceTest.toStdString(), branchNameSource.toStdString());
					break;
				case 1 :
					handler = new GitVcsHandler(config, fileNameSourceTest.toStdString(), branchNameSource.toStdString());
					break;
				case 2 :
					handler = new MercurialVcsHandler(config, fileNameSourceTest.toStdString(), branchNameSource.toStdString());
					break;
				case 3 :
					handler = new SvnVcsHandler(config, fileNameSourceTest.toStdString(), branchNameSource.toStdString());
					break;
			}
			
			handlerThread = new HandlerThread;
			handlerThread->setHandler(handler);
			QObject::connect(handlerThread, SIGNAL(handlerChanged(bool)), this, SLOT(onHandlerChanged(bool)));
			waitingStart();
			handlerThread->start();
			break;
		}
		case 2 :
		{
			fileNameSourceTest = ui->getLineEditArchive()->text();

			if(fileNameSourceTest==""){
				QMessageBox::critical(this, "Empty field", "Please provide project sources", QMessageBox::Ok);
				break;
			}
			int currentArchive = ui->getComboBoxArchive()->currentIndex();
			fileInfoSource = fileNameSourceTest;
			const char *convert_source = fileInfoSource.canonicalFilePath().toUtf8().constData();
			std::string str_source(convert_source);
			config = new Configuration(str_source, str_dest);
			cout << str_source << endl;
			switch(currentArchive){
				case 0 :
					handler = new Tarbz2TarballHandler(config, str_source);
					break;
				case 1 :
					handler = new TargzTarballHandler(config, str_source);
					break;
				case 2 :
					handler = new ZipTarballHandler(config, str_source);
					break;
			}
			
			handlerThread->setHandler(handler);
			QObject::connect(handlerThread, SIGNAL(handlerChanged(bool)), this, SLOT(onHandlerChanged(bool)));
			waitingStart();
			handlerThread->start();
			break;
		}
		default: break;
	}
}

void MainWindow::closeEvent(QCloseEvent* e){
	handlerThread->quit();
	delete handler;
	delete handlerThread;
	delete ui;
	QMainWindow::closeEvent(e);
}

void MainWindow::onHandlerChanged(bool isDone)
{
	Dialog *dialog = NULL;
	
	waitingStop();
	
	if(isDone) {
		config->setSourceDir(config->getDestDir()+"/sources_project");
		dialog = new Dialog(config);
		dialog->show();
		this->hide();
	} else {
		QMessageBox::critical(this, "Project issue", "Unable to load sources project\nCheck path you provide", QMessageBox::Ok);
	}
}

void MainWindow::waitingStart()
{
	ui->getCentralWidget()->setEnabled(false);
	ui->getWaitingMovie()->start();
	ui->getWaitingLabel()->setVisible(true);
}

void MainWindow::waitingStop()
{
	ui->getCentralWidget()->setEnabled(true);
	ui->getWaitingMovie()->stop();
	ui->getWaitingLabel()->setVisible(false);
}
