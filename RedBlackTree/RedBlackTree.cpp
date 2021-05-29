#include<iostream>
using namespace std;

enum COLOR {
	BLACK,
	RED
};

//��������
template<class V>
struct RBNode {
	//ָ�򸸽ڵ��ָ��
	RBNode* _parent;
	//ָ�����ӽڵ��ָ��
	RBNode* _left;
	//ָ���Һ��ӽڵ��ָ��
	RBNode* _right;
	//�ڵ����ɫ
	COLOR _color;
	//����
	V _val;
	//�ڵ�Ĺ��캯��
	RBNode(const V& val = V())
		:_parent(nullptr)
		,_left(nullptr)
		,_right(nullptr)
		,_color(RED)
		,_val(val)
	{}
};

//��װ������ĵ�����
template<class V>
struct RBTreeIterator {
	typedef RBNode<V> Node;
	typedef RBTreeIterator<V> Self;
	//��Ա��������������
	Node* _node;
	//���캯��
	RBTreeIterator(Node* node)
		:_node(node)
	{}
	//���� * �����
	V& operator*() {
		return _node->_val;
	}
	//���� -> �����
	V* operator->() {
		return &(_node->_val);
	}
	//���� != �����
	bool operator!=(const Self& it) {
		return _node != it._node;
	}
	//����ǰ�� ++ �����
	Self& operator++() {
		//�����ǰ�������Ľڵ�������������ô�������͸��µ���������������ڵ�
		if (_node->_right) {
			_node = _node->_right;
			while (_node->_left)
				_node = _node->_left;
		}
		//���û��������������������
		//�����ǰ�ڵ��Ǹ��ڵ�����ӣ���ôֱ�ӽ����������µ����ڵ�λ��
		//�����ǰ�ڵ��Ǹ��ڵ���Һ��ӣ���ô�ͽ���ǰ�ڵ���µ������λ�ã��������µ��游�ڵ��λ�ã�����ѭ���ж�
		else {
			//�õ���ǰ�ڵ�ĸ����
			Node* parent = _node->_parent;
			//ѭ���ж��Ƿ����ұ�
			while (parent->_right = _node) {
				_node = parent;
				parent = _node->_parent;
			}
			//�������û�����������������Ϊ�������Ľ������������ߵ�ͷ���λ��
			//�������û������������ô�ͻ��ڸ������ͷ���֮����ѭ��
			if (_node->_right != parent)
				_node = parent;
		}
		return *this;
	}
	Self& operator--() {
		//�����ǰ�������Ľڵ�������������ô�������͸��µ��������������ҽڵ�
		if (_node->_left) {
			_node = _node->_left;
			while (_node->_right)
				_node = _node->_right;
		}
		//���û��������������������
		//�����ǰ�ڵ��Ǹ��ڵ���Һ��ӣ���ôֱ�ӽ����������µ����ڵ�λ��
		//�����ǰ�ڵ��Ǹ��ڵ�����ӣ���ô�ͽ���ǰ�ڵ���µ������λ�ã��������µ��游�ڵ��λ�ã�����ѭ���ж�
		else {
			//�õ������
			Node* parent = _node->_parent;
			//ѭ���ж�
			while (parent->_left == _node) {
				_node = parent;
				parent = _node->_parent;
			}
			//�������û�����������������Ϊ�������Ľ������������ߵ�ͷ���λ��
			//�������û������������ô�ͻ��ڸ������ͷ���֮����ѭ��
			if (_node->_left != parent)
				_node = parent;
		}
		return *this;
	}
};

