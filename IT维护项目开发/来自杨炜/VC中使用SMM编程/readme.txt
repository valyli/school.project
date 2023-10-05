1. 把qdk目录拷贝到VC目录下
2. 把dll目录中的文件拷贝到windows系统目录下
3. 在VC设置Tools/Options/Directories下添加inlcude和lib目录
4. 在工程的Project/Settings/Link下添加连接库的名字。smmw32.lib为使用dll方式的Import库，smmw32s.lib为静态库连接。

5. testsmm为smm测试程序示例代码。