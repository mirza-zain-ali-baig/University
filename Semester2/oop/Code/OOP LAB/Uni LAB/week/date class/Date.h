class Date
{
	int *day, *month, *year;
public:
	Date(int=1, int=1, int=2001);
	Date(const Date &);
	void setDay(int);
	void setMonth(int);
	void setYear(int);
	int getDay();
	int getMonth();
	int getYear();

	void display();
};

