#include <iostream>
#include<fstream>
#include <sstream>
#include<string>
using namespace std;

const string patientFile = "patientFile.txt";
const string doctorFile = "doctorFile.txt";
const string appointmentFile = "appointmentFile.txt";
const string roomFile = "roomFile.txt";
const string medicalRecordFile = "medicalRecordFile.txt";
const string billFile = "billFile.txt";
const string adminStaffFile = "adminStaffFile.txt";

class Person {
protected:
	string name;
	int age;
	string address;
	string phonenumber;
public:
	Person() {
		name = "";
		age = 0;
		address ="";
		phonenumber ="";
	}
	Person(string n, int a, string ad, string p) :name(n), age(a), address(ad), phonenumber(p) {}
	string getname() {
		return name;
	}
	int getage() {
		return age;
	}
	string getaddress() {
		return address;
	}
	string getphonenumber() {
		return phonenumber;
	}
	virtual void display() = 0;
};

class Patient:public Person {
private:
	int patientID;
	string bloodGroup;
	string dateOfAdmission;

public:
	Patient() {
		patientID=0;
	    bloodGroup="";
	    dateOfAdmission="";
	}
	Patient(int patid, string bl, string date, string n, int a, string ad, string p) 
		:patientID(patid),bloodGroup(bl),dateOfAdmission(date), Person( n, a, ad, p) {
		};

	int getid() {
		return patientID;
	}
	string getbloodgroup() {
		return bloodGroup;
	}
	string getdate() {
		return  dateOfAdmission;
	}
	void Register() {
		cout << "\n==== Patient Registered Successfully ===="<<endl;
		cout << "Patient ID is: " << patientID << endl;
		cout << "Name is : " << name << endl;
		cout << "Blood Group is : " << bloodGroup << endl;
		cout << "Age: "<< age << endl;
		cout << "Phone Number and Address: " << phonenumber << ", " << address << endl;
		cout << "Date of Admission is: " << dateOfAdmission << endl;

		fstream patientfile(patientFile, ios::app);
		patientfile << patientID << "|" << name << "|" << age << "|" << address << "|" << phonenumber << "|" << bloodGroup << "|" << dateOfAdmission << endl;
		patientfile.close();
	}
	
	void display() {
		cout << "\n===== Patient Detail is =====" << endl;
		cout << "Name is: " << name << endl;
		cout << "Age is: " << age << endl;
		cout << "Address is: " << address << endl;
		cout << "Phone Number is: " << phonenumber << endl;
		cout << "Patient ID is: " << patientID << endl;
		cout << "Blood Group is: " << bloodGroup << endl;
		cout << "Date of Admission is: " << dateOfAdmission << endl;
	}
};

class Employee: public Person {
private:
	int employeeID;
	string date_of_joining;
protected:
 	int salary;
public:
	Employee() {
		employeeID = 0;
	    salary=0;
		date_of_joining="";
	}
	Employee(int id, int sal, string dj, string n, int a, string ad, string p)
		:Person(n, a, ad, p), employeeID(id), salary(sal), date_of_joining(dj) { 
	}
	
	int getEmployeeID() {
		return employeeID;
	}
	
	virtual double calculateSalary() {
		return salary;
	}

    void display() { 
        cout << "ID: " << employeeID << endl;
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
    }
};

class Doctor : public Employee {
private:
	string specialization;
	string licenseNumber;
    string schedule;
public:
    Doctor(){

	}

	Doctor(int id, double sal, string doj,
		string spec, string lic, string sch,
		string n, int a, string ad, string p)
		: Employee(id, sal, doj, n, a, ad, p) {
        schedule = sch;
		specialization = spec;
		licenseNumber = lic;
	}

	void addDiagnosis(int patientID, string diagnosis) {
		cout << "Added diagnosis for patient ID " << patientID << ": " << diagnosis << endl;
		fstream medfile(medicalRecordFile, ios::app);
		medfile << patientID << "|" << name << "|" << diagnosis << "|" << "Prescription" << "|" << "Today" << endl;
		medfile.close();
		cout << "Diagnosis saved to medical records!" << endl;
	}

