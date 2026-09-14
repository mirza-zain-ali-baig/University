#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

// File Handling
// File names:
const string userFile = "users.txt";
const string facilityFile = "facilities.txt";
const string bookingFile = "bookings.txt";
const string requestBookingFile = "requestBookings.txt";
const string billingFile = "billings.txt";
const string reportFile = "reports.txt";
const string studentFile = "student.txt";
const string facultyFile = "faculty.txt";
const string adminFile = "admin.txt";
 
class Facility{
private:
	int facilityID;
	string facilityName;
	string facilityType;
	double pricePerHour;
	string availabilityStatus;


public:
	Facility(){
		facilityID = 0;
		facilityName = "";
		facilityType = "";
		pricePerHour = 0;
		availabilityStatus = "";
	}

	Facility(int fid, string fname, string ftype, double price, string avail)
		:facilityID(fid), facilityName(fname), facilityType(ftype), pricePerHour(price), availabilityStatus(avail) {
	}

	int getFacilityID(){
		return facilityID;
	}

	string getFacilityType(){
		return facilityType;
	}

	double getPricePerHour(){
		return pricePerHour;
	}
	string getFacililtyName() {
		return facilityName;
	}

	string getAvailabilityStatus(){
		return availabilityStatus;
	}

	void display() {
		cout << "\n===== Facility Details =====" << endl;
		cout << "Facility ID: " << facilityID << endl;
		cout << "Facility Name: " << facilityName << endl;
		cout << "Facility Type: " << facilityType << endl;
		cout << "Price per Hour: " << pricePerHour << endl;
		cout << "Availability Status: " << availabilityStatus << endl;
		cout << "============================\n" << endl;
	}

	void addFacility(Facility *f){
		// Write facility to file
		if(f->facilityName.empty()){
			cout << "Facility name cannot be empty." << endl;
			return;
		}
		ofstream facFile(facilityFile, ios::app);
		if(!facFile.is_open()){
			cout << "Error opening facilities file!" << endl;
			return;
		}
		
		facFile << f->facilityID << "|" 
				<< f->facilityName << "|" 
				<< f->facilityType << "|" 
				<< f->pricePerHour << "|" 
				<< f->availabilityStatus << endl; 
		
		facFile.close();
		
		// Display the added facility
		f->display();
		cout << "Facility " << f->facilityName << " added successfully." << endl;
	}

	void editFacility(){
		// Display all facilities from file
		cout << "\n===== Current Facilities =====" << endl;
		ifstream facFile(facilityFile);
		string line;
		int lineNum = 1;
		while (getline(facFile, line))
		{
			cout << lineNum << ". " << line << endl;
			lineNum++;
		}
		facFile.close();

		if(lineNum == 1){
			cout << "No facilities available to edit." << endl;
			return;
		}

		int editLine;
		cout << "\nEnter the line number that you want to edit (1-" << lineNum-1 << "): ";
		cin >> editLine;
		
		if(editLine < 1 || editLine >= lineNum){
			cout << "Invalid line number!" << endl;
			return;
		}

		// Get new facility details
		int fID;
		string fName, fType, aStatus;
		double pHour;
		
		cout << "\nEnter new Facility Details:" << endl;
		cout << "Enter Facility ID: ";
		cin >> fID;
		cin.ignore();
		cout << "Enter Facility Name: ";
		getline(cin, fName);
		cout << "Enter Facility Type: ";
		getline(cin, fType);
		cout << "Enter price per hour: ";
		cin >> pHour;
		cin.ignore();
		cout << "Enter the availability Status: ";
		getline(cin, aStatus);

		// Read from original file and write to temp file
		ifstream file(facilityFile);
		ofstream tempFile("temp.txt");
		
		if(!file.is_open() || !tempFile.is_open()){
			cout << "Error opening files!" << endl;
			return;
		}

		int currentLine = 1;
		while(getline(file, line)){
			if(currentLine == editLine){
				// Write the edited facility data
				tempFile << fID << "|" << fName << "|" << fType << "|" 
						<< pHour << "|" << aStatus << endl;
				cout << "Line " << editLine << " updated successfully." << endl;
			}
			else{
				// Write the original line
				tempFile << line << endl;
			}
			currentLine++;
		}

		file.close();
		tempFile.close();

		// Replace original file with temp file
		remove(facilityFile.c_str());
		rename("temp.txt", facilityFile.c_str());

		// Display updated facility
		cout << "\n===== Updated Facility Details =====" << endl;
		cout << "Facility ID: " << fID << endl;
		cout << "Facility Name: " << fName << endl;
		cout << "Facility Type: " << fType << endl;
		cout << "Price per Hour: " << pHour << endl;
		cout << "Availability Status: " << aStatus << endl;
		cout << "====================================\n" << endl;
		
		cout << "Facility edited successfully." << endl;
	}

	void removeFacility(){
		// Display all facilities from file
		cout << "\n===== Current Facilities =====" << endl;
		ifstream facFile(facilityFile);
		string line;
		int lineNum = 1;
		while (getline(facFile, line))
		{
			cout << lineNum << ". " << line << endl;
			lineNum++;
		}
		facFile.close();

		if(lineNum == 1){
			cout << "No facilities available to remove." << endl;
			return;
		}

		int removeLine;
		cout << "\nEnter the line number that you want to remove (1-" << lineNum-1 << "): ";
		cin >> removeLine;
		
		if(removeLine < 1 || removeLine >= lineNum){
			cout << "Invalid line number!" << endl;
			return;
		}

		// Read from original file and write to temp file (skip the line to remove)
		ifstream file(facilityFile);
		ofstream tempFile("temp.txt");
		
		if(!file.is_open() || !tempFile.is_open()){
			cout << "Error opening files!" << endl;
			return;
		}

		int currentLine = 1;
		while(getline(file, line)){
			if(currentLine != removeLine){
				// Write all lines except the one to remove
				tempFile << line << endl;
			}
			currentLine++;
		}

		file.close();
		tempFile.close();

		// Replace original file with temp file
		remove(facilityFile.c_str());
		rename("temp.txt", facilityFile.c_str());
		
		cout << "Facility on line " << removeLine << " removed successfully." << endl;
	}

