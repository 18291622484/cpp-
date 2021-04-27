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
	//默认构造函数
	myPQueue() {}
	//使用迭代区间构造函数
	template<class it>
	myPQueue(it frist, it last)
		:v(frist, last)
	{
		//使用向下调整算法构建堆
		for (int root = (v.size() - 1) / 2; root >= 0; root--) {
			AdjustDown(root);
		}
	}
	//插入操作，插入后仍要形成一个堆，因此需要在插入后做向上调整算法
	void push(const T& val) {
		//插入
		v.push_back(val);
		//向上调整
		AdjustUp(v.size() - 1);
	}
	//删除操作，先将收尾元素互换，然后然后尾删，然后对头结点进行向下调整
	void pop() {
		//交换
		swap(v.front(), v.back());
		//删除
		v.pop_back();
		//向下调整
		AdjustDown(0);
	}
	//取堆顶元素，堆顶元素不能修改，修改会破坏堆结构
	const T& top() {
		return v.front();
	}
	//获取堆元素个数
	size_t size() {
		return v.size();
	}
	//判空操作
	bool empty() {
		return v.empty();
	}
private:
	//向下调整算法
	void AdjustDown(int root) {
		//先找到该节点的左孩子
		int child = root * 2 + 1;
		//如果这个孩子结点存在，那么就开始循环调整
		while (child < v.size()) {
			//判断右孩子是否存在
			if (child + 1 < v.size() && cmp(v[child], v[child + 1]))
				child++;
			//判断父结点是否比左右孩子中最大的还要大，如果是的，则交换
			if (cmp(v[root], v[child])) {
				//交换元素内容
				swap(v[root], v[child]);
				//修改父子下标
				root = child;
				child = root * 2 + 1;
			}
			else
				//如果父结点比两个孩子都大，则结束循环
				break;
		}
	}
	//向上调整算法
	void AdjustUp(int root) {
		//拿到节点的父结点
		int parent = (root - 1) / 2;
		//判断节点是否合法
		while (root) {
			//如果孩子结点比父结点要大，那么则交换
			if (cmp(v[parent], v[root])) {
				//交换结点内容
				swap(v[parent], v[root]);
				//更新变量
				root = parent;
				parent = (root - 1) / 2;
			}
			//如果孩子结点比父结点小，那么说明调整完毕
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