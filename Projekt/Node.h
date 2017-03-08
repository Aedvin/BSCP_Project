#pragma once
#include "Tag.h"
#include "Map.h"

class Node {
private:
	Node *mParent;
	Map<char *,Node> *mChildrens;
	Tag *mTag;
public:

};