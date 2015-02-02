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
#include "UI_mainwindow.h"
#include "handler/CvsVcsHandler.h"
#include "handler/GitVcsHandler.h"
#include "handler/MercurialVcsHandler.h"
#include "handler/SvnVcsHandler.h"
#include "handler/Tarbz2TarballHandler.h"
#include "handler/TargzTarballHandler.h"
#include "handler/ZipTarballHandler.h"
#include "handler/HandlerThread.h"

/**
 * MainWindow is first window opened to the user.
 *
 * On this window, user can select sources path where project is located, and define
 * where sublimeCode output files will be stored. This window also
 * allows many VSC to download projects
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	/**
	 * default constructor
	 * \param[in] parent upstream accessor
	 */
	explicit MainWindow(QWidget *parent = 0);
	/// default destructor
	~MainWindow();
	///start the spinner during long work
	void waitingStart();
	///stop the spinner after a long work
	void waitingStop();
private:
	UI_MainWindow1 *ui;             ///< GUI object
	QString fileNameSource;         ///< source path
	QString branchNameSource;       ///< source branch (in case of VCS using)
	QString fileNameDestination;    ///< build path
	QString fileNameArchive;        ///< archive path
	Configuration *config;          ///< current global configuration
	Handler* handler;               ///< handler on sources project
	HandlerThread *handlerThread;   ///< thread on handler (to display spinner)
    
public slots:
	///start sources loading from file system
	void findSources();
	///start build path checking
	void findDestination();
	///start tarball checking and decompression
	void findArchive();
	///action on "Next" button
	void Finish();
	/**
	 * check if a specific file exists on file system, from its name as a string
	 * \param[in] fname the file path to test
	 * \return True if file exists
	 * \return False otherwise
	 */
	bool exists(const char *fname);
	/**
	 * delete directory on the disk. Used to remove old "SublimeCode_build" on disk
	 * \param[in] file the directory path to delete
	 * \return True if succeded
	 * \return false otherwise
	 */
	bool removeDir(QString file);
	/**
	 * event when window is closed
	 * \param[in] e the event
	 */
	void closeEvent(QCloseEvent* e);
	/**
	 * state function, called when handler have done. Do some post-stuff after
	 * handler downloaded the project.
	 * \param[in] isDone True if handler have done when function is called
	 */
	void onHandlerChanged(bool isDone); 
};

#endif // MAINWINDOW_H
