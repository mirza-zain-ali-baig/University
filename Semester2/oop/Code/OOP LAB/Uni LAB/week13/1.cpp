// #include <iostream>
// using namespace std;

// class Shape {
// protected:
//     double width;
//     double height;
// public:
//     Shape(double w, double h) : width(w), height(h) {}
//     double area() {
//         return 0;
//     }
// };

// class Triangle : public Shape {
// public:
//     Triangle(double w, double h) : Shape(w, h) {}
//     double area() {
//         return 0.5 * width * height;
//     }
// };

// class Rectangle : public Shape {
// public:
//     Rectangle(double w, double h) : Shape(w, h) {}
//     double area() {
//         return width * height;
//     }
// };

// int main() {
//     Triangle t(10, 5);
//     Rectangle r(1, 5);
//     cout << t.area() << endl;
//     cout << r.area() << endl;
//     return 0;
// }


// 2

// #include <iostream>
// using namespace std;

// class Mother {
// public:
//     void display() {
//         cout << "This is the mother class display" << endl;
//     }
// };

// class Daughter : public Mother {
// public:
//     void display() {
//         cout << "This is the daughter class." << endl;
//     }
// };

// int main() {
//     Daughter d;
//     d.display();
//     return 0;
// }

// 3

// #include <iostream>
// using namespace std;

// class Animal {
// protected:
//     int age;
//     string gender;

// public:
//     Animal(int a, string g) : age(a), gender(g) {}

//       void isMammal() {
//         cout << "Checking if mammal..." << endl;
//     }

//       void mate() {
//         cout << "Animal is mating..." << endl;
//     }
// };

// class Duck : public Animal {
// private:
//     string beakColor;

// public:
//     Duck(int a, string g, string bc) : Animal(a, g), beakColor(bc) {}

//     void swim() {
//         cout << "Duck is swimming" << endl;
//     }

//     void quack() {
//         cout << "Duck is quacking" << endl;
//     }

//     void isMammal()  {
//         cout << "Duck is not a mammal" << endl;
//     }

//     void mate()   {
//         cout << "Duck is mating" << endl;
//     }

//     void display() {
//         cout << "Duck" << endl;
//         cout << "Age: " << age << endl;
//         cout << "Gender: " << gender << endl;
//         cout << "Beak Color: " << beakColor << endl;
//     }
// };

// class Fish : public Animal {
// private:
//     int sizeInFt;
//     bool canEat;

// public:
//     Fish(int a, string g, int sz, bool ce) : Animal(a, g), sizeInFt(sz), canEat(ce) {}

//     void swim() {
//         cout << "Fish is swimming" << endl;
//     }

//     void isMammal()   {
//         cout << "Fish is not a mammal" << endl;
//     }

//     void mate()   {
//         cout << "Fish is mating" << endl;
//     }

//     void display() {
//         cout << "  Fish  " << endl;
//         cout << "Age: " << age << endl;
//         cout << "Gender: " << gender << endl;
//         cout << "Size in Feet: " << sizeInFt << endl;
//         cout << "Can Eat: " << (canEat ? "Yes" : "No") << endl;
//     }
// };

// class Zebra : public Animal {
// private:
//     bool isWild;

// public:
//     Zebra(int a, string g, bool iw) : Animal(a, g), isWild(iw) {}

//     void run() {
//         cout << "Zebra is running" << endl;
//     }

//     void isMammal()   {
//         cout << "Zebra is a mammal" << endl;
//     }

//     void mate()   {
//         cout << "Zebra is mating" << endl;
//     }

//     void display() {
//         cout << "  Zebra  " << endl;
//         cout << "Age: " << age << endl;
//         cout << "Gender: " << gender << endl;
//         cout << "Is Wild: " << isWild << endl;
//     }
// };

// class Dolphin : public Animal {
// private:
//     string color;
//     int intelligence;

// public:
//     Dolphin(int a, string g, string c, int intel) : Animal(a, g), color(c), intelligence(intel) {}

//     void swim() {
//         cout << "Dolphin is swimming" << endl;
//     }

//     void isMammal()   {
//         cout << "Dolphin is a mammal" << endl;
//     }