	void viewSchedule() {
		cout << "\n===== Doctor's Schedule =====" << endl;
		cout << "Doctor: " << name << endl;
		cout << "Specialization: " << specialization << endl;
		cout << "Schedule: " << schedule << endl;
		cout << "=============================\n" << endl;
	}

	double calculateSalary() {
		return salary+7000;   
	}

	void saveData(){
		fstream doctorfile(doctorFile, ios::app);
		doctorfile << getEmployeeID() << "|" << name << "|" << age << "|" << address << "|" << phonenumber << "|" << specialization << "|" << licenseNumber << "|" << schedule << endl;
		doctorfile.close();
	}
	
	void viewMyAppointments() {
		cout << "\n===== My Appointments =====" << endl;
		ifstream appfile(appointmentFile);
		string line;
		bool found = false;
		
		while(getline(appfile, line)){
			stringstream ss(line);
			string appid, pname, dname, date, time, status;
			getline(ss, appid, '|');
			getline(ss, pname, '|');
			getline(ss, dname, '|');
			getline(ss, date, '|');
			getline(ss, time, '|');
			getline(ss, status, '|');
			
			if(dname == name) {
				cout << "Appointment ID: " << appid << endl;
				cout << "Patient: " << pname << endl;
				cout << "Date: " << date << endl;
				cout << "Time: " << time << endl;
				cout << "Status: " << status << endl;
				cout << "-------------------------" << endl;
				found = true;
			}
		}
		appfile.close();
		
		if(!found) {
			cout << "No appointments found!" << endl;
		}
		cout << "===========================\n" << endl;
	}
	
    void display() {
        cout << "\n===== Doctor Details =====" << endl;
        Employee::display();
        cout << "Specialization: " << specialization << endl;
        cout << "License: " << licenseNumber << endl;
        cout << "Schedule: " << schedule << endl;
        cout << "==========================\n" << endl;
    }
};

class AdminStaff: public Employee{
	string department;
	public:
	 AdminStaff(){
		department = "";
	 }

	 AdminStaff(string depName, int id, int sal, string df, string n, int a, string ad, string p): Employee(id,sal, df, n, a, ad, p){
		department = depName;
	 }

	 void manageStaff(){
		Employee::display();
		cout << "Department: " << department << endl;
		fstream adminfile(adminStaffFile, ios::app);
		adminfile << name << "|" << age << "|" << address << "|" << phonenumber << "|" << department << endl;
		adminfile.close();
	 }

	 void display() {
		cout << "\n===== Admin Staff Details =====" << endl;
		Employee::display();
		cout << "Department: " << department << endl;
		cout << "==============================\n" << endl;
	 }
};

class Appointment{
	Patient patient;
	Doctor doctor;
	int appointmentID;
	string date;
	string time;
	string status;

	public:
	 Appointment(){
		appointmentID = 0;
		date = "";
		time = "";
		status = "";
	 }

	 Appointment(Patient pat, Doctor doc, int appID, string dat, string t, string st) 
		: patient(pat), doctor(doc), appointmentID(appID), date(dat), time(t), status(st) {
	 }                                                                              

	 void bookAppointment(){
		cout << "\n===== Appointment Booked Successfully! =====" << endl;
		status = "Scheduled";

		cout << "Appointment ID: " << appointmentID << endl;
		cout << "Patient Name: " << patient.getname() << endl;
		cout << "Doctor Name: " << doctor.getname() << endl;
		cout << "Date: " << date << endl;
		cout << "Time: " << time << endl;
		cout << "Status: " << status << endl;
		cout << "=========================================\n" << endl;
		
		fstream appfile(appointmentFile, ios::app);
		appfile << appointmentID << "|" << patient.getname() << "|" << doctor.getname() << "|" << date << "|" << time << "|" << status << endl;
		appfile.close();
	 }
	 
