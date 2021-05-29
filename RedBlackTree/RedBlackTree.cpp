#include<iostream>
using namespace std;

enum COLOR {
	BLACK,
	RED
};

//红黑树结点
template<class V>
struct RBNode {
	//指向父节点的指针
	RBNode* _parent;
	//指向左孩子节点的指针
	RBNode* _left;
	//指向右孩子节点的指针
	RBNode* _right;
	//节点的颜色
	COLOR _color;
	//数据
	V _val;
	//节点的构造函数
	RBNode(const V& val = V())
		:_parent(nullptr)
		,_left(nullptr)
		,_right(nullptr)
		,_color(RED)
		,_val(val)
	{}
};

//封装红黑树的迭代器
template<class V>
struct RBTreeIterator {
	typedef RBNode<V> Node;
	typedef RBTreeIterator<V> Self;
	//成员变量：红黑树结点
	Node* _node;
	//构造函数
	RBTreeIterator(Node* node)
		:_node(node)
	{}
	//重载 * 运算符
	V& operator*() {
		return _node->_val;
	}
	//重载 -> 运算符
	V* operator->() {
		return &(_node->_val);
	}
	//重载 != 运算符
	bool operator!=(const Self& it) {
		return _node != it._node;
	}
	//重载前置 ++ 运算符
	Self& operator++() {
		//如果当前迭代器的节点有右子树，那么迭代器就更新到到右子树的最左节点
		if (_node->_right) {
			_node = _node->_right;
			while (_node->_left)
				_node = _node->_left;
		}
		//如果没有右子树，则分两种情况
		//如果当前节点是父节点的左孩子，那么直接将迭代器更新到父节点位置
		//如果当前节点是父节点的右孩子，那么就将当前节点更新到父结点位置，父结点更新到祖父节点的位置，继续循环判断
		else {
			//拿到当前节点的父结点
			Node* parent = _node->_parent;
			//循环判断是否在右边
			while (parent->_right = _node) {
				_node = parent;
				parent = _node->_parent;
			}
			//避免该树没有右子树的情况，因为迭代器的结束条件就是走到头结点位置
			//如果该树没有右子树，那么就会在根结点与头结点之间死循环
			if (_node->_right != parent)
				_node = parent;
		}
		return *this;
	}
	Self& operator--() {
		//如果当前迭代器的节点有左子树，那么迭代器就更新到到左子树的最右节点
		if (_node->_left) {
			_node = _node->_left;
			while (_node->_right)
				_node = _node->_right;
		}
		//如果没有左子树，则分两种情况
		//如果当前节点是父节点的右孩子，那么直接将迭代器更新到父节点位置
		//如果当前节点是父节点的左孩子，那么就将当前节点更新到父结点位置，父结点更新到祖父节点的位置，继续循环判断
		else {
			//拿到父结点
			Node* parent = _node->_parent;
			//循环判断
			while (parent->_left == _node) {
				_node = parent;
				parent = _node->_parent;
			}
			//避免该树没有左子树的情况，因为迭代器的结束条件就是走到头结点位置
			//如果该树没有左子树，那么就会在根结点与头结点之间死循环
			if (_node->_left != parent)
				_node = parent;
		}
		return *this;
	}
};

