#pragma once
#include "AllHeaders.h"
class date {
protected:
	int year;
	int month;
	int day;
public:
	date() { year = 0; month = 0; day = 0; }
	date(const int& d, const int& m, const int& y) { day = d; month = m; year = y; }
	bool valid();
	int getday() { return day; }
	int getmonth() { return month; }
	int getyear() { return year; }
	void setday(const int& a) { this->day = a; }
	void setmonth(const int& a) { this->month = a; }
	void setyear(const int& a) { this->year = a; }
	std::string datetos();
};
int long_date(date&);
std::ostream& operator << (std::ostream&, date&);
bool operator < (date&, date&);
bool operator == (date&, date&);
bool operator <=(date&, date&);
date currdate; // GLOBAL FOR KEEPING TRACK OF CURRENT DATE
void setcurrdate();