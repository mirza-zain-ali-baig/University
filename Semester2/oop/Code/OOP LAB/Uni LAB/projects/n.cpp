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

		if ( patientID == 0 && name == ""){
			cout << "Patient does not registered. " << endl;
		}
		else {
					
		cout << "\n==== Patient Registered Successfully ===="<<endl;
		cout << "Patient ID is: " << patientID << endl;
		cout << "Name is : " << name << endl;
		cout << "Blood Group is : " << bloodGroup << endl;
		cout << "Age: "<< age << endl;
		cout << "Phone Number and Address: " << phonenumber << ", " << address << endl;
		cout << "Date of Admission is: " << dateOfAdmission << endl;

		

		// Storing data in File
		fstream patientfile(patientFile, ios::app);
		patientfile << patientID << "|" << name << "|" << age << "|" << address << "|" << phonenumber << "|" << bloodGroup << "|" << dateOfAdmission << endl;
		patientfile.close();
		}

	}
	void getMedicalHistory() {
		cout << "==== Medical History Of patient is ====" << endl;
		    fstream patientfile(patientFile);
			string patid,a;
			string bl, date,n, ad, p,line;

			while(getline(patientfile, line)){
				stringstream ss(line);
				getline(ss, patid, '|');
				getline(ss, n, '|');
				getline(ss, a, '|');
				getline(ss, ad, '|');
				getline(ss, p, '|');
				getline(ss, bl, '|');
				getline(ss, date, '|');
				
				cout << "Patient ID is: " << patid << endl;
				cout << "Name is : " << n << endl;
				cout << "Age: "<< a << endl;
				cout << "Phone Number: " << phonenumber <<
				"\nAddress: " << ad << endl;
				cout << "Blood Group is : " << bl << endl;
				cout << "Date of Admission is: " << date << endl;
			}
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
	string diagnosis;
public:
    Doctor(){

	}

	Doctor(int id, double sal, string doj,
		string spec, string lic, string sch,
		string n, int a, string ad, string p, string diag)
		: Employee(id, sal, doj, n, a, ad, p) {
        schedule = sch;
		specialization = spec;
		licenseNumber = lic;
		diagnosis = diag;
	}

	void addDiagnosis(string d) {
		diagnosis = diagnosis + "," + d;
		cout << "Diagnosis: " << diagnosis << endl;
		cout << "Diagnosis added successfully!" << endl;
		// Save updated diagnosis to file
		fstream doctorfile(doctorFile, ios::app);
		doctorfile << "UPDATED_DIAGNOSIS|" << name << "|" << diagnosis << endl;
		doctorfile.close();
	}

	void viewSchedule() {
		cout << "View Schedule: " << schedule << endl;
	}

	double calculateSalary() {
		return salary+7000;   
	}

	void saveData(){
		fstream doctorfile(doctorFile, ios::app);
		doctorfile << name << "|" << age << "|" << address << "|" << phonenumber << "|" << specialization << "|" << licenseNumber << "|" << schedule << "|" << diagnosis << endl;
		doctorfile.close();
	}
    void display() {
        cout << "Doctor Details: " << endl;
        Employee::display();
        cout << "Specialization: " << specialization << endl;
        cout << "License: " << licenseNumber << endl;
        cout << "Schedule: " << schedule << endl;
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
		// Save admin staff data to file
		fstream adminfile(adminStaffFile, ios::app);
		adminfile << name << "|" << age << "|" << address << "|" << phonenumber << "|" << department << endl;
		adminfile.close();
	 }

	 void handleBilling(){
		Employee::display();
		cout << "Salary: " << salary << endl;
		cout << "Department: " << department << endl;
	 }
};

class Appointment{
	Patient patient;
	Doctor doctor;
	int appointmentID;
	string date;
	int time;
	string status;

	public:
	 Appointment(){
		appointmentID = 0;
		date = "";
		time = 0;
		status = "";
	 }

