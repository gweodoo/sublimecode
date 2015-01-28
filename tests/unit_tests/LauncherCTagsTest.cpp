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

#include "../../src/tags/LauncherCTags.h"
#include <cassert>

using namespace std;

int main(void) {
	Configuration config("..", ".");
	vector<string> list; list.push_back("my/super/path");
	LauncherCTags launcher(&config, list);
	assert(launcher.constructCommand() == "ctags  -Rn --c-kinds=+cdefgmnstuvx -f ./tags my/super/path ");
	assert(launcher.generateTagsFile());

	return 0;
}