	// Static method to view all facilities
	static void viewAllFacilities() {
		ifstream facFile(facilityFile);
		if(!facFile.is_open()){
			cout << "No facilities available or error opening file." << endl;
			return;
		}
		
		cout << "\n===== Available Facilities =====" << endl;
		string line;
		int count = 1;
		while(getline(facFile, line)){
			stringstream ss(line);
			string fid, fname, ftype, price, status;
			
			getline(ss, fid, '|');
			getline(ss, fname, '|');
			getline(ss, ftype, '|');
			getline(ss, price, '|');
			getline(ss, status, '|');
			
			cout << count++ << ". " << "ID: " << fid << ", Name: " << fname 
				 << ", Type: " << ftype << ", Price: $" << price 
				 << "/hr, Status: " << status << endl;
		}
		facFile.close();
		
		if(count == 1){
			cout << "No facilities available." << endl;
		}
		cout << "================================\n" << endl;
	}
	
	// Static method to get facility by ID
	static Facility* getFacilityById(int facilityId) {
		ifstream facFile(facilityFile);
		if(!facFile.is_open()){
			return nullptr;
		}
		
		string line;
		while(getline(facFile, line)){
			stringstream ss(line);
			string fid, fname, ftype, price, status;
			
			getline(ss, fid, '|');
			getline(ss, fname, '|');
			getline(ss, ftype, '|');
			getline(ss, price, '|');
			getline(ss, status, '|');
			
			if(stoi(fid) == facilityId){
				Facility* f = new Facility(stoi(fid), fname, ftype, stod(price), status);
				facFile.close();
				return f;
			}
		}
		
		facFile.close();
		return nullptr;
	}
	
	// Static method to get facility by line number
	static Facility* getFacilityByLine(int lineNum) {
		ifstream facFile(facilityFile);
		if(!facFile.is_open()){
			return nullptr;
		}
		
		string line;
		int currentLine = 1;
		while(getline(facFile, line)){
			if(currentLine == lineNum){
				stringstream ss(line);
				string fid, fname, ftype, price, status;
				
				getline(ss, fid, '|');
				getline(ss, fname, '|');
				getline(ss, ftype, '|');
				getline(ss, price, '|');
				getline(ss, status, '|');
				
				Facility* f = new Facility(stoi(fid), fname, ftype, stod(price), status);
				facFile.close();
				return f;
			}
			currentLine++;
		}
		
		facFile.close();
		return nullptr;
	}

};

class Booking{
	int bookingID;
	int userID;
	string date;
	string startTime;
	string endTime;
	string status;

	protected:
	 Facility *facility;
	public:
	 Booking(){
		bookingID = 0;
		userID = 0;
		date = "";
		startTime = "";
		endTime = "";
		status = "";
		facility = nullptr;
	 }

	 Booking(int bid, int uid, int fid, string d, string st, string et, string s, Facility *f)
		: bookingID(bid), userID(uid), date(d), startTime(st), endTime(et), status(s), facility(f) {
	 }
	 
	 void setBookingID(int id) { bookingID = id; }
	 void setUserID(int id) { userID = id; }
	 void setDate(string d) { date = d; }
	 void setStartTime(string st) { startTime = st; }
	 void setEndTime(string et) { endTime = et; }
	 void setStatus(string s) { status = s; }
	 void setFacility(Facility *f) { facility = f; }
	 
	 int getBookingID() { return bookingID; }
	 int getUserID() { return userID; }
	 string getDate() { return date; }
	 string getStartTime() { return startTime; }
	 string getEndTime() { return endTime; }
	 string getStatus() { return status; }
	 
	 void display() {
		cout << "\n===== Booking Details =====" << endl;                                      
		cout << "Booking ID: " << bookingID << endl;
		cout << "User ID: " << userID << endl;
		if (facility == nullptr){
			cout << "Facility: Not specified" << endl;
		}
		else{
			cout << "Facility name: " << facility->getFacililtyName() << endl;
		}
		cout << "Date: " << date << endl;
		cout << "Start Time: " << startTime << endl;
		cout << "End Time: " << endTime << endl;
		cout << "Status: " << status << endl;
		cout << "===========================\n" << endl;
	 }

	 void requestBooking(Facility *f){
		facility = f;
		status = "requested";
		ofstream inFile(requestBookingFile, ios::app);
		if(!inFile.is_open()){
			cout << "Booking file could not be opened!" << endl;
			return;
		}
		else {
			inFile << bookingID << "|" << userID << "|" << facility->getFacililtyName() << "|" 
				   << date << "|" << startTime << "|" << endTime << "|" << status << endl;
		}
		inFile.close();
		cout << "Booking ID " << bookingID << " has been requested for Facility: " << facility->getFacililtyName() << "." << endl;
	 }

