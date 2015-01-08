#ifndef TAGIDENTIFIER_H
#define TAGIDENTIFIER_H

#include "Tag.h"
#include "TagsManager.h"
class TagIdentifier
{
public:
~TagIdentifier();

private:
	std::vector<Tag*>* getTagFunctionWithName(std::string);
	void addToTagFunctionNumberOfArgument(Tag * tagToUpdate,int numberOfArgument);
	void addToTafgunctionTypeOfArgument(Tag* tagToUpdate,std::vector<std::string>* listOfArgumentType);
};

#endif // TAGIDENTIFIER_H
