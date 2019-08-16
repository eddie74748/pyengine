import time
import string
#加载c++模块
import hybrid

#定义属性变化回调
#self 对象实例
#old_value 变化前的值
#new_value 变化后的值
def property_call_back(self,old_value, new_value):
    print("=========value changed========")
    print(str(old_value)+"->"+str(new_value));

#定义python入口供C++调用
def entry(kernel):
    class_name = "CTestClass";
    #添加自定义类[类名]
    kernel.add_class(class_name);
    #添加属性[类名，属性名，属性类型]
    kernel.add_property(class_name,"p_int", hybrid.Property_Type.PROPERTY_INT);
    kernel.add_property(class_name,"p_bool", hybrid.Property_Type.PROPERTY_BOOL);
    kernel.add_property(class_name,"p_float", hybrid.Property_Type.PROPERTY_FLOAT);
    kernel.add_property(class_name,"p_double", hybrid.Property_Type.PROPERTY_DOUBLE);
    #设置属性变化回调 事件规则 "on_"+属性名+"changed" [类名，事件名，回调函数]
    kernel.add_event(class_name, "on_p_int_changed",property_call_back);
    kernel.add_event(class_name, "on_p_bool_changed",property_call_back);
    kernel.add_event(class_name, "on_p_float_changed",property_call_back);
    kernel.add_event(class_name, "on_p_double_changed",property_call_back);
    #创建类的实例[类名]
    obj = kernel.create_class(class_name);
    #设置属性值
    obj.set_property_value("p_int", 10);
    obj.set_property_value("p_bool", True);
    obj.set_property_value("p_float", 1.23);
    obj.set_property_value("p_double", 3.45);
    #显示属性值
    print("=========show value==============")
    print(obj.get_property_value("p_int"));
    print(obj.get_property_value("p_bool"));
    print(obj.get_property_value("p_float"));
    print(obj.get_property_value("p_double"));

def main():
    #设置python入口
    hybrid.set_entry(entry)
    loop_count = 0;
    while(loop_count < 2):
        hybrid.start();
        loop_count += 1;

#启动
main();
