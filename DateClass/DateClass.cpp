#include<iostream>
using namespace std;

class Date{
public:
	// ��ȡĳ��ĳ�µ�����
	int GetMonthDay(int year, int month) {
		//������д��ÿ�µ��������·����±��Ӧ
		int marr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		//��Ҫע����Ƕ��µ������б仯����������ͷ�����Ĳ�ͬ
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
			if (month == 2) {
				return marr[month] + 1;
			}
			return marr[month];
		}
		return marr[month];
	}

	// ȫȱʡ�Ĺ��캯��
	Date(int year = 1, int month = 1, int day = 1) {
		//������������Ƿ���ϳ���������������ΪĬ��ֵ
		if (year < 1 || month < 1 || month > 12 || day < 1 || day > GetMonthDay(year, month)) {
			_year = 1;
			_month = 1;
			_day = 1;
			cout << "������������,����Ϊ��1-1-1" << endl;
		}
		else {
			_year = year;
			_month = month;
			_day = day;
		}
	}

	// �������캯��
	Date(const Date& d) {
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	// ��ֵ���������
	Date& operator=(const Date& d) {
		if (this != &d) {
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}

	// ��������
	~Date() {}

	// ����+=����
	Date& operator+=(int day) {
		//������ǰ�·�ʣ�������Ƿ�������������
		day = day - GetMonthDay(_year, _month) + _day;
		//�����������ѭ�����ϼ�
		while (day > 0) {
			//�·ݱ仯���������12�������ϼ�һ�꣬�����·���Ϊһ��
			if (++_month > 12) {
				_month = 1;
				_year++;
			}
			_day = 0;
			day = day - GetMonthDay(_year, _month);
		}
		//��������Ϊʣ��Ĳ����ڵ�ǰ�·ݵ�����
		_day = GetMonthDay(_year, _month) + day;
		//�˴����ص���һ���ⲿ���������Կ��Է�������
		return *this;
	}

	// ����+����
	Date operator+(int day) {
		//��������Ĵ��룬���ı䵱ǰ���ڵ�ǰ���£�����һ�����֮�������
		Date tmp(*this);
		tmp += day;
		//�˴����ص���һ���ֲ����������Բ��ܷ�������
		return tmp;
	}

	// ����-����
	Date operator-(int day) {
		//���ô���
		Date tmp(*this);
		tmp -= day;
		return tmp;
	}

	// ����-=����
	Date& operator-=(int day) {
		//������ǰ�·������Ƿ��㹻��
		day = day - _day;
		//�������������ô��ѭ���仯
		while (day >= 0) {
			//�·ݼ�һ�������һ��С��1����ô����ݼ�һ�������·���Ϊʮ����
			if (--_month < 1) {
				_month = 12;
				//�����ݼ�һ��С��1����ô�ͽ�������ΪĬ��ֵ
				if (--_year < 1) {
					_year = 1;
					_month = 1;
					_day = 1;
				}
			}
			_day = GetMonthDay(_year, _month);
			day = day - _day;
		}
		//��������Ϊ���������෴��
		_day = -day;
		return *this;
	}

	// ǰ��++
	Date& operator++() {
		*this += 1;
		return *this;
	}

	// ����++
	Date operator++(int) {
		Date tmp(*this);
		*this += 1;
		return tmp;
	}

	// ����--
	Date operator--(int) {
		Date tmp(*this);
		*this -= 1;
		return tmp;
	}

	// ǰ��--
	Date& operator--() {
		*this -= 1;
		return *this;
	}

	// >���������
	bool operator>(const Date& d) {
		//�����ݴ��ڣ���ô������
		if (_year > d._year) {
			return true;
		}
		//��������ȣ���ô�Ƚ��·�
		else if (_year == d._year) {
			//����·ݴ��ڣ�������
			if (_month > d._month) {
				return true;
			}
			//����·���ȣ���ô�Ƚ�����
			else if (_month == d._month) {
				//�������ڣ�������
				if (_day > d._day) {
					return true;
				}
			}
		}
		//���򷵻ؼ�
		return false;
	}

	// ==���������
	bool operator==(const Date& d) {
		//�����ն���Ȳŷ�����
		if (_year == d._year && _month == d._month && _day == d._day) {
			return true;
		}
		return false;
	}

	// >=���������
	inline bool operator >= (const Date& d) {
		if (*this > d) {
			return true;
		}
		else if (*this == d) {
			return true;
		}
		return false;
	}

	// <���������
	bool operator < (const Date& d) {
		if (*this >= d) {
			return false;
		}
		return true;
	}

	// <=���������
	bool operator <= (const Date& d) {
		if (*this > d) {
			return false;
		}
		return true;
	}

	// !=���������
	bool operator != (const Date& d) {
		if (*this == d) {
			return false;
		}
		return true;
	}

	// ����-���� ��������
	int operator-(const Date& d) {
		//��С����һ��һ��ӣ�ֱ�����ڴ����ڣ���������������������Ҫע������
		if (*this >= d) {
			int count = 0;
			Date date(d);
			while ((date + count) != *this) {
				count++;
			}
			return count;
		}
		else {
			int count = 0;
			while ((*this + count) != d) {
				count++;
			}
			return -count;
		}
	}

	void print() const {
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main() {

	return 0;
}