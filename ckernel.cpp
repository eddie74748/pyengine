#include "ckernel.h"
#include "cobject.h"
#include "class_meta.h"
bool CKernel::add_class(const std::string & class_name)
{
	if (_class_meta_list.find(class_name) != _class_meta_list.end())
	{
		return false;
	}
	_class_meta_list[class_name]._class_name = class_name;
	return true;
}

bool CKernel::add_property(const std::string& class_name, const std::string& property_name, Property_Type type)
{
	auto it = _class_meta_list.find(class_name);
	if (it == _class_meta_list.end())
	{
		//class not exists
		return false;
	}
	class_meta& meta = it->second;
	if (meta._property_list.find(property_name) != meta._property_list.end())
	{
		//property exists.
		return false;
	}
	Property p;
	p._name = property_name;
	p._type = type;
	p._index = meta._proerty_count;
	meta._property_list[property_name] = p;
	++meta._proerty_count;
	return true;
}

bool CKernel::add_event(const std::string& class_name, const std::string& event_name, pybind11::function call_back)
{
	auto it = _class_meta_list.find(class_name);
	if (it == _class_meta_list.end())
	{
		//class not exists
		return false;
	}
	class_meta& meta = it->second;
	class_meta::event_list& event_list = meta._event_list;
	event_list[event_name].push_back(call_back);
	return true;
}

CObject* CKernel::create_class(const std::string& class_name)
{
	auto it = _class_meta_list.find(class_name);
	if (it == _class_meta_list.end())
	{
		//class not exists
		return nullptr;
	}
	return new CObject(it->second);
}
