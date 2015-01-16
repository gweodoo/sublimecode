/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef CREATEJSON_H
#define CREATEJSON_H

#include <vector>
#include <QDebug>
#include <QVariant>
#include <QFile>
#include "Tag.h"
#include "Graph.h"

class CreateJson {
	
public:
	explicit CreateJson();
	~CreateJson();
	void TransformToJson(Tag * tag);
	void buildItem(std::vector<Tag*> * tagVector, QTextStream * out, Graph * myGraph, int nbIterator);
	void buildItem(Tag* tag, QTextStream * out, Graph * myGraph, int nbIterator);
};

#endif // CREATEJSON_H
