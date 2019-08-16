#include <pybind11/pybind11.h>
#include <pybind11/complex.h>
#include <pybind11/chrono.h>
#include <thread>
#include <atomic>
#include <iostream>
#include "cobject.h"
#include "ckernel.h"
namespace py = pybind11;

py::function g_entry;
void set_entry(py::function f) {
	g_entry = f;
}
int start() {
	py::print("kernel start!!!");
	py::print("do something to initialize environment");
	CKernel kernel;
	g_entry(&kernel);
	return 0;
}
PYBIND11_MODULE(hybrid, m) {
	m.doc() = "pybind11 example plugin"; //
	m.def("set_entry", &set_entry);
	m.def("start", &start);
	py::class_<CKernel>(m, "CKernel")
		.def(py::init())
		.def("add_class", &CKernel::add_class)
		.def("add_property", &CKernel::add_property)
		.def("add_event", &CKernel::add_event)
		.def("create_class", &CKernel::create_class, py::return_value_policy::reference);
	py::class_<CObject>(m, "CObject")
		.def("set_property_value", py::overload_cast<const std::string&, int>(&CObject::set_property_value<int>))
		.def("set_property_value", py::overload_cast<const std::string&, bool>(&CObject::set_property_value<bool>))
		.def("set_property_value", py::overload_cast<const std::string&, float>(&CObject::set_property_value<float>))
		.def("set_property_value", py::overload_cast<const std::string&, double>(&CObject::set_property_value<double>))
		.def("get_property_value", &CObject::get_property_value, py::return_value_policy::take_ownership);
	py::enum_<Property_Type>(m, "Property_Type", py::arithmetic())
		.value("PROPERTY_INT", PROPERTY_INT)
		.value("PROPERTY_BOOL", PROPERTY_BOOL)
		.value("PROPERTY_FLOAT", PROPERTY_FLOAT)
		.value("PROPERTY_DOUBLE",PROPERTY_DOUBLE);
}