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
#ifndef TAGSPARSERIMPL_H
#define TAGSPARSERIMPL_H

#include "TagsParser.h"
#include "TagImpl.h"
#include "TagsManagerImpl.h"

class TagsParserImpl :  public TagsParser
{
private:
	TagsManagerImpl* myTagMan;
public:
	TagsParserImpl(TagsManagerImpl* man);
	virtual void loadFromFile ( std::string inputFile );
	virtual tagType identifyTypeFromFile(std::string type);
};

#endif // TAGSPARSERIMPL_H
