#pragma once
#include "stdafx.h"

#include "Map.h"

class Tag {
protected:
	string mName;
	string mId;
	string mClass;
	string mText;
	uint32_t mChildrenIds;
	bool mPair;
	Map<string, string>* mAttributes;
	Map<string, Tag*>* mChildrens;
	void init(char *name, char *id, char *className,char *text,bool pair);
	string* assembleAttribute(string& name, string& value);
	
public:
	Tag(char *name);
	Tag(char *name, char *id);
	Tag(char *name, char *id, char *className);
	Tag(char *name, char *id, char *className, char *text);
	Tag(char *name, char *id, char *className, char *text, bool pair);
	Tag(const Tag &t);
	string getName();
	string getId();
	string getText();
	string getClass();
	string getAttribute(char *name);
	bool isPair();
	Tag* getChildren(char* name);
	void setId(char *id);
	void setClass(char *className);
	void setText(char* text);
	void setPair(bool pair);
	void setAttribute(char *name, char *value);
	void addChildren(Tag* children);
	void removeAttribute(char *name);
	bool freeChildrens();
	Tag* operator[](char* name);
	Tag& operator=(const Tag &t);
	string* getHtml();
	~Tag();
};