	 void display() {
		cout << "\n===== Appointment Details =====" << endl;
		cout << "Appointment ID: " << appointmentID << endl;
		cout << "Patient: " << patient.getname() << endl;
		cout << "Doctor: " << doctor.getname() << endl;
		cout << "Date: " << date << endl;
		cout << "Time: " << time << endl;
		cout << "Status: " << status << endl;
		cout << "==============================\n" << endl;
	 }
};

class Room{
	int roomNO;
	string roomType;
	bool isOccupied;

	public:
	 Room(){
		roomNO = 0;
		roomType = "";
		isOccupied = 0;
	 }

	 string getRoomType() const{
		return roomType;
	 }
	 
	 Room(int ro, string rT, bool isO){
		roomNO = ro;
		roomType = rT;
		isOccupied = isO;
		
		fstream roomfile(roomFile, ios::app);
		roomfile << roomNO << "|" << roomType << "|" << (isOccupied ? "Occupied" : "Available") << endl;
		roomfile.close();
	 }
	 
	 void display() {
		cout << "\n===== Room Details =====" << endl;
		cout << "Room Number: " << roomNO << endl;
		cout << "Room Type: " << roomType << endl;
		cout << "Status: " << (isOccupied ? "Occupied" : "Available") << endl;
		cout << "========================\n" << endl;
	 }
};

class MedicalRecord{
	int recordID;
	string diagnosis;
	string prescription;
	string date;

	public:
	 MedicalRecord(){
		recordID = 0;
		diagnosis = "";
		prescription = "";
		date = "";
	 }

	 MedicalRecord(int rID, string di, string pres, string d){
		recordID = rID;
		diagnosis = di;
		prescription = pres;
		date = d;
	 }

	 void addEntry(){
		cout << "\n===== Medical Record Added =====" << endl;
		cout << "Record ID: "<< recordID << endl;
		cout << "Diagnosis: " << diagnosis << endl;
		cout << "Prescription: " << prescription << endl;
		cout << "Date: " << date << endl;
		cout << "===============================\n" << endl;
		
		fstream medfile(medicalRecordFile, ios::app);
		medfile << recordID << "|" << diagnosis << "|" << prescription << "|" << date << endl;
		medfile.close();
	 }
};

class Bill{
	Patient p1;
	Room r1;
	int billID;
	int amount;
	bool paymentStatus;
	string itemList[50];
	int itemCount;
	int roomCharges;
	
	public: 
	 Bill(){
		billID = 0;
		amount = 0;
		paymentStatus = false;
		for(int i = 0;i<50;i++){
			itemList[i] = "";
		}
		roomCharges = 0;
		itemCount = 0;
	 }

	 Bill(Patient p, Room r, int bid){
		p1 = p;
		r1 = r;
		billID = bid;
		paymentStatus = false;
		itemCount = 0;
	 }
	 
	 void addItem(string item) {
		 if(itemCount < 50) {
			 itemList[itemCount] = item;
			 itemCount++;
		 }
	 }
	 
	 void generateBill(){
		 if(r1.getRoomType() == "Ward"){
			 roomCharges = 600;
		}
		else if (r1.getRoomType() == "ICU"){
			roomCharges = 3000;
		}
		else{
			roomCharges = 1500;
		}
		
		amount = itemCount * 100 + roomCharges; // 100 per item as default
		
		cout << "\n===== Bill Generated =====" << endl;
		cout << "Bill ID: " << billID << endl;
		cout << "Patient: " << p1.getname() << endl;
		cout << "Room Type: " << r1.getRoomType() << endl;
		cout << "Room Charges: $" << roomCharges << endl;
		cout << "Items (" << itemCount << "): ";
		for(int i = 0; i < itemCount; i++){
			cout << itemList[i];
			if(i != itemCount-1) cout << ", ";
		}
		cout << "\nTotal Amount: $" << amount << endl;
		cout << "=========================\n" << endl;
		
		fstream billfile(billFile, ios::app);
		billfile << billID << "|" << p1.getname() << "|" << r1.getRoomType() << "|" << amount << "|Generated" << endl;
		billfile.close();
	}
	
