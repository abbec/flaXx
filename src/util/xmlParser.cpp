#include "util/xmlParser.h"
#include "xml/rapidxml.hpp"

#include <fstream>

using namespace flaXx;

bool XMLParser::parse()
{
	using namespace rapidxml;

	std::ifstream f(filename.c_str());
	std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); 

	xml_document<> doc;    // character type defaults to char
	doc.parse<0>(const_cast<char*>(str.c_str()));    // 0 means default parse flags

	// Pointer to the scene (root) node
	xml_node<> *sceneNode = doc.first_node();

	// The camera
	xml_node<> *cameraNode = sceneNode->first_node("camera\0");
	
	if (cameraNode)
	{
		for (xml_attribute<> *attr = cameraNode->first_attribute(); attr; attr = attr->next_attribute())
		{
			std::cout << "Node camera has attribute " << attr->name() << " ";
			std::cout << "with value " << attr->value() << "\n";
		}
	}
	else
	{
		// Camera defaults
		camera = std::tr1::shared_ptr<Camera>(new Camera(Vector3f(0.0), Vector3f(0.0, 0.0, 1.0), 1.0));
	}

	// The light(s)
	// Check if a light exists
	if (sceneNode->first_node("light\0"))
	{
		// Add the lights to the vector
	}
	else
	{
		// Create a default light
	}

	
	// Check if an object exists
	if (sceneNode->first_node("object\0"))
	{
		//Loop through all object nodes and create objects

	}








	// Clean up the XML tree
	doc.clear();
}

