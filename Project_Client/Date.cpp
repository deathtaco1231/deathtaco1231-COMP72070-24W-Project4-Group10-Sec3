#include "AllHeaders.h"
#include "Date.h"
bool date::valid(void) {
	if (year < 0) return false;
	if (month > 12 || month < 1) return false;
	if (day > 31 || day < 1) return false;
	if ((day == 31 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)))
		return false;
	if (day == 30 && month == 2) return false;
	if (year < 2000) {
		if ((day == 29 && month == 2) && !((year - 1900) % 4 == 0)) return false;
	};
	if (year > 2000) {
		if ((day == 29 && month == 2) && !((year - 2000) % 4 == 0)) return false;
	};
	return true;
}
std::string date::datetos(void) {
	return std::string(this->year + '/' + this->month + '/' + this->day);
}
int long_date(date& d) {
	if (d.valid())
		return d.getyear() * 10000 + d.getmonth() * 100 + d.getday();
	return -1;
};
std::ostream& operator << (std::ostream& os, date& d) {
	if (d.valid()) { os << " " << long_date(d) << " "; }
	else { os << " invalid date "; };
	return os;
}
bool operator < (date& d1, date& d2) {
	if (!d1.valid()) { return false; }; // not meaningful, return anything
	if (!d2.valid()) { return false; }; // should really be an exception, but ?
	if (d1.getyear() < d2.getyear()) { return true; }
	else if (d1.getyear() > d2.getyear()) { return false; }
	else { // same year
		if (d1.getmonth() < d2.getmonth()) { return true; }
		else if (d1.getmonth() > d2.getmonth()) { return false; }
		else { // same month
			if (d1.getday() < d2.getday()) { return true; }
			else { return false; }
		};
	};
	return false;
};
bool operator == (date& d1, date& d2) {
	// check for equality
	if (!d1.valid()) { return false; };
	if (!d2.valid()) { return false; };
	if ((d1.getday() == d2.getday())
		&& (d1.getmonth() == d2.getmonth())
		&& (d1.getyear() == d2.getyear())) {
		return true;
	};
	return false;
}
bool operator <=(date& d1, date& d2) {
	if (d1 == d2) { return true; }
	return (d1 < d2);
}