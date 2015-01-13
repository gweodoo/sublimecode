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
#include <QApplication>
#include <QFile>
#include <QIODevice>
#include <QStyle>
#include "TagsManagerImpl.h"
#include "TagImpl.h"
#include "TagsParserImpl.h"
#include "LauncherCscope.h"
#include "LauncherCTags.h"
#include "dialog.h"

using namespace std;

int main(int argc, char **argv){

	QApplication a(argc, argv);
	
	//Affichage vue
	QFile file(":/style.qss");
	
	if(file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		a.setStyleSheet(file.readAll());
		file.close();
	}
	
	//QString file2("/home/alexandre/Documents/SublimeCode");
	//QString file3(".");
	
	//Configuration *c = new Configuration(file2.toStdString(),file3.toStdString());
	
	//Dialog *w = new Dialog (c);
	MainWindow w;
	w.show();
	
	return a.exec();
}
