#include<iostream>
using namespace std;

template<class T>
struct BSNode{
	//���ݽڵ�Ĺ��캯��
	BSNode(const T& data)
		:_data(data)
		,_left(nullptr)
		,_right(nullptr)
	{}
	//��ŵ�����
	T _data;
	//ָ��ڵ������
	BSNode<T>* _left;
	//ָ��ڵ���Һ���
	BSNode<T>* _right;
};

template<class T>
class BSTree {
public:
	typedef BSNode<T> Node;
	//���캯��
	BSTree()
		:root(nullptr)
	{}
	//��������
	~BSTree() {
		if (root) {
			//�������ٶ����������ĺ���
			destory(root);
			root = nullptr;
		}
	}
	//����һ�ݶ���������
	Node* copy(Node* root) {
		//�ߵ��յĽ����ݹ鷵��
		if (root == nullptr)
			return nullptr;
		//����͸��Ƶ�ǰ�ڵ�
		Node* idx = new Node(root->_data);
		//���Ƶ�ǰ�ڵ������
		idx->_left = copy(root->_left);
		//���Ƶ�ǰ�ڵ���Һ���
		idx->_right = copy(root->_right);
		return idx;
	}
	//��������
	BSTree(const BSTree<T>& tree)
		:root(copy(tree->root))
	{}
	//���ҽ��
	Node* find(const T& val) {
		Node* idx = root;
		//ѭ����������
		while (idx) {
			//������ֵ����Ҫ���ҵ�ֵ����ô���ؽ��
			if (idx->_data == val)
				return idx;
			//������ֵ����Ҫ���ҵ�ֵ�����������Ӳ���
			else if (idx->_data > val)
				idx = idx->_left;
			//������ֵС��Ҫ���ҵ�ֵ���������Һ��Ӳ���
			else
				idx = idx->_right;
		}
	}
	//����һ�����
	bool insert(const T& val) {
		//����ǿ���������뵽���ڵ�
		if (root == nullptr) {
			root = new Node(val);
			return true;
		}
		//����������ѭ�����������ҵ�һ�����ʵ�λ��
		//Ϊ�ҵ����ʵ�λ�õĸ����
		Node* tmp = root;
		//Ϊ�ҵ��ĺ���λ��
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
		//�ҵ�λ�ú��ж���Ҫ���뵽��߻����ұ�
		idx = new Node(val);
		if (tmp->_data > val)
			tmp->_left = idx;
		else
			tmp->_right = idx;
		return true;
	}
	//�����������������ӡ����
	void inorder() {
		_inorder(root);
		cout << endl;
	}
	//ɾ���ڵ�
	bool erase(const T& val) {
		//�������ҵ�Ҫɾ���Ľ��
		Node* cur = root;
		Node* parent = root;
		//ѭ�����������ҵ�Ҫɾ���Ľ�㣬���ұ���ýڵ�ĸ����
		while (cur) {
			if (cur->_data == val)
				break;
			parent = cur;
			if (cur->_data > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		//�Ƿ��ҵ�Ҫɾ���ڵ㣬û�ҵ��򷵻�ʧ��
		if (cur == nullptr)
			return false;
		//Ҫɾ���Ľ��û�����ӵ����
		if (cur->_left == nullptr) {
			//ɾ���ڵ�Ϊ�����
			if(cur == root){}
			else if (parent->_left == cur)
				parent->_left = cur->_right;
			else
				parent->_right = cur->_right;
			delete cur;
			cur = nullptr;
		}
		//Ҫɾ�����û���Һ��ӵ����
		else if (cur->right == nullptr) {
			//ɾ���ڵ�Ϊ�����
			if (cur == root) {}
			else if(parent->left == cur)
				parent->left = cur->left;
			else
				parent->right = cur->left;
			delete cur;
			cur = nullptr;
		}
		//Ҫɾ���ڵ����Һ��Ӷ�����
		else {
			//�ȱ���Ҫɾ���Ľ��
			Node* _root = cur;
			//Ȼ��ʼ��ɾ���ڵ��������е����ҽڵ�
			parent = cur;
			cur = cur->_left;
			while (cur->_right) {
				parent = cur;
				cur = cur->_right;
			}
			//�ҵ����ҽڵ�󽻻����ҽڵ���Ҫɾ���ڵ��ֵ����ʱ���ҽڵ����Ҫɾ���Ľڵ���
			swap(_root->_data, cur->_data);
			//Ȼ���ж�ɾ���ڵ������ӻ����Һ���
			if (parent->_left == cur)
				//��ɾ���ڵ���������������ڵ�����
				parent->_left = cur->_left;
			else
				//��ɾ���ڵ���������������ڵ���ұ�
				parent->_right = cur->_left;
			delete cur;
		}
		return true;
	}
private:
	//��������������������˱�������������
	void _inordef(Node* root) {
		if (root) {
			//�ȱ������ӣ��ٱ�����ǰ�ڵ㣬�������Һ���
			_inorder(root->_left);
			cout << root->_data << " ";
			_inorder(root->_right);
		}
	}
	//���ٶ�����
	void destory(Node* root) {
		if (root) {
			//ɾ�����Һ���֮����ɾ�������
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