	 void makePayment(){
		cout << "\n===== Payment Receipt =====" << endl;
		p1.display();
		cout << "Bill ID: " << billID << endl;
		cout << "Amount Paid: $" << amount << endl;
		cout << "Payment Status: PAID" << endl;
		cout << "===========================\n" << endl;
		
		paymentStatus = true;
		fstream billfile(billFile, ios::app);
		billfile << billID << "|" << p1.getname() << "|" << amount << "|Paid" << endl;
		billfile.close();
	 }
};

class Hospital{
	Patient *patients[100];
	int pCount;
	Doctor *doctors[40];
	int dCount;
	Room *rooms[150];
	int rCount;
	
	public:
	 Hospital(){
		pCount = 0;
		dCount = 0;
		rCount = 0;
	 }
	 
	 void addDoctor(Doctor *d){
		if(dCount < 40){
			doctors[dCount] = d;
			dCount++;
			cout << "Doctor added to hospital system successfully." << endl;
		}
		else{
			cout << "Doctor limit reached!" << endl;
		}
	 }
	 
	 void addPatient(Patient *p){
		if(pCount < 100){
			patients[pCount] = p;
			pCount++;
		}
		else{
			cout << "Patient limit reached!" << endl;
		}
	 }
	 
	 void viewAllPatients() {
		 cout << "\n===== All Patients =====" << endl;
		 ifstream patientfile(patientFile);
		 string line;
		 int count = 1;
		 
		 if(!patientfile.is_open()) {
			 cout << "No patient records found!" << endl;
			 return;
		 }
		 
		 while(getline(patientfile, line)){
			 stringstream ss(line);
			 string patid, n, a, ad, p, bl, date;
			 getline(ss, patid, '|');
			 getline(ss, n, '|');
			 getline(ss, a, '|');
			 getline(ss, ad, '|');
			 getline(ss, p, '|');
			 getline(ss, bl, '|');
			 getline(ss, date, '|');
			 
			 cout << count << ". ID: " << patid << ", Name: " << n << ", Age: " << a 
				  << ", Blood Group: " << bl << ", Admission Date: " << date << endl;
			 count++;
		 }
		 patientfile.close();
		 
		 if(count == 1) {
			 cout << "No patients registered yet!" << endl;
		 }
		 cout << "=========================\n" << endl;
	 }
	 
	 void viewAllDoctors() {
		 cout << "\n===== All Doctors =====" << endl;
		 ifstream doctorfile(doctorFile);
		 string line;
		 int count = 1;
		 
		 if(!doctorfile.is_open()) {
			 cout << "No doctor records found!" << endl;
			 return;
		 }
		 
		 while(getline(doctorfile, line)){
			 stringstream ss(line);
			 string id, n, a, ad, p, spec, lic, sch;
			 getline(ss, id, '|');
			 getline(ss, n, '|');
			 getline(ss, a, '|');
			 getline(ss, ad, '|');
			 getline(ss, p, '|');
			 getline(ss, spec, '|');
			 getline(ss, lic, '|');
			 getline(ss, sch, '|');
			 
			 cout << count << ". ID: " << id << ", Name: Dr. " << n << ", Specialization: " << spec 
				  << ", License: " << lic << endl;
			 count++;
		 }
		 doctorfile.close();
		 
		 if(count == 1) {
			 cout << "No doctors registered yet!" << endl;
		 }
		 cout << "========================\n" << endl;
	 }
	 