	 void viewBookingDetails(){
		ifstream outFile(bookingFile);
		if(!outFile.is_open()){
			cout << "No bookings available." << endl;
			return;
		}
		else {
			string line;
			int i = 1;
			cout << "\n===== All Bookings =====" << endl;
			while(getline(outFile, line)){
				cout << i++ << ". ";
				int bid, uid;
				string fn, da, st, et, sta, b, u;
				stringstream ss(line);

				getline(ss, b, '|');
				bid = stoi(b); // convert string to int
				getline(ss, u, '|');
				uid = stoi(u); // convert string to int
				getline(ss, fn, '|');
				getline(ss, da, '|');
				getline(ss, st, '|');
				getline(ss, et, '|');
				getline(ss, sta, '|');

				cout << "Booking ID: " << bid << ", User ID: " << uid << ", Facility: " << fn
					 << ", Date: " << da << ", Time: " << st << " to " << et
					 << ", Status: " << sta << endl;
			}
			if(i == 1){
				cout << "No bookings available." << endl;
			}
			cout << "========================\n" << endl;
		}
	 }
	 
	 // View bookings for specific user
	 void viewMyBookings(int userId){
		ifstream outFile(bookingFile);
		if(!outFile.is_open()){
			cout << "No bookings available." << endl;
			return;
		}
		else {
			string line;
			int i = 1;
			bool found = false;
			cout << "\n===== My Bookings =====" << endl;
			while(getline(outFile, line)){
				int bid, uid;
				string fn, da, st, et, sta, b, u;
				stringstream ss(line);

				getline(ss, b, '|');
				bid = stoi(b);
				getline(ss, u, '|');
				uid = stoi(u);
				getline(ss, fn, '|');
				getline(ss, da, '|');
				getline(ss, st, '|');
				getline(ss, et, '|');
				getline(ss, sta, '|');
				
				if(uid == userId){
					cout << i++ << ". ";
					cout << "Booking ID: " << bid << ", Facility: " << fn
						 << ", Date: " << da << ", Time: " << st << " to " << et
						 << ", Status: " << sta << endl;
					found = true;
				}
			}
			if(!found){
				cout << "You have no bookings." << endl;
			}
			cout << "======================\n" << endl;
		}
	 }
	 
	 // View booking requests for specific user
	 void viewMyBookingRequests(int userId){
		ifstream outFile(requestBookingFile);
		if(!outFile.is_open()){
			cout << "No booking requests available." << endl;
			return;
		}
		else {
			string line;
			int i = 1;
			bool found = false;
			cout << "\n===== My Booking Requests =====" << endl;
			while(getline(outFile, line)){
				int bid, uid;
				string fn, da, st, et, sta, b, u;
				stringstream ss(line);

				getline(ss, b, '|');
				bid = stoi(b);
				getline(ss, u, '|');
				uid = stoi(u);
				getline(ss, fn, '|');
				getline(ss, da, '|');
				getline(ss, st, '|');
				getline(ss, et, '|');
				getline(ss, sta, '|');
				
				if(uid == userId){
					cout << i++ << ". ";
					cout << "Booking ID: " << bid << ", Facility: " << fn
						 << ", Date: " << da << ", Time: " << st << " to " << et
						 << ", Status: " << sta << endl;
					found = true;
				}
			}
			if(!found){
				cout << "You have no pending booking requests." << endl;
			}
			cout << "===============================\n" << endl;
		}
	 }

	 void cancelBooking(int userId){
		// First show user's bookings
		viewMyBookings(userId);
		
		int bookingId;
		cout << "Enter the Booking ID you want to cancel (or 0 to go back): ";
		cin >> bookingId;
		
		if(bookingId == 0){
			cout << "Cancellation cancelled." << endl;
			return;
		}
		
		// Read all bookings and create temp file without the cancelled booking
		ifstream outFile(bookingFile);
		ofstream tempFile("temp.txt");
		
		if(!outFile.is_open() || !tempFile.is_open()){
			cout << "Error opening files!" << endl;
			return;
		}
		
		string line;
		bool found = false;
		while(getline(outFile, line)){
			stringstream ss(line);
			string bid, uid, fn, da, st, et, sta;
			
			getline(ss, bid, '|');
			getline(ss, uid, '|');
			getline(ss, fn, '|');
			getline(ss, da, '|');
			getline(ss, st, '|');
			getline(ss, et, '|');
			getline(ss, sta, '|');
			
			int currentBookingId = stoi(bid);
			int currentUserId = stoi(uid);
			
			if(currentBookingId == bookingId && currentUserId == userId){
				// Skip this booking (cancel it)
				found = true;
				cout << "Booking ID " << bookingId << " has been cancelled." << endl;
			}
			else{
				// Write all other bookings
				tempFile << line << endl;
			}
		}
		
		outFile.close();
		tempFile.close();
		
		if(!found){
			cout << "Booking ID " << bookingId << " not found or you don't have permission to cancel it." << endl;
			remove("temp.txt");
			return;
		}
		
		// Replace original file with temp file
		remove(bookingFile.c_str());
		rename("temp.txt", bookingFile.c_str());
	 }

	void viewBookingRequests(){
		cout << "\n===== Booking Requests =====" << endl;
		ifstream outFile(requestBookingFile);
		if(!outFile.is_open()){
			cout << "No booking requests available." << endl;
			return;
		}
		else {
			string line;
			int lineNum = 1;
			while(getline(outFile, line)){
				cout << lineNum << ". " << line << endl;
				lineNum++;
			}
			if(lineNum == 1){
				cout << "No booking requests available." << endl;
			}
			cout << "===========================\n" << endl;
		}
	}

