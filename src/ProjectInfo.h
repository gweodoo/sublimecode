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

#ifndef FILESYSTEMPARSER_H
#define FILESYSTEMPARSER_H

#include "Utils.h"
#include "Configuration.h"

class ProjectInfo
{
private:
	Configuration *config;
	std::vector<std::string> filesTree;
	std::map<std::string ,std::string> mapProjectInfo;
public:
	ProjectInfo(Configuration *config);
	void addFilesList(std::vector<std::string> filesList);
	void analyzeSourcesTree();

};

#endif // FILESYSTEMPARSER_H
