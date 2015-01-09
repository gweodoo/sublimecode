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

#include "TagsManagerImpl.h"
#include "TagImpl.h"
#include "TagsParserImpl.h"
#include "LauncherCscope.h"
#include "LauncherCTags.h"


using namespace std;

int main(int argc, char **argv){

	Configuration config("..", ".");
	LauncherCTags launcher(&config);
	TagsManagerImpl manager(&config);
	TagsParserImpl parser(&manager);

	launcher.addPathToAnalyze("/home/adamj/Téléchargements/vlc-2.1.5");
	launcher.generateTagsFile();
	parser.loadFromFile("./tags");
	manager.findSpecificTag("OMX_MARKTYPE", "/home/adamj/Téléchargements/vlc-2.1.5/modules/codec/omxil/OMX_Types.h", 297)->display();
}