	void approveORrejectBooking(){
		// Show all booking requests
		cout << "\n===== Pending Booking Requests =====" << endl;
		ifstream outFile(requestBookingFile);
		if(!outFile.is_open()){
			cout << "No booking requests available." << endl;
			return;
		}
		
		vector<string> requests;
		string line;
		int lineNum = 1;
		while(getline(outFile, line)){
			cout << lineNum << ". " << line << endl;
			requests.push_back(line);
			lineNum++;
		}
		outFile.close();

		if(requests.empty()){
			cout << "No booking requests available." << endl;
			return;
		}

		int selectedLine;
		cout << "\nEnter the line number of the booking to approve/reject (1-" << requests.size() << "): ";
		cin >> selectedLine;
		
		if(selectedLine < 1 || selectedLine > requests.size()){
			cout << "Invalid line number!" << endl;
			return;
		}

		// Parse the selected request
		string selectedRequest = requests[selectedLine-1];
		stringstream ss(selectedRequest);
		string bid, uid, fn, da, st, et, sta;
		
		getline(ss, bid, '|');
		getline(ss, uid, '|');
		getline(ss, fn, '|');
		getline(ss, da, '|');
		getline(ss, st, '|');
		getline(ss, et, '|');
		getline(ss, sta, '|');

		// Ask for decision
		char decision;
		cout << "\nBooking Details:" << endl;
		cout << "Booking ID: " << bid << endl;
		cout << "User ID: " << uid << endl;
		cout << "Facility: " << fn << endl;
		cout << "Date: " << da << endl;
		cout << "Time: " << st << " to " << et << endl;
		
		cout << "\nEnter 'A' to approve or 'R' to reject: ";
		cin >> decision;

		// Process decision
		if(toupper(decision) == 'A'){
			// Add to approved bookings file
			ofstream bookFile(bookingFile, ios::app);
			if(!bookFile.is_open()){
				cout << "Error opening bookings file!" << endl;
				return;
			}
			bookFile << bid << "|" << uid << "|" << fn << "|" << da << "|" << st << "|" << et << "|Approved" << endl;
			bookFile.close();
			
			// Remove from requests file
			ofstream tempFile("temp.txt");
			for(int i = 0; i < requests.size(); i++){
				if(i != selectedLine-1){
					tempFile << requests[i] << endl;
				}
			}
			tempFile.close();
			
			remove(requestBookingFile.c_str());
			rename("temp.txt", requestBookingFile.c_str());
			
			cout << "Booking ID " << bid << " has been APPROVED." << endl;
		}
		else if(toupper(decision) == 'R'){
			// Remove from requests file (reject)
			ofstream tempFile("temp.txt");
			for(int i = 0; i < requests.size(); i++){
				if(i != selectedLine-1){
					tempFile << requests[i] << endl;
				}
			}
			tempFile.close();
			
			remove(requestBookingFile.c_str());
			rename("temp.txt", requestBookingFile.c_str());
			
			cout << "Booking ID " << bid << " has been REJECTED." << endl;
		}
		else{
			cout << "Invalid decision. No changes made." << endl;
		}
	}
};	

class Billing{
	int billID;
	int bookingID;
	int userID;
	double amount;
	string paymentStatus;
	string paymentDate;

	public:
	 Billing(){
		billID = 0;
		bookingID = 0;
		userID = 0;
		amount = 0;
		paymentStatus = "";
		paymentDate = "";
	 }

	 Billing(int bid, int bkid, int uid, double amt, string pstatus, string pdate)
		: billID(bid), bookingID(bkid), userID(uid), amount(amt), paymentStatus(pstatus), paymentDate(pdate) {
	 }

	 void display() {
		cout << "\n===== Billing Details =====" << endl;
		cout << "Bill ID: " << billID << endl;
		cout << "Booking ID: " << bookingID << endl;
		cout << "User ID: " << userID << endl;
		cout << "Amount: " << amount << endl;
		cout << "Payment Status: " << paymentStatus << endl;
		cout << "Payment Date: " << paymentDate << endl;
		cout << "===========================\n" << endl;
	 }

};

class Report{
	int reportID;
	string reportType;
	string generatedDate;
	int totalBookings;
	double totalRevenue;
	public:
	 Report(){
		reportID = 0;
		reportType = "";
		generatedDate = "";
		totalBookings = 0;
		totalRevenue = 0;
	 }

	 Report(int rid, string rtype, string gdate, int tbookings, double trevenue)
		: reportID(rid), reportType(rtype), generatedDate(gdate), totalBookings(tbookings), totalRevenue(trevenue) {
	 }

	 void display() {
		cout << "\n===== Report Details =====" << endl;
		cout << "Report ID: " << reportID << endl;
		cout << "Report Type: " << reportType << endl;
		cout << "Generated Date: " << generatedDate << endl;
		cout << "Total Bookings: " << totalBookings << endl;
		cout << "Total Revenue: " << totalRevenue << endl;
		cout << "==========================\n" << endl;
	 }

	 void saveReport(){
		ofstream reportSave(reportFile, ios::app);
		if(!reportSave.is_open()){
			cout << "Error opening report file!" << endl;
			return;
		}
		reportSave << reportID << "|" << reportType << "|" << generatedDate << "|" << totalBookings << "|" << totalRevenue << endl; 
		reportSave.close();
		cout << "Report saved successfully to " << reportFile << endl;
	 }
	 
	 void generateReport(){
		// Generate actual report data from files
		ifstream bookFile(bookingFile);
		ifstream facFile(facilityFile);
		
		totalBookings = 0;
		totalRevenue = 0.0;
		
		// Count total bookings
		string line;
		while(getline(bookFile, line)){
			totalBookings++;
			
			// Parse booking to get facility name and calculate revenue
			stringstream ss(line);
			string bid, uid, fn, da, st, et, sta;
			
			getline(ss, bid, '|');
			getline(ss, uid, '|');
			getline(ss, fn, '|');
			getline(ss, da, '|');
			getline(ss, st, '|');
			getline(ss, et, '|');
			getline(ss, sta, '|');
			
			// For simplicity, assume 1 hour booking and get price from facility
			// In real implementation, you would calculate hours and get actual price
			totalRevenue += 100.0; // Placeholder value
		}
		bookFile.close();
		
		// Set report type and date
		reportType = "Monthly Summary";
		// Get current date (simplified)
		generatedDate = "2024-01-01"; // Placeholder
		
		cout << "\n===== Report Generated =====" << endl;
		cout << "Total Bookings: " << totalBookings << endl;
		cout << "Total Revenue: $" << totalRevenue << endl;
		cout << "============================\n" << endl;
	 }
};


