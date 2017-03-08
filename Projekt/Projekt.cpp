// Projekt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>

#include <stdio.h>
#include <iostream>
#include <fstream>

#include "Document.h"


int main()
{
	Document doc = Document();
	Tag* html = doc.htmlTag();
	html->addChildren(new Tag("head", "", "","",true));
	html->getChildren("head")->addChildren(new Tag("title", "", "", "Zaverecna prace c++", true));
	html->addChildren(new Tag("body","","","",true));
	Tag* img = new Tag("img");
	img->setAttribute("src", "img/Koala.jpg");
	img->setAttribute("style", "width:300px;height:300px");
	html->getChildren("body")->addChildren(img);
	std::ofstream file;
	file.open("test.html", std::ofstream::out);
	file << doc;
	file.close();
	std::cout << doc;
    return 0;
}

