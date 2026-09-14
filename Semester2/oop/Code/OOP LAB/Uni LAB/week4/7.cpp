#include <iostream>
using namespace std;

class dayType {
private:
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    int currentDay;
 
public:
    dayType() {
        currentDay = 0;
    }

    dayType(string day) {
        setDay(day);
    }

    void setDay(string day) {
        for (int i = 0; i < 7; i++) {
            if (days[i] == day) {
                currentDay = i;
                return;
            }
        }
        cout << "Invalid day entered! Defaulting to Sunday.\n";
        currentDay = 0;
    }

    string getDay() {
        return days[currentDay];
    }

    void printDay() {
        cout << "Current day: " << days[currentDay] << endl;
    }

    string nextDay() {
        return days[(currentDay + 1) % 7];
    }

    string previousDay() {
        return days[(currentDay + 6) % 7];
    }

    string addDays(int num) {
        return days[(currentDay + num) % 7];
    }
};

int main() {
    dayType today("Tue");

    today.printDay();
    cout << "Next day: " << today.nextDay() << endl;
    cout << "Previous day: " << today.previousDay() << endl;
    cout << "After adding 4 days: " << today.addDays(4) << endl;
    cout << "After adding 13 days: " << today.addDays(13) << endl;

    return 0;
}
