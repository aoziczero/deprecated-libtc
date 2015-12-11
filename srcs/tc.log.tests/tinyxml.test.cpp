#include "stdafx.h"
#include <tinyxml2/tinyxml2.h>

TEST( tinyxml2 , create ) {
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode* root = doc.NewElement("Root");
	doc.InsertFirstChild(root);
	tinyxml2::XMLElement* pe = doc.NewElement( "IntVal");
	pe->SetText(10);
	pe->SetAttribute("day" , 10);
	root->InsertEndChild(pe);
//	doc.SaveFile( "./SavedData.xml" );

}
