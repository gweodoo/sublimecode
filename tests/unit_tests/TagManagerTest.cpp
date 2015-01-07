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
#include "../../src/TagsManagerImpl.h"
#include <cassert>

using namespace std;

int main(void) {
	TagImpl tag("nameTag", "FileNameTag", 459, TYPE_STRUCT);
	TagImpl tag2("nameTag2", "FileNameTag2", 666, TYPE_FUNCTION);
	TagsManagerImpl tagMan;


	assert(tagMan.isEmpty());

	assert(tagMan.addTag(&tag));
	assert(tagMan.addTag(&tag2));
	tagMan.display();

	assert(! tagMan.isEmpty());
	assert(tagMan.findSpecificTag("nameTag", "FileNameTag", 459) == &tag);
	assert(tagMan.findSpecificTag("nameTag", "FileNameTag", 469) == NULL);
	assert(tagMan.findSpecificTag("nameTag", "ErrorNameTag", 459) == NULL);
	assert(tagMan.findSpecificTag("errorTag", "FileNameTag", 459) == NULL);

	assert(tagMan.delTag(&tag));
	assert(tagMan.delTag(&tag2));

	assert(tagMan.isEmpty());
	return 0;
}