//红黑树
template<class K, class V, class keyofval>
class RBTree {
public:
	typedef RBNode<V> Node;
	typedef RBTreeIterator<V> iterator;
	//构造函数
	RBTree()
		//创建一个空的头结点
		:_header(new Node)
	{
		_header->_left = _header->_right = _header;
	}
	//迭代器
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
	//插入操作
	pair<iterator, bool> insert(const V& val) {
		//如果是一个空红黑树，那么就直接插入数据
		if (_header->_parent == nullptr) {
			//直接插入数据
			Node* root = new Node(val);
			//建立连接
			root->_parent = _header;
			_header->_parent = _header->_left = _header->_right = root;
			root->_color = BLACK;
			return make_pair(iterator(_header->_parent), true);
		}
		//仿函数：用来获取存储数据所需要的比较数据——key，这个由上层（map/set等）提供
		keyofval kov;
		//开始搜索待插入数据
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
		//找到位置后开始进行插入,并建立链接
		cur = new Node(val);
		if (kov(parent->_val) > kov(cur))
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;
		Node* tmp = cur;
		//向上判断当前节点与父结点的颜色是否符合
		while (cur->_color == RED && cur->_parent->_color == RED) {
			parent = cur->_parent;
			//先拿到祖父节点
			Node* gfather = parent->_parent;
			//分情况讨论，如果父节点是祖父节点的左子树
			if (gfather->_left == parent) {
				//此时判断叔叔结点是否存在
				Node* uncle = gfather->_right;
				//如果存在则进行下面的调整
				if (uncle && uncle->_color == RED) {
					//将父结点和叔叔结点的颜色改为黑色
					parent->_color = uncle->_color = BLACK;
					//将祖父节点的颜色改为红色
					gfather->_color = RED;
					//由于祖父节点被变为红色，所以有可能引发潜在问题，所以继续向上
					cur = gfather;
				}
				//如果叔叔节点不存在或者叔叔结点是黑色的
				else {
					//判断是否需要双旋，双旋条件：父亲是祖父的左节点，当前节点是父亲的右结点
					if (parent->_right == cur) {
						//父结点先进行左旋
						RotateL(parent);
						//此时cur、parent的指向是反的，所以需要交换
						swap(cur, parent);
					}
					//此时再对祖父节点进行右旋
					RotaleR(gfather);
					//再修改节点的颜色
					parent->_color = BLACK;
					gfather->_color = RED;
					break;
				}
			}
			//分情况讨论，如果父节点是祖父节点的右子树
			else{
				//此时判断叔叔结点是否存在
				Node* uncle = gfather->_right;
				//如果存在则进行下面的调整
				if (uncle && uncle->_color == RED) {
					//将父结点和叔叔结点的颜色改为黑色
					parent->_color = uncle->_color = BLACK;
					//将祖父节点的颜色改为红色
					gfather->_color = RED;
					//由于祖父节点被变为红色，所以有可能引发潜在问题，所以继续向上
					cur = gfather;
				}
				//如果叔叔节点不存在或者叔叔结点是黑色的
				else {
					//判断是否需要双旋，双旋条件：父亲是祖父的右节点，当前节点是父亲的左结点
					if (parent->_left == cur) {
						//父结点先进行右旋
						RotateR(parent);
						//此时cur、parent的指向是反的，所以需要交换
						swap(cur, parent);
					}
					//此时再对祖父节点进行左旋
					RotaleL(gfather);
					//再修改节点的颜色
					parent->_color = BLACK;
					gfather->_color = RED;
					break;
				}
			}
		}
		//调整完成后，在调整的过程中可能会改变根节点的颜色，所以改回黑色就好
		_header->_parent->_color = BLACK;
		//并且修改头结点的左右指针的指向
		_header->_left = LeftMost();
		_header->_right = RightMost();
		return make_pair(iterator(tmp), true);
	}
	//检测该红黑树是否满足红黑树的左右性质
	bool isBalance() {
		//如果是空树，这就是红黑树
		if (_header->_parent == nullptr)
			return true;
		//如果跟是红色，则不是红黑树
		if (_header->_parent->_color == RED)
			return false;
		//接下来判断是否有连续红色以及每条路径的黑色结点个数
		int count = 0, num = 0;
		Node* cur = _header->_parent;
		while (cur) {
			if (cur->_color == BLACK)
				num++;
			cur = cur->_left;
		}
		return _isBalance(_header->_parent, count, num);
	}
	//中序遍历
	void inorder() {
		_inorder(_header->_parent);
		cout << endl;
	}
private:
	//左旋操作
	void RotateL(Node* cur) {
		//获取要旋转节点的右孩子curR
		Node* curR = cur->_right;
		//获取右孩子curR的左孩子curRL
		Node* curRL = curR->_left;
		//开始建立指针连接
		cur->_right = curRL;
		curR->_left = cur;
		if (curRL)
			curRL->_parent = cur;
		//如果要旋转结点是根结点，特殊处理
		if (cur == _header->_parent) {
			_header->_parent = curR;
			curR->_parent = _header;
		}
		//不是根节点则正常处理
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
	//右旋操作
	void RotateR(Node* cur) {
		//获取要旋转节点的左孩子curL
		Node* curL = cur->_left;
		//获取左孩子curL的右孩子curLR
		Node* curLR = curL->_right;
		//开始建立指针连接
		cur->_left = curLR;
		curL->_right = cur;
		if (curLR)
			curLR->_parent = cur;
		//如果要旋转结点是根结点，特殊处理
		if (cur == _header->_parent) {
			_header->_parent = curL;
			curL->_parent = _header;
		}
		//不是根节点则正常处理
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
	//获取最左节点
	Node* LeftMost() {
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;
		return cur;
	}
	//获取最右节点
	Node* RightMost() {
		Node* cur = _header->_parent;
		while (cur && cur->_right)
			cur = cur->_right;
		return cur;
	}
	//递归判断是否为红黑树
	bool _isBalance(Node* node, int count, int num) {
		//当走到空节点时，判断黑色结点个数是否与确定的一样
		if (node == nullptr)
			return count == num;
		//判断是否出现连续的红色结点
		if (node->_parent && node->_color == RED && node->_parent->_color == RED)
			return false;
		//计数一条路径上黑色节点的个数
		if (node->_color == BLACK)
			count++;
		//同时判断左右子树是否也满足
		return _isBalance(node->_left, count, num)
			&& _isBalance(node->_right, count, num);
	}
	//中序遍历
	void _inorder(Node* root) {
		if (root) {
			_inorder(root->_left);
			cout << root->_val << ' ';
			_inorder(root->_right);
		}
	}
	Node* _header;
};


//利用红黑树来简单实现map
template<class K, class V>
class Map {
	struct keyofval {
		const K& operator()(const pair<K, V>& val) {
			return val.first;
		}
	};
	RBTree<K, pair<K, V>, keyofval> rbt;
public:
	//因为这是未实例化的类的迭代器，所以编译器识别不了，因此需要加上一个typename，告诉编译器这个类可以延迟确定，所以这个迭代器可以使用
	typedef typename RBTree<K, pair<K, V>, keyofval>::iterator iterator;
	pair<iterator, bool> insert(const pair<K, V>& kv) {
		return rbt.insert(kv);
	}
	//Map的迭代器
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
		//方括号的作用是：先插入一个默认值的键值对，成功与失败都返回一个迭代器，该迭代器指向了键值为key的结点
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