	 void viewAllAppointments() {
		 cout << "\n===== All Appointments =====" << endl;
		 ifstream appfile(appointmentFile);
		 string line;
		 int count = 1;
		 
		 if(!appfile.is_open()) {
			 cout << "No appointment records found!" << endl;
			 return;
		 }
		 
		 while(getline(appfile, line)){
			 stringstream ss(line);
			 string appid, pname, dname, date, time, status;
			 getline(ss, appid, '|');
			 getline(ss, pname, '|');
			 getline(ss, dname, '|');
			 getline(ss, date, '|');
			 getline(ss, time, '|');
			 getline(ss, status, '|');
			 
			 cout << count << ". App ID: " << appid << ", Patient: " << pname 
				  << ", Doctor: " << dname << ", Date: " << date << " " << time 
				  << ", Status: " << status << endl;
			 count++;
		 }
		 appfile.close();
		 
		 if(count == 1) {
			 cout << "No appointments scheduled yet!" << endl;
		 }
		 cout << "============================\n" << endl;
	 }
	 
	 void viewAllEmployees() {
		 cout << "\n===== All Employees =====" << endl;
		 ifstream empfile(adminStaffFile);
		 string line;
		 int count = 1;
		 
		 if(!empfile.is_open()) {
			 cout << "No employee records found!" << endl;
			 return;
		 }
		 
		 while(getline(empfile, line)){
			 stringstream ss(line);
			 string n, a, ad, p, dept;
			 getline(ss, n, '|');
			 getline(ss, a, '|');
			 getline(ss, ad, '|');
			 getline(ss, p, '|');
			 getline(ss, dept, '|');
			 
			 cout << count << ". Name: " << n << ", Age: " << a 
				  << ", Department: " << dept << ", Phone: " << p << endl;
			 count++;
		 }
		 empfile.close();
		 
		 if(count == 1) {
			 cout << "No employees registered yet!" << endl;
		 }
		 cout << "==========================\n" << endl;
	 }
	 
	 void viewHistory() {
		 cout << "\n===== System Logs =====" << endl;
		 cout << "1. Patient Records" << endl;
		 viewAllPatients();
		 cout << "2. Doctor Records" << endl;
		 viewAllDoctors();
		 cout << "3. Appointment Records" << endl;
		 viewAllAppointments();
		 cout << "4. Employee Records" << endl;
		 viewAllEmployees();
		 cout << "==========================\n" << endl;
	 }
	 
	 void bookNewAppointment() {
		 cout << "\n===== Book New Appointment =====" << endl;
		 string pname, dname, date, time;
		 int appID;
		 
		 cout << "Enter Appointment ID: ";
		 cin >> appID;
		 cin.ignore();
		 
		 cout << "Enter Patient Name: ";
		 getline(cin, pname);
		 
		 cout << "Enter Doctor Name: ";
		 getline(cin, dname);
		 
		 cout << "Enter Date (DD-MM-YYYY): ";
		 getline(cin, date);
		 
		 cout << "Enter Time (HH:MM): ";
		 getline(cin, time);
		 
		 Patient tempPatient(0, "", "", pname, 0, "", "");
		 Doctor tempDoctor(0, 0, "", "", "", "", dname, 0, "", "");
		 
		 Appointment newAppointment(tempPatient, tempDoctor, appID, date, time, "Scheduled");
		 newAppointment.bookAppointment();
		 
		 cout << "Appointment booked successfully!" << endl;
	 }
};

class UserAuthentication {
	private:
		string username;
		string password;
		string userRole;

	public:
	    UserAuthentication() {
			username = "";
			password = "";
			userRole = "";
		}
		
		UserAuthentication(string user, string pass, string ur) : username(user), password(pass), userRole(ur) {
		}

		void registerUser(string user, string pass, string role) {
			username = user;
			password = pass;
			userRole = role;
			fstream authfile("userAuthFile.txt", ios::app);
			authfile << username << "|" << password << "|" << userRole << endl;
			authfile.close();
			cout << "User " << username << " registered successfully with role " << userRole << "." << endl;
		}

		bool verifyRole(string requiredRole) {
			return (userRole == requiredRole);
		}

