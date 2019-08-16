# pyengine
export c++ object engine for python programing

# 编译
1. git clone https://github.com/eddie74748/pyengine.git
2. git submodule update --init --recursive
3. 切换至工程主目录
4. mkdir build
5. cd build
6. cmake -G "Visual Studio 15 2017 Win64" ..
7. 在build目录下使用vs2017打开hybrid.sln进行编译
# 调试
1. 在vs2017中右击hybrid工程，选择[属性]->[配置属性]->[调试], 
    * [命令]一栏填写python程序运行路径。
    * [命令参数] 填写"test_class.py"
    * [工作目录] 设置为 "$(ProjectDir)$(Configuration)"
2. 将主目录下"test_class.py"拷贝至模块生成路径下,默认为Debug或者Release
3. 设置hybrid为启动项目
4. F5执行调试
# 当前支持的功能
1. 使用python脚本在C++模块中添加类
2. 为类添加属性，目前支持3种类型
    * int
    * float
    * double
3. 实例化类
4. 设置和获取属性值
5. 可为属性添加回调，当属性发生变化时触发回调，可多次注册形成回调链表。
# 更多
更多使用详情，参考test_class.py脚本