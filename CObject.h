#pragma once
#include <string.h>
#include <string>
#include <functional>
#include <unordered_map>
#include <list>
#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <vector>
#include "CAny.h"

class CObject;
enum Property_Type
{
	PROPERTY_INT,
	PROPERTY_BOOL= PROPERTY_INT,
	PROPERTY_FLOAT,
	PROPERTY_DOUBLE=PROPERTY_FLOAT,

};


template<typename SupportType>
struct SupportTypeResult
{
	enum {result = 0};
};
template<> struct SupportTypeResult<int>
{
	enum { result = PROPERTY_INT };
};
template<> struct SupportTypeResult<bool>
{
	enum {result = PROPERTY_INT};
};
template<> struct SupportTypeResult<float>
{
	enum { result = PROPERTY_FLOAT };
};
template<> struct SupportTypeResult<double>
{
	enum {result = PROPERTY_FLOAT};
};

struct Property_Value 
{
	Any _value;
};

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