		bool login(string user, string pass) {
			fstream authfile("userAuthFile.txt");
			string line, u, p, r;
			bool found = false;
			
			if(!authfile.is_open()) {
				cout << "No user database found!" << endl;
				return false;
			}
			
			while (getline(authfile, line)) {
				stringstream ss(line);
				getline(ss, u, '|');
				getline(ss, p, '|');
				getline(ss, r, '|');
				if (u == user && p == pass) {
					username = user;
					password = pass;
					userRole = r;
					found = true;
					break;
				}
			}
			authfile.close();
			return found;
		}

		void logout() {
			cout << "User " << username << " logged out successfully." << endl;
			username = "";
			password = "";
			userRole = "";
		}
		
		string getUserRole() {
			return userRole;
		}
		
		string getUsername() {
			return username;
		}
};

void adminMenu(Hospital &hospital) {
	int choice;
	do {
		cout << "\n===== ADMIN MENU =====" << endl;
		cout << "1- Add new doctor" << endl;
		cout << "2- Add new employee" << endl;
		cout << "3- Add new operator" << endl;
		cout << "4- Hospital Details" << endl;
		cout << "5- History" << endl;
		cout << "6- Logout" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		
		switch (choice) {
			case 1: {
				cout << "\n=== Add New Doctor ===" << endl;
				string name, specialization, license, schedule, address, phone, doj;
				int id, age;
				double salary;
				
				cout << "Enter Doctor ID: ";
				cin >> id;
				cin.ignore();
				cout << "Enter Name: ";
				getline(cin, name);
				cout << "Enter Age: ";
				cin >> age;
				cin.ignore();
				cout << "Enter Address: ";
				getline(cin, address);
				cout << "Enter Phone: ";
				getline(cin, phone);
				cout << "Enter Specialization: ";
				getline(cin, specialization);
				cout << "Enter License Number: ";
				getline(cin, license);
				cout << "Enter Schedule (e.g., Mon-Fri 9AM-5PM): ";
				getline(cin, schedule);
				cout << "Enter Date of Joining: ";
				getline(cin, doj);
				cout << "Enter Salary: ";
				cin >> salary;
				
				Doctor* newDoctor = new Doctor(id, salary, doj, specialization, license, schedule, name, age, address, phone);
				newDoctor->saveData();
				hospital.addDoctor(newDoctor);
				cout << "Doctor added successfully!" << endl;
				break;
			}
			case 2: {
				cout << "\n=== Add New Employee ===" << endl;
				string name, department, address, phone, doj;
				int id, age, salary;
				
				cout << "Enter Employee ID: ";
				cin >> id;
				cin.ignore();
				cout << "Enter Name: ";
				getline(cin, name);
				cout << "Enter Age: ";
				cin >> age;
				cin.ignore();
				cout << "Enter Address: ";
				getline(cin, address);
				cout << "Enter Phone: ";
				getline(cin, phone);
				cout << "Enter Department: ";
				getline(cin, department);
				cout << "Enter Date of Joining: ";
				getline(cin, doj);
				cout << "Enter Salary: ";
				cin >> salary;
				
				AdminStaff newEmployee(department, id, salary, doj, name, age, address, phone);
				newEmployee.manageStaff();
				cout << "Employee added successfully!" << endl;
				break;
			}
			case 3: {
				cout << "\n=== Add New Operator ===" << endl;
				string username, password;
				cout << "Enter Username for new operator: ";
				cin >> username;
				cout << "Enter Password: ";
				cin >> password;
				
				UserAuthentication auth;
				auth.registerUser(username, password, "Operator");
				cout << "Operator registered successfully!" << endl;
				break;
			}
			case 4: {
				int subChoice;
				cout << "\n=== Hospital Details ===" << endl;
				cout << "1- All Patients" << endl;
				cout << "2- All Doctors" << endl;
				cout << "3- All Appointments" << endl;
				cout << "4- All Employees" << endl;
				cout << "Enter choice: ";
				cin >> subChoice;
				
				switch(subChoice) {
					case 1: hospital.viewAllPatients(); break;
					case 2: hospital.viewAllDoctors(); break;
					case 3: hospital.viewAllAppointments(); break;
					case 4: hospital.viewAllEmployees(); break;
					default: cout << "Invalid choice!" << endl;
				}
				break;
			}
			case 5:
				hospital.viewHistory();
				break;
			case 6:
				cout << "Logging out..." << endl;
				return;
			default:
				cout << "Invalid choice! Please try again." << endl;
		}
	} while (choice != 6);
}