class Users{
	private:
	 int id;
	 string name;
	 string password;
	 string role;

	protected:
	 Facility* facilities;
	 Booking* bookings;
	public:
	 Users(){
		id = 0;
		name = "";
		password = "";
		role = "";
		facilities = nullptr;
		bookings = nullptr;
	 }
	 Users(int uid, string uname, string pwd, string r, Facility *f, Booking *b): id(uid), name(uname), password(pwd), role(r), facilities(f), bookings(b) {
	 }

	 int getID() const{
		return id;
	 }

	 string getName() const{
		return name;
	 }
	 
	 string getRole() const{
		return role;
	 }
	 
	 string getPassword() const{
		return password;
	 }
	 
	 void setID(int uid) { id = uid; }
	 void setName(string n) { name = n; }
	 void setPassword(string p) { password = p; }
	 void setRole(string r) { role = r; }
	 
	 virtual void displayInfo() = 0;
};

class Student: public Users{
	string department;
	string semester;
	public:
	 Student(){
		department = "";
		semester = "";
	 }

	 Student(string dep, string sem,  int uid, string uname, string pwd, string r, Facility *f, Booking *b): Users(uid, uname, pwd, r, f, b){
		department = dep;
		semester = sem;
	 }

	 void registerStudent(){
		ofstream inFile(studentFile, ios::app);
		if(!inFile.is_open()){
			cout << "User file could not be opened!" << endl;
			return;
		}
		else {
			inFile << getID() << "|" << getName() << "|" << department << "|" << semester << endl;
		}
		inFile.close();
	 }

	 void displayInfo() {
		cout << "\n===== Student Details =====" << endl;
		cout << "ID: " << getID() << endl;
		cout << "Name: " << getName() << endl;
		cout << "Department: " << department << endl;
		cout << "Semester: " << semester << endl;
		cout << "===========================\n" << endl;
	 }

	 void viewFacilities(){
		Facility::viewAllFacilities();
	 }

	 void requestBooking(int userId){
		// Show available facilities
		Facility::viewAllFacilities();
		
		// Ask for facility selection
		int facilityChoice;
		cout << "Enter the facility number you want to book (or 0 to cancel): ";
		cin >> facilityChoice;
		
		if(facilityChoice == 0){
			cout << "Booking cancelled." << endl;
			return;
		}
		
		// Get the selected facility
		Facility* selectedFacility = Facility::getFacilityByLine(facilityChoice);
		if(!selectedFacility){
			cout << "Invalid facility selection!" << endl;
			return;
		}
		
		// Check if facility is available
		if(selectedFacility->getAvailabilityStatus() != "Available" && 
		   selectedFacility->getAvailabilityStatus() != "available"){
			cout << "Sorry, this facility is not available for booking." << endl;
			delete selectedFacility;
			return;
		}
		
		// Get booking details
		int bookingId;
		string date, startTime, endTime;
		
		cout << "Enter Booking ID: ";
		cin >> bookingId;
		cin.ignore();
		cout << "Enter Date (YYYY-MM-DD): ";
		getline(cin, date);
		cout << "Enter Start Time (HH:MM): ";
		getline(cin, startTime);
		cout << "Enter End Time (HH:MM): ";
		getline(cin, endTime);
		
		// Create booking object
		Booking* booking = new Booking();
		booking->setBookingID(bookingId);
		booking->setUserID(userId);
		booking->setDate(date);
		booking->setStartTime(startTime);
		booking->setEndTime(endTime);
		booking->setFacility(selectedFacility);
		
		// Request the booking
		booking->requestBooking(selectedFacility);
		
		cout << "\nBooking request submitted successfully!" << endl;
		cout << "Booking ID: " << bookingId << endl;
		cout << "Facility: " << selectedFacility->getFacililtyName() << endl;
		cout << "Date: " << date << endl;
		cout << "Time: " << startTime << " to " << endTime << endl;
		cout << "Status: Pending Approval\n" << endl;
		
		delete booking;
		delete selectedFacility;
	 }

	 void viewBookings(int userId){
		if(bookings != nullptr){
			bookings->viewMyBookings(userId);
			bookings->viewMyBookingRequests(userId);
		} else {
			cout << "No booking system available." << endl;
		}
	 }

	 void cancelBooking(int userId){
		if(bookings != nullptr){
			bookings->cancelBooking(userId);
		} else {
			cout << "No booking system available." << endl;
		}
	 }
};

class Faculty: public Users{
	string designation;
	string department;
	public:
	 Faculty(){
		designation = "";
		department = "";
	 }

	 Faculty(string des, string dep, int uid, string uname, string pwd, string r, Facility *f,Booking *b ): Users(uid, uname, pwd, r, f, b){
		designation = des;
		department = dep;
	 }

	 	void registerFaculty(){
		ofstream inFile(facultyFile, ios::app);
		if(!inFile.is_open()){
			cout << "User file could not be opened!" << endl;
			return;
		}
		else {
			inFile << getID() << "|" << getName() << "|" << department << "|" << designation << endl;
		}
		inFile.close();
	 }
	 