//     void mate()   {
//         cout << "Dolphin is mating" << endl;
//     }

//     void display() {
//         cout << "  Dolphin  " << endl;
//         cout << "Age: " << age << endl;
//         cout << "Gender: " << gender << endl;
//         cout << "Color: " << color << endl;
//         cout << "Intelligence Level: " << intelligence << endl;
//     }
// };

// int main() {
//     Duck duck(5, "Male", "yellow");
//     Zebra zebra(8, "Female", true);
//     Dolphin dolphin(6, "Male", "gray", 95);

//     cout << " Duck Details  " << endl;
//     duck.display();
//     duck.isMammal();
//     duck.mate();
//     duck.swim();
//     duck.quack();

//     cout << "  Zebra Details  " << endl;
//     zebra.display();
//     zebra.isMammal();
//     zebra.mate();
//     zebra.run();

//     cout << " Dolphin Details  " << endl;
//     dolphin.display();
//     dolphin.isMammal();
//     dolphin.mate();
//     dolphin.swim();

//     return 0;
// }


//Lab 13
// 13.1

// #include <iostream>
// using namespace std;

// class AA {
// public:
//     AA() {
//         cout << "Constructor of AA  " << endl;
//     }

//     ~AA() {
//         cout << "Destructor of AA  " << endl;
//     }
// };

// class BB : public AA {
// public:
//     BB() {
//         cout << "Constructor of BB  " << endl;
//     }

//     ~BB() {
//         cout << "Destructor of BB  " << endl;
//     }
// };

// class CC : public BB {
// public:
//     CC() {
//         cout << "Constructor of CC" << endl;
//     }

//     ~CC() {
//         cout << "Destructor of CC  " << endl;
//     }
// };

// class DD : public CC {
// public:
//     DD() {
//         cout << "Constructor of DD  " << endl;
//     }

//     ~DD() {
//         cout << "Destructor of DD  " << endl;
//     }
// };

// int main() {
//     cout << "Creating object of DD class:" << endl;
//     DD obj;
//     cout << "\nObject out of scope:" << endl;

//     return 0;
// }


// 13.2


// #include <iostream>
// using namespace std;

// class Card {
// private:
//     string cardNumber;
//     string ownerName;
//     string expiryDate;

// public:
//     Card() {}

//     Card(string cardNum, string owner, string expiry) 
//         : cardNumber(cardNum), ownerName(owner), expiryDate(expiry) {}

//     void setCardNumber(string cardNum) {
//         cardNumber = cardNum;
//     }

//     string getCardNumber() {
//         return cardNumber;
//     }

//     void setOwnerName(string owner) {
//         ownerName = owner;
//     }

//     string getOwnerName() {
//         return ownerName;
//     }

//     void setExpiryDate(string expiry) {
//         expiryDate = expiry;
//     }

//     string getExpiryDate() {
//         return expiryDate;
//     }
// };

// class CallingCard : public Card {
// private:
//     string amount;
//     string companyName;
//     string pin;

// public:
//     CallingCard() {}

//     CallingCard(string cardNum, string owner, string expiry, string amt, string company, string p)
//         : Card(cardNum, owner, expiry), amount(amt), companyName(company), pin(p) {}

//     void setAmount(string amt) {
//         amount = amt;
//     }

//     string getAmount() {
//         return amount;
//     }

//     void setCompanyName(string company) {
//         companyName = company;
//     }

//     string getCompanyName() {
//         return companyName;
//     }

//     void setPin(string p) {
//         pin = p;
//     }

//     string getPin() {
//         return pin;
//     }

//     void displayInfo() {
//         cout << "\nCalling Card Information:" << endl;
//         cout << "Card Number: " << getCardNumber() << endl;
//         cout << "Owner Name: " << getOwnerName() << endl;
//         cout << "Expiry Date: " << getExpiryDate() << endl;
//         cout << "Amount: " << amount << endl;
//         cout << "Company Name: " << companyName << endl;
//         cout << "PIN: " << pin << endl;
//     }
// };

// class IdCard : public Card {
// private:
//     string cnicNumber;
//     int age;

// public:
//     IdCard() {}

//     IdCard(string cardNum, string owner, string expiry, string cnic, int a)
//         : Card(cardNum, owner, expiry), cnicNumber(cnic), age(a) {}