void doctorMenu(UserAuthentication &auth, Hospital &hospital) {
	int choice;
	do {
		cout << "\n===== DOCTOR MENU =====" << endl;
		cout << "Welcome Dr. " << auth.getUsername() << endl;
		cout << "1- View Appointments" << endl;
		cout << "2- View Schedule" << endl;
		cout << "3- Add Diagnosis" << endl;
		cout << "4- View All Appointments" << endl;
		cout << "5- Logout" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		
		switch (choice) {
			case 1: {
				cout << "\n=== My Appointments ===" << endl;
				Doctor tempDoctor(0, 0, "", "", "", "", auth.getUsername(), 0, "", "");
				tempDoctor.viewMyAppointments();
				break;
			}
			case 2: {
				cout << "\n=== My Schedule ===" << endl;
				Doctor tempDoctor(0, 0, "", "", "", "", auth.getUsername(), 0, "", "");
				tempDoctor.viewSchedule();
				break;
			}
			case 3: {
				cout << "\n=== Add Diagnosis ===" << endl;
				int patientID;
				string diagnosis;
				cout << "Enter Patient ID: ";
				cin >> patientID;
				cin.ignore();
				cout << "Enter Diagnosis: ";
				getline(cin, diagnosis);
				
				Doctor tempDoctor(0, 0, "", "", "", "", auth.getUsername(), 0, "", "");
				tempDoctor.addDiagnosis(patientID, diagnosis);
				break;
			}
			case 4:
				hospital.viewAllAppointments();
				break;
			case 5:
				cout << "Logging out..." << endl;
				return;
			default:
				cout << "Invalid choice! Please try again." << endl;
		}
	} while (choice != 5);
}

void operatorMenu(Hospital &hospital) {
	int choice;
	do {
		cout << "\n===== OPERATOR MENU =====" << endl;
		cout << "1- Add a patient" << endl;
		cout << "2- Book Appointment" << endl;
		cout << "3- Generate Bill" << endl;
		cout << "4- Process Payment" << endl;
		cout << "5- View History" << endl;
		cout << "6- Logout" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		
		switch (choice) {
			case 1: {
				cout << "\n=== Add New Patient ===" << endl;
				int id, age;
				string name, bloodGroup, date, address, phone;
				
				cout << "Enter Patient ID: ";
				cin >> id;
				cin.ignore();
				cout << "Enter Name: ";
				getline(cin, name);
				cout << "Enter Age: ";
				cin >> age;
				cin.ignore();
				cout << "Enter Address: ";
				getline(cin, address);
				cout << "Enter Phone: ";
				getline(cin, phone);
				cout << "Enter Blood Group: ";
				getline(cin, bloodGroup);
				cout << "Enter Date of Admission (DD-MM-YYYY): ";
				getline(cin, date);
				
				Patient* newPatient = new Patient(id, bloodGroup, date, name, age, address, phone);
				newPatient->Register();
				hospital.addPatient(newPatient);
				delete newPatient;
				break;
			}
			case 2:
				hospital.bookNewAppointment();
				break;
			case 3: {
				cout << "\n=== Generate Bill ===" << endl;
				string pname, roomType;
				int billID, patientID;
				
				cout << "Enter Bill ID: ";
				cin >> billID;
				cin.ignore();
				cout << "Enter Patient Name: ";
				getline(cin, pname);
				cout << "Enter Room Type (ICU/Private/Ward): ";
				getline(cin, roomType);
				
				Patient tempPatient(0, "", "", pname, 0, "", "");
				Room tempRoom(0, roomType, true);
				Bill bill(tempPatient, tempRoom, billID);
				
				int itemCount;
				cout << "Enter number of items: ";
				cin >> itemCount;
				cin.ignore();
				
				for(int i = 0; i < itemCount; i++) {
					string item;
					cout << "Enter item " << (i+1) << ": ";
					getline(cin, item);
					bill.addItem(item);
				}
				
				bill.generateBill();
				break;
			}
			case 4: {
				cout << "\n=== Process Payment ===" << endl;
				string pname;
				int billID;
				
				cout << "Enter Bill ID: ";
				cin >> billID;
				cin.ignore();
				cout << "Enter Patient Name: ";
				getline(cin, pname);
				
				Patient tempPatient(0, "", "", pname, 0, "", "");
				Room tempRoom(0, "", true);
				Bill bill(tempPatient, tempRoom, billID);
				bill.makePayment();
				break;
			}
			case 5:
				hospital.viewHistory();
				break;
			case 6:
				cout << "Logging out..." << endl;
				return;
			default:
				cout << "Invalid choice! Please try again." << endl;
		}
	} while (choice != 6);
}

