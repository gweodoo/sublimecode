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

#include "../../src/TagImpl.h"
#include <cassert>

using namespace std;

int main(void) {
	TagImpl tag("nameTag", "FileNameTag", 459, TYPE_STRUCT);

	tag.display();file:///home/adamj/Documents/cours/S9/PFE/SublimeCode/tests/unit_tests/TagTest.cpp
	assert(tag.getFileName() == "FileNameTag");
	assert(tag.getName() == "nameTag");
	assert(tag.getLineNumber() == 459);
	assert(tag.getType() == TYPE_STRUCT);

	tag.addInfoByKey("key", "value");
	assert(tag.getInfoByKey("key") == "value");

	return 0;
}