	 Appointment( Patient pat, Doctor doc,int appID, string dat, int t, string st ): patient(pat), doctor(doc){
		appointmentID= appID;
		date = dat;
		time = t;
		status = st;
	 }                                                                              

	 void bookAppointment(){
		cout << " Appointment Booked Successfully! " << endl;
		status = "Booked";

		cout << "Appointment ID: " << appointmentID << endl;
		cout << "Patient Name: " << patient.getname() << endl;
		cout << "Doctor Name: " << doctor.getname() << endl;
		cout << "Status, Time and Date: " << status << ", " << time << ", " << date << endl;
		
		// Save appointment data to file
		fstream appfile(appointmentFile, ios::app);
		appfile << appointmentID << "|" << patient.getname() << "|" << doctor.getname() << "|" << date << "|" << time << "|" << status << endl;
		appfile.close();
	 }

	 void cancelAppointment(){
		cout << "Appointemnt Cancelled Successfully!" << endl;
		status = "Cancelled";

		cout << "Appointment Cancelled Details. " << endl;
		cout << "Appointment ID: " << appointmentID << endl;
		cout << "Patient Name: " << patient.getname() << endl;
		cout << "Doctor Name: " << doctor.getname() << endl;
		cout << "Status, Time and Date: " << status << ", " << time << ", " << date << endl;
		
		// Save cancelled appointment to file
		fstream appfile(appointmentFile, ios::app);
		appfile << appointmentID << "|" << patient.getname() << "|" << doctor.getname() << "|" << date << "|" << time << "|" << status << endl;
		appfile.close();
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
		
		// Save room data to file when created
		fstream roomfile(roomFile, ios::app);
		roomfile << roomNO << "|" << roomType << "|" << (isOccupied ? "Occupied" : "Available") << endl;
		roomfile.close();
	 }
	void checkAvailablity(){
		if(isOccupied == false){
			cout << "Room Available. " << endl;
		}
		// Update room status in file
		fstream roomfile(roomFile, ios::app);
		roomfile << "CHECK_AVAILABILITY|" << roomNO << "|" << (isOccupied ? "Occupied" : "Available") << endl;
		roomfile.close();
	}

	void assignPatient(){
		cout << "Patient Successfully assigned to this roomNO: " << roomNO << endl;
		isOccupied = true;
		// Update room assignment in file
		fstream roomfile(roomFile, ios::app);
		roomfile << "ASSIGN_PATIENT|" << roomNO << "|Occupied" << endl;
		roomfile.close();
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
		cout << "Record added Successfully "<< endl;
		cout << "Record ID: "<< recordID << endl;
		cout << "Diagnosis: " << diagnosis << endl;
		cout << "Prescription: " << prescription << endl;
		cout << "Date: " << date << endl;
		
		// Save medical record to file
		fstream medfile(medicalRecordFile, ios::app);
		medfile << recordID << "|" << diagnosis << "|" << prescription << "|" << date << endl;
		medfile.close();
	 }

	 void getRecordByDate(Patient p){
		if(p.getdate() == date){
			p.display(); 
		}
		else {
			cout << "Record not found with that date!";
		}
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
	 }

	 Bill(Patient p, Room r, int bid, int a, string item[], int n){
		p1 = p;
		r1 = r;
		billID = bid;
		paymentStatus = false;
		for(int i = 0; i<n;i++){
			itemList[i] = item[i];
		}
		itemCount = n;
	 }
	 void generateBill(int amountPerItem){
		 if(r1.getRoomType() == "Ward"){
			 roomCharges = 600;
		}
		else if ( r1.getRoomType() == "ICU"){
			roomCharges = 3000;
		}
		else{
			roomCharges = 1500;
		}
		amount = itemCount * amountPerItem + roomCharges;
		cout << "Bill Generated Successfully!" << endl;
		cout << "Bill Amount: " << amount << endl; 
		
		// Save bill generation to file
		fstream billfile(billFile, ios::app);
		billfile << billID << "|" << p1.getname() << "|" << r1.getRoomType() << "|" << amount << "|Generated" << endl;
		billfile.close();
	}
	
