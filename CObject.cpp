#include "CObject.h"


Property_Value init_type_value(Property_Type type)
{
	Property_Value value;
	switch (type)
	{
	case PROPERTY_INT:
		value._value = (int)0;
		break;
	case PROPERTY_FLOAT:
		value._value = (float)0.0;
	default:
		break;
	}
	return value;
}

CObject::~CObject()
{
}
// 
// bool CObject::set_property_value(const std::string& property_name, int value)
// {
// 	auto it = _class_meta._property_list.find(property_name);
// 	if (it == _class_meta._property_list.end())
// 	{
// 		return false;
// 	}
// 	if (it->second._type != PROPERTY_INT)
// 	{
// 		return false;
// 	}
// 	int index = it->second._index;
// 	int old_value = _property[index]._value;
// 	_property[index]._value = value;
// 	//trigger event
// 	std::string event_name("on_");
// 	event_name += property_name;
// 	event_name += "_changed";
// 	auto ev_it = _class_meta._event_list.find(event_name);
// 	if (ev_it != _class_meta._event_list.end())
// 	{
// 		for (auto& elment : ev_it->second)
// 		{
// 			elment(this, old_value, value);
// 		}
// 	}
// 
// 	return true;
// }

pybind11::object* CObject::get_property_value(const std::string& property_name)
{
	auto it = _class_meta._property_list.find(property_name);
	if (it == _class_meta._property_list.end())
	{
		throw std::runtime_error("invalidate property!");
		return false;
	}
	pybind11::object* py_obj = nullptr;
	{
		Property_Type type = it->second._type;
		int index = it->second._index;
		switch (type)
		{
		case PROPERTY_INT:
			py_obj = new pybind11::int_((int)_property[index]._value);
			break;
		case PROPERTY_FLOAT:
			py_obj = new pybind11::float_((float)_property[index]._value);
			break;
		default:
			break;
		}
	}
	return py_obj;
}

void CObject::init_property()
{
	if (_class_meta._proerty_count > 0)
	{
		_property.resize(_class_meta._proerty_count);
		for (auto& elment: _class_meta._property_list)
		{
			 _property[elment.second._index] = init_type_value(elment.second._type);
		}
	}
}

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
