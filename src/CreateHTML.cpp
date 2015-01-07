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

#include <iostream>
#include <fstream>  
#include "CreateHTML.h"

CreateHTML::CreateHTML(){}
CreateHTML::~CreateHTML(){}

void CreateHTML::CreateHTMLfile(QString file)
{
	const char* fileChar;
	QByteArray ba = file.toLatin1();
	fileChar = ba.data();
	ofstream outfile (fileChar);
	CreateHTMLbase(fileChar);
}

void CreateHTML::CreateHTMLbase(const char* file)
{
	ofstream myfile;
	myfile.open(file);
	myfile << "<!DOCTYPE html>" << endl;
	myfile << "<html>" << endl;
	myfile << "<head>" << endl;
	myfile << "<title>Page Title</title>" << endl;
	myfile << "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">" << endl;
	myfile << "</head>" << endl;
	myfile << "<body>" << endl;
	myfile << "<p>Denis la pute</p>" << endl;
	myfile << "</body>" << endl;
	myfile << "</html>" << endl;
	myfile.close();
}