	 void displayInfo() {
		cout << "\n===== Faculty Details =====" << endl;
		cout << "ID: " << getID() << endl;
		cout << "Name: " << getName() << endl;
		cout << "Designation: " << designation << endl;
		cout << "Department: " << department << endl;
		cout << "===========================\n" << endl;
	 }

	 void viewFacilities(){
		Facility::viewAllFacilities();
	 }

	 void requestBooking(int userId){
		// Show available facilities
		Facility::viewAllFacilities();
		
		// Ask for facility selection
		int facilityChoice;
		cout << "Enter the facility number you want to book (or 0 to cancel): ";
		cin >> facilityChoice;
		
		if(facilityChoice == 0){
			cout << "Booking cancelled." << endl;
			return;
		}
		
		// Get the selected facility
		Facility* selectedFacility = Facility::getFacilityByLine(facilityChoice);
		if(!selectedFacility){
			cout << "Invalid facility selection!" << endl;
			return;
		}
		
		// Check if facility is available
		if(selectedFacility->getAvailabilityStatus() != "Available" && 
		   selectedFacility->getAvailabilityStatus() != "available"){
			cout << "Sorry, this facility is not available for booking." << endl;
			delete selectedFacility;
			return;
		}
		
		// Get booking details
		int bookingId;
		string date, startTime, endTime;
		
		cout << "Enter Booking ID: ";
		cin >> bookingId;
		cin.ignore();
		cout << "Enter Date (YYYY-MM-DD): ";
		getline(cin, date);
		cout << "Enter Start Time (HH:MM): ";
		getline(cin, startTime);
		cout << "Enter End Time (HH:MM): ";
		getline(cin, endTime);
		
		// Create booking object
		Booking* booking = new Booking();
		booking->setBookingID(bookingId);
		booking->setUserID(userId);
		booking->setDate(date);
		booking->setStartTime(startTime);
		booking->setEndTime(endTime);
		booking->setFacility(selectedFacility);
		
		// Request the booking
		booking->requestBooking(selectedFacility);
		
		cout << "\nBooking request submitted successfully!" << endl;
		cout << "Booking ID: " << bookingId << endl;
		cout << "Facility: " << selectedFacility->getFacililtyName() << endl;
		cout << "Date: " << date << endl;
		cout << "Time: " << startTime << " to " << endTime << endl;
		cout << "Status: Pending Approval\n" << endl;
		
		delete booking;
		delete selectedFacility;
	 }

	 void viewBookings(int userId){
		if(bookings != nullptr){
			bookings->viewMyBookings(userId);
			bookings->viewMyBookingRequests(userId);
		} else {
			cout << "No booking system available." << endl;
		}
	 }

	 void cancelBooking(int userId){
		if(bookings != nullptr){
			bookings->cancelBooking(userId);
		} else {
			cout << "No booking system available." << endl;
		}
	 }

	 
};

class Admin: public Users{
	string roleDescription;
	public:
	 Admin(){
		roleDescription = "";
	 }

	 Admin(string roleDesc, int uid, string uname, string pwd, string r, Facility *f, Booking *b): Users(uid, uname, pwd, r, f, b){
		roleDescription = roleDesc;
	 } 

	 void displayInfo() {
		cout << "\n===== Admin Details =====" << endl;
		cout << "ID: " << getID() << endl;
		cout << "Name: " << getName() << endl;
		cout << "Role Description: " << roleDescription << endl;
		cout << "=========================\n" << endl;
	 }

	 void addFacility(Facility *f){
		if(facilities != nullptr){
			facilities->addFacility(f);
		} else {
			cout << "No facility system available." << endl;
		}
	 }

	 void editFacility(){
		if(facilities != nullptr){
			facilities->editFacility();
		} else {
			cout << "No facility system available." << endl;
		}
	 }

	 void removeFacility(){
		if(facilities != nullptr){
			facilities->removeFacility();
		} else {
			cout << "No facility system available." << endl;
		}
	 }

	 void viewBookingRequests(){
		if(bookings != nullptr){
			bookings->viewBookingRequests();
		} else {
			cout << "No booking system available." << endl;
		}
	 }

	 void approveORrejectBooking(){
		if(bookings != nullptr){
			bookings->approveORrejectBooking();
		} else {
			cout << "No booking system available." << endl;
		}
	 }

	 void generateReports(Report *r){
		if(r != nullptr){
			r->generateReport();
		} else {
			cout << "No report system available." << endl;
		}
	 }


};



class System{
	vector<Users*> users;
	vector<Facility*> facilities;
	vector<Booking*> bookings;
	vector<Billing*> billings;
	vector<Report*> reports;

	public:
	 System(){
		users = {};
		facilities = {};
		bookings = {};
		billings = {};
		reports = {};
	 }

	 void addUser(Users *u){
		users.push_back(u);
	 }
	 void addFacilitys(Facility *f){
		facilities.push_back(f);
	 }
	 void addBooking(Booking *b){
		bookings.push_back(b);
	 }
	 void addBilling(Billing *b){
		billings.push_back(b);
	 }
	 void addReport(Report *r){
		reports.push_back(r);
	 }

