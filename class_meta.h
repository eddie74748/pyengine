#pragma once
#include <string.h>
#include <string>
#include "property_type.h"

struct Property 
{
	std::string _name;
	Property_Type _type;
	int _index=0;
};

struct class_meta
{
	using property_list = std::unordered_map<std::string, Property>;
	using event_list = std::unordered_map<std::string, std::list<pybind11::function>>;
	std::string _class_name;
	property_list _property_list;
	event_list _event_list;
	int _proerty_count = 0;
};


