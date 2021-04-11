#include<iostream>
using namespace std;

//ÿ���ڵ����
template<class T>
struct ListNode {
	//�ڵ��ŵ�����
	T _date;
	//ָ��ǰһ���ڵ��ָ��
	ListNode<T>* _prev;
	//ָ���һ���ڵ��ָ��
	ListNode<T>* _next;
	//�ڵ���Ĺ��캯��
	ListNode(const T& val = T())
		:_date(val)
		, _prev(nullptr)
		,_next(nullptr)
	{}
};
//���ڵ�ĵ�����ʹ�����װ�����������Ϳ���ʵ�ֶԵ������ĳ��������
template<class T, class ref, class ptr>
struct ListIterator {
	//ʹ�ñ������򻯴���
	typedef ListIterator<T, ref, ptr> Self;
	typedef ListNode<T> Node;
	typedef Node* pNode;
	//���캯��
	ListIterator(pNode node)
		:_node(node)
	{}
	//* ���������
	ref operator*() {
		return _node->_date;
	}
	//ǰ��++ ���������
	Self& operator++() {
		_node = _node->_next;
		return *this;
	}
	//����++ ���������
	Self operator++(int) {
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}
	//ǰ��-- ���������
	Self& operator--() {
		_node = _node->_prev;
		return *this;
	}
	//����-- ���������
	Self operator--(int) {
		Self tmp(*this);
		_node = _node->_prev;
		return tmp;
	}
	//-> ���������
	ptr operator->() {
		return *(_node->_date);
	}
	//== �����������
	bool operator==(const Self& it) {
		return _node == it->_node;
	}
	//!= ���������
	bool operator!=(const Self& it) {
		return _node != it->_node;
	}
	//��װ������
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
	//�׵�����
	iterator begin() {
		return iterator(_header->_next);
	}
	//β������
	iterator end() {
		return iterator(_header);
	}
	//ֻ���׵�����
	const_iterator begin()const {
		return const_iterator(_header->_next);
	}
	//ֻ��β������
	const_iterator end()const {
		return const_iterator(_header);
	}
	//�޲ι��캯��
	mylist()
		:_header(new Node())
	{
		//ͷ���ѭ��ָ������
		_header->_date = _header->_prev = _header;
	}
	//���캯��:����n���ڵ�
	mylist(size_t n, const T& val = T())
		:_header(new Node())
	{
		//�ȴ�����ͷ���
		_header->_next = _header->_prev = _header;
		//��ʹ��β��ӿڽ���Ԫ�صĲ���
		for(int i = 0; i < n; i++)
			push_back(val);
	}
	//���캯��:ʹ�õ����������
	template<class inputIterator>
	mylist(inputIterator frist, inputIterator last)
		:_header(new Node())
	{
		//�ȴ���ͷ���
		_header->_next = _header->_prev = _header;
		//��ʹ��β��ӿڽ����������Ԫ�ز���
		while (frist != last)
			push_back(*(frist++));
	}
	//������캯��
	mylist(const mylist<T>& list)
		:_header(new Node())
	{
		//�ȴ���ͷ���
		_header->_next = _header->_prev = _header;
		//ѭ��������㵽��������,ʹ��forѭ��ʮ�ַ����
		for (auto& e : list) {
			//����β��ӿ�����������
			push_back(e);
		}
	}
	//��ֵ�����
	mylist<T>& operator=(const mylist<T>& list) {
		//�鿴�Ƿ�����ͬһ�����������������и�ֵ
		if (this != &list) {
			//�ͷ�ԭ�нڵ�
			pNode idx = _header->_next;
			while (idx != _header) {
				pNode tmp = idx->_next;
				delete idx;
				idx = pNode;
			}
			//�������
			for (auto& e : list) {
				push_back(e);
			}
		}
		return *this;
	}
	//��������
	~mylist() {
		//�õ���һ����Ч���
		pNode node = _header->_next;
		//ѭ��ɾ�����������������ٴ��ߵ�ͷ���
		while (node != _header) {
			//�ȱ��浱ǰ�ڵ�
			pNode tmp = node;
			//�ߵ���һ���ڵ�
			node = node->_next;
			//ɾ����ǰ�ڵ�
			delete tmp;
		}
		//���ɾ��ͷ���
		delete _header;
		_header = nullpte;
	}
	//������λ�ò�����
	void insert(iterator pos, const T& val) {
		//�������㣬Ȼ��ֵ
		pNode node = new Node(val);
		//���½ڵ���뵽ָ��������λ��,���γ�ѭ���ṹ
		//�������õ�ָ������λ�õ�ǰһ�����
		pNode idx = pos._node->_prev;
		//�޸Ĳ������ǰһ������ָ��
		idx->_next = node;
		node->_prev = idx;
		//�޸Ĳ�����ͺ�һ���ڵ��ָ��
		node->_next = pos._node;
		pos._node->_prev = node;
	}
	//β��ӿ�
	void push_back(T& val) {
		//�ӿڸ��ã�β����ǲ��뵽β������ǰһ��λ��
		insert(end(), val);
	}
	//ͷ��ӿ�
	void push_front(T& val) {
		//�ӿڸ��ã�ͷ����ǲ��뵽�׵�����ǰһ��λ��
		insert(begin(), val);
	}
	//ɾ��������λ�ý��
	iterator erase(iterator pos) {
		//�ж�ɾ��λ���Ƿ�Ϊβ���������������������ɾ��
		if (pos != end()) {
			//�õ�ɾ��λ�õ�ǰһ�����
			pNode tmp = pos._node->_prev;
			//ɾ���ڵ��ǰһ���ڵ��nextָ��ָ��ɾ���ڵ����һ���ڵ�
			tmp->_next = pos._node->_next;
			//ɾ���ڵ����һ���ڵ��prevָ��ɾ���ڵ��ǰһ���ڵ�
			pos._node->_next->_prev = tmp;
			//ɾ����ǰ�ڵ�
			delete pos._node;
			//��ǰ������ʧЧ��������һ���ڵ�ĵ�����
			return iterator(tmp->_next)
		}
		//�����β����������ô��ֱ�ӷ����Լ�
		return pos;
	}
	//ͷɾ�ӿ�
	void pop_front() {
		erase(begin());
	}
	//βɾ�ӿ�
	void pop_back() {
		erase(--end());
	}
	//clear ��ս��ӿ�
	void clear() {
		//�õ���һ����Ч���
		pNode node = _header->_next;
		//ѭ��ɾ�����������������ٴ��ߵ�ͷ���
		while (node != _header) {
			//�ȱ��浱ǰ�ڵ�
			pNode tmp = node;
			//�ߵ���һ���ڵ�
			node = node->_next;
			//ɾ����ǰ�ڵ�
			delete tmp;
		}
		//���ͷ�����Ϊѭ��
		_header->_next = _header->_prev = _header;
	}
private:
	pNode _header;
};

int main() {

	return 0;
}