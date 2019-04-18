//在这个类中包括了指针类成员变量m_data，当类中包括指针类成员变量时，
//一定要重载其拷贝构造函数、赋值函数和析构函数，这既是对C++程序员的基本要求

//在C++中，下面三种对象需要调用拷贝构造函数 
//1. 对象以值传递的方式传入函数参数
//2. 对象以值传递的方式从函数返回
//3. 对象需要通过另外一个对象进行初始化


#include <iostream>
class String
{
public:
	String(const char *str = NULL);//普通构造函数
	String(const String &str);//拷贝构造函数
	String & operator =(const String &str);//赋值函数
	~String();//析构函数
private:
	char* m_data;//用于保存字符串
};

//普通构造函数
String::String(const char *str) {
	if (str == NULL) {
		m_data = new char[1]; //对空字符串自动申请存放结束标志'\0'的空间 
		if (m_data == NULL) {//内存是否申请成功
			std::cout << "申请内存失败！" << std::endl;
			exit(1);
		}
		m_data[0] = '\0';
	}
	else {
		int length = strlen(str);
		m_data = new char[length + 1];
		if (m_data == NULL) {//内存是否申请成功
			std::cout << "申请内存失败！" << std::endl;
			exit(1);
		}
		strcpy(m_data, str);
	}
}
//拷贝构造函数
String::String(const String &str) { //输入参数为const型
	int length = strlen(str.m_data);
	m_data = new char[length + 1];
	if (m_data == NULL) {//内存是否申请成功
		std::cout << "申请内存失败！" << std::endl;
		exit(1);
	}
	strcpy(m_data, str.m_data);
}
//赋值函数
String& String::operator =(const String &str) {//输入参数为const型
	if (this == &str) //检查自赋值
		return *this;
	int length = strlen(str.m_data);
	delete[] m_data;//释放原来的内存资源
	m_data = new char[length + 1];
	if (m_data == NULL) {//内存是否申请成功
		std::cout << "申请内存失败！" << std::endl;
		exit(1);
	}
	strcpy(m_data, str.m_data);
	return *this;//返回本对象的引用
}
//析构函数
String::~String() {
	delete[] m_data;
}

void main() {
	String a;
	String b("abc");
	system("pause");
}
