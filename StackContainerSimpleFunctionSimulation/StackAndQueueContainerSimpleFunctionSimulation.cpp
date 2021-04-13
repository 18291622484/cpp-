#include<iostream>
#include<vector>
#include<list>
using namespace std;

template<class T, class Con = vector<T>>
class mystack {
public:
	mystack(){}
	void push(const T& val) {
		_st.push_back(val);
	}
	void pop() {
		_st.pop_back();
	}
	T& top() {
		return _st.back();
	}
	const T& top()const {
		return _st.back();
	}
	size_t size()const {
		return _st.size();
	}
	bool empty()const {
		_st.empty();
	}
private:
	Con _st;
};

template<class T, class Con = list<T>>
class myqueue {
public:
	myqueue() {}
	void push(const T& val) {
		_qu.push_back(val);
	}
	void pop() {
		_qu.pop_front();
	}
	T& front() {
		return _qu.front();
	}
	const T& front()const {
		return _qu.front();
	}
	T& back() {
		return _qu.back();
	}
	const T& back()const {
		return _qu.back();
	}
	size_t size()const {
		return _qu.size();
	}
	bool empty()const {
		_qu.empty();
	}
private:
	Con _qu;
};

int main() {

	return 0;
}