//     void setCnicNumber(string cnic) {
//         cnicNumber = cnic;
//     }

//     string getCnicNumber() {
//         return cnicNumber;
//     }

//     void setAge(int a) {
//         age = a;
//     }

//     int getAge() {
//         return age;
//     }

//     void displayInfo() {
//         cout << "\nID Card Information:" << endl;
//         cout << "Card Number: " << getCardNumber() << endl;
//         cout << "Owner Name: " << getOwnerName() << endl;
//         cout << "Expiry Date: " << getExpiryDate() << endl;
//         cout << "CNIC Number: " << cnicNumber << endl;
//         cout << "Age: " << age << endl;
//     }
// };

// class DrivingLicenseCard : public Card {
// private:
//     string licenseType;
//     string issuedInCity;

// public:
//     DrivingLicenseCard() {}

//     DrivingLicenseCard(string cardNum, string owner, string expiry, string type, string city)
//         : Card(cardNum, owner, expiry), licenseType(type), issuedInCity(city) {}

//     void setLicenseType(string type) {
//         licenseType = type;
//     }

//     string getLicenseType() {
//         return licenseType;
//     }

//     void setIssuedInCity(string city) {
//         issuedInCity = city;
//     }

//     string getIssuedInCity() {
//         return issuedInCity;
//     }

//     void displayInfo() {
//         cout << "\nDriving License Card Information:" << endl;
//         cout << "Card Number: " << getCardNumber() << endl;
//         cout << "Owner Name: " << getOwnerName() << endl;
//         cout << "Expiry Date: " << getExpiryDate() << endl;
//         cout << "License Type: " << licenseType << endl;
//         cout << "Issued in City: " << issuedInCity << endl;
//     }
// };

// int main() {
//     CallingCard callingCard("7797", "Ahn", "12/2026", "500", "Jaz", "124");
//     IdCard idCard("1230", "Fali", "060", "42238", 28);
//     DrivingLicenseCard drivingLicense("DL-001", "Hsk", "09", "Hy", "Lah");

//     callingCard.displayInfo();
//     idCard.displayInfo();
//     drivingLicense.displayInfo();

//     callingCard.setAmount("100");
//     idCard.setAge(29);
//     drivingLicense.setIssuedInCity("Isd");

//     cout << "\n\nUpdated Information:" << endl;
//     callingCard.displayInfo();
//     idCard.displayInfo();
//     drivingLicense.displayInfo();

//     return 0;
// }


// 13.3

// #include <iostream>
// using namespace std;

// class Person {
// private:
//     string name;
//     int age;

// public:
//     Person(string n, int a) : name(n), age(a) {}

//     string getName() {
//         return name;
//     }

//     int getAge() {
//         return age;
//     }

//     void displayPersonInfo() {
//         cout << "Name: " << name << endl;
//         cout << "Age: " << age << endl;
//     }
// };

// class Employee : public Person {
// private:
//     double salary;
//     int employeeId;

// public:
//     Employee(string n, int a, int id, double sal) 
//         : Person(n, a), employeeId(id), salary(sal) {}

//     void displayEmployeeInfo() {
//         cout << "\n  Employee Information  " << endl;
//         displayPersonInfo();
//         cout << "Employee ID: " << employeeId << endl;
//         cout << "Salary: " << salary << endl;
//     }
// };

// class Baseball_Player : public Person {
// private:
//     double battingAverage;
//     int totalRuns;

// public:
//     Baseball_Player(string n, int a, double avg, int runs) 
//         : Person(n, a), battingAverage(avg), totalRuns(runs) {}

//     void displayBaseballPlayerInfo() {
//         cout << "\n  Baseball Player Information  " << endl;
//         displayPersonInfo();
//         cout << "Batting Average: " << battingAverage << endl;
//         cout << "Total Runs: " << totalRuns << endl;
//     }
// };

// int main() {
//     Employee emp("Johh", 35, 12345, 750);
//     Baseball_Player player("Mn", 28, 0.5, 15);

//     emp.displayEmployeeInfo();
//     player.displayBaseballPlayerInfo();

//     return 0;
// }