	void registerUser(string username, string password, string role){
    ofstream user(userFile, ios::app);
    if (!user.is_open()) {
        cout << "User file could not be opened!" << endl;
        return;
    }

    user << username << "|" << password << "|" << role << endl;
    user.close();

    if(role == "Student" || role == "student"){
        cout << "\n=== Student Registered Successfully ===\n";

        string dep, sem;
        int id;
        cout << "Enter Department: ";
        cin >> dep;
        cout << "Enter Semester: ";
        cin >> sem;
        cout << "Enter ID: ";
        cin >> id;

        Facility* f1 = new Facility();
        Booking* b1 = new Booking();
        Student* s = new Student(dep, sem, id, username, password, role, f1, b1);

        s->registerStudent();
        addUser(s);
    }
    else if(role == "Faculty" || role == "faculty"){
        cout << "\n=== Faculty Registered Successfully ===\n";

        string designation, dep;
        int id;
        cout << "Enter Designation: ";
        cin >> designation;
        cout << "Enter Department: ";
        cin >> dep;
        cout << "Enter ID: ";
        cin >> id;

        Facility* f1 = new Facility();
        Booking* b1 = new Booking();
        Faculty* f = new Faculty(designation, dep, id, username, password, role, f1, b1);

        f->registerFaculty();
        addUser(f);
    }
    else if(role == "Admin" || role == "admin"){
        cout << "\n=== Admin Registered Successfully ===\n";

        string roleDes;
        int id;
        cin.ignore();
        cout << "Enter Role Description: ";
        getline(cin, roleDes);
        cout << "Enter ID: ";
        cin >> id;

        Facility* f1 = new Facility();
        Booking* b1 = new Booking();
        Admin* a = new Admin(roleDes, id, username, password, role, f1, b1);

        addUser(a);
    }
    else{
        cout << "Invalid role!" << endl;
       }
    }


