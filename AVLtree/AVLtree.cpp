#include<iostream>
using namespace std;

template<class T>
struct AVLNode {
	//数据
	T _data;
	//平衡因子
	int _bf;
	//左孩子指针
	AVLNode* _left;
	//右孩子指针
	AVLNode* _right;
	//父结点指针
	AVLNode* _parent;
	//带参构造函数
	AVLNode(const T& val = T())
		:_parent(nullptr)
		,_left(nullptr)
		,_right(nullptr)
		,_data(val)
		,_bf(0)
	{}
};

template<class T>
class AVLTree {
public:
	typedef AVLNode<T> Node;
	//构造函数
	AVLTree()
		:_root(nullptr)
	{}
	//左旋操作
	void RotateL(Node* parent) {
		//先拿到要旋转节点的右孩子
		Node* node = parent->_right;
		//再拿到要旋转节点的右孩子的左节点
		Node* nodeleft = node->_left;
		//进行重新链接
		parent->_right = nodeleft;
		if(nodeleft)
			nodeleft->_parent = parent;
		//如果要旋转的节点是根结点，那么需要额外考虑
		if (parent == _root) {
			_root = node;
			node->_parent = nullptr;
		}
		//如果不是根结点那么则正常调整
		else {
			Node* tmp = parent->_parent;
			node->_parent = tmp;
			if (tmp->_left == parent)
				tmp->_left = node;
			else
				tmp->_right = node;
		}
		parent->_parent = node;
		node->_left = parent;
		//调整平衡因子
		parent->_bf = node->_bf = 0;
	}
	//右旋操作
	void RotateR(Node* parent) {
		//先拿到要旋转节点的左孩子
		Node* node = parent->_left;
		//再拿到要旋转节点的左孩子的右节点
		Node* noderight = node->_right;
		//接着调整链接
		parent->_left = noderight;
		if (noderight)
			noderight->_parent = parent;
		//如果要旋转的节点是根结点，则需要额外考虑
		if (parent == _root) {
			_root = node;
			node->_parent = nullptr;
		}
		//如果不是则正常调整
		else {
			Node* tmp = parent->_parent;
			node->_parent = tmp;
			if (tmp->_left = parent)
				tmp->_left = node;
			else
				tmp->_right = node;
		}
		parent->_parent = node;
		node->_right = parent;
		//调整平衡因子
		parent->_bf = node->_bf = 0;
	}
	//数据插入
	bool insert(const T& val) {
		//如果当前树的为空树，那么直接将结点插入
		if (_root == nullptr) {
			_root = new Node(val);
			return true;
		}
		//否则就先先找到一个合适的位置（二叉搜索树的查找一样），然后插入
		Node* parent = nullptr;
		Node* node = _root;
		while (node) {
			parent = node;
			if (node->_data == val)
				return false;
			else if (node->_data > val)
				node = node->_left;
			else
				node = node->_right;
		}
		//找到合适的位置后，将结点插入，并且将指针链接起来
		node = new Node(val);
		if (parent->_data > val)
			parent->_left = node;
		else
			parent->_right = node;
		node->_parent = parent;
		//插入结点后开始调整平衡因子
		while (parent) {
			//更新父节点的平衡因子
			if (parent->_left == node)
				parent->_bf--;
			else
				parent->_bf++;
			//检查平衡因子的变化情况
			if (parent->_bf == 0)
				//如果变为0，则说明无影响
				break;
			else if (parent->_bf == -1 || parent->_bf == 1) {
				//继续向上检查平衡因子
				node = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) {
				if (parent->_bf == -2 && node->_bf == -1)
					//此时需要进行右旋调整
					RotateR(parent);
				else if(parent->_bf == 2 && node->_bf == 1)
					//此时需要进行左旋调整
					RotateL(parent);
				else if (parent->_bf == -2 && node->_bf == 1) {
					//先保存当前节点的右子树的平衡因子
					int bf = node->_right->_bf;
					//以当前节点先进行左旋，再以父结点进行右旋
					RotateL(node);
					RotateR(node);
					//修正平衡因子
					if (bf == -1) {
						parent->_bf = 1;
						node->_bf = 0;
					}
					else if (bf == 1) {
						parent->_bf = 0;
						node->_bf = -1;
					}
				}
				else if (parent->_bf == 2 && node->_bf == -1) {
					//先保存当前节点的左子树的平衡因子
					int bf = node->_left->_bf;
					//以当前节点先进行右旋，再以父结点进行左旋
					RotateR(node);
					RotateL(node);
					//修正平衡因子
					if (bf == -1) {
						parent->_bf = 0;
						node->_bf = 1;
					}
					else if(bf == 1) {
						parent->_bf = -1;
						node->_bf = 0;
					}
				}
				//调整完毕，结束循环
				break;
			}
		}
		return true;
	}
	//中序遍历
	void inorder() {
		_inorder(_root);
		cout << endl;
	}
	//检查左右子树高度差与平衡因子是否相同
	bool isBalance(Node* root) {
		//如果是空树则返回真
		if (root == nullptr)
			return true;
		//拿到左右子树高度
		int left = High(root->_left);
		int right = High(root->right);
		//判断左右子树高度差是否等于平衡因子
		if (right - left == root->_bf)
			return false;
		//返回当前节点的平衡因子是否小于2，并且左右子树是否满足
		return abs(root->_bf) < 2 && isBalance(root->left) && isBalance(root->right);
	}
	//获取树的高度
	int High(Node* root) {
		if (root == nullptr)
			return 0;
		//树的高度是左右子树中较高的那一个
		int left = High(root->_left);
		int right = High(root->_right);
		return left > right ? left + 1 : right + 1;
	}

	//删除节点：先按照二叉搜索树删除节点的方法进行删除，删除掉之后调整平衡因子
	//删除之后父节点的平衡因子变为 -1 或者 1，则说明不需要进行调整
	//删除时候父结点的平衡因子变为 0，那么需要向上继续调整，直到遇到第一个 -2 或者 2，然后开始旋转调整
private:
	//二叉树的中序遍历
	void _inorder(Node* root) {
		if (root == nullptr)
			return;
		_inorder(root->_left);
		cout << root->_data << " ";
		_inorder(root->_right);
	}
	Node* _root;
};

int main() {

	return 0;
}