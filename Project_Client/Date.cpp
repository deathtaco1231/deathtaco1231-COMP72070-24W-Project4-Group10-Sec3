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
	std::stringstream s;
	s << this->year << "/" << this->month << "/" << this->day;
	return s.str();
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
void setcurrdate(void) {
	int mon = 0;
	time_t today = time(0); // Gets time in seconds since january 1 1970
	char* todaysdate = ctime(&today);
	std::stringstream s(todaysdate);
	std::string year, month, day, garbage;
	std::getline(s, garbage, ' '); // Data returned we dont care about
	std::getline(s, month, ' ');
	std::getline(s, day, ' ');
	std::getline(s, garbage, ' ');
	std::getline(s, year, '\n');
	currdate.setday(stoi(day));
	if (!month.compare("Jan"))
		currdate.setmonth(mon = 1);
	else if (!month.compare("Feb"))
		currdate.setmonth(mon = 2);
	else if (!month.compare("Mar"))
		currdate.setmonth(mon = 3);
	else if (!month.compare("Apr"))
		currdate.setmonth(mon = 4);
	else if (!month.compare("May"))
		currdate.setmonth(mon = 5);
	else if (!month.compare("Jun"))
		currdate.setmonth(mon = 6);
	else if (!month.compare("Jul"))
		currdate.setmonth(mon = 7);
	else if (!month.compare("Aug"))
		currdate.setmonth(mon = 8);
	else if (!month.compare("Sep"))
		currdate.setmonth(mon = 9);
	else if (!month.compare("Oct"))
		currdate.setmonth(mon = 10);
	else if (!month.compare("Nov"))
		currdate.setmonth(mon = 11);
	else
		currdate.setmonth(mon = 12);

	currdate.setyear(stoi(year));
}