	bool login(string username, string password, string role, int &userId){
    ifstream file(userFile);
    if(!file.is_open()){
        cout << "User file could not be opened!" << endl;
        return false;
    }   

    string line;
    bool found = false;

    while(getline(file, line)){
        stringstream ss(line);
        string u, p, r;
        getline(ss, u, '|');
        getline(ss, p, '|');
        getline(ss, r, '|');

        if(username == u && password == p && role == r){
            found = true;
            
            // Try to get user ID from specific role files
            if(role == "student" || role == "Student"){
                ifstream studentFileRead(studentFile);
                while(getline(studentFileRead, line)){
                    stringstream ss2(line);
                    string sid, sname, sdept, ssem;
                    getline(ss2, sid, '|');
                    getline(ss2, sname, '|');
                    getline(ss2, sdept, '|');
                    getline(ss2, ssem, '|');
                    
                    if(sname == username){
                        userId = stoi(sid);
                        break;
                    }
                }
                studentFileRead.close();
            }
            else if(role == "faculty" || role == "Faculty"){
                ifstream facultyFileRead(facultyFile);
                while(getline(facultyFileRead, line)){
                    stringstream ss2(line);
                    string fid, fname, fdept, fdesig;
                    getline(ss2, fid, '|');
                    getline(ss2, fname, '|');
                    getline(ss2, fdept, '|');
                    getline(ss2, fdesig, '|');
                    
                    if(fname == username){
                        userId = stoi(fid);
                        break;
                    }
                }
                facultyFileRead.close();
            }
            else if(role == "admin" || role == "Admin"){
                userId = 1; // Default admin ID
            }
            
            return found;
        }
    }
    file.close();
    return found;
    }

	 
	void mainMenu(){
        int choice;
        do{
        cout << "\n=== Campus Facility Booking and Billing System ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
		cin.ignore();
		if(cin.fail()){
			cout << "Invalid Input. " << endl;
			return;
		}
		
        switch(choice){
        case 1:{
            string u, p, r;
            cout << "Enter Username: ";
            cin >> u;
            cout << "Enter Password: ";
            cin >> p;
            cout << "Enter Role (Student/Faculty/Admin): ";
            cin >> r;
            registerUser(u, p, r);
            break;
        }
        case 2:{
            string u, p, r;
            int userId = 0;
            cout << "Enter Username: ";
            cin >> u;
            cout << "Enter Password: ";
            cin >> p;
            cout << "Enter Role: ";
            cin >> r;
            
            if(login(u, p, r, userId)){
                    cout << "\nLogin successful. Welcome, " << u << "!\n";
                    if(r == "student" || r == "Student"){
                        int studentChoice;
                        do {
                        cout << "\n=== Student Menu ===" << endl;
                        cout << "1. View Facilities"<< endl;
                        cout << "2. Request Booking"<< endl;
                        cout << "3. View my Bookings"<< endl;
                        cout << "4. Cancel Booking"<< endl;
                        cout << "5. Logout " << endl;
                        cout << "Enter your choice: ";
                        cin >> studentChoice;
                        
                            switch(studentChoice){
                            case 1:{
                                // View all facilities
                                Facility::viewAllFacilities();
                                break;
                            }
                            case 2:{
                                // Request booking
                                Student* s = new Student();
                                s->requestBooking(userId);
                                delete s;
                                break;
                            }
                            case 3:{
                                // View my bookings
                                Facility* f1 = new Facility();
                                Booking* b1 = new Booking();
                                Student* s = new Student("", "", userId, u, p, r, f1, b1);
                                s->viewBookings(userId);
                                delete f1;
                                delete b1;
                                delete s;
                                break;
                            }
							case 4:{
                                // Cancel booking
                                Facility* f1 = new Facility();
                                Booking* b1 = new Booking();
                                Student* s = new Student("", "", userId, u, p, r, f1, b1);
                                s->cancelBooking(userId);
                                delete f1;
                                delete b1;
                                delete s;
                                break;
                            }
                            case 5:{
                                cout << "Logging out..." << endl;
                                break;
                            }
							default:
								cout << "Invalid choice." << endl;
								break;
                            }
                        } while(studentChoice != 5);
                    }
					else if(r == "faculty" || r == "Faculty"){
						int facultyChoice;
						do {
						cout << "\n=== Faculty Menu ===" << endl;
						cout << "1. View Facilities"<< endl;
						cout << "2. Request Booking"<< endl;
						cout << "3. View my Bookings"<< endl;
						cout << "4. Cancel Booking"<< endl;
						cout << "5. Logout " << endl;
						cout << "Enter your choice: ";
						cin >> facultyChoice;
						
							switch(facultyChoice){
							case 1:{
								// View all facilities
                                Facility::viewAllFacilities();
								break;
							}
							case 2:{
                                // Request booking
                                Faculty* f = new Faculty();
                                f->requestBooking(userId);
                                delete f;
								break;
							}
							case 3:{
								// View my bookings
								Facility* f1 = new Facility();
								Booking* b1 = new Booking();
								Faculty* f = new Faculty("", "", userId, u, p, r, f1, b1);
								f->viewBookings(userId);
								delete f1;
								delete b1;
								delete f;
								break;
							}
							case 4:{
								// Cancel booking
								Facility* f1 = new Facility();
								Booking* b1 = new Booking();
								Faculty* f = new Faculty("", "", userId, u, p, r, f1, b1);
								f->cancelBooking(userId);
								delete f1;
								delete b1;
								delete f;
								break;
							}
							case 5:{
								cout << "Logging out..." << endl;
								break;
							}
							default:
								cout << "Invalid choice." << endl;
								break;
						}
						} while(facultyChoice != 5);
					}
					else if(r == "admin" || r == "Admin"){
						int adminChoice;
						do {
						cout << "\n=== Admin Menu ===" << endl;
						cout << "1. Add Facility"<< endl;
						cout << "2. Edit facility"<< endl;
						cout << "3. Remove facility "<< endl;
						cout << "4. View booking requests  " << endl;
						cout << "5. Approve or reject booking " << endl;
						cout << "6. Generate reports " << endl;
						cout << "7. Save report " << endl;
						cout << "8. Logout " << endl;
						cout << "Enter your choice: ";
						cin >> adminChoice;
						
							switch(adminChoice){
							case 1:{
                                // Create a new facility
                                string fname, ftype, avail;
                                int fid;
                                double price;
                                cout << "Enter Facility ID: ";
                                cin >> fid;
								cin.ignore();
                                cout << "Enter Facility Name: ";
                                getline(cin, fname);
                                cout << "Enter Facility Type: ";
                                getline(cin, ftype);
                                cout << "Enter Price per Hour: ";
                                cin >> price;
								cin.ignore();
                                cout << "Enter Availability Status: ";
                                getline(cin, avail);
                                
                                Facility* f = new Facility(fid, fname, ftype, price, avail);
								
								// Create Admin object and add facility
								Facility* f1 = new Facility();
								Booking* b1 = new Booking();
								Admin* a = new Admin("Administrator", 1, "admin", "admin", "admin", f1, b1);
								a->addFacility(f);
								
								delete f;
								delete f1;
								delete b1;
								delete a;
								break;
							}
							case 2:{
								// Create Admin object and edit facility
								Facility* f1 = new Facility();
								Booking* b1 = new Booking();
								Admin* a = new Admin("Administrator", 1, "admin", "admin", "admin", f1, b1);
								a->editFacility();
								
								delete f1;
								delete b1;
								delete a;
								break;
							}
							case 3:{
								// Create Admin object and remove facility
								Facility* f1 = new Facility();
								Booking* b1 = new Booking();
								Admin* a = new Admin("Administrator", 1, "admin", "admin", "admin", f1, b1);
								a->removeFacility();
								
								delete f1;
								delete b1;
								delete a;
								break;
							}
							case 4:{
								// Create Admin object and view booking requests
								Facility* f1 = new Facility();
								Booking* b1 = new Booking();
								Admin* a = new Admin("Administrator", 1, "admin", "admin", "admin", f1, b1);
								a->viewBookingRequests();
								
								delete f1;
								delete b1;
								delete a;
								break;
							}
							case 5:{
								// Create Admin object and approve/reject booking
								Facility* f1 = new Facility();
								Booking* b1 = new Booking();
								Admin* a = new Admin("Administrator", 1, "admin", "admin", "admin", f1, b1);
								a->approveORrejectBooking();
								
								delete f1;
								delete b1;
								delete a;
								break;
							}
							case 6:{
								// Generate report
								Report* r = new Report();
								Facility* f1 = new Facility();
								Booking* b1 = new Booking();
								Admin* a = new Admin("Administrator", 1, "admin", "admin", "admin", f1, b1);
								a->generateReports(r);
								
								delete r;
								delete f1;
								delete b1;
								delete a;
								break;
							}
							case 7:{
                                // Save a report
                                int rid, tbookings;
                                string rtype, gdate;
                                double trevenue;
                                cout << "Enter Report ID: ";
                                cin >> rid;
                                cout << "Enter Report Type: ";
                                cin >> rtype;
                                cout << "Enter Generated Date: ";
                                cin >> gdate;
                                cout << "Enter Total Bookings: ";
                                cin >> tbookings;
                                cout << "Enter Total Revenue: ";
                                cin >> trevenue;
                                
                                Report* r = new Report(rid, rtype, gdate, tbookings, trevenue);
								r->saveReport();
								delete r;
								break;
							}
							case 8:{
								cout << "Logging out..." << endl;
								break;
							}
							default:
								cout << "Invalid choice." << endl;
								break;
						}
						} while(adminChoice != 8);
					}
					else{
						cout << "Invalid role." << endl;

						break;
					}
            }
            else
                cout << "Invalid username, password or role.\n";
            break;
        }
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while(choice != 3);
  }
};

int main(){
	System s1;
	s1.mainMenu();
	return 0;
}