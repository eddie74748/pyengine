#pragma once

enum Property_Type
{
	PROPERTY_INT,
	PROPERTY_BOOL = PROPERTY_INT,
	PROPERTY_FLOAT,
	PROPERTY_DOUBLE = PROPERTY_FLOAT,
};

template<typename SupportType>
struct SupportTypeResult
{
	enum { result = 0 };
};
template<> struct SupportTypeResult<int>
{
	enum { result = PROPERTY_INT };
};
template<> struct SupportTypeResult<bool>
{
	enum { result = PROPERTY_INT };
};
template<> struct SupportTypeResult<float>
{
	enum { result = PROPERTY_FLOAT };
};
template<> struct SupportTypeResult<double>
{
	enum { result = PROPERTY_FLOAT };
};


