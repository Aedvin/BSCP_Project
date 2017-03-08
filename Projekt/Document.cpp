#include "stdafx.h"

#include "Document.h"

#include <string.h>


Document::Document() 
{
	mHtml = new Tag("html", "", "", "", true);
}

Document::Document(const Document &d) {
	mHtml = new Tag("html");
	*mHtml = *d.mHtml;
}

Document& Document::operator=(const Document &d) {
	if (&d == this) {
		return *this;
	}
	delete mHtml;
	mHtml = new Tag("html");
	*mHtml = *d.mHtml;
}

Tag* Document::htmlTag() {
	return mHtml;
}

Document::~Document()
{
	mHtml->freeChildrens();
	delete mHtml;
}


std::ostream& operator<<(std::ostream& out,const Document &d) {
	string *html = d.mHtml->getHtml();
	out << *html;
	delete html;
	return out;
}