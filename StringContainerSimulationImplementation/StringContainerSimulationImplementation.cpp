#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

class mystring {
public:
	//迭代器,其实就是字符指针
	typedef char* iterator;
	typedef const char* const_iterator;
	//首地址
	iterator begin() {
		return _date;
	}
	const_iterator begin()const {
		return _date;
	}
	//尾地址后一个地址
	iterator end() {
		return _date + _size;
	}
	const_iterator end()const {
		return _date + _size;
	}
	//构造函数
	mystring(const char* date = "")
		//strlen是一个遍历的操作，尽量少用，所以先获取到值，然后使用
		//根据初始赋值的字符串来初始化变量
		:_size(strlen(date))
		, _capacity(_size)
		, _date(new char[_size + 1])
	{
		//将初始值拷贝到字符空间
		strcpy(_date, date);
	}
	mystring(const char& ch)
		:_size(1)
		, _capacity(1)
		, _date(new char[2])
	{
		_date[0] = ch;
		_date[1] = '\0';
	}
	//拷贝构造
	mystring(const mystring& str)
		//用一个对象的数值初始化另一个对象
		:_size(str._size)
	    ,_capacity(str._capacity)
		,_date(new char[_capacity + 1])
	{
		//将初始值拷贝到字符空间
		strcpy(_date, str._date);
	}
	//赋值运算符
	mystring operator=(const mystring& str) {
		//如果赋值对象与被赋值对象相同，那么就不用赋值了
		if (this != &str) {
			//变量赋值
			_size = str._size;
			_capacity = str._capacity;
			//释放原有空间空间
			delete[] _date;
			//开辟新空间存放赋值内容
			_date = new char[_capacity + 1];
			strcpy(_date, str._date);
		}
	}
	//析构函数
	~mystring() {
		//如果字符指针非空，那么可以进行释放
		if (_date) {
			//释放空间
			delete[] _date;
			//赋值为空，保证变量的安全性
			_date = nullptr;
			_size = _capacity = 0;
		}
	}
	//获取元素个数
	size_t size()const {
		return _size;
	}
	//获取容量大小
	size_t capacity()const {
		return _capacity;
	}
	//交换函数
	void myswap(mystring& str) {
		swap(_size, str._size);
		swap(_capacity, str._capacity);
		swap(_date, str._date);
	}
	//普通对象的访问
	char& operator[](size_t pos) {
		//如果下表不合法，那么直接断言报错
		assert(pos < _size && pos >= 0);
		return _date[pos];
	}
	//const对象的访问
	const char& operator[](size_t pos)const {
		//如果下表不合法，那么直接断言报错
		assert(pos < _size && pos >= 0);
		return _date[pos];
	}
	//返回const修饰的字符空间首地址
	const char* c_str()const {
		return _date;
	}
	//增大容量
	void reserve(size_t num) {
		//如果是增大容量那么执行，如果是减小容量那么就不执行
		if (num > _capacity) {
			//开辟新空间
			char* tmp = new char[num + 1];
			//将原有元素拷贝放入
			strcpy(tmp, _date);
			//释放原有空间
			delete[] _date;
			//更新变量
			_date = tmp;
			_capacity = num;
		}
	}
	//改变有效元素个数
	void resize(size_t num, const char& ch = '\0') {
		//如果改变的之后有效元素个数大于容量，那么就需要增容
		if (num > _capacity) {
			reserve(num);
		}
		//如果是增加有效元素个数，那么新增的位置填充指定字符ch
		if (num > _size) {
			memset(_date + _size, ch, num - _size);
		}
		//更新变量
		_size = num;
		_date[_size] = '\0';
	}
	//尾插一个字符
	void push_back(const char& ch) {
		//如果空间容量不够，那么进行增容
		if (_size == _capacity) {
			size_t num = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(num);
		}
		//将字符插入，更新变量
		_date[_size++] = ch;
		_date[_size] = '\0';
	}
	//append追加字符
	mystring& append(const char* str) {
		//前面说过了，strlen少使用，记录下结果，以后直接使用
		int len = strlen(str);
		//如果空间不够追加需增容
		if (_capacity - _size < len) {
			reserve(_size + len);
		}
		//将内容拷贝过去
		strcpy(_date + _size, str);
		//更新变量
		_size = _size + len;
		return *this;
	}
	//+=追加C风格字符串
	mystring& operator+=(const char* str) {
		append(str);
		return *this;
	}
	//+=追加对象操作
	mystring& operator+=(const mystring& str) {
		append(str._date);
		return *this;
	}
	//+=追加单个字符
	mystring& operator+=(const char& ch) {
		push_back(ch);
		return *this;
	}
	//插入C风格字符串操作
	mystring& insert(size_t pos, const char* str) {
		//检查插入的位置是否正确
		assert(pos <= _size);
		size_t len = strlen(str);
		//检查容量是否足够插入，不够则需要增容
		if (_capacity < _size + len) {
			reserve(_size + len);
		}
		//向后移动元素
		size_t end = _capacity;
		while (end > pos + len - 1) {
			_date[end] = _date[end - len];
			end--;
		}
		//将内容拷贝过去
		memcpy(_date + pos, str, len);
		//更新变量
		_size = _capacity;
		return *this;
	}
	//插入单个字符
	mystring& insert(size_t pos, const char& ch) {
		//检查插入的位置是否正确
		assert(pos <= _size);
		//检查容量是否足够插入，不够则需要增容
		if (_size == _capacity) {
			reserve(_capacity + 1);
		}
		//向后移动元素
		size_t end = _capacity;
		while (end > pos) {
			_date[end] = _date[end - 1];
			end--;
		}
		//将内容拷贝过去
		_date[pos] = ch;
		//更新变量
		_size++;
		return *this;
	}
	//删除元素
	mystring& erase(size_t pos, size_t len = npos) {
		//检查位置是否合法
		assert(pos < _size);
		//如果删除长度大于等于剩余元素，那么就意味着删除剩余全部元素
		if (len == npos || pos + len >= _size) {
			_size = pos;
			_date[_size] = '\0';
		}
		//否则就删除指定长度元素，也就是将剩余元素移动到被删除的位置
		else {
			size_t begin = pos + len;
			while (begin <= _size) {
				_date[pos++] = _date[begin++];
			}
			//更新变量
			_size -= len;
		}
		return *this;
	}
	//查找单个字符
	size_t find(const char& ch, size_t pos = 0)const {
		//循环查找，找到返回下标
		for (size_t i = pos; i < _size; i++) {
			if (_date[i] == ch) {
				return i;
			}
		}
		//其他情况未找到，那么返回最大值npos
		return npos;
	}
	//查找C风格字符串
	size_t find(const char* str, size_t pos = 0) {
		//检查位置是否合法
		assert(pos < _size);
		//使用库函数strstr进行字符串匹配查找
		char* pstr = strstr(_date + pos, str);
		//查找到的是一个地址，因此需要返回一个相对于_date的偏移量
		if (pstr) {
			return pstr - _date;
		}
		//未找到则返回一个最大值
		return npos;
	}
	//截取字符串
	mystring substr(size_t pos = 0, size_t len = npos)const {
		//参数合法性检验
		assert(pos < _size);
		//如果截取长度大于等于剩余长度，那么就将剩余长度的元素都返回
		if (len == npos || pos + len >= _size) {
			mystring str(_date + pos);
			return str;
		}
		//否则就返回对应长度的字符串
		else {
			//开辟足够的空间
			char* arr = new char[len + 1];
			//将内容放入
			memcpy(arr, _date + pos, len);
			arr[len] = '\0';
			//构建一个对象
			mystring str(arr);
			delete[] arr;
			//返回副本
			return str;
		}
	}
private:
	//有效元素个数
	size_t _size;
	//最大容量
	size_t _capacity;
	//存放字符空间首地址
	char* _date;
	//静态变量最大值
	static const size_t npos;
};
const size_t mystring::npos = -1;
//+拼接操作
mystring operator+(const mystring& str1, const mystring& str2) {
	mystring str(str1);
	return str += str2;
}
mystring operator+(const char* str1, const mystring& str2) {
	mystring str(str1);
	return str += str2;
}
mystring operator+(const char str1, const mystring& str2) {
	mystring str(str1);
	return str += str2;
}
//比较操作
bool operator<(const mystring& str1, const mystring& str2) {
	int ret = strcmp(str1.c_str(), str2.c_str());
	if (ret < 0)
		return true;
	return false;
}
bool operator==(const mystring& str1, const mystring& str2) {
	int ret = strcmp(str1.c_str(), str2.c_str());
	if (ret == 0)
		return true;
	return false;
}
bool operator<=(const mystring& str1, const mystring& str2) {
	return str1 < str2 || str1 == str2;
}
bool operator>(const mystring& str1, const mystring& str2) {
	return !(str1 <= str2);
}
bool operator>=(const mystring& str1, const mystring& str2) {
	return !(str1 <= str2);
}
bool operator!=(const mystring& str1, const mystring& str2) {
	return !(str1 == str2);
}
//输出函数
ostream& operator<<(ostream& _cout, mystring& str) {
	_cout << str.c_str();
	return _cout;
}
//输入函数
istream& operator>>(istream& _cin, mystring& str) {
	char ch = 0;
	//如果是一般的输入，那么遇到空格和换行时，是不会读入的，因为他们是分割符
	//那么想要读取到空格和换行，那么就调用输入流的成员函数
	while (ch = _cin.get()) {
		if (ch == ' ' || ch == '\n' || ch == EOF)
			break;
		str += ch;
	}
	return _cin;
}
int main() {
	mystring s1("zhm");
	mystring s2("521");
	s1 += s2;
	if (s1 < s2) {
		cout << s1 << endl;
	}
	else {
		cout << s2 << endl;
	}
	return 0;
}