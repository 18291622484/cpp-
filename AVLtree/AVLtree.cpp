#include<iostream>
using namespace std;

template<class T>
struct AVLNode {
	//����
	T _data;
	//ƽ������
	int _bf;
	//����ָ��
	AVLNode* _left;
	//�Һ���ָ��
	AVLNode* _right;
	//�����ָ��
	AVLNode* _parent;
	//���ι��캯��
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
	//���캯��
	AVLTree()
		:_root(nullptr)
	{}
	//��������
	void RotateL(Node* parent) {
		//���õ�Ҫ��ת�ڵ���Һ���
		Node* node = parent->_right;
		//���õ�Ҫ��ת�ڵ���Һ��ӵ���ڵ�
		Node* nodeleft = node->_left;
		//������������
		parent->_right = nodeleft;
		if(nodeleft)
			nodeleft->_parent = parent;
		//���Ҫ��ת�Ľڵ��Ǹ���㣬��ô��Ҫ���⿼��
		if (parent == _root) {
			_root = node;
			node->_parent = nullptr;
		}
		//������Ǹ������ô����������
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
		//����ƽ������
		parent->_bf = node->_bf = 0;
	}
	//��������
	void RotateR(Node* parent) {
		//���õ�Ҫ��ת�ڵ������
		Node* node = parent->_left;
		//���õ�Ҫ��ת�ڵ�����ӵ��ҽڵ�
		Node* noderight = node->_right;
		//���ŵ�������
		parent->_left = noderight;
		if (noderight)
			noderight->_parent = parent;
		//���Ҫ��ת�Ľڵ��Ǹ���㣬����Ҫ���⿼��
		if (parent == _root) {
			_root = node;
			node->_parent = nullptr;
		}
		//�����������������
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
		//����ƽ������
		parent->_bf = node->_bf = 0;
	}
	//���ݲ���
	bool insert(const T& val) {
		//�����ǰ����Ϊ��������ôֱ�ӽ�������
		if (_root == nullptr) {
			_root = new Node(val);
			return true;
		}
		//����������ҵ�һ�����ʵ�λ�ã������������Ĳ���һ������Ȼ�����
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
		//�ҵ����ʵ�λ�ú󣬽������룬���ҽ�ָ����������
		node = new Node(val);
		if (parent->_data > val)
			parent->_left = node;
		else
			parent->_right = node;
		node->_parent = parent;
		//�������ʼ����ƽ������
		while (parent) {
			//���¸��ڵ��ƽ������
			if (parent->_left == node)
				parent->_bf--;
			else
				parent->_bf++;
			//���ƽ�����ӵı仯���
			if (parent->_bf == 0)
				//�����Ϊ0����˵����Ӱ��
				break;
			else if (parent->_bf == -1 || parent->_bf == 1) {
				//�������ϼ��ƽ������
				node = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) {
				if (parent->_bf == -2 && node->_bf == -1)
					//��ʱ��Ҫ������������
					RotateR(parent);
				else if(parent->_bf == 2 && node->_bf == 1)
					//��ʱ��Ҫ������������
					RotateL(parent);
				else if (parent->_bf == -2 && node->_bf == 1) {
					//�ȱ��浱ǰ�ڵ����������ƽ������
					int bf = node->_right->_bf;
					//�Ե�ǰ�ڵ��Ƚ������������Ը�����������
					RotateL(node);
					RotateR(node);
					//����ƽ������
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
					//�ȱ��浱ǰ�ڵ����������ƽ������
					int bf = node->_left->_bf;
					//�Ե�ǰ�ڵ��Ƚ������������Ը�����������
					RotateR(node);
					RotateL(node);
					//����ƽ������
					if (bf == -1) {
						parent->_bf = 0;
						node->_bf = 1;
					}
					else if(bf == 1) {
						parent->_bf = -1;
						node->_bf = 0;
					}
				}
				//������ϣ�����ѭ��
				break;
			}
		}
		return true;
	}
	//�������
	void inorder() {
		_inorder(_root);
		cout << endl;
	}
	//������������߶Ȳ���ƽ�������Ƿ���ͬ
	bool isBalance(Node* root) {
		//����ǿ����򷵻���
		if (root == nullptr)
			return true;
		//�õ����������߶�
		int left = High(root->_left);
		int right = High(root->right);
		//�ж����������߶Ȳ��Ƿ����ƽ������
		if (right - left == root->_bf)
			return false;
		//���ص�ǰ�ڵ��ƽ�������Ƿ�С��2���������������Ƿ�����
		return abs(root->_bf) < 2 && isBalance(root->left) && isBalance(root->right);
	}
	//��ȡ���ĸ߶�
	int High(Node* root) {
		if (root == nullptr)
			return 0;
		//���ĸ߶������������нϸߵ���һ��
		int left = High(root->_left);
		int right = High(root->_right);
		return left > right ? left + 1 : right + 1;
	}

	//ɾ���ڵ㣺�Ȱ��ն���������ɾ���ڵ�ķ�������ɾ����ɾ����֮�����ƽ������
	//ɾ��֮�󸸽ڵ��ƽ�����ӱ�Ϊ -1 ���� 1����˵������Ҫ���е���
	//ɾ��ʱ�򸸽���ƽ�����ӱ�Ϊ 0����ô��Ҫ���ϼ���������ֱ��������һ�� -2 ���� 2��Ȼ��ʼ��ת����
private:
	//���������������
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