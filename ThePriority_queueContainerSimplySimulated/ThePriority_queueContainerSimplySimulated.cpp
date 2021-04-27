#include<iostream>
#include<vector>
using namespace std;

template<class T>
struct _less {
	bool operator()(const T& left, const T& right) {
		return left < right;
	}
};

template<class T>
struct _greater {
	bool operator()(const T& left, const T& right) {
		return left > right;
	}
};

template<class T, class Con = vector<T>, class Cmp = _less<T>>
class myPQueue {
public:
	//Ĭ�Ϲ��캯��
	myPQueue() {}
	//ʹ�õ������乹�캯��
	template<class it>
	myPQueue(it frist, it last)
		:v(frist, last)
	{
		//ʹ�����µ����㷨������
		for (int root = (v.size() - 1) / 2; root >= 0; root--) {
			AdjustDown(root);
		}
	}
	//����������������Ҫ�γ�һ���ѣ������Ҫ�ڲ���������ϵ����㷨
	void push(const T& val) {
		//����
		v.push_back(val);
		//���ϵ���
		AdjustUp(v.size() - 1);
	}
	//ɾ���������Ƚ���βԪ�ػ�����Ȼ��Ȼ��βɾ��Ȼ���ͷ���������µ���
	void pop() {
		//����
		swap(v.front(), v.back());
		//ɾ��
		v.pop_back();
		//���µ���
		AdjustDown(0);
	}
	//ȡ�Ѷ�Ԫ�أ��Ѷ�Ԫ�ز����޸ģ��޸Ļ��ƻ��ѽṹ
	const T& top() {
		return v.front();
	}
	//��ȡ��Ԫ�ظ���
	size_t size() {
		return v.size();
	}
	//�пղ���
	bool empty() {
		return v.empty();
	}
private:
	//���µ����㷨
	void AdjustDown(int root) {
		//���ҵ��ýڵ������
		int child = root * 2 + 1;
		//���������ӽ����ڣ���ô�Ϳ�ʼѭ������
		while (child < v.size()) {
			//�ж��Һ����Ƿ����
			if (child + 1 < v.size() && cmp(v[child], v[child + 1]))
				child++;
			//�жϸ�����Ƿ�����Һ��������Ļ�Ҫ������ǵģ��򽻻�
			if (cmp(v[root], v[child])) {
				//����Ԫ������
				swap(v[root], v[child]);
				//�޸ĸ����±�
				root = child;
				child = root * 2 + 1;
			}
			else
				//����������������Ӷ��������ѭ��
				break;
		}
	}
	//���ϵ����㷨
	void AdjustUp(int root) {
		//�õ��ڵ�ĸ����
		int parent = (root - 1) / 2;
		//�жϽڵ��Ƿ�Ϸ�
		while (root) {
			//������ӽ��ȸ����Ҫ����ô�򽻻�
			if (cmp(v[parent], v[root])) {
				//�����������
				swap(v[parent], v[root]);
				//���±���
				root = parent;
				parent = (root - 1) / 2;
			}
			//������ӽ��ȸ����С����ô˵���������
			else
				break;
		}
	}
private:
	Con v;
	Cmp cmp;
};

int main() {

	return 0;
}