	 void makePayment(){
		cout << "Bill Payment Details. " << endl;
		 p1.display();
		 cout << "Bill Id: " << billID << endl;
		 cout << "Item Lists: ";
		 for(int i = 0;i<itemCount;i++){
			cout << itemList[i] << ", ";
		 }
		 cout << "\n" << endl;

		 cout << "Payment Status: Paid" << endl;
		 paymentStatus = true;
		 
		 // Save payment to file
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
	 Hospital(Patient *p, int pC, Doctor *d, int dC, Room *r, int rC){
		pCount = pC;
		for(int i = 0;i<pCount;i++){
			patients[i] = p+i;
		}
		dCount = dC;
		for(int i = 0;i<dCount;i++){
			doctors[i] = d+i;
		}
		rCount = rC;
		for(int i = 0;i<rCount;i++){
			rooms[i] = r+i;
		}
		
		// Save hospital initialization to file
		fstream hospfile("hospitalFile.txt", ios::app);
		hospfile << "HOSPITAL_INIT|Patients:" << pCount << "|Doctors:" << dCount << "|Rooms:" << rCount << endl;
		hospfile.close();
	 }

	 void addDoctor(Doctor *d){
		if(dCount < 40){
		dCount++;
		doctors[dCount] = d;
		cout << "Doctor added Successfully." << endl;
		
		// Save doctor addition to file
		fstream hospfile("hospitalFile.txt", ios::app);
		hospfile << "ADD_DOCTOR|" << d->getname() << "|TotalDoctors:" << dCount << endl;
		hospfile.close();
		}
		else{
			cout << "Doctor index filled already!" << endl;
		}
	 }

	 void findPatient(Patient p){
		for(int i = 0;i<pCount;i++){
			if(patients[i]->getid()== p.getid()) {
				cout << "Patient Found! Details: ";
				patients[i]->display();
				
				// Save patient search to file
				fstream hospfile("hospitalFile.txt", ios::app);
				hospfile << "FIND_PATIENT|Found|ID:" << p.getid() << "|Name:" << p.getname() << endl;
				hospfile.close();
				return;
			}
		}
		cout << "Patient does not exist. " << endl;
		
		// Save unsuccessful search to file
		fstream hospfile("hospitalFile.txt", ios::app);
		hospfile << "FIND_PATIENT|NotFound|ID:" << p.getid() << endl;
		hospfile.close();
	 }
};

class userAuthentication {
	private:
		string username;
		string password;
		string userRole;

