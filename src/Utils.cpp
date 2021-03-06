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
using namespace std;

bool checkCommandExistency(std::string command, bool required){
	std::string starter = "which "+command+" > /dev/null 2>&1";
	int ret = system(starter.c_str());
	if(WEXITSTATUS(ret) != 0) {
		if(required){
			scWarning("Command " << command << " wasn't found and is required");
		} else {
			scWarning("Command " << command << " wasn't found");
		}
		return false;
	}
	return true;
}

map< string, int > splitOn ( string chain, char split ) {
	stringstream flux(chain);
	map<string, int> splitLine;
	string cur;
	int i = 0;
	while(getline(flux, cur, split)){
		splitLine[cur] = i++;
	}
	return splitLine;
}
