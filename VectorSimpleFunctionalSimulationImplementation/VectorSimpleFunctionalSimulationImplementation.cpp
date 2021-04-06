#include<iostream>
#include<string>
using namespace std;

template<class T>
class myvector {
	//������
	typedef T* iterator;
	typedef const T* const_iterator;
	//�ɶ���д������
	iterator begin() {
		return _start;
	}
	iterator end() {
		return _finish;
	}
	//ֻ��������
	const_iterator begin()const {
		return _start;
	}
	const_iterator end()const {
		return _finish;
	}
	//��ȡ��ЧԪ�ظ���
	size_t size()const {
		return _finish - _start;
	}
	//��ȡ������С
	size_t capacity()const {
		return _end_of_storage - _start;
	}
	//�޲ι��캯��
	myvector()
		:_start(nullptr)
		,_finish(nullptr)
		,_end_of_storage(nullptr)
	{}
	//���ι��캯��
	myvector(size_t n, const T& val = T())
		:_start(new T[n])
		, _finish(_start + n)
		, _end_of_storage(_start + n)
	{
		//ʹ���� 0 ֵ���г�ʼ��
		for (int i = 0; i < n; i++) {
			_start[i] = val;
		}
	}
	//ʹ�õ��������캯��
	template<class inputiterator>
	myvector(inputiterator frist, inputiterator last)
		:_start(nullptr)
		, _finish(nullptr)
		, _end_of_storage(nullptr)
	{
		//ʹ�õ�����������ݽ��г�ʼ��
		while (frist != end) {
			push_back(*frist);
			frist++;
		}
	}
	//��������
	myvector(const myvector<T>& copy)
		:_start(nullptr)
		, _finish(nullptr)
		, _end_of_storage(nullptr)
	{
		size_t n = copy.capacity();
		_start = new T[n];
		//�˴�ֻ�ܽ��и�ֵ������������ʹ���ڴ濽������Ϊ������Զ������ͣ���ô�����ǳ����
		for (size_t i = 0; i < copy.size(); i++) {
			//�˴��Ǹ�ֵ������������Զ������ͣ���ô������Զ������ͱ�����������
			_start[i] = copy[i];
		}
		_finish = _start + copy.size();
		_end_of_storage = _start + n;
	}
	//��ֵ�������ͳд��
	myvector<T>& operator=(const myvector<T>& v) {
		if (this != &v) {
			delete[] _start;
			size_t n = v.capacity();
			_start = new T[n];
			//�˴�ֻ�ܽ��и�ֵ������������ʹ���ڴ濽������Ϊ������Զ������ͣ���ô�����ǳ����
			for (size_t i = 0; i < v.size(); i++) {
				//�˴��Ǹ�ֵ������������Զ������ͣ���ô������Զ������ͱ�����������
				_start[i] = v[i];
			}
			_finish = _start + v.size();
			_end_of_storage = _start + n;
		}
		return *this;
	}
	//��ֵ������ִ�д��
	myvector<T>& operator=(myvector<T> v) {
		Swap(v);
		return *this;
	}
	//�ڲ���������
	void Swap(myvector<T>& v) {
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_end_of_storage, v._end_of_storage);
	}
	//��������
	~myvector() {
		if (_start) {
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
	}
	//���ʲ���
	T& operator[](size_t pos) {
		//�ж�λ���Ƿ�Ϸ�
		if (pos >= begin() && pos < end()) {
			return _start[pos];
		}
	}
	const T& operator[](size_t pos)const {
		//�ж�λ���Ƿ�Ϸ�
		if (pos >= begin() && pos < end()) {
			return _start[pos];
		}
	}
	//�ı���ЧԪ�ظ���
	void resize(size_t n, const T& val = T()) {
		//��������ݣ���������Ƿ��㹻
		if (n > capacity()) {
			reserve(n);
		}
		//�������Ŀռ丳ָ��ֵ
		if (n > size()) {
			size_t num = n - size();
			while(num--) {
				*_finish = val;
				_finish++;
			}
		}
		//Ȼ���޸���ЧԪ�ظ���ָ��_finish
		_finish = _start + n;
	}
	//�ı�����
	void reserve(size_t n) {
		//��������ݣ���ôִ�в���
		if (n > capacity()) {
			//�õ�ԭʼ���ݳ���
			size_t len = size();
			//�����¿ռ�
			T* arr = new T[n];
			//�����ԭʼ�ռ䣬��ô��Ҫ��ԭʼ���ݿ������¿ռ䣬���ͷ�ԭʼ�ռ�
			if (_start) {
				//�˴�ֻ�ܽ��и�ֵ������������ʹ���ڴ濽������Ϊ������Զ������ͣ���ô�����ǳ����
				for (size_t i = 0; i < len; i++) {
					//�˴��Ǹ�ֵ������������Զ������ͣ���ô������Զ������ͱ�����������
					arr[i] = _start[i];
				}
				delete[] _start;
			}
			//���±���
			_start = arr;
			_finish = _start + len; 
			_end_of_storage = _start + n;
		}
	}
	//β�����
	void push_back(const T& val = T()) {
		//�жϿռ��Ƿ��㹻������������迪��
		if (_finish == _end_of_storage) {
			size_t n = capacity() == 0 ? 1 : 2 * capacity();
			reserve(n);
		}
		//����β������
		*_finish = val;
		//���±���
		_finish++;
	}
	//�����������λ�ò���Ԫ��
	iterator insert(iterator pos, const T& val) {
		//������λ��
		if (pos <= begin() && pos >= end()) {
			//��������Ƿ��㹻
			if (_finish == _end_of_storage) {
				//Ҫ�������ݣ�������Ҫ���и��£������ȼ�¼�µ�������ԭʼλ�õ�ƫ����
				size_t len = pos - _start;
				//�����Ҫ���µ�����
				size_t n = capacity == 0 ? 1 : 2 * capacity;
				//����
				reserve(n);
				//���µ�����������λ�õĻ����ϼ���ƫ����
				pos = _start + len;
			}
			//Ԫ������ƶ�
			iterator tmp = _finish;
			while (tmp != pos) {
				*tmp = *(tmp - 1);
				tmp--;
			}
			//����Ԫ��
			*pos = val;
			//���±���
			_finish++;
		}
		return pos;
	}
	//ɾ��Ԫ��
	iterator erase(iterator pos) {
		//���λ��
		if (pos >= begin() && pos < end()) {
			iterator start = pos + 1;
			//ѭ����ǰ�ƶ�һ��Ԫ��
			while (start != _finish) {
				*(start - 1) = *start;
				start++;
			}
			//���±���
			_finish--;
		}
		return pos;
	}
	//βɾ����
	void pop_back() {
		//����ɾ������
		erase(_finish - 1);
	}
private:
	//����ʹ��ָ������֯һ��vector����
	//��ָ��
	iterator _start;
	//���һ����ЧԪ�صĺ�һ��λ��
	iterator _finish;
	//���ٿռ�����һ��Ԫ�غ�һ��λ��
	iterator _end_of_storage;
};
template<class T>
ostream& operator<<(ostream& _cout, const myvector<T>& v) {
	for (size_t i = 0; i < v.size(); i++) {
		_cout << v[i] << ' ';
	}
	_cout << endl;
	return cout;
}
int main() {

	return 0;
}