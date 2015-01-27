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

#include "TagsManagerImpl.h"
#include "TagImpl.h"
#include "TagsParserImpl.h"
#include "LauncherCscope.h"
#include "LauncherCTags.h"

#include <QApplication>

#include "TagsManagerImpl.h"
#include "TagImpl.h"
#include "TagsParserImpl.h"
#include "LauncherCscope.h"
#include "LauncherCTags.h"

#include "Graph.h"
#include "GraphCaller.h"
 
using namespace std;

int main(int argc, char **argv){

	QPointer<QApplication> app;
	int ret = 0;
	do{
		if(app) delete app;
		app = new QApplication(argc, argv);

		//Affichage vue
		QFile file(":/style.qss");

		if(file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			app->setStyleSheet(file.readAll());
			file.close();
		}

		MainWindow w;
		w.show();
		ret = app->exec();
	}while(ret == APPLICATION_REBOOT);

	return ret;
}
