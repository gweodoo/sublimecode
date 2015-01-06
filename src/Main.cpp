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
#include "mainwindow.h"
#include <QApplication>
#include "TagsManagerImpl.h"
#include "TagImpl.h"
#include "TagsParserImpl.h"

using namespace std;

int main(int argc, char **argv){
	TagImpl tag1("tag1", "tag.c", 1034, TYPE_FUNCTION);
	TagImpl tag2("tag2", "tag.c", 66, TYPE_MEMBER);

	TagsManagerImpl tagMan;

/**	tagMan.addTag(&tag1);
	tagMan.addTag(&tag2);
	tag1.addInfoByKey(FIELD_CLASS, "mySuperClass");
	cout << "TAG = " << tag1.getInfoByKey(FIELD_CLASS);
	tagMan.display();
	cout << "You pla " << endl;
	tagMan.delTag(&tag1);
**/
	TagsParserImpl tagParse(&tagMan);
	tagParse.loadFromFile("/home/adamj/Téléchargements/vlc-2.1.5/tags");
	//tagMan.display();
	tagMan.findSpecificTag("OMX_MARKTYPE", "modules/codec/omxil/OMX_Types.h", 297)->display();
}
