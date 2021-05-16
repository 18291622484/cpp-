#include<iostream>
using namespace std;

template<class T>
struct BSNode{
	//数据节点的构造函数
	BSNode(const T& data)
		:_data(data)
		,_left(nullptr)
		,_right(nullptr)
	{}
	//存放的数据
	T _data;
	//指向节点的左孩子
	BSNode<T>* _left;
	//指向节点的右孩子
	BSNode<T>* _right;
};

template<class T>
class BSTree {
public:
	typedef BSNode<T> Node;
	//构造函数
	BSTree()
		:root(nullptr)
	{}
	//析构函数
	~BSTree() {
		if (root) {
			//调用销毁二叉搜索树的函数
			destory(root);
			root = nullptr;
		}
	}
	//复制一份二叉搜索树
	Node* copy(Node* root) {
		//走到空的结点则递归返回
		if (root == nullptr)
			return nullptr;
		//否则就复制当前节点
		Node* idx = new Node(root->_data);
		//复制当前节点的左孩子
		idx->_left = copy(root->_left);
		//复制当前节点的右孩子
		idx->_right = copy(root->_right);
		return idx;
	}
	//拷贝构造
	BSTree(const BSTree<T>& tree)
		:root(copy(tree->root))
	{}
	//查找结点
	Node* find(const T& val) {
		Node* idx = root;
		//循环遍历查找
		while (idx) {
			//如果结点值等于要查找的值，那么返回结点
			if (idx->_data == val)
				return idx;
			//如果结点值大于要查找的值，则走向左孩子查找
			else if (idx->_data > val)
				idx = idx->_left;
			//如果结点值小于要查找的值，则走向右孩子查找
			else
				idx = idx->_right;
		}
	}
	//插入一个结点
	bool insert(const T& val) {
		//如果是空树，则插入到根节点
		if (root == nullptr) {
			root = new Node(val);
			return true;
		}
		//接线来就是循环遍历树，找到一个合适的位置
		//为找到合适的位置的父结点
		Node* tmp = root;
		//为找到的合适位置
		Node* idx = root;
		while (idx) {
			tmp = idx;
			if (idx->_data == val)
				return false;
			else if (idx->_data > val)
				idx = idx->_left;
			else
				idx = idx->_right;
		}
		//找到位置后判断是要插入到左边还是右边
		idx = new Node(val);
		if (tmp->_data > val)
			tmp->_left = idx;
		else
			tmp->_right = idx;
		return true;
	}
	//将二叉搜索树有序打印出来
	void inorder() {
		_inorder(root);
		cout << endl;
	}
	//删除节点
	bool erase(const T& val) {
		//在树中找到要删除的结点
		Node* cur = root;
		Node* parent = root;
		//循环遍历树，找到要删除的结点，并且保存该节点的父结点
		while (cur) {
			if (cur->_data == val)
				break;
			parent = cur;
			if (cur->_data > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		//是否找到要删除节点，没找到则返回失败
		if (cur == nullptr)
			return false;
		//要删除的结点没有左孩子的情况
		if (cur->_left == nullptr) {
			//删除节点为根结点
			if(cur == root){}
			else if (parent->_left == cur)
				parent->_left = cur->_right;
			else
				parent->_right = cur->_right;
			delete cur;
			cur = nullptr;
		}
		//要删除结点没有右孩子的情况
		else if (cur->right == nullptr) {
			//删除节点为根结点
			if (cur == root) {}
			else if(parent->left == cur)
				parent->left = cur->left;
			else
				parent->right = cur->left;
			delete cur;
			cur = nullptr;
		}
		//要删除节点左右孩子都存在
		else {
			//先保留要删除的结点
			Node* _root = cur;
			//然后开始找删除节点左子树中的最右节点
			parent = cur;
			cur = cur->_left;
			while (cur->_right) {
				parent = cur;
				cur = cur->_right;
			}
			//找到最右节点后交换最右节点与要删除节点的值，此时最右节点就是要删除的节点了
			swap(_root->_data, cur->_data);
			//然后判断删除节点是左孩子还是右孩子
			if (parent->_left == cur)
				//将删除节点的左子树赋给父节点的左边
				parent->_left = cur->_left;
			else
				//将删除节点的左子树赋给父节点的右边
				parent->_right = cur->_left;
			delete cur;
		}
		return true;
	}
private:
	//二叉搜索树中序遍历，此遍历结果是有序的
	void _inordef(Node* root) {
		if (root) {
			//先遍历左孩子，再遍历当前节点，最后遍历右孩子
			_inorder(root->_left);
			cout << root->_data << " ";
			_inorder(root->_right);
		}
	}
	//销毁二叉树
	void destory(Node* root) {
		if (root) {
			//删除左右孩子之后，再删除根结点
			destory(root->_left);
			destory(root->_right);
			delete root;
		}
	}
	Node* root;
};

int main() {

	return 0;
}