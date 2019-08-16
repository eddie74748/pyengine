#pragma once
#include <string.h>
#include <string>
#include <unordered_map>
#include <list>
#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <vector>
#include "property_type.h"
#include "property_value.h"
struct class_meta;
class CObject
{
public:
	CObject(const class_meta& meta):_class_meta(meta)
	{
		init_property();
	}
	~CObject();
	template<typename SupportType>
	bool set_property_value(const std::string& property_name, SupportType value)
	{
		auto it = _class_meta._property_list.find(property_name);
		if (it == _class_meta._property_list.end())
		{
			return false;
		}
		if (it->second._type != SupportTypeResult<SupportType>::result)
		{
			return false;
		}
		int index = it->second._index;
		SupportType old_value = _property[index]._value;
		_property[index]._value = value;
		//trigger event
		std::string event_name("on_");
		event_name += property_name;
		event_name += "_changed";
		auto ev_it = _class_meta._event_list.find(event_name);
		if (ev_it != _class_meta._event_list.end())
		{
			for (auto& elment : ev_it->second)
			{
				elment(this, old_value, value);
			}
		}

		return true;
	}
	pybind11::object* get_property_value(const std::string& property_name);
protected:
	//void trigger_event(const std::string event_name);
	void init_property();
protected:
	const class_meta& _class_meta;
	std::vector<Property_Value> _property;
};

