#include "stdafx.h"
#include "Tag.h"

void Tag::init(char *name, char *id, char *className, char *text, bool pair) {
	mName = string(name);
	mId = string(id);
	mClass = string(className);
	mText = string(text);
	mPair = pair;
	mChildrenIds = 0;
	mChildrens = new Map<string, Tag*>();
	mAttributes = new Map<string, string>();
}

string* Tag::assembleAttribute(string& name, string& value) {
	string* str = new string(" ");
	str->append(name);
	str->append("=\"");
	str->append(value);
	str->append("\"");
	return str;
}

bool Tag::freeChildrens() {
	Iterator<Tag*> it = mChildrens->getAll();
	it.begin();
	if (it.length() > 0) {
		while (it.hasNext()) {
			Tag* next = *it.next();
			if (next->freeChildrens()) {
				delete next;
			}
			else {
				throw std::exception("Memory free error");
			}
		}
	}
	return true;
}


Tag::Tag(char *name) {
	init(name, "", "", "", false);
}

Tag::Tag(char *name, char *id) {
	init(name, id, "", "", false);
}

Tag::Tag(char *name, char *id, char *className) {
	init(name, id, className, "", false);
}

Tag::Tag(char *name, char *id, char *className, char *text) {
	init(name, id, className, text, false);
}

Tag::Tag(char *name, char *id, char *className, char *text, bool pair) {
	init(name, id, className, text, pair);
}

Tag::Tag(const Tag &t) {
	mName = t.mName;
	mId = t.mId;
	mClass = t.mClass;
	mText = t.mText;
	mChildrenIds = t.mChildrenIds;
	mPair = t.mPair;
	mAttributes = new Map<string, string>();
	mChildrens = new Map<string, Tag*>();
	Iterator<string> childrenIds = t.mChildrens->getAllKeys();
	Iterator<Tag*> childrens = t.mChildrens->getAll();
	if (childrenIds.length() == childrens.length()) {
		childrenIds.begin();
		childrens.begin();
		while (childrenIds.hasNext() && childrens.hasNext()) {
			mChildrens->put(*childrenIds.next(), *childrens.next());
		}
	}

	Iterator<string> attrName = t.mAttributes->getAllKeys();
	Iterator<string> attrValue = t.mAttributes->getAll();
	if (attrName.length() == attrValue.length()) {
		attrName.begin();
		attrValue.begin();
		while (attrName.hasNext() && attrValue.hasNext()) {
			mAttributes->put(*attrName.next(), *attrValue.next());
		}
	}
}

string Tag::getName() {
	return string(mName);
}

string Tag::getId() {
	return string(mId);
}

string Tag::getClass() {
	return string(mClass);
}

string Tag::getAttribute(char *name) {
	Iterator<string> it = mAttributes->getAll();
	if (it.length() > 0) {
		it.begin();
		return *it.next();
	}
}

string Tag::getText() {
	return string(mText);
}

bool Tag::isPair() {
	return mPair;
}

Tag* Tag::getChildren(char* name) {
	if (mPair) {
		Iterator<Tag*> it = mChildrens->get(string(name));
		if (it.length() > 0) {
			it.begin();
			return *it.next();
		}
		else {
			throw std::exception("No children found");
		}
	}
	else {
		throw std::exception("Cannot add children to non-pair tag");
	}
}

void Tag::setId(char *id) {
	mId = string(id);
}

void Tag::setClass(char *className) {
	mClass = string(className);
}

void Tag::setText(char* text) {
	mText = string(text);
}

void Tag::setPair(bool pair) {
	mPair = pair;
}

void Tag::setAttribute(char *name, char *value) {
	Iterator<string> it = mAttributes->get(string(name));
	if (it.length() > 0) {
		it.begin();
		*it.next() = string(value);
	}
	else {
		mAttributes->put(string(name), string(value));
	}
}

void Tag::addChildren(Tag* children) {
	if (mPair) {
		mChildrens->put(children->getName(), children);
	}
	else {
		throw std::exception("Cannot add children to non-pair tag");
	}
}

void Tag::removeAttribute(char *name) {
	mAttributes->remove(string(name));
}

Tag* Tag::operator[](char *name) {
	Iterator<Tag*> it = mChildrens->get(string(name));
	if (it.length() > 0) {
		it.begin();
		return *it.next();
	}
	throw std::exception("Cannot found children with given index");
}

Tag& Tag::operator=(const Tag &t) {
	if (&t == this) {
		return *this;
	}
	mName = t.mName;
	mId = t.mId;
	mClass = t.mClass;
	mText = t.mText;
	mChildrenIds = t.mChildrenIds;
	mPair = t.mPair;

	freeChildrens();
	delete mAttributes;
	delete mChildrens;

	mAttributes = new Map<string, string>();
	mChildrens = new Map<string, Tag*>();

	Iterator<string> childrenIds = t.mChildrens->getAllKeys();
	Iterator<Tag*> childrens = t.mChildrens->getAll();
	if (childrenIds.length() == childrens.length()) {
		childrenIds.begin();
		childrens.begin();
		while (childrenIds.hasNext() && childrens.hasNext()) {
			mChildrens->put(*childrenIds.next(), *childrens.next());
		}
	}

	Iterator<string> attrName = t.mAttributes->getAllKeys();
	Iterator<string> attrValue = t.mAttributes->getAll();
	if (attrName.length() == attrValue.length()) {
		attrName.begin();
		attrValue.begin();
		while (attrName.hasNext() && attrValue.hasNext()) {
			mAttributes->put(*attrName.next(), *attrValue.next());
		}
	}

	return *this;
}

string* Tag::getHtml() {
	string* str = new string("");
	str->append("<");
	str->append(mName);
	if (mId.compare("") != 0) {
		string* buffer = assembleAttribute(string("id"), mId);
		str->append(*buffer);
		delete buffer;
	}
	if (mClass.compare("") != 0) {
		string* buffer = assembleAttribute(string("class"), mClass);
		str->append(*buffer);
		delete buffer;
	}

	Iterator<string> iAttr = mAttributes->getAll();
	Iterator<string> iAttrName = mAttributes->getAllKeys();
	if (iAttr.length() == iAttrName.length()) {
		iAttr.begin();
		iAttrName.begin();
		while (iAttr.hasNext() && iAttrName.hasNext()) {
			string* buffer = assembleAttribute(*iAttrName.next(), *iAttr.next());
			str->append(*buffer);
			delete buffer;
		}
	}

	str->append(">");
	if (mText.compare("") != 0 && mPair) {
		str->append(mText);
	}
	Iterator<Tag*> it = mChildrens->getAll();
	it.begin();
	if (it.length() > 0) {
		while (it.hasNext()) {
			string* buffer = (*it.next())->getHtml();
			str->append(*buffer);
			delete buffer;
		}
	}
	if (mPair) {
		str->append("</");
		str->append(mName);
		str->append(">");
	}
	return str;
}


Tag::~Tag() {
	delete mChildrens;
	delete mAttributes;
}