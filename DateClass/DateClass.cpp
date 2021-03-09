#include<iostream>
using namespace std;

class Date{
public:
	// 获取某年某月的天数
	int GetMonthDay(int year, int month) {
		//以数组写出每月的天数，月份与下表对应
		int marr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		//需要注意的是二月的天数有变化，区分闰年和非闰年的不同
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
			if (month == 2) {
				return marr[month] + 1;
			}
			return marr[month];
		}
		return marr[month];
	}

	// 全缺省的构造函数
	Date(int year = 1, int month = 1, int day = 1) {
		//检测输入日期是否符合常理，若果有误，设置为默认值
		if (year < 1 || month < 1 || month > 12 || day < 1 || day > GetMonthDay(year, month)) {
			_year = 1;
			_month = 1;
			_day = 1;
			cout << "输入日期有误,已设为：1-1-1" << endl;
		}
		else {
			_year = year;
			_month = month;
			_day = day;
		}
	}

	// 拷贝构造函数
	Date(const Date& d) {
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	// 赋值运算符重载
	Date& operator=(const Date& d) {
		if (this != &d) {
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}

	// 析构函数
	~Date() {}

	// 日期+=天数
	Date& operator+=(int day) {
		//看看当前月份剩余天数是否满足所加天数
		day = day - GetMonthDay(_year, _month) + _day;
		//若果不满足就循环向上加
		while (day > 0) {
			//月份变化，如果超过12，则向上加一年，并将月份置为一月
			if (++_month > 12) {
				_month = 1;
				_year++;
			}
			_day = 0;
			day = day - GetMonthDay(_year, _month);
		}
		//最终日期为剩余的不大于当前月份的天数
		_day = GetMonthDay(_year, _month) + day;
		//此处返回的是一个外部变量，所以可以返回引用
		return *this;
	}

	// 日期+天数
	Date operator+(int day) {
		//复用上面的代码，不改变当前日期的前提下，返回一个相加之后的日期
		Date tmp(*this);
		tmp += day;
		//此处返回的是一个局部变量，所以不能返回引用
		return tmp;
	}

	// 日期-天数
	Date operator-(int day) {
		//复用代码
		Date tmp(*this);
		tmp -= day;
		return tmp;
	}

	// 日期-=天数
	Date& operator-=(int day) {
		//看看当前月份天数是否足够减
		day = day - _day;
		//如果不够减，那么就循环变化
		while (day >= 0) {
			//月份减一，如果减一后小于1，那么就年份减一，并将月份置为十二月
			if (--_month < 1) {
				_month = 12;
				//如果年份减一后小于1，那么就将日期置为默认值
				if (--_year < 1) {
					_year = 1;
					_month = 1;
					_day = 1;
				}
			}
			_day = GetMonthDay(_year, _month);
			day = day - _day;
		}
		//最终日期为不够减的相反数
		_day = -day;
		return *this;
	}

	// 前置++
	Date& operator++() {
		*this += 1;
		return *this;
	}

	// 后置++
	Date operator++(int) {
		Date tmp(*this);
		*this += 1;
		return tmp;
	}

	// 后置--
	Date operator--(int) {
		Date tmp(*this);
		*this -= 1;
		return tmp;
	}

	// 前置--
	Date& operator--() {
		*this -= 1;
		return *this;
	}

	// >运算符重载
	bool operator>(const Date& d) {
		//如果年份大于，那么返回真
		if (_year > d._year) {
			return true;
		}
		//如果年份相等，那么比较月份
		else if (_year == d._year) {
			//如果月份大于，返回真
			if (_month > d._month) {
				return true;
			}
			//如果月份相等，那么比较天数
			else if (_month == d._month) {
				//天数大于，返回真
				if (_day > d._day) {
					return true;
				}
			}
		}
		//否则返回假
		return false;
	}

	// ==运算符重载
	bool operator==(const Date& d) {
		//年月日都相等才返回真
		if (_year == d._year && _month == d._month && _day == d._day) {
			return true;
		}
		return false;
	}

	// >=运算符重载
	inline bool operator >= (const Date& d) {
		if (*this > d) {
			return true;
		}
		else if (*this == d) {
			return true;
		}
		return false;
	}

	// <运算符重载
	bool operator < (const Date& d) {
		if (*this >= d) {
			return false;
		}
		return true;
	}

	// <=运算符重载
	bool operator <= (const Date& d) {
		if (*this > d) {
			return false;
		}
		return true;
	}

	// !=运算符重载
	bool operator != (const Date& d) {
		if (*this == d) {
			return false;
		}
		return true;
	}

	// 日期-日期 返回天数
	int operator-(const Date& d) {
		//用小日期一天一天加，直到等于大日期，返回所需的相加天数，需要注意正负
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