void mainMenu() {
	Hospital hospital;
	UserAuthentication auth;
	int mainChoice;
	
	fstream checkFile("userAuthFile.txt");
	if (!checkFile.is_open()) {
		auth.registerUser("admin", "admin123", "Admin");
		auth.registerUser("doctor1", "doc123", "Doctor");
		auth.registerUser("operator1", "op123", "Operator");
		cout << "Default users created successfully!" << endl;
		cout << "Admin: admin/admin123" << endl;
		cout << "Doctor: doctor1/doc123" << endl;
		cout << "Operator: operator1/op123" << endl;
	}
	checkFile.close();
	
	do {
		cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====" << endl;
		cout << "=====================================" << endl;
		cout << "1- Admin Login" << endl;
		cout << "2- Doctor Login" << endl;
		cout << "3- Operator Login" << endl;
		cout << "4- Exit" << endl;
		cout << "=====================================" << endl;
		cout << "Enter your choice: ";
		cin >> mainChoice;
		
		switch (mainChoice) {
			case 1: {
				string username, password;
				cout << "\n=== ADMIN LOGIN ===" << endl;
				cout << "Username: ";
				cin >> username;
				cout << "Password: ";
				cin >> password;
				
				if (auth.login(username, password)) {
					if (auth.verifyRole("Admin")) {
						cout << "Admin login successful!" << endl;
						adminMenu(hospital);
					} else {
						cout << "Access denied! Admin role required." << endl;
					}
				} else {
					cout << "Login failed! Invalid credentials." << endl;
				}
				break;
			}
			case 2: {
				string username, password;
				cout << "\n=== DOCTOR LOGIN ===" << endl;
				cout << "Username: ";
				cin >> username;
				cout << "Password: ";
				cin >> password;
				
				if (auth.login(username, password)) {
					if (auth.verifyRole("Doctor")) {
						cout << "Doctor login successful!" << endl;
						doctorMenu(auth, hospital);
					} else {
						cout << "Access denied! Doctor role required." << endl;
					}
				} else {
					cout << "Login failed! Invalid credentials." << endl;
				}
				break;
			}
			case 3: {
				string username, password;
				cout << "\n=== OPERATOR LOGIN ===" << endl;
				cout << "Username: ";
				cin >> username;
				cout << "Password: ";
				cin >> password;
				
				if (auth.login(username, password)) {
					if (auth.verifyRole("Operator")) {
						cout << "Operator login successful!" << endl;
						operatorMenu(hospital);
					} else {
						cout << "Access denied! Operator role required." << endl;
					}
				} else {
					cout << "Login failed! Invalid credentials." << endl;
				}
				break;
			}
			case 4:
				cout << "\nThank you for using Hospital Management System!" << endl;
				cout << "Exiting..." << endl;
				return;
			default:
				cout << "Invalid choice! Please try again." << endl;
		}
	} while (mainChoice != 4);
}

int main() {
	mainMenu();
	return 0;
}