//�����
template<class K, class V, class keyofval>
class RBTree {
public:
	typedef RBNode<V> Node;
	typedef RBTreeIterator<V> iterator;
	//���캯��
	RBTree()
		//����һ���յ�ͷ���
		:_header(new Node)
	{
		_header->_left = _header->_right = _header;
	}
	//������
	iterator begin() {
		return iterator(_header->_left);
	}
	iterator end() {
		return iterator(_header);
	}
	iterator rbegin() {
		return iterator(_header->_right);
	}
	iterator rend() {
		return iterator(_header);
	}
	//�������
	pair<iterator, bool> insert(const V& val) {
		//�����һ���պ��������ô��ֱ�Ӳ�������
		if (_header->_parent == nullptr) {
			//ֱ�Ӳ�������
			Node* root = new Node(val);
			//��������
			root->_parent = _header;
			_header->_parent = _header->_left = _header->_right = root;
			root->_color = BLACK;
			return make_pair(iterator(_header->_parent), true);
		}
		//�º�����������ȡ�洢��������Ҫ�ıȽ����ݡ���key��������ϲ㣨map/set�ȣ��ṩ
		keyofval kov;
		//��ʼ��������������
		Node* parent = nullptr;
		Node* cur = _header->_parent;
		while (cur) {
			parent = cur;
			if (kov(cur->_val) == kov(val))
				return make_pair(iterator(cur), false);
			else if (kov(cur->_val) > kov(val))
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		//�ҵ�λ�ú�ʼ���в���,����������
		cur = new Node(val);
		if (kov(parent->_val) > kov(cur))
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;
		Node* tmp = cur;
		//�����жϵ�ǰ�ڵ��븸������ɫ�Ƿ����
		while (cur->_color == RED && cur->_parent->_color == RED) {
			parent = cur->_parent;
			//���õ��游�ڵ�
			Node* gfather = parent->_parent;
			//��������ۣ�������ڵ����游�ڵ��������
			if (gfather->_left == parent) {
				//��ʱ�ж��������Ƿ����
				Node* uncle = gfather->_right;
				//����������������ĵ���
				if (uncle && uncle->_color == RED) {
					//�����������������ɫ��Ϊ��ɫ
					parent->_color = uncle->_color = BLACK;
					//���游�ڵ����ɫ��Ϊ��ɫ
					gfather->_color = RED;
					//�����游�ڵ㱻��Ϊ��ɫ�������п�������Ǳ�����⣬���Լ�������
					cur = gfather;
				}
				//�������ڵ㲻���ڻ����������Ǻ�ɫ��
				else {
					//�ж��Ƿ���Ҫ˫����˫���������������游����ڵ㣬��ǰ�ڵ��Ǹ��׵��ҽ��
					if (parent->_right == cur) {
						//������Ƚ�������
						RotateL(parent);
						//��ʱcur��parent��ָ���Ƿ��ģ�������Ҫ����
						swap(cur, parent);
					}
					//��ʱ�ٶ��游�ڵ��������
					RotaleR(gfather);
					//���޸Ľڵ����ɫ
					parent->_color = BLACK;
					gfather->_color = RED;
					break;
				}
			}
			//��������ۣ�������ڵ����游�ڵ��������
			else{
				//��ʱ�ж��������Ƿ����
				Node* uncle = gfather->_right;
				//����������������ĵ���
				if (uncle && uncle->_color == RED) {
					//�����������������ɫ��Ϊ��ɫ
					parent->_color = uncle->_color = BLACK;
					//���游�ڵ����ɫ��Ϊ��ɫ
					gfather->_color = RED;
					//�����游�ڵ㱻��Ϊ��ɫ�������п�������Ǳ�����⣬���Լ�������
					cur = gfather;
				}
				//�������ڵ㲻���ڻ����������Ǻ�ɫ��
				else {
					//�ж��Ƿ���Ҫ˫����˫���������������游���ҽڵ㣬��ǰ�ڵ��Ǹ��׵�����
					if (parent->_left == cur) {
						//������Ƚ�������
						RotateR(parent);
						//��ʱcur��parent��ָ���Ƿ��ģ�������Ҫ����
						swap(cur, parent);
					}
					//��ʱ�ٶ��游�ڵ��������
					RotaleL(gfather);
					//���޸Ľڵ����ɫ
					parent->_color = BLACK;
					gfather->_color = RED;
					break;
				}
			}
		}
		//������ɺ��ڵ����Ĺ����п��ܻ�ı���ڵ����ɫ�����ԸĻغ�ɫ�ͺ�
		_header->_parent->_color = BLACK;
		//�����޸�ͷ��������ָ���ָ��
		_header->_left = LeftMost();
		_header->_right = RightMost();
		return make_pair(iterator(tmp), true);
	}
	//���ú�����Ƿ�������������������
	bool isBalance() {
		//����ǿ���������Ǻ����
		if (_header->_parent == nullptr)
			return true;
		//������Ǻ�ɫ�����Ǻ����
		if (_header->_parent->_color == RED)
			return false;
		//�������ж��Ƿ���������ɫ�Լ�ÿ��·���ĺ�ɫ������
		int count = 0, num = 0;
		Node* cur = _header->_parent;
		while (cur) {
			if (cur->_color == BLACK)
				num++;
			cur = cur->_left;
		}
		return _isBalance(_header->_parent, count, num);
	}
	//�������
	void inorder() {
		_inorder(_header->_parent);
		cout << endl;
	}
private:
	//��������
	void RotateL(Node* cur) {
		//��ȡҪ��ת�ڵ���Һ���curR
		Node* curR = cur->_right;
		//��ȡ�Һ���curR������curRL
		Node* curRL = curR->_left;
		//��ʼ����ָ������
		cur->_right = curRL;
		curR->_left = cur;
		if (curRL)
			curRL->_parent = cur;
		//���Ҫ��ת����Ǹ���㣬���⴦��
		if (cur == _header->_parent) {
			_header->_parent = curR;
			curR->_parent = _header;
		}
		//���Ǹ��ڵ�����������
		else {
			Node* node = cur->_parent;
			curR->_parent = node;
			if (node->_left == cur)
				node->_left = curR;
			else
				node->_right = curR;
		}
		cur->_parent = curR;
	}
	//��������
	void RotateR(Node* cur) {
		//��ȡҪ��ת�ڵ������curL
		Node* curL = cur->_left;
		//��ȡ����curL���Һ���curLR
		Node* curLR = curL->_right;
		//��ʼ����ָ������
		cur->_left = curLR;
		curL->_right = cur;
		if (curLR)
			curLR->_parent = cur;
		//���Ҫ��ת����Ǹ���㣬���⴦��
		if (cur == _header->_parent) {
			_header->_parent = curL;
			curL->_parent = _header;
		}
		//���Ǹ��ڵ�����������
		else {
			Node* node = cur->_parent;
			curL->_parent = node;
			if (node->_left == cur)
				node->_left = curL;
			else
				node->_right = curL;
		}
		cur->_parent = curL;
	}
	//��ȡ����ڵ�
	Node* LeftMost() {
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;
		return cur;
	}
	//��ȡ���ҽڵ�
	Node* RightMost() {
		Node* cur = _header->_parent;
		while (cur && cur->_right)
			cur = cur->_right;
		return cur;
	}
	//�ݹ��ж��Ƿ�Ϊ�����
	bool _isBalance(Node* node, int count, int num) {
		//���ߵ��սڵ�ʱ���жϺ�ɫ�������Ƿ���ȷ����һ��
		if (node == nullptr)
			return count == num;
		//�ж��Ƿ���������ĺ�ɫ���
		if (node->_parent && node->_color == RED && node->_parent->_color == RED)
			return false;
		//����һ��·���Ϻ�ɫ�ڵ�ĸ���
		if (node->_color == BLACK)
			count++;
		//ͬʱ�ж����������Ƿ�Ҳ����
		return _isBalance(node->_left, count, num)
			&& _isBalance(node->_right, count, num);
	}
	//�������
	void _inorder(Node* root) {
		if (root) {
			_inorder(root->_left);
			cout << root->_val << ' ';
			_inorder(root->_right);
		}
	}
	Node* _header;
};


//���ú��������ʵ��map
template<class K, class V>
class Map {
	struct keyofval {
		const K& operator()(const pair<K, V>& val) {
			return val.first;
		}
	};
	RBTree<K, pair<K, V>, keyofval> rbt;
public:
	//��Ϊ����δʵ��������ĵ����������Ա�����ʶ���ˣ������Ҫ����һ��typename�����߱��������������ӳ�ȷ���������������������ʹ��
	typedef typename RBTree<K, pair<K, V>, keyofval>::iterator iterator;
	pair<iterator, bool> insert(const pair<K, V>& kv) {
		return rbt.insert(kv);
	}
	//Map�ĵ�����
	iterator begin() {
		return rbt.begin();
	}
	iterator end() {
		return rbt.end();
	}
	iterator rbegin() {
		return rbt.rbegin();
	}
	iterator rend() {
		rbt.rend();
	}
	V& operator[](const K& key) {
		//�����ŵ������ǣ��Ȳ���һ��Ĭ��ֵ�ļ�ֵ�ԣ��ɹ���ʧ�ܶ�����һ�����������õ�����ָ���˼�ֵΪkey�Ľ��
		pair<iterator, bool> ret = rbt.insert(make_pair(key, V()));
		return ret.first->second;
	}
};

template<class V>
class Set {
	struct keyofval {
		const V& operator()(const V& key) {
			return key;
		}
	};
	RBTree<V, V, keyofval> rbt;
public:
	typedef typename RBTree<V, V, keyofval>::iterator iterator;
	pair<iterator, bool> insert(const V& val) {
		return rbt.insert(val);
	}
};

int main() {
	
	return 0;
}