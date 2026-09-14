#include "Date.h"
#include<iostream>
using namespace std;

int main() {
	Date d(7, 15, 2025);
	d.display();
	Date d2(d);
	/*d2.setDay(d.getDay());
	d2.setMonth(d.getMonth());
	d2.setYear(d.getYear());*/
	d2.setDay(30);
	d.display();
	d2.display();
	return 0;
}