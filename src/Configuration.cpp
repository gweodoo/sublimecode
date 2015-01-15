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

#include "Configuration.h"
using namespace std;

Configuration::Configuration(){};
Configuration::Configuration(std::string sources, std::string dest) {

	this->sourcesDir=sources;
	this->destDir=dest;
	const short MAX = 1024;
	char buf[MAX];

	memset(buf, '\0', MAX);
	int ret = readlink("/proc/self/exe", buf, MAX);

	if(ret == MAX || ret == -1){
		scError("An error occured !");
	}
	this->scRootPath = string(buf).substr(0, ret - 15);
}

std::string Configuration::getSourcesDir() const
{
	return this->sourcesDir;
}

std::string Configuration::getDestDir() const
{
	return this->destDir;
}

string Configuration::getRootPath() const {
	return this->scRootPath;
}

Configuration::~Configuration() {
}
