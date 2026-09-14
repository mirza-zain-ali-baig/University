#include "Date.h"
#include <iostream>
using namespace std;


Date::Date(int d, int m, int y) {
	day = new int;
	month = new int;
	year = new int;
	*day = d;
	*month = m;
	*year = y;
}
Date::Date(const Date& obj) {
	day = new int;
	month = new int;
	year = new int;

	*day = *obj.day;
	*month = *obj.month;
	*year = *obj.year;
}
void Date::setDay(int d) {
	*day = d;
}
void Date::setMonth(int m) {
	*month = m;
}
void Date::setYear(int y) {
	*year = y;
}
int Date::getDay() { return *day; }
int Date::getMonth() { return *month; }
int Date::getYear() { return *year; }

void Date::display() {

		cout << *day << '/' << *month << '/' << *year << endl;
}
