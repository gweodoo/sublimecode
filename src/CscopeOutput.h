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
#ifndef CSCOPEOUTPUT_H
#define CSCOPEOUTPUT_H

#include"Utils.h"

/**
 * Represents a Line output given by cscope;
 * 
 */

class CscopeOutput
{
public:
	CscopeOutput(std::string fileName,std::string tagName,std::string signature,int line );
	CscopeOutput();
	~CscopeOutput();
	/**
	* classical getter for fileName-tagName-Line-Signature
	*/
	std::string getFileName();
	std::string getTagName();
	std::string getSignature();
	int getLine();
	/**
	* classical setter for fileName-tagName-Line-Signature
	*/
	void setFileName(std::string fileName);
	void setTagName(std::string tagName);
	void setSignature(std::string signature);
	void setLine(int line);

private:
	/**
	 * Needs 4 attributes Cscope always giving as output fileName-tagName-Line-Signature
	 */
	std::string fileName;
	std::string tagName;
	std::string signature;
	int line;

};

#endif // CSCOPEOUTPUT_H
