#include "cobject.h"
#include "class_meta.h"

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

