#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

class mystring {
public:
	//������,��ʵ�����ַ�ָ��
	typedef char* iterator;
	typedef const char* const_iterator;
	//�׵�ַ
	iterator begin() {
		return _date;
	}
	const_iterator begin()const {
		return _date;
	}
	//β��ַ��һ����ַ
	iterator end() {
		return _date + _size;
	}
	const_iterator end()const {
		return _date + _size;
	}
	//���캯��
	mystring(const char* date = "")
		//strlen��һ�������Ĳ������������ã������Ȼ�ȡ��ֵ��Ȼ��ʹ��
		//���ݳ�ʼ��ֵ���ַ�������ʼ������
		:_size(strlen(date))
		, _capacity(_size)
		, _date(new char[_size + 1])
	{
		//����ʼֵ�������ַ��ռ�
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
	//��������
	mystring(const mystring& str)
		//��һ���������ֵ��ʼ����һ������
		:_size(str._size)
	    ,_capacity(str._capacity)
		,_date(new char[_capacity + 1])
	{
		//����ʼֵ�������ַ��ռ�
		strcpy(_date, str._date);
	}
	//��ֵ�����
	mystring operator=(const mystring& str) {
		//�����ֵ�����뱻��ֵ������ͬ����ô�Ͳ��ø�ֵ��
		if (this != &str) {
			//������ֵ
			_size = str._size;
			_capacity = str._capacity;
			//�ͷ�ԭ�пռ�ռ�
			delete[] _date;
			//�����¿ռ��Ÿ�ֵ����
			_date = new char[_capacity + 1];
			strcpy(_date, str._date);
		}
	}
	//��������
	~mystring() {
		//����ַ�ָ��ǿգ���ô���Խ����ͷ�
		if (_date) {
			//�ͷſռ�
			delete[] _date;
			//��ֵΪ�գ���֤�����İ�ȫ��
			_date = nullptr;
			_size = _capacity = 0;
		}
	}
	//��ȡԪ�ظ���
	size_t size()const {
		return _size;
	}
	//��ȡ������С
	size_t capacity()const {
		return _capacity;
	}
	//��������
	void myswap(mystring& str) {
		swap(_size, str._size);
		swap(_capacity, str._capacity);
		swap(_date, str._date);
	}
	//��ͨ����ķ���
	char& operator[](size_t pos) {
		//����±��Ϸ�����ôֱ�Ӷ��Ա���
		assert(pos < _size && pos >= 0);
		return _date[pos];
	}
	//const����ķ���
	const char& operator[](size_t pos)const {
		//����±��Ϸ�����ôֱ�Ӷ��Ա���
		assert(pos < _size && pos >= 0);
		return _date[pos];
	}
	//����const���ε��ַ��ռ��׵�ַ
	const char* c_str()const {
		return _date;
	}
	//��������
	void reserve(size_t num) {
		//���������������ôִ�У�����Ǽ�С������ô�Ͳ�ִ��
		if (num > _capacity) {
			//�����¿ռ�
			char* tmp = new char[num + 1];
			//��ԭ��Ԫ�ؿ�������
			strcpy(tmp, _date);
			//�ͷ�ԭ�пռ�
			delete[] _date;
			//���±���
			_date = tmp;
			_capacity = num;
		}
	}
	//�ı���ЧԪ�ظ���
	void resize(size_t num, const char& ch = '\0') {
		//����ı��֮����ЧԪ�ظ���������������ô����Ҫ����
		if (num > _capacity) {
			reserve(num);
		}
		//�����������ЧԪ�ظ�������ô������λ�����ָ���ַ�ch
		if (num > _size) {
			memset(_date + _size, ch, num - _size);
		}
		//���±���
		_size = num;
		_date[_size] = '\0';
	}
	//β��һ���ַ�
	void push_back(const char& ch) {
		//����ռ�������������ô��������
		if (_size == _capacity) {
			size_t num = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(num);
		}
		//���ַ����룬���±���
		_date[_size++] = ch;
		_date[_size] = '\0';
	}
	//append׷���ַ�
	mystring& append(const char* str) {
		//ǰ��˵���ˣ�strlen��ʹ�ã���¼�½�����Ժ�ֱ��ʹ��
		int len = strlen(str);
		//����ռ䲻��׷��������
		if (_capacity - _size < len) {
			reserve(_size + len);
		}
		//�����ݿ�����ȥ
		strcpy(_date + _size, str);
		//���±���
		_size = _size + len;
		return *this;
	}
	//+=׷��C����ַ���
	mystring& operator+=(const char* str) {
		append(str);
		return *this;
	}
	//+=׷�Ӷ������
	mystring& operator+=(const mystring& str) {
		append(str._date);
		return *this;
	}
	//+=׷�ӵ����ַ�
	mystring& operator+=(const char& ch) {
		push_back(ch);
		return *this;
	}
	//����C����ַ�������
	mystring& insert(size_t pos, const char* str) {
		//�������λ���Ƿ���ȷ
		assert(pos <= _size);
		size_t len = strlen(str);
		//��������Ƿ��㹻���룬��������Ҫ����
		if (_capacity < _size + len) {
			reserve(_size + len);
		}
		//����ƶ�Ԫ��
		size_t end = _capacity;
		while (end > pos + len - 1) {
			_date[end] = _date[end - len];
			end--;
		}
		//�����ݿ�����ȥ
		memcpy(_date + pos, str, len);
		//���±���
		_size = _capacity;
		return *this;
	}
	//���뵥���ַ�
	mystring& insert(size_t pos, const char& ch) {
		//�������λ���Ƿ���ȷ
		assert(pos <= _size);
		//��������Ƿ��㹻���룬��������Ҫ����
		if (_size == _capacity) {
			reserve(_capacity + 1);
		}
		//����ƶ�Ԫ��
		size_t end = _capacity;
		while (end > pos) {
			_date[end] = _date[end - 1];
			end--;
		}
		//�����ݿ�����ȥ
		_date[pos] = ch;
		//���±���
		_size++;
		return *this;
	}
	//ɾ��Ԫ��
	mystring& erase(size_t pos, size_t len = npos) {
		//���λ���Ƿ�Ϸ�
		assert(pos < _size);
		//���ɾ�����ȴ��ڵ���ʣ��Ԫ�أ���ô����ζ��ɾ��ʣ��ȫ��Ԫ��
		if (len == npos || pos + len >= _size) {
			_size = pos;
			_date[_size] = '\0';
		}
		//�����ɾ��ָ������Ԫ�أ�Ҳ���ǽ�ʣ��Ԫ���ƶ�����ɾ����λ��
		else {
			size_t begin = pos + len;
			while (begin <= _size) {
				_date[pos++] = _date[begin++];
			}
			//���±���
			_size -= len;
		}
		return *this;
	}
	//���ҵ����ַ�
	size_t find(const char& ch, size_t pos = 0)const {
		//ѭ�����ң��ҵ������±�
		for (size_t i = pos; i < _size; i++) {
			if (_date[i] == ch) {
				return i;
			}
		}
		//�������δ�ҵ�����ô�������ֵnpos
		return npos;
	}
	//����C����ַ���
	size_t find(const char* str, size_t pos = 0) {
		//���λ���Ƿ�Ϸ�
		assert(pos < _size);
		//ʹ�ÿ⺯��strstr�����ַ���ƥ�����
		char* pstr = strstr(_date + pos, str);
		//���ҵ�����һ����ַ�������Ҫ����һ�������_date��ƫ����
		if (pstr) {
			return pstr - _date;
		}
		//δ�ҵ��򷵻�һ�����ֵ
		return npos;
	}
	//��ȡ�ַ���
	mystring substr(size_t pos = 0, size_t len = npos)const {
		//�����Ϸ��Լ���
		assert(pos < _size);
		//�����ȡ���ȴ��ڵ���ʣ�೤�ȣ���ô�ͽ�ʣ�೤�ȵ�Ԫ�ض�����
		if (len == npos || pos + len >= _size) {
			mystring str(_date + pos);
			return str;
		}
		//����ͷ��ض�Ӧ���ȵ��ַ���
		else {
			//�����㹻�Ŀռ�
			char* arr = new char[len + 1];
			//�����ݷ���
			memcpy(arr, _date + pos, len);
			arr[len] = '\0';
			//����һ������
			mystring str(arr);
			delete[] arr;
			//���ظ���
			return str;
		}
	}
private:
	//��ЧԪ�ظ���
	size_t _size;
	//�������
	size_t _capacity;
	//����ַ��ռ��׵�ַ
	char* _date;
	//��̬�������ֵ
	static const size_t npos;
};
const size_t mystring::npos = -1;
//+ƴ�Ӳ���
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
//�Ƚϲ���
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
//�������
ostream& operator<<(ostream& _cout, mystring& str) {
	_cout << str.c_str();
	return _cout;
}
//���뺯��
istream& operator>>(istream& _cin, mystring& str) {
	char ch = 0;
	//�����һ������룬��ô�����ո�ͻ���ʱ���ǲ������ģ���Ϊ�����Ƿָ��
	//��ô��Ҫ��ȡ���ո�ͻ��У���ô�͵����������ĳ�Ա����
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