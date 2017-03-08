#pragma once
#include <iostream>
#include "Map.h"
#include "Tag.h"
class Document 
{
private:
	Tag* mHtml;
public:
	Document();
	Document(const Document &d);
	Document& operator=(const Document &d);
	Tag* htmlTag();
	friend std::ostream& operator<<(std::ostream &out,const Document &d);
	~Document();
};

