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

#include "Utils.h"
#include "mainView.h"
#include "mainwindow.h"
#include "CreateHTML.h"
#include "GraphCaller.h"
#include <QApplication>
#include <QFile>
#include <QIODevice>
#include <QStyle>
#include <QApplication>
 
using namespace std;

/**
 *  ======= MAIN =========
 * Start the whole application.
 * It is possible to call QApplication.exit(APPLICATION_REBOOT) to restart the application from scratch
 * \param[in] argc number of arguments given to sublimeCode
 * \param[in] argv arguments array with options
 */
int main(int argc, char **argv){

	QApplication app(argc, argv);
	int ret = 0;

	//view loading
	QFile file(":/style.qss");

	if(file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		app.setStyleSheet(file.readAll());
		file.close();
	}

	//starting starting window
	MainWindow w;
	w.show();
	ret = app.exec();

	if(ret == APPLICATION_REBOOT){
		QStringList args = app.arguments();
		args.removeFirst();
		QProcess::startDetached(app.applicationFilePath(), args);
		app.quit();
		ret = 0;
	}
	return ret;
}
