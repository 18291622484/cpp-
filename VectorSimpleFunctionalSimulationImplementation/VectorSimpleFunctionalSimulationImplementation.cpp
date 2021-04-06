#include<iostream>
#include<string>
using namespace std;

template<class T>
class myvector {
	//迭代器
	typedef T* iterator;
	typedef const T* const_iterator;
	//可读可写迭代器
	iterator begin() {
		return _start;
	}
	iterator end() {
		return _finish;
	}
	//只读迭代器
	const_iterator begin()const {
		return _start;
	}
	const_iterator end()const {
		return _finish;
	}
	//获取有效元素个数
	size_t size()const {
		return _finish - _start;
	}
	//获取容量大小
	size_t capacity()const {
		return _end_of_storage - _start;
	}
	//无参构造函数
	myvector()
		:_start(nullptr)
		,_finish(nullptr)
		,_end_of_storage(nullptr)
	{}
	//带参构造函数
	myvector(size_t n, const T& val = T())
		:_start(new T[n])
		, _finish(_start + n)
		, _end_of_storage(_start + n)
	{
		//使用类 0 值进行初始化
		for (int i = 0; i < n; i++) {
			_start[i] = val;
		}
	}
	//使用迭代器构造函数
	template<class inputiterator>
	myvector(inputiterator frist, inputiterator last)
		:_start(nullptr)
		, _finish(nullptr)
		, _end_of_storage(nullptr)
	{
		//使用迭代区间的内容进行初始化
		while (frist != end) {
			push_back(*frist);
			frist++;
		}
	}
	//拷贝构造
	myvector(const myvector<T>& copy)
		:_start(nullptr)
		, _finish(nullptr)
		, _end_of_storage(nullptr)
	{
		size_t n = copy.capacity();
		_start = new T[n];
		//此处只能进行赋值操作，而不能使用内存拷贝，因为如果是自定义类型，那么会出现浅拷贝
		for (size_t i = 0; i < copy.size(); i++) {
			//此处是赋值操作，如果是自定义类型，那么会调用自定义类型本身的深拷贝操作
			_start[i] = copy[i];
		}
		_finish = _start + copy.size();
		_end_of_storage = _start + n;
	}
	//赋值运算符传统写法
	myvector<T>& operator=(const myvector<T>& v) {
		if (this != &v) {
			delete[] _start;
			size_t n = v.capacity();
			_start = new T[n];
			//此处只能进行赋值操作，而不能使用内存拷贝，因为如果是自定义类型，那么会出现浅拷贝
			for (size_t i = 0; i < v.size(); i++) {
				//此处是赋值操作，如果是自定义类型，那么会调用自定义类型本身的深拷贝操作
				_start[i] = v[i];
			}
			_finish = _start + v.size();
			_end_of_storage = _start + n;
		}
		return *this;
	}
	//赋值运算符现代写法
	myvector<T>& operator=(myvector<T> v) {
		Swap(v);
		return *this;
	}
	//内部交换函数
	void Swap(myvector<T>& v) {
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_end_of_storage, v._end_of_storage);
	}
	//析构函数
	~myvector() {
		if (_start) {
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
	}
	//访问操作
	T& operator[](size_t pos) {
		//判断位置是否合法
		if (pos >= begin() && pos < end()) {
			return _start[pos];
		}
	}
	const T& operator[](size_t pos)const {
		//判断位置是否合法
		if (pos >= begin() && pos < end()) {
			return _start[pos];
		}
	}
	//改变有效元素个数
	void resize(size_t n, const T& val = T()) {
		//如果是增容，检查容量是否足够
		if (n > capacity()) {
			reserve(n);
		}
		//对新增的空间赋指定值
		if (n > size()) {
			size_t num = n - size();
			while(num--) {
				*_finish = val;
				_finish++;
			}
		}
		//然后修改有效元素个数指针_finish
		_finish = _start + n;
	}
	//改变容量
	void reserve(size_t n) {
		//如果是增容，那么执行操作
		if (n > capacity()) {
			//拿到原始数据长度
			size_t len = size();
			//开辟新空间
			T* arr = new T[n];
			//如果有原始空间，那么就要将原始内容拷贝到新空间，并释放原始空间
			if (_start) {
				//此处只能进行赋值操作，而不能使用内存拷贝，因为如果是自定义类型，那么会出现浅拷贝
				for (size_t i = 0; i < len; i++) {
					//此处是赋值操作，如果是自定义类型，那么会调用自定义类型本身的深拷贝操作
					arr[i] = _start[i];
				}
				delete[] _start;
			}
			//更新变量
			_start = arr;
			_finish = _start + len; 
			_end_of_storage = _start + n;
		}
	}
	//尾插操作
	void push_back(const T& val = T()) {
		//判断空间是否足够，如果不够则需开辟
		if (_finish == _end_of_storage) {
			size_t n = capacity() == 0 ? 1 : 2 * capacity();
			reserve(n);
		}
		//进行尾插数据
		*_finish = val;
		//更新变量
		_finish++;
	}
	//在任意迭代器位置插入元素
	iterator insert(iterator pos, const T& val) {
		//检查插入位置
		if (pos <= begin() && pos >= end()) {
			//检查容量是否足够
			if (_finish == _end_of_storage) {
				//要进行增容，迭代器要进行更新，所以先记录下迭代器与原始位置的偏移量
				size_t len = pos - _start;
				//检查需要更新的容量
				size_t n = capacity == 0 ? 1 : 2 * capacity;
				//增容
				reserve(n);
				//更新迭代器，在新位置的基础上加上偏移量
				pos = _start + len;
			}
			//元素向后移动
			iterator tmp = _finish;
			while (tmp != pos) {
				*tmp = *(tmp - 1);
				tmp--;
			}
			//插入元素
			*pos = val;
			//更新变量
			_finish++;
		}
		return pos;
	}
	//删除元素
	iterator erase(iterator pos) {
		//检查位置
		if (pos >= begin() && pos < end()) {
			iterator start = pos + 1;
			//循环向前移动一个元素
			while (start != _finish) {
				*(start - 1) = *start;
				start++;
			}
			//更新变量
			_finish--;
		}
		return pos;
	}
	//尾删操作
	void pop_back() {
		//调用删除操作
		erase(_finish - 1);
	}
private:
	//这里使用指针来组织一个vector容器
	//首指针
	iterator _start;
	//最后一个有效元素的后一个位置
	iterator _finish;
	//开辟空间的最后一个元素后一个位置
	iterator _end_of_storage;
};
template<class T>
ostream& operator<<(ostream& _cout, const myvector<T>& v) {
	for (size_t i = 0; i < v.size(); i++) {
		_cout << v[i] << ' ';
	}
	_cout << endl;
	return cout;
}
int main() {

	return 0;
}