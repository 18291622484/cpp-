#include<iostream>
using namespace std;

//每个节点的类
template<class T>
struct ListNode {
	//节点存放的数据
	T _date;
	//指向前一个节点的指针
	ListNode<T>* _prev;
	//指向后一个节点的指针
	ListNode<T>* _next;
	//节点类的构造函数
	ListNode(const T& val = T())
		:_date(val)
		, _prev(nullptr)
		,_next(nullptr)
	{}
};
//将节点的迭代器使用类封装起来，这样就可以实现对迭代器的常规操作了
template<class T, class ref, class ptr>
struct ListIterator {
	//使用别名来简化代码
	typedef ListIterator<T, ref, ptr> Self;
	typedef ListNode<T> Node;
	typedef Node* pNode;
	//构造函数
	ListIterator(pNode node)
		:_node(node)
	{}
	//* 运算符重载
	ref operator*() {
		return _node->_date;
	}
	//前置++ 运算符重载
	Self& operator++() {
		_node = _node->_next;
		return *this;
	}
	//后置++ 运算符重载
	Self operator++(int) {
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}
	//前置-- 运算符重载
	Self& operator--() {
		_node = _node->_prev;
		return *this;
	}
	//后置-- 运算符重载
	Self operator--(int) {
		Self tmp(*this);
		_node = _node->_prev;
		return tmp;
	}
	//-> 运算符重载
	ptr operator->() {
		return *(_node->_date);
	}
	//== 不等于运算符
	bool operator==(const Self& it) {
		return _node == it->_node;
	}
	//!= 运算符重载
	bool operator!=(const Self& it) {
		return _node != it->_node;
	}
	//封装迭代器
	pNode _node;
};
template<class T>
class mylist {
public:
	typedef ListNode<T> Node;
	typedef Node* pNode;
	typedef ListIterator<T, T&, T*> iterator;
	typedef ListIterator<T, const T&, const T*> const_iterator;
	typedef ListIterator<T, T&, T*> reverse_iterator;
	typedef ListIterator<T, const T&, const T*> const_reverse_iterator;
	//首迭代器
	iterator begin() {
		return iterator(_header->_next);
	}
	//尾迭代器
	iterator end() {
		return iterator(_header);
	}
	//只读首迭代器
	const_iterator begin()const {
		return const_iterator(_header->_next);
	}
	//只读尾迭代器
	const_iterator end()const {
		return const_iterator(_header);
	}
	//无参构造函数
	mylist()
		:_header(new Node())
	{
		//头结点循环指向自身
		_header->_date = _header->_prev = _header;
	}
	//构造函数:构建n个节点
	mylist(size_t n, const T& val = T())
		:_header(new Node())
	{
		//先创建出头结点
		_header->_next = _header->_prev = _header;
		//在使用尾插接口进行元素的插入
		for(int i = 0; i < n; i++)
			push_back(val);
	}
	//构造函数:使用迭代区间进行
	template<class inputIterator>
	mylist(inputIterator frist, inputIterator last)
		:_header(new Node())
	{
		//先创建头结点
		_header->_next = _header->_prev = _header;
		//在使用尾插接口将迭代区间的元素插入
		while (frist != last)
			push_back(*(frist++));
	}
	//深拷贝构造函数
	mylist(const mylist<T>& list)
		:_header(new Node())
	{
		//先创建头结点
		_header->_next = _header->_prev = _header;
		//循环拷贝结点到新链表中,使用for循环十分方便简单
		for (auto& e : list) {
			//复用尾插接口来构建链表
			push_back(e);
		}
	}
	//赋值运算符
	mylist<T>& operator=(const mylist<T>& list) {
		//查看是否是相同一个对象，如果不是则进行赋值
		if (this != &list) {
			//释放原有节点
			pNode idx = _header->_next;
			while (idx != _header) {
				pNode tmp = idx->_next;
				delete idx;
				idx = pNode;
			}
			//拷贝结点
			for (auto& e : list) {
				push_back(e);
			}
		}
		return *this;
	}
	//析构函数
	~mylist() {
		//拿到第一个有效结点
		pNode node = _header->_next;
		//循环删除，结束条件就是再次走到头结点
		while (node != _header) {
			//先保存当前节点
			pNode tmp = node;
			//走到下一个节点
			node = node->_next;
			//删除当前节点
			delete tmp;
		}
		//最后删除头结点
		delete _header;
		_header = nullpte;
	}
	//在任意位置插入结点
	void insert(iterator pos, const T& val) {
		//先申请结点，然后赋值
		pNode node = new Node(val);
		//将新节点插入到指定迭代器位置,并形成循环结构
		//所以先拿到指定迭代位置的前一个结点
		pNode idx = pos._node->_prev;
		//修改插入结点和前一个结点的指向
		idx->_next = node;
		node->_prev = idx;
		//修改插入结点和后一个节点的指向
		node->_next = pos._node;
		pos._node->_prev = node;
	}
	//尾插接口
	void push_back(T& val) {
		//接口复用，尾插就是插入到尾迭代器前一个位置
		insert(end(), val);
	}
	//头插接口
	void push_front(T& val) {
		//接口复用，头插就是插入到首迭代器前一个位置
		insert(begin(), val);
	}
	//删除迭代器位置结点
	iterator erase(iterator pos) {
		//判断删除位置是否为尾迭代器，如果不是则正常删除
		if (pos != end()) {
			//拿到删除位置的前一个结点
			pNode tmp = pos._node->_prev;
			//删除节点的前一个节点的next指针指向删除节点的下一个节点
			tmp->_next = pos._node->_next;
			//删除节点的下一个节点的prev指向删除节点的前一个节点
			pos._node->_next->_prev = tmp;
			//删除当前节点
			delete pos._node;
			//当前迭代器失效，返回下一个节点的迭代器
			return iterator(tmp->_next)
		}
		//如果是尾迭代器，那么就直接返回自己
		return pos;
	}
	//头删接口
	void pop_front() {
		erase(begin());
	}
	//尾删接口
	void pop_back() {
		erase(--end());
	}
	//clear 清空结点接口
	void clear() {
		//拿到第一个有效结点
		pNode node = _header->_next;
		//循环删除，结束条件就是再次走到头结点
		while (node != _header) {
			//先保存当前节点
			pNode tmp = node;
			//走到下一个节点
			node = node->_next;
			//删除当前节点
			delete tmp;
		}
		//最后将头结点置为循环
		_header->_next = _header->_prev = _header;
	}
private:
	pNode _header;
};

int main() {

	return 0;
}