	public:
	    userAuthentication() {
			username = "";
			password = "";
			userRole = "";
		}
		userAuthentication(string user, string pass, string ur) : username(user), password(pass), userRole(ur) {
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

		void verifyRole( string requiredRole) {
			if (userRole == requiredRole) {
				cout << "Access granted for role: " << userRole << endl;
			} 
			else {
				cout << "Access denied. Required role: " << requiredRole << ", but user role is: " << userRole << endl;
			}
		}

		bool login(string user, string pass, string role) {
			fstream authfile("userAuthFile.txt");
			string line, u, p, r;
			while (getline(authfile, line)) {
				stringstream ss(line);
				getline(ss, u, '|');
				getline(ss, p, '|');
				getline(ss, r, '|');
				if (u == user && p == pass) {
					authfile.close();
					verifyRole(role);
					return true;
				}
			}
			authfile.close();
			return false;
		}

		void logout() {
			cout << "User " << username << " logged out successfully." << endl;
		}


		void adminSubMenu(){
			int choice;
			cout << "===== Admin Sub Menu =====" << endl;
			cout << "1-	Add new doctor" << endl;
			cout << "2- Add new employee" << endl;
			cout << "3- Add new operator" << endl;
			cout << "4- Hospital Details" << endl;
			cout << "5- History" << endl;
			cout << "6- Exit" << endl;
			cout << "Enter your choice: ";
			cin >> choice;
			switch (choice) {
				case 1:
					cout << "Managing Users..." << endl;
					break;
				case 2:
					cout << "Viewing Reports..." << endl;
					break;
				case 3:
					cout << "Accessing System Settings..." << endl;
					break;
				case 4:
					logout();
					break;
				default:
					cout << "Invalid choice. Please try again." << endl;
			}
		}

void mainMenu(){

	 int choice;
	 cout << "===== Hospital Management System =====" << endl;
	 cout << "--------------------------------------" << endl;
	 cout << "1- Admin Login" << endl;
	 cout << "2- Doctor Login" << endl;
	 cout << "3- Operator Login" << endl;
	 cout << "4- Exit" << endl;
	 cout << "--------------------------------------" << endl;

	 
	 cout << "Enter the choice: ";
	 cin >> choice;
	 switch (choice){
	 case 1:
		{
			 string adminPass;	
		 string adminUser;
		cout << "Enter the Admin Username: ";
		cin >> adminUser;
		cout << "Enter the Admin Password: ";
		cin >> adminPass;
		
		 if(login(adminUser, adminPass, "Admin")){
			cout << "Admin Login Successful!" << endl;
			cout << "Welcome, " << adminUser << "!" << endl;
			cout << "\n";
			adminSubMenu();
		 }
		 else{
			cout << "Admin Login Failed! Incorrect credentials." << endl;
			mainMenu();
		 }
		break;
		}
	  case 2:
		 // Doctor login logic
		 Hospital h1;
		

		 break;
	  case 3:
		 // Operator login logic
		 break;
	  case 4:
		 cout << "Exiting the system. Goodbye!" << endl;
		 break;
	  default:
		 cout << "Invalid choice. Please try again." << endl;
	 }
};

int main(){
	


	 



    // Patient* p = new Patient[2];
    // Doctor* d = new Doctor[2];
    // Room* r = new Room[3];

    // p[0] = Patient(0,"O+", "25-12-2025", "Ali", 19, "Mughal pura, Lahore", "0325-9809422");
    // p[1] = Patient(1,"O-", "25-12-2025", "Hamza", 20, "Mughal pura, Lahore", "0335-9809429");


	// p[0].display();

    // d[0] = Doctor(0,50000,"09-12-2025", "Cardiologist", "D13990-2025", "hi","Dr. Umer", 40, "Phase 6, Lahore", "090909", "Heart Patient");
    // d[1] = Doctor(1,80000,"3-12-2015", "Orthopedic", "D13ij90-2025", "huh","Dr. Awais", 36, "Phase 3, Lahore", "0908009", "Heart Patient");
	
	// d[0].saveData();
	// d[1].saveData();

    // r[0] = Room(1, "ICU", false);
    // r[1] = Room(2, "Private", false);
    // r[2] = Room(3, "Ward", false);
    
    
    // Hospital h1(p, 2, d, 2, r, 3);
    // h1.findPatient(p[0]);
    
    // AdminStaff admin1("Billing", 101, 30000, "01-01-2023", "John Admin", 35, "Street 1", "1234567890");
    // admin1.manageStaff();
    
    // Appointment app1(p[0], d[0], 1, "26-12-2025", 1400, "Pending");
    // app1.bookAppointment();
    
    // string items[] = {"Medicine", "Test", "Consultation"};
    // Bill bill1(p[0], r[0], 1001, 0, items, 3);
    // bill1.generateBill(500);
    // bill1.makePayment();
    
    // MedicalRecord medRec1(1, "Fever", "Paracetamol 500mg", "25-12-2025");
    // medRec1.addEntry();




    // delete[] d;
    // delete[] p;
    // delete[] r;
    return 0;
} 