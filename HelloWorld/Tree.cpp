#include "Tree.h"
#include "Clock.h"


bool Tree::isTreeFullyCutted()
{
	if (ammountOfTrees <= 0)
	{
		return true;
	}
	return false;
}

void Tree::TreeIsCut()
{
	ammountOfTrees += -1;
}
