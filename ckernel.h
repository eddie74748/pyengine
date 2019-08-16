#pragma once
#include <string.h>
#include <string>
#include <unordered_map>
#include <list>
#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include "property_type.h"
#include "class_meta.h"

class CObject;
class CKernel
{
public:
	CKernel() {};
	~CKernel() {};
public:
	//describe class
	bool add_class(const std::string& class_name);
	bool add_property(const std::string& class_name, const std::string& property_name, Property_Type type);
	bool add_event(const std::string& class_name,const std::string& event_name, pybind11::function call_back);
	//create class
	CObject* create_class(const std::string& class_name);
private:
	using class_meta_list = std::unordered_map<std::string, class_meta>;
	class_meta_list _class_meta_list;
};


