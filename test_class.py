import hybrid
import json

def callback(obj):
    obj.function()
    print('callback trigger',type(obj))
def entry(str):
    json.loads(str)
    hybrid.fetch_count()
def property_call_back(self,old_value, new_value):
    print(old_value);
    print("->");
    print(new_value);
def entry(kernel):
    class_name = "CTestClass";
    kernel.add_class(class_name);
    kernel.add_property(class_name,"p_int", hybrid.Property_Type.PROPERTY_INT);
    kernel.add_event(class_name, "on_p_int_changed",property_call_back);

    obj = kernel.create_class(class_name);
    obj.set_property_value("p_int", 10);
    test_v = obj.get_property_value("p_int");
    test_v = obj.get_property_value("p_intt");
    print(test_v);

hybrid.set_entry(entry)
hybrid.start()
