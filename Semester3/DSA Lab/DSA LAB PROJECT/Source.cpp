#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cmath>
using namespace std;

// ============================================================
// CONSTANT File Names
// ============================================================
const string customersFile = "Customers.txt";
const string ridersFile = "Riders.txt";
const string restaurantsFile = "Restaurants.txt";
const string ordersFile = "Orders.txt";
const string orderHistoryFile = "OrderHistory.txt";

// ============================================================
//  HELPER FUNCTIONS
// ============================================================
string intToString(int number) {
    if (number == 0) {
        return "0";
    }
    string result = "";
    bool isNegative = false;
    if (number < 0) {
        isNegative = true;
        number = -number;
    }
    while (number > 0) {
        result = char('0' + number % 10) + result;
        number /= 10;
    }
    if (isNegative) {
        return "-" + result;
    }
    else {
        return result;
    }
}

string doubleToString(double number) {
    int integerPart = (int)number;
    double fraction = number - integerPart;
    if (fraction < 0) fraction = -fraction;
    int fractionalPart = (int)(fraction * 100 + 0.5);
    string fracStr = intToString(fractionalPart);
    if (fractionalPart < 10) {
        fracStr = "0" + fracStr;
    }
    return intToString(integerPart) + "." + fracStr;
}

int stringToInt(const string& text) {
    if (text.empty()) {
        return 0;
    }
    int result = 0;
    int startIndex = 0;
    bool isNegative = false;
    if (text[0] == '-') {
        isNegative = true;
        startIndex = 1;
    }
    for (int i = startIndex; i < (int)text.size(); i++) {
        if (text[i] >= '0' && text[i] <= '9') {
            result = result * 10 + (text[i] - '0');
        }
    }
    if (isNegative) {
        return -result;
    }
    else {
        return result;
    }
}

double stringToDouble(const string& text) {
    if (text.empty()) {
        return 0.0;
    }
    double integerPart = 0.0;
    int startIndex = 0;
    bool isNegative = false;
    if (startIndex < (int)text.size() && text[startIndex] == '-') {
        isNegative = true; startIndex++;
    }
    for (; startIndex < (int)text.size() && text[startIndex] != '.'; startIndex++) {
        integerPart = integerPart * 10.0 + (text[startIndex] - '0');
    }
    if (startIndex < (int)text.size() && text[startIndex] == '.') {
        startIndex++;
        double fractionFactor = 0.1;
        for (; startIndex < (int)text.size(); startIndex++) {
            integerPart += (text[startIndex] - '0') * fractionFactor;
            fractionFactor *= 0.1;
        }
    }
    if (isNegative) {
        return -integerPart;
    }
    else {
        return integerPart;
    }
}

void writeToHistoryFile(const string& orderIdentifier, const string& previousStatus,
    const string& newStatus, const string& timeStamp) {
    ofstream historyOutput(orderHistoryFile, ios::app);
    if (historyOutput.is_open()) {
        historyOutput << orderIdentifier << endl;
        historyOutput << previousStatus << endl;
        historyOutput << newStatus << endl;
        historyOutput << timeStamp << endl;
        historyOutput.close();
    }
}

// ============================================================
//  SECTION 1: ENTITY CLASSES  (profile data only - no auth)
// ============================================================

// ============================================================
// 1a. Customer Class
// ============================================================

class Customer {
    string customerId;
    string customerName;
    string customerPhone;
    string customerAddress;
    string customerCategory;   // Regular / Premium / VIP
public:
    // Default Constructor
    Customer() {
        customerId = " ";
        customerName = " ";
        customerPhone = " ";
        customerAddress = " ";
        customerCategory = "Regular";
    }

    // Parameterized Constructor
    Customer(string id, string name, string phone,
        string address, string category) {
        customerId = id;
        customerName = name;
        customerPhone = phone;
        customerAddress = address;
        customerCategory = category;
    }

    // Setters
    void setCustomerId(string id) { customerId = id; }
    void setCustomerName(string newName) { customerName = newName; }
    void setCustomerPhone(string phone) { customerPhone = phone; }
    void setCustomerAddress(string addr) { customerAddress = addr; }
    void setCustomerCategory(string cat) { customerCategory = cat; }

    // Getters
    string getCustomerId() const { return customerId; }
    string getCustomerName() const { return customerName; }
    string getCustomerPhone() const { return customerPhone; }
    string getCustomerAddress() const { return customerAddress; }
    string getCustomerCategory() const { return customerCategory; }

    // File Handling
    void saveFile() {
        ofstream outputFile(customersFile, ios::app);
        if (outputFile.is_open()) {
            outputFile << customerId << endl;
            outputFile << customerName << endl;
            outputFile << customerPhone << endl;
            outputFile << customerAddress << endl;
            outputFile << customerCategory << endl;
            outputFile.close();
        }
        else {
            cout << "\tError While Opening Customers File." << endl;
        }
    }

    bool loadFile(ifstream& inputFile) {
        string id, name, phone, address, category;
        if (!getline(inputFile, id)) {
            return false;
        }
        else {
            customerId = id;
            getline(inputFile, name);
            customerName = name;
            getline(inputFile, phone);
            customerPhone = phone;
            getline(inputFile, address);
            customerAddress = address;
            getline(inputFile, category);
            customerCategory = category;
            return true;
        }
    }

    void saveToStream(ofstream& outputFile) {
        outputFile << customerId << endl;
        outputFile << customerName << endl;
        outputFile << customerPhone << endl;
        outputFile << customerAddress << endl;
        outputFile << customerCategory << endl;
    }

    void display() const {
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t Customer_ID     ||\t -> " << customerId << endl;
        cout << "||" << "\t Name            ||\t -> " << customerName << endl;
        cout << "||" << "\t Phone           ||\t -> " << customerPhone << endl;
        cout << "||" << "\t Address         ||\t -> " << customerAddress << endl;
        cout << "||" << "\t Category        ||\t -> " << customerCategory << endl;
        cout << "==" << "====================================================================" << endl;
    }
};

// ============================================================
// 1b. Rider Class
// ============================================================

class Rider {
    string riderId;
    string riderName;
    string riderPhone;
    string riderCurrentLocation;
    int activeDeliveryCount;
    int maxDeliveryCapacity;
    bool riderAvailable;
public:
    // Default Constructor
    Rider() {
        riderId = " ";
        riderName = " ";
        riderPhone = " ";
        riderCurrentLocation = " ";
        activeDeliveryCount = 0;
        maxDeliveryCapacity = 3;
        riderAvailable = true;
    }

    // Parameterized Constructor
    Rider(string id, string name, string phone,
        string location, int mCapacity) {
        riderId = id;
        riderName = name;
        riderPhone = phone;
        riderCurrentLocation = location;
        activeDeliveryCount = 0;
        maxDeliveryCapacity = mCapacity;
        riderAvailable = true;
    }

    // Setters
    void setRiderId(string id) { riderId = id; }
    void setRiderName(string name) { riderName = name; }
    void setRiderPhone(string phone) { riderPhone = phone; }
    void setRiderCurrentLocation(string loc) { riderCurrentLocation = loc; }
    void setActiveDeliveryCount(int nCount) { activeDeliveryCount = nCount; }
    void setMaxDeliveryCapacity(int nCapacity) { maxDeliveryCapacity = nCapacity; }
    void setRiderAvailable(bool status) { riderAvailable = status; }

    // Getters
    string getRiderId() const { return riderId; }
    string getRiderName() const { return riderName; }
    string getRiderPhone() const { return riderPhone; }
    string getRiderCurrentLocation() const { return riderCurrentLocation; }
    int getActiveDeliveryCount() const { return activeDeliveryCount; }
    int getMaxDeliveryCapacity() const { return maxDeliveryCapacity; }
    bool getRiderAvailable() const { return riderAvailable; }
    int getCurrentWorkload() const { return activeDeliveryCount; }

    bool canAcceptNewOrder() const {
        return riderAvailable && (activeDeliveryCount < maxDeliveryCapacity);
    }

    void assignNewOrder() {
        activeDeliveryCount++;
        if (activeDeliveryCount >= maxDeliveryCapacity) {
            riderAvailable = false;
        }
    }

    void markDeliveryComplete() {
        if (activeDeliveryCount > 0) {
            activeDeliveryCount--;
        }
        if (activeDeliveryCount < maxDeliveryCapacity) {
            riderAvailable = true;
        }
    }

    // File Handling
    void saveFile() {
        ofstream outputFile(ridersFile, ios::app);
        if (outputFile.is_open()) {
            outputFile << riderId << endl;
            outputFile << riderName << endl;
            outputFile << riderPhone << endl;
            outputFile << riderCurrentLocation << endl;
            outputFile << activeDeliveryCount << endl;
            outputFile << maxDeliveryCapacity << endl;
            outputFile << riderAvailable << endl;
            outputFile.close();
        }
        else {
            cout << "\tError While Opening Riders File." << endl;
        }
    }

    bool loadFile(ifstream& inputFile) {
        string id, name, phone, location;
        string activeCount, maxCapacity, available;
        if (!getline(inputFile, id)) {
            return false;
        }
        else {
            riderId = id;
            getline(inputFile, name);
            riderName = name;
            getline(inputFile, phone);
            riderPhone = phone;
            getline(inputFile, location);
            riderCurrentLocation = location;
            getline(inputFile, activeCount);
            activeDeliveryCount = stringToInt(activeCount);
            getline(inputFile, maxCapacity);
            maxDeliveryCapacity = stringToInt(maxCapacity);
            getline(inputFile, available);
            if (available == "1") {
                riderAvailable = true;
            }
            else {
                riderAvailable = false;
            }
            return true;
        }
    }

    void saveToStream(ofstream& outputFile) {
        outputFile << riderId << endl;
        outputFile << riderName << endl;
        outputFile << riderPhone << endl;
        outputFile << riderCurrentLocation << endl;
        outputFile << activeDeliveryCount << endl;
        outputFile << maxDeliveryCapacity << endl;
        outputFile << riderAvailable << endl;
    }

    void display() const {
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t Rider_ID        ||\t -> " << riderId << endl;
        cout << "||" << "\t Name            ||\t -> " << riderName << endl;
        cout << "||" << "\t Phone           ||\t -> " << riderPhone << endl;
        cout << "||" << "\t Location        ||\t -> " << riderCurrentLocation << endl;
        cout << "||" << "\t Deliveries      ||\t -> " << activeDeliveryCount << " / " << maxDeliveryCapacity << endl;
        cout << "||" << "\t Available       ||\t -> " << (riderAvailable ? "YES" : "NO") << endl;
        cout << "==" << "====================================================================" << endl;
    }
};

// ============================================================
// 1c. Restaurant Class
// ============================================================

class Restaurant {
    string restaurantId;
    string restaurantName;
    string restaurantLocation;
    int restaurantCapacity;
    int restaurantCurrentLoad;
public:
    // Default Constructor
    Restaurant() {
        restaurantId = " ";
        restaurantName = " ";
        restaurantLocation = " ";
        restaurantCapacity = 5;
        restaurantCurrentLoad = 0;
    }

    // Parameterized Constructor
    Restaurant(string id, string name, string location, int nCapacity) {
        restaurantId = id;
        restaurantName = name;
        restaurantLocation = location;
        restaurantCapacity = nCapacity;
        restaurantCurrentLoad = 0;
    }

    // Setters
    void setRestaurantId(string id) { restaurantId = id; }
    void setRestaurantName(string name) { restaurantName = name; }
    void setRestaurantLocation(string loc) { restaurantLocation = loc; }
    void setRestaurantCapacity(int nCap) { restaurantCapacity = nCap; }
    void setRestaurantCurrentLoad(int load) { restaurantCurrentLoad = load; }

    // Getters
    string getRestaurantId() const { return restaurantId; }
    string getRestaurantName() const { return restaurantName; }
    string getRestaurantLocation() const { return restaurantLocation; }
    int getRestaurantCapacity() const { return restaurantCapacity; }
    int getRestaurantCurrentLoad() const { return restaurantCurrentLoad; }

    bool isKitchenOverloaded() const {
        return restaurantCurrentLoad >= restaurantCapacity;
    }

    double getKitchenLoadPercent() const {
        if (restaurantCapacity != 0) {
            return (restaurantCurrentLoad * 100.0) / restaurantCapacity;
        }
        else {
            return 100.0;
        }
    }
    int estimateWaitTimeMinutes() const {
        return restaurantCurrentLoad * 8;
    }

    void incrementLoad() {
        if (restaurantCurrentLoad < restaurantCapacity) {
            restaurantCurrentLoad++;
        }
    }
    void decrementLoad() {
        if (restaurantCurrentLoad > 0) {
            restaurantCurrentLoad--;
        }
    }

    // File Handling
    void saveFile() {
        ofstream outputFile(restaurantsFile, ios::app);
        if (outputFile.is_open()) {
            outputFile << restaurantId << endl;
            outputFile << restaurantName << endl;
            outputFile << restaurantLocation << endl;
            outputFile << restaurantCapacity << endl;
            outputFile << restaurantCurrentLoad << endl;
            outputFile.close();
        }
        else {
            cout << "\tError While Opening Restaurants File." << endl;
        }
    }

    bool loadFile(ifstream& inputFile) {
        string id, name, location, capacity, load;
        if (!getline(inputFile, id)) {
            return false;
        }
        else {
            restaurantId = id;
            getline(inputFile, name);
            restaurantName = name;
            getline(inputFile, location);
            restaurantLocation = location;
            getline(inputFile, capacity);
            restaurantCapacity = stringToInt(capacity);
            getline(inputFile, load);
            restaurantCurrentLoad = stringToInt(load);
            return true;
        }
    }

    void saveToStream(ofstream& outputFile) {
        outputFile << restaurantId << endl;
        outputFile << restaurantName << endl;
        outputFile << restaurantLocation << endl;
        outputFile << restaurantCapacity << endl;
        outputFile << restaurantCurrentLoad << endl;
    }

    void display() const {
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t Restaurant_ID   ||\t -> " << restaurantId << endl;
        cout << "||" << "\t Name            ||\t -> " << restaurantName << endl;
        cout << "||" << "\t Location        ||\t -> " << restaurantLocation << endl;
        cout << "||" << "\t Capacity        ||\t -> " << restaurantCapacity << endl;
        cout << "||" << "\t Current_Load    ||\t -> " << restaurantCurrentLoad << " / " << restaurantCapacity << endl;
        cout << "||" << "\t Load_%          ||\t -> " << getKitchenLoadPercent() << "%" << endl;
        cout << "||" << "\t Est_Wait        ||\t -> " << estimateWaitTimeMinutes() << " min" << endl;
        cout << "||" << "\t Status          ||\t -> " << (isKitchenOverloaded() ? "OVERLOADED" : "Available") << endl;
        cout << "==" << "====================================================================" << endl;
    }
};

// ============================================================
// 1d. Order Class
// ============================================================

class Order {
    string orderIdentifier;
    string customerIdentifier;
    string restaurantIdentifier;
    string assignedRiderId;
    string orderedItems;
    int orderPriority;    // 1=Low, 2=Normal, 3=High, 4=VIP
    int preparationTimeMinutes;
    int deliveryDeadlineMinutes;
    double deliveryCostAmount;
    string orderStatus;     // placed/accepted/queued/prepared/assigned/picked/delivered/delayed/cancelled/rerouted
    string orderTimestamp;
public:
    // Default Constructor
    Order() {
        orderIdentifier = " ";
        customerIdentifier = " ";
        restaurantIdentifier = " ";
        assignedRiderId = "Unassigned";
        orderedItems = " ";
        orderPriority = 2;
        preparationTimeMinutes = 15;
        deliveryDeadlineMinutes = 60;
        deliveryCostAmount = 0.0;
        orderStatus = "placed";
        orderTimestamp = " ";
    }

    // Parameterized Constructor
    Order(string newOrderId, string newCustomerId, string newRestaurantId,
        string newItems, int newPriority, int newPrepTime,
        int newDeadline, double newCost) {
        orderIdentifier = newOrderId;
        customerIdentifier = newCustomerId;
        restaurantIdentifier = newRestaurantId;
        assignedRiderId = "Unassigned";
        orderedItems = newItems;
        orderPriority = newPriority;
        preparationTimeMinutes = newPrepTime;
        deliveryDeadlineMinutes = newDeadline;
        deliveryCostAmount = newCost;
        orderStatus = "placed";
        orderTimestamp = " ";
    }

    // Setters
    void setOrderIdentifier(string newId) { orderIdentifier = newId; }
    void setCustomerIdentifier(string newId) { customerIdentifier = newId; }
    void setRestaurantIdentifier(string newId) { restaurantIdentifier = newId; }
    void setAssignedRiderId(string newId) { assignedRiderId = newId; }
    void setOrderedItems(string newItems) { orderedItems = newItems; }
    void setOrderPriority(int newPriority) { orderPriority = newPriority; }
    void setPreparationTimeMinutes(int newTime) { preparationTimeMinutes = newTime; }
    void setDeliveryDeadlineMinutes(int newDeadline) { deliveryDeadlineMinutes = newDeadline; }
    void setDeliveryCostAmount(double newCost) { deliveryCostAmount = newCost; }
    void setOrderStatus(string newStatus) { orderStatus = newStatus; }
    void setOrderTimestamp(string newTimestamp) { orderTimestamp = newTimestamp; }

    // Getters
    string getOrderIdentifier() const { return orderIdentifier; }
    string getCustomerIdentifier() const { return customerIdentifier; }
    string getRestaurantIdentifier() const { return restaurantIdentifier; }
    string getAssignedRiderId() const { return assignedRiderId; }
    string getOrderedItems() const { return orderedItems; }
    int getOrderPriority() const { return orderPriority; }
    int getPreparationTimeMinutes() const { return preparationTimeMinutes; }
    int getDeliveryDeadlineMinutes() const { return deliveryDeadlineMinutes; }
    double getDeliveryCostAmount() const { return deliveryCostAmount; }
    string getOrderStatus() const { return orderStatus; }
    string getOrderTimestamp() const { return orderTimestamp; }

    string getPriorityLabel() const {
        if (orderPriority == 4) {
            return "VIP";
        }
        if (orderPriority == 3) {
            return "High";
        }
        if (orderPriority == 2) {
            return "Normal";
        }
        else {
            return "Low";
        }
    }

    // File Handling
    void saveFile() {
        ofstream outputFile(ordersFile, ios::app);
        if (outputFile.is_open()) {
            outputFile << orderIdentifier << endl;
            outputFile << customerIdentifier << endl;
            outputFile << restaurantIdentifier << endl;
            outputFile << assignedRiderId << endl;
            outputFile << orderedItems << endl;
            outputFile << orderPriority << endl;
            outputFile << preparationTimeMinutes << endl;
            outputFile << deliveryDeadlineMinutes << endl;
            outputFile << deliveryCostAmount << endl;
            outputFile << orderStatus << endl;
            outputFile << orderTimestamp << endl;
            outputFile.close();
        }
    }

    bool loadFile(ifstream& inputFile) {
        string orderId, customerId, restaurantId, riderId;
        string items, priority, prepTime, deadline;
        string cost, status, timestamp;
        if (!getline(inputFile, orderId)) {
            return false;
        }
        else {
            orderIdentifier = orderId;
            getline(inputFile, customerId);
            customerIdentifier = customerId;
            getline(inputFile, restaurantId);
            restaurantIdentifier = restaurantId;
            getline(inputFile, riderId);
            assignedRiderId = riderId;
            getline(inputFile, items);
            orderedItems = items;
            getline(inputFile, priority);
            orderPriority = stringToInt(priority);
            getline(inputFile, prepTime);
            preparationTimeMinutes = stringToInt(prepTime);
            getline(inputFile, deadline);
            deliveryDeadlineMinutes = stringToInt(deadline);
            getline(inputFile, cost);
            deliveryCostAmount = stringToDouble(cost);
            getline(inputFile, status);
            orderStatus = status;
            getline(inputFile, timestamp);
            orderTimestamp = timestamp;
            return true;
        }
    }

    void saveToStream(ofstream& outputFile) {
        outputFile << orderIdentifier << endl;
        outputFile << customerIdentifier << endl;
        outputFile << restaurantIdentifier << endl;
        outputFile << assignedRiderId << endl;
        outputFile << orderedItems << endl;
        outputFile << orderPriority << endl;
        outputFile << preparationTimeMinutes << endl;
        outputFile << deliveryDeadlineMinutes << endl;
        outputFile << deliveryCostAmount << endl;
        outputFile << orderStatus << endl;
        outputFile << orderTimestamp << endl;
    }

    void display() const {
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t Order_ID        ||\t -> " << orderIdentifier << endl;
        cout << "||" << "\t Customer_ID     ||\t -> " << customerIdentifier << endl;
        cout << "||" << "\t Restaurant_ID   ||\t -> " << restaurantIdentifier << endl;
        cout << "||" << "\t Rider_ID        ||\t -> " << assignedRiderId << endl;
        cout << "||" << "\t Items           ||\t -> " << orderedItems << endl;
        cout << "||" << "\t Priority        ||\t -> " << getPriorityLabel() << " (" << orderPriority << ")" << endl;
        cout << "||" << "\t Prep_Time       ||\t -> " << preparationTimeMinutes << " min" << endl;
        cout << "||" << "\t Deadline        ||\t -> " << deliveryDeadlineMinutes << " min" << endl;
        cout << "||" << "\t Cost            ||\t -> Rs. " << deliveryCostAmount << endl;
        cout << "||" << "\t Status          ||\t -> " << orderStatus << endl;
        cout << "||" << "\t Timestamp       ||\t -> " << orderTimestamp << endl;
        cout << "==" << "====================================================================" << endl;
    }
};

// ============================================================
//  SECTION 2: DATA STRUCTURE CLASSES
// ============================================================

class OrderPriorityQueue {
    friend class FoodExpressSystem;
    Order* heapArray;
    int     heapSize;

    bool hasHigherPriority(const Order& firstOrder, const Order& secondOrder) const {
        if (firstOrder.getOrderPriority() != secondOrder.getOrderPriority()) {

            if (firstOrder.getOrderPriority() > secondOrder.getOrderPriority()) {
                return true;
            }
            else {
                return false;
            }

        }
        else {
            if (firstOrder.getDeliveryDeadlineMinutes() < secondOrder.getDeliveryDeadlineMinutes()) {
                return true;
            }
            else {
                return false;
            }

        }
    }

    void bubbleUp(int currentIndex) {
        while (currentIndex > 0) {
            int parentIndex = (currentIndex - 1) / 2;
            if (hasHigherPriority(heapArray[currentIndex], heapArray[parentIndex])) {
                Order temporaryOrder = heapArray[currentIndex];
                heapArray[currentIndex] = heapArray[parentIndex];
                heapArray[parentIndex] = temporaryOrder;
                currentIndex = parentIndex;
            }
            else break;
        }
    }

    void bubbleDown(int currentIndex) {
        while (true) {
            int leftChildIndex = 2 * currentIndex + 1;
            int rightChildIndex = 2 * currentIndex + 2;
            int bestIndex = currentIndex;
            if (leftChildIndex < heapSize && hasHigherPriority(heapArray[leftChildIndex], heapArray[bestIndex])) {
                bestIndex = leftChildIndex;
            }
            if (rightChildIndex < heapSize && hasHigherPriority(heapArray[rightChildIndex], heapArray[bestIndex])) {
                bestIndex = rightChildIndex;
            }
            if (bestIndex == currentIndex) {
                break;
            }
            Order temporaryOrder = heapArray[currentIndex];
            heapArray[currentIndex] = heapArray[bestIndex];
            heapArray[bestIndex] = temporaryOrder;
            currentIndex = bestIndex;
        }
    }

public:
    OrderPriorityQueue() : heapSize(0) {
        heapArray = new Order[500];
    }
    ~OrderPriorityQueue() {
        delete[] heapArray;
    }

    bool isEmpty() const {
        return heapSize == 0;
    }
    int  getSize() const { return heapSize; }

    void insertOrder(const Order& newOrder) {
        if (heapSize >= 500) {
            cout << "\tScheduler is Full!" << endl; return;
        }
        heapArray[heapSize] = newOrder;
        bubbleUp(heapSize);
        heapSize++;
    }

    Order peekTopOrder() const {
        return heapArray[0];
    }

    Order extractHighestPriority() {
        Order topOrder = heapArray[0];
        heapArray[0] = heapArray[heapSize - 1];
        heapSize--;
        bubbleDown(0);
        return topOrder;
    }

    bool cancelOrderById(const string& targetOrderId) {
        for (int i = 0; i < heapSize; i++) {
            if (heapArray[i].getOrderIdentifier() == targetOrderId) {
                heapArray[i] = heapArray[heapSize - 1];
                heapSize--;
                bubbleDown(i);
                bubbleUp(i);
                return true;
            }
        }
        return false;
    }

    bool updateOrderPriority(const string& targetOrderId, int newPriorityLevel) {
        for (int i = 0; i < heapSize; i++) {
            if (heapArray[i].getOrderIdentifier() == targetOrderId) {
                heapArray[i].setOrderPriority(newPriorityLevel);
                bubbleUp(i);
                bubbleDown(i);
                return true;
            }
        }
        return false;
    }

    void displayAllOrders() const {
        if (heapSize == 0) {
            cout << "\tScheduler Queue is Empty." << endl;
            return;
        }

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t      SCHEDULED ORDERS    " << endl;
        cout << "==" << "====================================================================" << endl;

        for (int i = 0; i < heapSize; i++) {
            cout << "||" << "\t [" << i + 1 << "] Order_ID\t||\t -> " << heapArray[i].getOrderIdentifier() << endl;
            cout << "||" << "\t     Priority\t||\t -> " << heapArray[i].getPriorityLabel() << endl;
            cout << "||" << "\t     Status\t||\t -> " << heapArray[i].getOrderStatus() << endl;
            cout << "||" << "\t     Deadline\t||\t -> " << heapArray[i].getDeliveryDeadlineMinutes() << " min" << endl;

            if (i < heapSize - 1) {
                cout << "||" << "----------------------------------------------------------------" << endl;
            }
        }

        cout << "==" << "====================================================================" << endl;

    }
};

// Circular Queue

class KitchenCircularQueue {
    Order* queueArray;
    int frontIndex;
    int rearIndex;
    int orderCount;
    int maximumSize;
    string ownerRestaurantId;
public:
    KitchenCircularQueue() : frontIndex(0), rearIndex(-1), orderCount(0), maximumSize(50) {
        queueArray = new Order[50];
        ownerRestaurantId = " ";
    }
    ~KitchenCircularQueue() {
        delete[] queueArray;
    }

    void setOwnerRestaurantId(string restaurantId) { ownerRestaurantId = restaurantId; }
    string getOwnerRestaurantId() const { return ownerRestaurantId; }
    int getOrderCount() const { return orderCount; }
    bool isQueueEmpty() const {
        return orderCount == 0;
    }
    bool isQueueFull() const {
        return orderCount == maximumSize;
    }

    bool enqueueOrder(const Order& newOrder) {
        if (isQueueFull()) {
            return false;
        }
        rearIndex = (rearIndex + 1) % maximumSize;
        queueArray[rearIndex] = newOrder;
        orderCount++;
        return true;
    }

    Order dequeueOrder() {
        Order frontOrder = queueArray[frontIndex];
        frontIndex = (frontIndex + 1) % maximumSize;
        orderCount--;
        return frontOrder;
    }

    Order peekFrontOrder() const {
        return queueArray[frontIndex];
    }

    bool removeOrderById(const string& targetOrderId) {
        for (int i = 0; i < orderCount; i++) {
            int arrayIndex = (frontIndex + i) % maximumSize;
            if (queueArray[arrayIndex].getOrderIdentifier() == targetOrderId) {
                for (int shiftIndex = i; shiftIndex < orderCount - 1; shiftIndex++) {
                    int currentSlot = (frontIndex + shiftIndex) % maximumSize;
                    int nextSlot = (frontIndex + shiftIndex + 1) % maximumSize;
                    queueArray[currentSlot] = queueArray[nextSlot];
                }
                orderCount--;
                rearIndex = (frontIndex + orderCount - 1 + maximumSize) % maximumSize;
                return true;
            }
        }
        return false;
    }

    void displayQueueContents() const {
        if (isQueueEmpty()) {
            cout << "\tKitchen [" << ownerRestaurantId << "] is empty." << endl;
            return;
        }
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t     SCHEDULED ORDERS    " << endl;
        cout << "==" << "====================================================================" << endl;

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t   KITCHEN [" << ownerRestaurantId << "] (" << orderCount << " Orders)   " << endl;
        cout << "==" << "====================================================================" << endl;

        for (int i = 0; i < orderCount; i++) {
            int arrayIndex = (frontIndex + i) % maximumSize;

            cout << "||" << "\t [" << i + 1 << "] Order_ID\t||\t -> " << queueArray[arrayIndex].getOrderIdentifier() << endl;
            cout << "||" << "\t     Items\t||\t -> " << queueArray[arrayIndex].getOrderedItems() << endl;
            cout << "||" << "\t     Prep Time\t||\t -> " << queueArray[arrayIndex].getPreparationTimeMinutes() << " min" << endl;

            if (i < orderCount - 1) {
                cout << "||" << "----------------------------------------------------------------" << endl;
            }
        }

        cout << "==" << "====================================================================" << endl;
    }
};

// DS-3: Singly Linked List search

struct RiderListNode {
    Rider riderData;
    RiderListNode* next;

    RiderListNode(const Rider& riderRecord) : riderData(riderRecord), next(nullptr) {}
};

class CityRouteGraph;

class RiderLinkedList {
    RiderListNode* head;
    int totalNodes;

public:
    // Constructor
    RiderLinkedList() : head(nullptr), totalNodes(0) {}

    // Destructor
    ~RiderLinkedList() {
        RiderListNode* currentNode = head;
        while (currentNode != nullptr) {
            RiderListNode* tempNode = currentNode->next;
            delete currentNode;
            currentNode = tempNode;
        }
        head = nullptr;
    }

    void insertRiderAtEnd(const Rider& newRider) {
        RiderListNode* newNode = new RiderListNode(newRider);

        if (head == nullptr) {
            head = newNode;
            totalNodes++;
            return;
        }

        RiderListNode* currentNode = head;
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
        totalNodes++;
    }

    Rider* findBestAvailableRider() {
        RiderListNode* currentNode = head;
        RiderListNode* bestRiderNode = nullptr;

        while (currentNode != nullptr) {
            if (currentNode->riderData.canAcceptNewOrder()) {
                if (bestRiderNode == nullptr ||
                    currentNode->riderData.getCurrentWorkload() < bestRiderNode->riderData.getCurrentWorkload()) {
                    bestRiderNode = currentNode;
                }
            }
            currentNode = currentNode->next;
        }

        return (bestRiderNode != nullptr) ? &(bestRiderNode->riderData) : nullptr;
    }

    Rider* findBestAvailableRider(const string& restaurantLocation, const CityRouteGraph& routeGraph);

    Rider* findRiderById(const string& targetRiderId) {
        RiderListNode* currentNode = head;

        while (currentNode != nullptr) {
            if (currentNode->riderData.getRiderId() == targetRiderId) {
                return &(currentNode->riderData);
            }
            currentNode = currentNode->next;
        }
        return nullptr;
    }

    void synchronizeRiderStatus(const string& targetRiderId, int updatedDeliveryCount, bool updatedAvailability) {
        RiderListNode* currentNode = head;

        while (currentNode != nullptr) {
            if (currentNode->riderData.getRiderId() == targetRiderId) {
                currentNode->riderData.setActiveDeliveryCount(updatedDeliveryCount);
                currentNode->riderData.setRiderAvailable(updatedAvailability);
                return;
            }
            currentNode = currentNode->next;
        }
    }

    void displayAllRiders() const {
        if (head == nullptr) {
            cout << "\tNo Riders Registered." << endl;
            return;
        }

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t\t   ACTIVE RIDER POOL (" << totalNodes << ")" << endl;
        cout << "==" << "====================================================================" << endl;

        RiderListNode* currentNode = head;
        int displayIndex = 1;

        while (currentNode != nullptr) {
            cout << "||" << "\t [" << displayIndex++ << "] Rider Record: " << endl;
            currentNode->riderData.display();

            currentNode = currentNode->next;

            if (currentNode != nullptr) {
                cout << "||" << "----------------------------------------------------------------" << endl;
            }
        }
        cout << "==" << "====================================================================" << endl;
    }
};

// DS-4: Adjacency Matrix Graph + Dijkstra

const int MAXIMUM_CITY_LOCATIONS = 15;

class CityRouteGraph {
    double distanceMatrix[MAXIMUM_CITY_LOCATIONS][MAXIMUM_CITY_LOCATIONS];
    string locationNameList[MAXIMUM_CITY_LOCATIONS];
    int totalLocations;
    bool roadBlockedMatrix[MAXIMUM_CITY_LOCATIONS][MAXIMUM_CITY_LOCATIONS];
public:
    CityRouteGraph() : totalLocations(0) {
        for (int i = 0; i < MAXIMUM_CITY_LOCATIONS; i++) {
            locationNameList[i] = "";
            for (int colIndex = 0; colIndex < MAXIMUM_CITY_LOCATIONS; colIndex++) {
                distanceMatrix[i][colIndex] = -1;
                roadBlockedMatrix[i][colIndex] = false;
            }
        }
    }

    int addCityLocation(const string& locationName) {
        if (totalLocations >= MAXIMUM_CITY_LOCATIONS) {
            return -1;
        }
        locationNameList[totalLocations] = locationName;
        return totalLocations++;
    }

    void addBidirectionalRoad(int fromIndex, int toIndex, double distanceKm) {
        if (fromIndex < 0 || toIndex < 0 || fromIndex >= totalLocations || toIndex >= totalLocations) {
            cout << "\t Out Of Locations" << endl;
            return;
        }
        distanceMatrix[fromIndex][toIndex] = distanceKm;
        distanceMatrix[toIndex][fromIndex] = distanceKm;
    }

    void blockRoad(int fromIndex, int toIndex) {
        roadBlockedMatrix[fromIndex][toIndex] = roadBlockedMatrix[toIndex][fromIndex] = true;
    }
    void unblockRoad(int fromIndex, int toIndex) {
        roadBlockedMatrix[fromIndex][toIndex] = roadBlockedMatrix[toIndex][fromIndex] = false;
    }

    int getTotalLocations() const { return totalLocations; }

    int findLocationIndex(const string& locationName) const {
        for (int i = 0; i < totalLocations; i++)
            if (locationNameList[i] == locationName) {
                return i;
            }
        return -1;
    }

    void runDijkstra(int sourceIndex, double shortestDistances[], int previousNodeList[]) const {
        bool visitedNodes[MAXIMUM_CITY_LOCATIONS] = { false };
        for (int nodeIndex = 0; nodeIndex < totalLocations; nodeIndex++) {
            shortestDistances[nodeIndex] = 1e9;
            previousNodeList[nodeIndex] = -1;
        }
        shortestDistances[sourceIndex] = 0;

        for (int iteration = 0; iteration < totalLocations; iteration++) {
            int nearestUnvisited = -1;
            for (int nodeIndex = 0; nodeIndex < totalLocations; nodeIndex++)
                if (!visitedNodes[nodeIndex] && (nearestUnvisited == -1 || shortestDistances[nodeIndex] < shortestDistances[nearestUnvisited]))
                    nearestUnvisited = nodeIndex;
            if (nearestUnvisited == -1 || shortestDistances[nearestUnvisited] >= 1e9) break;
            visitedNodes[nearestUnvisited] = true;
            for (int neighborIndex = 0; neighborIndex < totalLocations; neighborIndex++) {
                if (distanceMatrix[nearestUnvisited][neighborIndex] > 0 &&
                    !roadBlockedMatrix[nearestUnvisited][neighborIndex] &&
                    !visitedNodes[neighborIndex]) {
                    double newDistance = shortestDistances[nearestUnvisited] + distanceMatrix[nearestUnvisited][neighborIndex];
                    if (newDistance < shortestDistances[neighborIndex]) {
                        shortestDistances[neighborIndex] = newDistance;
                        previousNodeList[neighborIndex] = nearestUnvisited;
                    }
                }
            }
        }
    }

    void printShortestRoute(const string& sourceName, const string& destinationName) const {
        int sourceIdx = findLocationIndex(sourceName);

        int destinationIdx = findLocationIndex(destinationName);

        if (sourceIdx == -1 || destinationIdx == -1) {
            cout << "\tLocation not found!" << endl;
            return;
        }
        double shortestDistances[MAXIMUM_CITY_LOCATIONS];

        int previousNodeList[MAXIMUM_CITY_LOCATIONS];
        runDijkstra(sourceIdx, shortestDistances, previousNodeList);
        if (shortestDistances[destinationIdx] >= 1e9) {
            cout << "\tNo route found (road may be blocked)!" << endl;
            return;
        }
        int routePath[MAXIMUM_CITY_LOCATIONS];

        int pathLength = 0;
        int currentNode = destinationIdx;
        while (currentNode != -1) {
            routePath[pathLength++] = currentNode; currentNode = previousNodeList[currentNode];
        }
        cout << "\t====== Shortest Route ======" << endl;
        cout << "\tFrom     : " << sourceName << "  ->  To: " << destinationName << endl;
        cout << "\tRoute    : ";
        for (int pathIndex = pathLength - 1; pathIndex >= 0; pathIndex--) {
            cout << locationNameList[routePath[pathIndex]];
            if (pathIndex > 0) cout << " -> ";
        }
        cout << endl;
        cout << "\tDistance : " << shortestDistances[destinationIdx] << " km" << endl;
        cout << "\tEst. Cost: Rs. " << shortestDistances[destinationIdx] * 15.0 << endl;
        cout << "\t============================" << endl;
    }

    void compareAlternativeRoutes(int sourceIdx, int waypointIdx, int destinationIdx) const {

        double directDistances[MAXIMUM_CITY_LOCATIONS];

        int directPrevious[MAXIMUM_CITY_LOCATIONS];

        runDijkstra(sourceIdx, directDistances, directPrevious);
        double viaDistances[MAXIMUM_CITY_LOCATIONS];

        int viaPrevious[MAXIMUM_CITY_LOCATIONS];
        runDijkstra(waypointIdx, viaDistances, viaPrevious);

        double directRouteCost = directDistances[destinationIdx];

        double viaRouteCost = directDistances[waypointIdx] + viaDistances[destinationIdx];

        cout << "\t====== Route Comparison ======" << endl;
        cout << "\tDirect Route    : " << directRouteCost << " km" << endl;
        cout << "\tVia [" << locationNameList[waypointIdx] << "] : " << viaRouteCost << " km" << endl;
        cout << "\tRecommended     : " << (directRouteCost <= viaRouteCost ? "Direct Route" : "Via " + locationNameList[waypointIdx]) << endl;
        cout << "\t==============================" << endl;
    }

    void displayCityMap() const {

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t\t   CITY LOCATION LIST   " << endl;
        cout << "==" << "====================================================================" << endl;

        for (int locationIdx = 0; locationIdx < totalLocations; locationIdx++) {
            cout << "||" << "\t [" << locationIdx << "] Location\t||\t -> " << locationNameList[locationIdx] << endl;

            if (locationIdx < totalLocations - 1) {
                cout << "||" << "----------------------------------------------------------------" << endl;
            }
        }

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t\tLIVE ROAD NETWORK (KM)   " << endl;
        cout << "==" << "====================================================================" << endl;

        bool hasConnections = false;

        for (int fromIdx = 0; fromIdx < totalLocations; fromIdx++) {
            for (int toIdx = fromIdx + 1; toIdx < totalLocations; toIdx++) {

                if (distanceMatrix[fromIdx][toIdx] > 0) {
                    hasConnections = true;

                    cout << "||" << "\t Route\t\t||\t -> " << locationNameList[fromIdx] << " <-> " << locationNameList[toIdx] << endl;
                    cout << "||" << "\t Distance\t||\t -> " << distanceMatrix[fromIdx][toIdx] << " km" << endl;

                    if (roadBlockedMatrix[fromIdx][toIdx]) {
                        cout << "||" << "\t STATUS\t\t||\t -> [BLOCKED / CLOSED]" << endl;
                    }
                    else {
                        cout << "||" << "\t STATUS\t\t||\t -> [OPERATIONAL]" << endl;
                    }

                    cout << "||" << "----------------------------------------------------------------" << endl;
                }

            }
        }

        if (!hasConnections) {
            cout << "||" << "\t No active road connections established in database.            " << endl;
        }

        cout << "==" << "====================================================================" << endl;
    }
};

Rider* RiderLinkedList::findBestAvailableRider(const string& restaurantLocation, const CityRouteGraph& routeGraph) {
    RiderListNode* currentNode = head;
    RiderListNode* bestRiderNode = nullptr;
    double bestScore = 1e18;
    int restaurantIdx = routeGraph.findLocationIndex(restaurantLocation);
    while (currentNode != nullptr) {
        if (currentNode->riderData.canAcceptNewOrder()) {
            double distance = 0.0;
            if (restaurantIdx != -1) {
                int riderLocIdx = routeGraph.findLocationIndex(currentNode->riderData.getRiderCurrentLocation());
                if (riderLocIdx != -1) {
                    double shortestDistances[MAXIMUM_CITY_LOCATIONS];
                    int previousNodeList[MAXIMUM_CITY_LOCATIONS];
                    routeGraph.runDijkstra(riderLocIdx, shortestDistances, previousNodeList);
                    distance = shortestDistances[restaurantIdx];
                }
            }
            if (distance >= 1e9) {
                distance = 999.0;
            }
            double currentScore = (currentNode->riderData.getCurrentWorkload() * 15.0) + distance;
            if (bestRiderNode == nullptr || currentScore < bestScore) {
                bestRiderNode = currentNode;
                bestScore = currentScore;
            }
        }
        currentNode = currentNode->next;
    }
    return (bestRiderNode != nullptr) ? &(bestRiderNode->riderData) : nullptr;
}

// DS-5: Hash Table
struct HashTableNode {
    string recordKey;
    string recordValue;
    HashTableNode* nextChainNode;

    HashTableNode(const string& key, const string& value)
        : recordKey(key), recordValue(value), nextChainNode(nullptr) {
    }
};

class SearchHashTable {
    static const int TABLE_CAPACITY = 101;
    HashTableNode* tableSlots[TABLE_CAPACITY];

    int computeHashIndex(const string& recordKey) const {
        int hashValue = 0;
        for (int charIndex = 0; charIndex < (int)recordKey.size(); charIndex++) {
            hashValue = (hashValue * 31 + recordKey[charIndex]) % TABLE_CAPACITY;
        }
        return hashValue;
    }

public:
    // Constructor g
    SearchHashTable() {
        for (int i = 0; i < TABLE_CAPACITY; i++) {
            tableSlots[i] = nullptr;
        }
    }

    // Destructor
    ~SearchHashTable() {
        for (int slotIndex = 0; slotIndex < TABLE_CAPACITY; slotIndex++) {
            HashTableNode* currentNode = tableSlots[slotIndex];
            while (currentNode != nullptr) {
                HashTableNode* tempNode = currentNode->nextChainNode;
                delete currentNode;
                currentNode = tempNode;
            }
            tableSlots[slotIndex] = nullptr;
        }
    }

    void insertRecord(const string& recordKey, const string& recordValue) {
        int slotIndex = computeHashIndex(recordKey);
        HashTableNode* currentNode = tableSlots[slotIndex];

        while (currentNode != nullptr) {
            if (currentNode->recordKey == recordKey) {
                currentNode->recordValue = recordValue;
                return;
            }
            currentNode = currentNode->nextChainNode;
        }

        HashTableNode* newNode = new HashTableNode(recordKey, recordValue);
        newNode->nextChainNode = tableSlots[slotIndex];
        tableSlots[slotIndex] = newNode;
    }

    string searchRecord(const string& recordKey) const {
        int slotIndex = computeHashIndex(recordKey);
        HashTableNode* currentNode = tableSlots[slotIndex];

        while (currentNode != nullptr) {
            if (currentNode->recordKey == recordKey) {
                return currentNode->recordValue;
            }
            currentNode = currentNode->nextChainNode;
        }
        return "";
    }

    void displayAllRecords() const {
        int totalRecords = 0;

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t\t   SEARCH INDEX   " << endl;
        cout << "==" << "====================================================================" << endl;

        for (int slotIndex = 0; slotIndex < TABLE_CAPACITY; slotIndex++) {
            HashTableNode* currentNode = tableSlots[slotIndex];

            while (currentNode != nullptr) {
                totalRecords++;

                cout << "||" << "\t Slot Index\t||\t -> [" << slotIndex << "]" << endl;
                cout << "||" << "\t Identifier Key\t||\t -> " << currentNode->recordKey << endl;
                cout << "||" << "\t Account Value\t||\t -> " << currentNode->recordValue << endl;

                currentNode = currentNode->nextChainNode;

                if (currentNode != nullptr) {
                    cout << "||" << "\t                \t||\t    (Chained Collision Node)" << endl;
                    cout << "||" << "----------------------------------------------------------------" << endl;
                }
            }
        }

        if (totalRecords == 0) {
            cout << "||" << "\t Search Index is completely empty.                              " << endl;
        }
        else {
            cout << "||" << "----------------------------------------------------------------" << endl;
            cout << "||" << "\t Total Indexing\t||\t -> " << totalRecords << " Active Records mapped" << endl;
        }

        cout << "==" << "====================================================================" << endl;
    }

    void filterOrdersByRestaurant(const string& restaurantId) const {
        int matchedCount = 0;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "                ORDERS FILTERED BY RESTAURANT: " << restaurantId << endl;
        cout << "==" << "====================================================================" << endl;
        for (int i = 0; i < TABLE_CAPACITY; i++) {
            HashTableNode* cur = tableSlots[i];
            while (cur != nullptr) {
                if (cur->recordValue.rfind("Order|", 0) == 0) {
                    size_t p1 = cur->recordValue.find('|');
                    size_t p2 = cur->recordValue.find('|', p1 + 1);
                    size_t p3 = cur->recordValue.find('|', p2 + 1);
                    size_t p4 = cur->recordValue.find('|', p3 + 1);
                    if (p3 != string::npos) {
                        string restId = (p4 == string::npos) ?
                            cur->recordValue.substr(p3 + 1) :
                            cur->recordValue.substr(p3 + 1, p4 - p3 - 1);
                        if (restId == restaurantId) {
                            matchedCount++;
                            cout << "||" << "\t Order ID   \t||\t -> " << cur->recordKey << endl;
                            string status = (p3 == string::npos) ? "" : cur->recordValue.substr(p2 + 1, p3 - p2 - 1);
                            cout << "||" << "\t Status     \t||\t -> " << status << endl;
                            if (p4 != string::npos) {
                                cout << "||" << "\t Price      \t||\t -> Rs. " << cur->recordValue.substr(p4 + 1) << endl;
                            }
                            cout << "||" << "----------------------------------------------------------------" << endl;
                        }
                    }
                }
                cur = cur->nextChainNode;
            }
        }
        if (matchedCount == 0) {
            cout << "||" << "\t No orders found for Restaurant " << restaurantId << " in Hash Index." << endl;
        }
        else {
            cout << "||" << "\t Found " << matchedCount << " order(s) for Restaurant " << restaurantId << " in Hash Index." << endl;
        }
        cout << "==" << "====================================================================" << endl;
    }

    void filterOrdersByPriceRange(double minPrice, double maxPrice) const {
        int matchedCount = 0;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "                ORDERS FILTERED BY PRICE RANGE: " << minPrice << " - " << maxPrice << endl;
        cout << "==" << "====================================================================" << endl;
        for (int i = 0; i < TABLE_CAPACITY; i++) {
            HashTableNode* cur = tableSlots[i];
            while (cur != nullptr) {
                if (cur->recordValue.rfind("Order|", 0) == 0) {
                    size_t p1 = cur->recordValue.find('|');
                    size_t p2 = cur->recordValue.find('|', p1 + 1);
                    size_t p3 = cur->recordValue.find('|', p2 + 1);
                    size_t p4 = cur->recordValue.find('|', p3 + 1);
                    if (p4 != string::npos) {
                        string priceStr = cur->recordValue.substr(p4 + 1);
                        double price = 0.0;
                        size_t dot = priceStr.find('.');
                        if (dot != string::npos) {
                            string intPart = priceStr.substr(0, dot);
                            string decPart = priceStr.substr(dot + 1);
                            double ip = 0;
                            for (int cIdx = 0; cIdx < (int)intPart.size(); cIdx++) {
                                char c = intPart[cIdx];
                                if (c >= '0' && c <= '9') ip = ip * 10 + (c - '0');
                            }
                            double dp = 0;
                            double divisor = 10;
                            for (int cIdx = 0; cIdx < (int)decPart.size(); cIdx++) {
                                char c = decPart[cIdx];
                                if (c >= '0' && c <= '9') {
                                    dp += (c - '0') / divisor;
                                    divisor *= 10;
                                }
                            }
                            price = ip + dp;
                        }
                        else {
                            for (int cIdx = 0; cIdx < (int)priceStr.size(); cIdx++) {
                                char c = priceStr[cIdx];
                                if (c >= '0' && c <= '9') price = price * 10 + (c - '0');
                            }
                        }
                        if (price >= minPrice && price <= maxPrice) {
                            matchedCount++;
                            cout << "||" << "\t Order ID   \t||\t -> " << cur->recordKey << endl;
                            string status = cur->recordValue.substr(p2 + 1, p3 - p2 - 1);
                            string restId = cur->recordValue.substr(p3 + 1, p4 - p3 - 1);
                            cout << "||" << "\t Restaurant \t||\t -> " << restId << endl;
                            cout << "||" << "\t Status     \t||\t -> " << status << endl;
                            cout << "||" << "\t Price      \t||\t -> Rs. " << priceStr << endl;
                            cout << "||" << "----------------------------------------------------------------" << endl;
                        }
                    }
                }
                cur = cur->nextChainNode;
            }
        }
        if (matchedCount == 0) {
            cout << "||" << "\t No orders found within the price range." << endl;
        }
        else {
            cout << "||" << "\t Found " << matchedCount << " order(s) within the price range in Hash Index." << endl;
        }
        cout << "==" << "====================================================================" << endl;
    }

    void filterByKeyword(const string& keyword) const {
        int found = 0;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "                      FILTER BY KEYWORD: " << keyword << endl;
        cout << "==" << "====================================================================" << endl;
        for (int i = 0; i < TABLE_CAPACITY; i++) {
            HashTableNode* cur = tableSlots[i];
            while (cur != nullptr) {
                if (cur->recordValue.find(keyword) != string::npos || cur->recordKey.find(keyword) != string::npos) {
                    cout << "|| Key: " << cur->recordKey << " | Value: " << cur->recordValue << endl;
                    found++;
                }
                cur = cur->nextChainNode;
            }
        }
        cout << "\t[" << found << " record(s) matched keyword: " << keyword << "]" << endl;
        cout << "==" << "====================================================================" << endl;
    }
};

// DS-6: Stack
struct HistoryStackEntry {
    string orderIdentifier;
    string previousStatus;
    string newStatus;
    string transitionTimestamp;
};

class OrderHistoryStack {
    HistoryStackEntry* stackArray;
    int topIndex;
public:
    OrderHistoryStack() : topIndex(-1) {
        stackArray = new HistoryStackEntry[1000];
    }

    ~OrderHistoryStack() {
        delete[] stackArray;
    }

    bool isStackEmpty() const {
        return topIndex == -1;
    }
    bool isStackFull()  const {
        return topIndex == 999;
    }
    int  getStackSize() const { return topIndex + 1; }

    void pushTransition(const string& orderIdentifier, const string& previousStatus,
        const string& newStatus, const string& timestamp) {
        if (isStackFull()) {
            cout << "\tHistory Stack Full!" << endl;
            return;
        }
        topIndex++;
        stackArray[topIndex] = { orderIdentifier, previousStatus, newStatus, timestamp };

        writeToHistoryFile(orderIdentifier, previousStatus, newStatus, timestamp);
    }
    void loadHistoryFromFile() {
        ifstream file(orderHistoryFile);
        if (!file.is_open()) {
            return; 
        }

        string orderId, prevStatus, newStatus, timestamp;
        while (getline(file, orderId)) {
            if (!getline(file, prevStatus)) break;
            if (!getline(file, newStatus)) break;
            if (!getline(file, timestamp)) break;

            if (!isStackFull()) {
                topIndex++;
                stackArray[topIndex] = { orderId, prevStatus, newStatus, timestamp };
            }
        }
        file.close();
    }
    HistoryStackEntry popTopEntry() {
        return stackArray[topIndex--];
    }

    void displayOrderTimeline(const string& targetOrderId) const {
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t      TIMELINE: ORDER [" << targetOrderId << "]   " << endl;
        cout << "==" << "====================================================================" << endl;

        bool recordFound = false;

        for (int stackIndex = 0; stackIndex <= topIndex; stackIndex++) {
            if (stackArray[stackIndex].orderIdentifier == targetOrderId) {
                recordFound = true;
                cout << "||" << "\t [" << stackArray[stackIndex].transitionTimestamp << "]" << endl;
                cout << "||" << "\t Progress\t||\t -> " << stackArray[stackIndex].previousStatus << " -> " << stackArray[stackIndex].newStatus << endl;

                if (stackIndex < topIndex) {
                    cout << "||" << "----------------------------------------------------------------" << endl;
                }
            }
        }

        if (!recordFound) {
            cout << "||" << "\t No history entries found for order [" << targetOrderId << "]        " << endl;
        }
        cout << "==" << "====================================================================" << endl;
    }

    void displayCompleteHistory() const {
        if (isStackEmpty()) {
            cout << "\tNo history recorded." << endl;
            return;
        }

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t\tCOMPLETE ORDER HISTORY LOG   " << endl;
        cout << "==" << "====================================================================" << endl;

        for (int stackIndex = topIndex; stackIndex >= 0; stackIndex--) {
            cout << "||" << "\t Timestamp\t||\t -> " << stackArray[stackIndex].transitionTimestamp << endl;
            cout << "||" << "\t Order_ID\t||\t -> " << stackArray[stackIndex].orderIdentifier << endl;
            cout << "||" << "\t Transition\t||\t -> " << stackArray[stackIndex].previousStatus << " -> " << stackArray[stackIndex].newStatus << endl;

            if (stackIndex > 0) {
                cout << "||" << "----------------------------------------------------------------" << endl;
            }
        }
        cout << "==" << "====================================================================" << endl;
    }
};
//  SECTION 4: PERFORMANCE ANALYZER
class PerformanceAnalyzer {
public:
    void runHeapInsertionTest() {
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t   HEAP INSERTION PERFORMANCE TEST   " << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t Structure\t||\t -> Max-Heap (Priority Queue)" << endl;
        cout << "||" << "\t Theoretical\t||\t -> O(log n)" << endl;
        cout << "||" << "----------------------------------------------------------------" << endl;

        int testSizes[3] = { 100, 1000, 5000 };
        for (int testIndex = 0; testIndex < 3; testIndex++) {
            int totalElements = testSizes[testIndex];
            long long totalOperations = 0;

            for (int element = totalElements; element >= 1; element--) {
                int levelCalc = element;
                while (levelCalc > 0) {
                    levelCalc /= 2;
                    totalOperations++;
                }
            }

            cout << "||" << "\t Size (N)\t||\t -> " << totalElements << endl;
            cout << "||" << "\t Estimated Ops\t||\t -> " << totalOperations << endl;
            cout << "||" << "\t Avg/Insert\t||\t -> " << (double)totalOperations / totalElements << endl;

            if (testIndex < 2) {
                cout << "||" << "----------------------------------------------------------------" << endl;
            }
        }
        cout << "==" << "====================================================================" << endl;
    }

    void runHashSearchTest() {
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t   HASH TABLE SEARCH PERFORMANCE TEST   " << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t Structure\t||\t -> Hash Table (Chaining)" << endl;
        cout << "||" << "\t Theoretical\t||\t -> O(1) avg, O(n) worst" << endl;
        cout << "||" << "----------------------------------------------------------------" << endl;

        int testSizes[3] = { 100, 1000, 5000 };
        for (int testIndex = 0; testIndex < 3; testIndex++) {
            int    totalElements = testSizes[testIndex];
            double loadFactor = (double)totalElements / 101;
            double avgComparisons = 1.0 + loadFactor / 2.0;

            cout << "||" << "\t Elements (N)\t||\t -> " << totalElements << endl;
            cout << "||" << "\t Load Factor\t||\t -> " << loadFactor << endl;
            cout << "||" << "\t Avg Comps\t||\t -> " << avgComparisons << endl;

            if (testIndex < 2) {
                cout << "||" << "----------------------------------------------------------------" << endl;
            }
        }
        cout << "==" << "====================================================================" << endl;
    }

    void runDijkstraPerformanceTest() {
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t   DIJKSTRA ROUTE PERFORMANCE TEST   " << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t Algorithm\t||\t -> Dijkstra (Adjacency Matrix)" << endl;
        cout << "||" << "\t Theoretical\t||\t -> O(V^2)" << endl;
        cout << "||" << "----------------------------------------------------------------" << endl;

        int vertexCounts[3] = { 5, 10, 15 };
        for (int testIndex = 0; testIndex < 3; testIndex++) {
            int       totalVertices = vertexCounts[testIndex];
            long long totalOps = (long long)totalVertices * totalVertices;

            cout << "||" << "\t Vertices (V)\t||\t -> " << totalVertices << " locations" << endl;
            cout << "||" << "\t Cost (V^2 Ops)\t||\t -> " << totalOps << endl;

            if (testIndex < 2) {
                cout << "||" << "----------------------------------------------------------------" << endl;
            }
        }
        cout << "==" << "====================================================================" << endl;
    }

    void runScalabilityTest() {
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t       SCALABILITY SCENARIO ANALYSIS   " << endl;
        cout << "==" << "====================================================================" << endl;

        int testSizes[5] = { 10, 100, 500, 1000, 5000 };
        for (int testIndex = 0; testIndex < 5; testIndex++) {
            int    totalElements = testSizes[testIndex];
            double heapComplexity = (totalElements > 0) ? (log((double)totalElements) / log(2.0)) : 0.0;

            cout << "||" << "\t [Test Sample Case]  ||\t -> N = " << totalElements << endl;
            cout << "||" << "\t -> Max-Heap O(logN) ||\t -> " << heapComplexity << endl;
            cout << "||" << "\t -> Hash Table O(1)  ||\t -> 1.0" << endl;
            cout << "||" << "\t -> Dijkstra O(V^2)  ||\t -> 225 (Fixed Matrix 15x15)" << endl;

            if (testIndex < 4) {
                cout << "||" << "----------------------------------------------------------------" << endl;
            }
        }
        cout << "==" << "====================================================================" << endl;
    }

    void displayComplexitySummary() {
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t\t     ALGORITHM COMPLEXITY SUMMARY   " << endl;
        cout << "==" << "====================================================================" << endl;

        cout << "||" << " Order Scheduling    ||\t Max-Heap       -> Insert/Extract O(log n)" << endl;
        cout << "||" << "----------------------------------------------------------------" << endl;
        cout << "||" << " Kitchen Balancing   ||\t Circular Queue -> Enqueue/Dequeue O(1)" << endl;
        cout << "||" << "----------------------------------------------------------------" << endl;
        cout << "||" << " Rider Management    ||\t Linked List    -> Insert O(1), Search O(n)" << endl;
        cout << "||" << "----------------------------------------------------------------" << endl;
        cout << "||" << " Route Optimization  ||\t Graph Matrix   -> Dijkstra O(V^2)" << endl;
        cout << "||" << "----------------------------------------------------------------" << endl;
        cout << "||" << " Search & Retrieval  ||\t Hash Table     -> O(1) avg, O(n) worst" << endl;
        cout << "||" << "----------------------------------------------------------------" << endl;
        cout << "||" << " History & Undo      ||\t Stack          -> Push/Pop O(1)" << endl;

        cout << "==" << "====================================================================" << endl;
    }
};
//  SECTION 5: FOODEXPRESS SYSTEM  (data operations only)

class FoodExpressSystem {
public:
    // Entity storage arrays
    Customer* customerList[200];
    int totalCustomers;
    Rider* riderList[200];
    int totalRiders;
    Restaurant* restaurantList[50];
    int totalRestaurants;
    Order* orderList[500];
    int totalOrders;

    // Data Structures
    OrderPriorityQueue orderScheduler;
    KitchenCircularQueue kitchenQueues[10];
    int totalKitchenQueues;
    RiderLinkedList riderPool;
    CityRouteGraph cityRouteMap;
    SearchHashTable searchIndex;
    OrderHistoryStack historyStack;
    PerformanceAnalyzer performanceAnalyzer;

private:
    // -------------------------------------------------------
    //  Get current timestamp string
    // -------------------------------------------------------
    string getCurrentTimestamp() {
        time_t currentTime = time(nullptr);
        struct tm* timeInfo = localtime(&currentTime);

        string timestampStr = intToString(timeInfo->tm_mday) + "/"
            + intToString(timeInfo->tm_mon + 1) + "/"
            + intToString(timeInfo->tm_year + 1900) + " "
            + intToString(timeInfo->tm_hour) + ":"
            + (timeInfo->tm_min < 10 ? "0" : "") + intToString(timeInfo->tm_min) + ":"
            + (timeInfo->tm_sec < 10 ? "0" : "") + intToString(timeInfo->tm_sec);

        return timestampStr;
    }

    // -------------------------------------------------------
    //  Setup the 15-location Lahore city map
    // -------------------------------------------------------
    void buildCityMap() {
        cityRouteMap.addCityLocation("Mall Road");            // 0
        cityRouteMap.addCityLocation("Gulberg");              // 1
        cityRouteMap.addCityLocation("DHA Phase 1");          // 2
        cityRouteMap.addCityLocation("Model Town");           // 3
        cityRouteMap.addCityLocation("Johar Town");           // 4
        cityRouteMap.addCityLocation("Cantt");                // 5
        cityRouteMap.addCityLocation("Bahria Town");          // 6
        cityRouteMap.addCityLocation("Wapda Town");           // 7
        cityRouteMap.addCityLocation("Faisal Town");          // 8
        cityRouteMap.addCityLocation("Garden Town");          // 9
        cityRouteMap.addCityLocation("Shadman");              // 10
        cityRouteMap.addCityLocation("Ichra");                // 11
        cityRouteMap.addCityLocation("Bhatta Chowk");         // 12
        cityRouteMap.addCityLocation("Allama Iqbal Airport"); // 13
        cityRouteMap.addCityLocation("Ring Road");            // 14

        cityRouteMap.addBidirectionalRoad(0, 1, 3.5);
        cityRouteMap.addBidirectionalRoad(0, 10, 2.0);
        cityRouteMap.addBidirectionalRoad(0, 5, 6.0);
        cityRouteMap.addBidirectionalRoad(1, 2, 5.2);
        cityRouteMap.addBidirectionalRoad(1, 3, 4.1);
        cityRouteMap.addBidirectionalRoad(1, 9, 2.8);
        cityRouteMap.addBidirectionalRoad(2, 5, 3.0);
        cityRouteMap.addBidirectionalRoad(3, 4, 6.0);
        cityRouteMap.addBidirectionalRoad(3, 8, 3.5);
        cityRouteMap.addBidirectionalRoad(3, 11, 3.2);
        cityRouteMap.addBidirectionalRoad(4, 7, 4.2);
        cityRouteMap.addBidirectionalRoad(4, 6, 8.5);
        cityRouteMap.addBidirectionalRoad(5, 13, 7.0);
        cityRouteMap.addBidirectionalRoad(6, 14, 5.0);
        cityRouteMap.addBidirectionalRoad(7, 14, 3.8);
        cityRouteMap.addBidirectionalRoad(8, 9, 2.2);
        cityRouteMap.addBidirectionalRoad(9, 10, 1.8);
        cityRouteMap.addBidirectionalRoad(10, 11, 2.5);
        cityRouteMap.addBidirectionalRoad(11, 12, 1.5);
        cityRouteMap.addBidirectionalRoad(12, 13, 9.0);
        cityRouteMap.addBidirectionalRoad(14, 13, 12.0);
        cityRouteMap.addBidirectionalRoad(6, 7, 4.0);
    }

    // -------------------------------------------------------
    //  Load all data from files
    // -------------------------------------------------------
    void loadAllData() {
        historyStack.loadHistoryFromFile();
        // Load Customers.txt
        ifstream customerInputFile(customersFile);
        if (customerInputFile.is_open()) {
            while (totalCustomers < 200) {
                Customer* newCustomer = new Customer();
                if (newCustomer->loadFile(customerInputFile)) {
                    customerList[totalCustomers++] = newCustomer;
                    searchIndex.insertRecord(newCustomer->getCustomerId(),
                        "Customer|" + newCustomer->getCustomerName() + "|" + newCustomer->getCustomerCategory());
                }
                else {
                    delete newCustomer;
                    break;
                }
            }
            customerInputFile.close();
        }
        // Load Restaurants.txt
        ifstream restaurantInputFile(restaurantsFile);
        if (restaurantInputFile.is_open()) {
            while (totalRestaurants < 50) {
                Restaurant* newRestaurant = new Restaurant();
                if (newRestaurant->loadFile(restaurantInputFile)) {
                    restaurantList[totalRestaurants++] = newRestaurant;
                    searchIndex.insertRecord(newRestaurant->getRestaurantId(),
                        "Restaurant|" + newRestaurant->getRestaurantName() + "|" + newRestaurant->getRestaurantLocation());
                    if (totalKitchenQueues < 10) {
                        kitchenQueues[totalKitchenQueues].setOwnerRestaurantId(newRestaurant->getRestaurantId());
                        totalKitchenQueues++;
                    }
                }
                else {
                    delete newRestaurant;
                    break;
                }
            }
            restaurantInputFile.close();
        }

        // Load Riders.txt
        ifstream riderInputFile(ridersFile);
        if (riderInputFile.is_open()) {
            while (totalRiders < 200) {
                Rider* newRider = new Rider();
                if (newRider->loadFile(riderInputFile)) {
                    riderList[totalRiders++] = newRider;
                    riderPool.insertRiderAtEnd(*newRider);
                    searchIndex.insertRecord(newRider->getRiderId(),
                        "Rider|" + newRider->getRiderName() + "|" + newRider->getRiderCurrentLocation());
                }
                else {
                    delete newRider;
                    break;
                }
            }
            riderInputFile.close();
        }


       

      
        ifstream orderInputFile(ordersFile);
        if (orderInputFile.is_open()) {
            while (totalOrders < 500) {
                Order* newOrder = new Order();
                if (newOrder->loadFile(orderInputFile)) {
                    orderList[totalOrders++] = newOrder;

                    searchIndex.insertRecord(newOrder->getOrderIdentifier(),
                        "Order|" + newOrder->getCustomerIdentifier() + "|" + newOrder->getOrderStatus() + "|" +
                        newOrder->getRestaurantIdentifier() + "|" + doubleToString(newOrder->getDeliveryCostAmount()));

                    string currentStatus = newOrder->getOrderStatus();

                    if (currentStatus == "placed" || currentStatus == "accepted" || currentStatus == "queued") {
                        orderScheduler.insertOrder(*newOrder);
                    }

                    if (currentStatus == "placed" || currentStatus == "accepted" || currentStatus == "queued" || currentStatus == "rerouted") {
                        for (int queueIndex = 0; queueIndex < totalKitchenQueues; queueIndex++) {
                            if (kitchenQueues[queueIndex].getOwnerRestaurantId() == newOrder->getRestaurantIdentifier()) {
                                kitchenQueues[queueIndex].enqueueOrder(*newOrder);
                                break;
                            }
                        }

                        for (int restaurantIndex = 0; restaurantIndex < totalRestaurants; restaurantIndex++) {
                            if (restaurantList[restaurantIndex]->getRestaurantId() == newOrder->getRestaurantIdentifier()) {
                                restaurantList[restaurantIndex]->incrementLoad();
                                break;
                            }
                        }
                    }
                }
                else {
                    delete newOrder;
                    break;
                }
            }
            orderInputFile.close();
        }
    }

public:
    //  Constructor
    FoodExpressSystem() {
        totalCustomers = 0;
        totalRiders = 0;
        totalRestaurants = 0;
        totalOrders = 0;
        totalKitchenQueues = 0;
        loadAllData();
        buildCityMap();
    }

    //  Destructor
    ~FoodExpressSystem() {
        for (int idx = 0; idx < totalCustomers; idx++) {
            delete customerList[idx];
        }
        for (int idx = 0; idx < totalRestaurants; idx++) {
            delete restaurantList[idx];
        }
        for (int idx = 0; idx < totalRiders; idx++) {
            delete riderList[idx];
        }
        for (int idx = 0; idx < totalOrders; idx++) {
            delete orderList[idx];
        }
    }
    // Update order status
    bool updateOrderStatusInFile(const string& targetOrderId, const string& newOrderStatus,
        const string& newRiderIdAssigned = "") {
        ifstream inputFile(ordersFile);
        ofstream tempOutputFile("TempOrders.txt");
        if (!inputFile.is_open()) {
            return false;
        }
        Order tempOrder;
        bool  recordFound = false;

        while (tempOrder.loadFile(inputFile)) {
            if (tempOrder.getOrderIdentifier() == targetOrderId) {
                recordFound = true;
                string previousStatus = tempOrder.getOrderStatus();
                tempOrder.setOrderStatus(newOrderStatus);
                if (newRiderIdAssigned != "") {
                    tempOrder.setAssignedRiderId(newRiderIdAssigned);
                }
                historyStack.pushTransition(targetOrderId, previousStatus, newOrderStatus, getCurrentTimestamp());
                searchIndex.insertRecord(targetOrderId,
                    "Order|" + tempOrder.getCustomerIdentifier() + "|" + newOrderStatus + "|" +
                    tempOrder.getRestaurantIdentifier() + "|" + doubleToString(tempOrder.getDeliveryCostAmount()));
            }
            tempOrder.saveToStream(tempOutputFile);
        }
        inputFile.close();
        tempOutputFile.close();

        if (recordFound) {
            remove(ordersFile.c_str());
            rename("TempOrders.txt", ordersFile.c_str());
        }
        else {
            remove("TempOrders.txt");
        }
        return recordFound;
    }

    void persistOrderPriorityChangeInFile(const string& targetOrderId, int updatedPriority) {
        ifstream inputFile(ordersFile);
        ofstream tempOutputFile("TempOrders.txt");
        Order tempOrder;
        while (tempOrder.loadFile(inputFile)) {
            if (tempOrder.getOrderIdentifier() == targetOrderId) {
                tempOrder.setOrderPriority(updatedPriority);
                searchIndex.insertRecord(targetOrderId,
                    "Order|" + tempOrder.getCustomerIdentifier() + "|" + tempOrder.getOrderStatus() + "|" +
                    tempOrder.getRestaurantIdentifier() + "|" + doubleToString(tempOrder.getDeliveryCostAmount()));
            }
            tempOrder.saveToStream(tempOutputFile);
        }
        inputFile.close();
        tempOutputFile.close();
        remove(ordersFile.c_str());
        rename("TempOrders.txt", ordersFile.c_str());
    }

    //  Helper: Persist rider data changes to Riders.txt
    void persistRiderChanges(const string& targetRiderId, int updatedDeliveryCount, bool updatedAvailability) {
        ifstream inputFile(ridersFile);
        ofstream tempOutputFile("TempRiders.txt");
        Rider tempRider;

        while (tempRider.loadFile(inputFile)) {
            if (tempRider.getRiderId() == targetRiderId) {
                tempRider.setActiveDeliveryCount(updatedDeliveryCount);
                tempRider.setRiderAvailable(updatedAvailability);
            }
            tempRider.saveToStream(tempOutputFile);
        }
        inputFile.close();
        tempOutputFile.close();
        remove(ridersFile.c_str());
        rename("TempRiders.txt", ridersFile.c_str());
    }

    //  restaurant load

    void persistRestaurantLoad(const string& targetRestaurantId, int updatedLoad) {
        ifstream inputFile(restaurantsFile);
        ofstream tempOutputFile("TempRestaurants.txt");
        Restaurant tempRestaurant;

        while (tempRestaurant.loadFile(inputFile)) {
            if (tempRestaurant.getRestaurantId() == targetRestaurantId) {
                tempRestaurant.setRestaurantCurrentLoad(updatedLoad);
            }
            tempRestaurant.saveToStream(tempOutputFile);
        }
        inputFile.close();
        tempOutputFile.close();
        remove(restaurantsFile.c_str());
        rename("TempRestaurants.txt", restaurantsFile.c_str());
    }





    // 🚀 Register a New Customer Profile
    Customer* registerNewCustomer(string id, string name, string phone, string address, string category) {
        if (totalCustomers >= 200) {
            cout << "\tCustomer registry limit reached." << endl;
            return nullptr;
        }
        // Duplicate check
        for (int i = 0; i < totalCustomers; i++) {
            if (customerList[i]->getCustomerId() == id) {
                cout << "\tCustomer ID already exists!" << endl;
                return nullptr;
            }
        }

        Customer* newCustomer = new Customer(id, name, phone, address, category);
        newCustomer->saveFile(); // Saves securely to Customers.txt
        customerList[totalCustomers++] = newCustomer;

        // Sync with Chained Hash Table Search Index
        searchIndex.insertRecord(id, "Customer|" + name + "|" + category + "|" + address);
        return newCustomer;
    }

    // 🚀 Register a New Rider Fleet Unit
    Rider* registerNewRider(string id, string name, string phone, string location, int capacity) {
        if (totalRiders >= 200) {
            cout << "\tRider fleet capacity maxed out." << endl;
            return nullptr;
        }
        // Duplicate check
        for (int i = 0; i < totalRiders; i++) {
            if (riderList[i]->getRiderId() == id) {
                cout << "\tRider ID already exists!" << endl;
                return nullptr;
            }
        }

        Rider* newRider = new Rider(id, name, phone, location, capacity);
        newRider->saveFile(); // Saves securely to Riders.txt
        riderList[totalRiders++] = newRider;

        // Link to live driver optimization pool node chain
        riderPool.insertRiderAtEnd(*newRider);

        // Sync with Chained Hash Table Search Index
        searchIndex.insertRecord(id, "Rider|" + name + "|" + location);
        return newRider;
    }






    //  Signup Operations
    // -------------------------------------------------------
    //  Register a new restaurant (Admin only)
    // -------------------------------------------------------
    Restaurant* registerNewRestaurant(string restaurantId, string restaurantName,
        string restaurantLocation, int restaurantCapacity) {
        if (totalRestaurants >= 50) {
            cout << "\tRestaurant limit reached." << endl;
            return nullptr;
        }
        // Check if ID already exists
        for (int idx = 0; idx < totalRestaurants; idx++) {
            if (restaurantList[idx]->getRestaurantId() == restaurantId) {
                cout << "\tRestaurant ID already exists! Choose another." << endl;
                return nullptr;
            }
        }

        Restaurant* newRestaurant = new Restaurant(restaurantId, restaurantName,
            restaurantLocation, restaurantCapacity);
        newRestaurant->saveFile();
        restaurantList[totalRestaurants++] = newRestaurant;

        searchIndex.insertRecord(restaurantId,
            "Restaurant|" + restaurantName + "|" + restaurantLocation);

        if (totalKitchenQueues < 10) {
            kitchenQueues[totalKitchenQueues].setOwnerRestaurantId(restaurantId);
            totalKitchenQueues++;
        }

        return newRestaurant;
    }

    Order* placeNewOrder(string customerIdentifier, string restaurantIdentifier,
        string orderedItems, int priorityLevel,
        int preparationTimeMinutes, int deadlineMinutes, double deliveryCost) {
        if (totalOrders >= 500) {
            cout << "\tOrder limit reached." << endl;
            return nullptr;
        }

        string newOrderId = "ORD" + intToString(totalOrders + 1);
        time_t currentTime = time(nullptr);
        struct tm* timeInfo = localtime(&currentTime);

        string timestamp = intToString(timeInfo->tm_mday) + "/"
            + intToString(timeInfo->tm_mon + 1) + "/"
            + intToString(timeInfo->tm_year + 1900) + " "
            + intToString(timeInfo->tm_hour) + ":"
            + (timeInfo->tm_min < 10 ? "0" : "") + intToString(timeInfo->tm_min);

        Order* newOrder = new Order(newOrderId, customerIdentifier, restaurantIdentifier,
            orderedItems, priorityLevel, preparationTimeMinutes,
            deadlineMinutes, deliveryCost);
        newOrder->setOrderTimestamp(timestamp);
        newOrder->saveFile();
        orderList[totalOrders++] = newOrder;

        orderScheduler.insertOrder(*newOrder);
        searchIndex.insertRecord(newOrderId,
            "Order|" + customerIdentifier + "|placed|" + restaurantIdentifier + "|" + doubleToString(deliveryCost));
        historyStack.pushTransition(newOrderId, "new", "placed", timestamp);

        // Add to restaurant kitchen queue
        for (int queueIndex = 0; queueIndex < totalKitchenQueues; queueIndex++) {
            if (kitchenQueues[queueIndex].getOwnerRestaurantId() == restaurantIdentifier) {
                kitchenQueues[queueIndex].enqueueOrder(*newOrder);
                break;
            }
        }

        // Increment restaurant load
        for (int restaurantIndex = 0; restaurantIndex < totalRestaurants; restaurantIndex++) {
            if (restaurantList[restaurantIndex]->getRestaurantId() == restaurantIdentifier) {
                restaurantList[restaurantIndex]->incrementLoad();
                persistRestaurantLoad(restaurantIdentifier, restaurantList[restaurantIndex]->getRestaurantCurrentLoad());
                break;
            }
        }

        return newOrder;
    }

    string getCurrentTime() {
        time_t     currentTime = time(nullptr);
        struct tm* timeInfo = localtime(&currentTime);
        return intToString(timeInfo->tm_mday) + "/" + intToString(timeInfo->tm_mon + 1) + "/"
            + intToString(timeInfo->tm_year + 1900) + " " + intToString(timeInfo->tm_hour) + ":"
            + (timeInfo->tm_min < 10 ? "0" : "") + intToString(timeInfo->tm_min);
    }

    void handleDelayedOrdersEscalation() {
        int escalatedCount = 0;
        for (int i = 0; i < orderScheduler.heapSize; i++) {
            if (orderScheduler.heapArray[i].getDeliveryDeadlineMinutes() <= 25 && orderScheduler.heapArray[i].getOrderPriority() < 4) {
                string orderId = orderScheduler.heapArray[i].getOrderIdentifier();
                cout << "\t[ESCALATING] Order " << orderId
                    << " (Deadline: " << orderScheduler.heapArray[i].getDeliveryDeadlineMinutes()
                    << " min) to VIP priority due to aging." << endl;

                orderScheduler.heapArray[i].setOrderPriority(4);

                // Update in orderList
                for (int j = 0; j < totalOrders; j++) {
                    if (orderList[j] && orderList[j]->getOrderIdentifier() == orderId) {
                        orderList[j]->setOrderPriority(4);
                        break;
                    }
                }

                // Persist changes to Orders.txt
                persistOrderPriorityChangeInFile(orderId, 4);

                escalatedCount++;
            }
        }
        if (escalatedCount > 0) {
            for (int i = (orderScheduler.heapSize / 2) - 1; i >= 0; i--) {
                orderScheduler.bubbleDown(i);
            }
            cout << "\t[SUCCESS] Re-heapified scheduler queue. " << escalatedCount << " order(s) escalated." << endl;
        }
        else {
            cout << "\t[INFO] No orders close to breaching deadline. No escalation needed." << endl;
        }
    }
};

// GLOBAL SYSTEM POINTER
FoodExpressSystem* foodSystem = 0;

//  MENU FUNCTIONS

// ============================================================
//  MODULE MENUS
// ============================================================
void schedulerMenu() {
    int menuChoice;
    do {
        system("cls");

        // Auto-run delayed orders escalation
        foodSystem->handleDelayedOrdersEscalation();

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "               MODULE 1: DYNAMIC ORDER SCHEDULING                 || " << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t 1.  Add New Order (Manual Capture)                         ||" << endl;
        cout << "||" << "\t 2.  Cancel Active Order by Unique ID                       ||" << endl;
        cout << "||" << "\t 3.  Update Existing Order Priority                         ||" << endl;
        cout << "||" << "\t 4.  Process Next Highest Priority Order                    ||" << endl;
        cout << "||" << "\t 5.  View All Scheduled Orders                              ||" << endl;
        cout << "||" << "\t 6.  Run Delayed Orders Escalation Manually                 ||" << endl;
        cout << "||" << "--------------------------------------------------------------------" << endl;
        cout << "||" << "\t 0.  Back to Main Menu                                      || " << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "\tEnter Your Choice: ";
        cin >> menuChoice;
        cin.ignore();

        if (menuChoice == 1) {
            system("cls");
            string customerIdInput, restaurantIdInput, itemsInput;
            int    priorityInput, prepTimeInput, deadlineInput;
            double deliveryCostInput;

            cout << "==" << "====================================================================" << endl;
            cout << "||" << "                    MANUAL ORDER LOG ENTRY CAPTURE                ||    " << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tCustomer ID      : ";
            getline(cin, customerIdInput);
            cout << "\tRestaurant ID    : ";
            getline(cin, restaurantIdInput);
            cout << "\tItems Ordered    : ";
            getline(cin, itemsInput);
            cout << "\tPriority (1-4)   : ";
            cin >> priorityInput;
            cin.ignore();
            cout << "\tPrep Time (min)  : ";
            cin >> prepTimeInput;
            cin.ignore();
            cout << "\tDeadline (min)   : ";
            cin >> deadlineInput;
            cin.ignore();
            cout << "\tDelivery Cost    : ";
            cin >> deliveryCostInput;
            cin.ignore();
            cout << "==" << "====================================================================" << endl;

            Order* addedOrder = foodSystem->placeNewOrder(customerIdInput, restaurantIdInput,
                itemsInput, priorityInput, prepTimeInput, deadlineInput, deliveryCostInput);

            if (addedOrder != nullptr) {
                cout << "\n\t[SUCCESS]: Order [" << addedOrder->getOrderIdentifier() << "] Added to Heap Scheduler." << endl;
            }
            system("pause");
        }
        else if (menuChoice == 2) {
            system("cls");
            string targetOrderId;
            cout << "==" << "====================================================================" << endl;
            cout << "||" << "                             CANCEL ORDER                         || " << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tOrder ID to Cancel : ";
            getline(cin, targetOrderId);
            cout << "==" << "====================================================================" << endl;

            foodSystem->orderScheduler.cancelOrderById(targetOrderId);

            if (foodSystem->updateOrderStatusInFile(targetOrderId, "cancelled")) {
                cout << "\n\t[SUCCESS]: Order [" << targetOrderId << "] Cancelled Successfully." << endl;
            }
            else {
                cout << "\n\t[ERROR]: Order ID Not Found in Database." << endl;
            }
            system("pause");

        }
        else if (menuChoice == 3) {
            system("cls");
            string targetOrderId; int newPriorityLevel;
            cout << "==" << "====================================================================" << endl;
            cout << "||" << "                     UPDATE ORDER PRIORITY FILTER                 ||    " << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tOrder ID         : ";
            getline(cin, targetOrderId);
            cout << "\tNew Priority(1-4): ";
            cin >> newPriorityLevel;
            cin.ignore();
            cout << "==" << "====================================================================" << endl;

            if (foodSystem->orderScheduler.updateOrderPriority(targetOrderId, newPriorityLevel)) {
                cout << "\n\t[SUCCESS]: Priority Updated in Max-Heap Scheduler Structure." << endl;
            }
            else {
                cout << "\n\t[ERROR]: Order Not Found in Active Heap Scheduler." << endl;
            }
            system("pause");

        }
        else if (menuChoice == 4) {
            system("cls");
            if (foodSystem->orderScheduler.isEmpty()) {
                cout << "==" << "====================================================================" << endl;
                cout << "||" << "\t No active orders remaining inside priority queue scheduler.     " << endl;
                cout << "==" << "====================================================================" << endl;
            }
            else {
                Order highestPriorityOrder = foodSystem->orderScheduler.extractHighestPriority();

                cout << "==" << "====================================================================" << endl;
                cout << "||" << "                 PROCESSING HIGHEST PRIORITY DISPATCH             ||" << endl;
                cout << "==" << "====================================================================" << endl;

                highestPriorityOrder.display();
                foodSystem->updateOrderStatusInFile(highestPriorityOrder.getOrderIdentifier(), "accepted");

                cout << "||" << "\t STATUS UPDATE  ||\t -> Order Sent to Kitchen." << endl;
                cout << "==" << "====================================================================" << endl;
            }
            system("pause");

        }
        else if (menuChoice == 5) {
            system("cls");
            foodSystem->orderScheduler.displayAllOrders();
            system("pause");

        }
        else if (menuChoice == 6) {
            system("cls");
            foodSystem->handleDelayedOrdersEscalation();
            system("pause");

        }
        else if (menuChoice != 0) {
            cout << "\t[âŒ INVALID CHOICE]: Please select a value between 0 and 6." << endl;
            system("pause");
        }
    } while (menuChoice != 0);
}



void databaseManagementMenu() {
    int menuChoice;
    do {
        system("cls");
        cout << "==" << "====================================================================" << endl;
        cout << "||                ADMIN DATABASE HUB CONTROL PANEL                ||" << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t 1.  Register New Customer Profile                          ||" << endl;
        cout << "||" << "\t 2.  Register New Rider Fleet Unit                          ||" << endl;
        cout << "||" << "--------------------------------------------------------------------" << endl;
        cout << "||" << "\t 0.  Back to Main Menu                                      ||" << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "\tEnter Your Choice: ";
        cin >> menuChoice;
        cin.ignore();

        if (menuChoice == 1) {
            system("cls");
            string id, name, phone, addr, cat;
            cout << "==" << "====================================================================" << endl;
            cout << "||                    MANUAL CUSTOMER LOG CAPTURE                 ||" << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tCustomer Unique ID (e.g., C4)  : "; getline(cin, id);
            cout << "\tFull Name                      : "; getline(cin, name);
            cout << "\tPhone Number                   : "; getline(cin, phone);
            cout << "\tDelivery Address Sector        : "; getline(cin, addr);
            cout << "\tAccount Tier (Regular/Premium/VIP): "; getline(cin, cat);
            cout << "==" << "====================================================================" << endl;

            Customer* c = foodSystem->registerNewCustomer(id, name, phone, addr, cat);
            if (c != nullptr) {
                cout << "\n\t[SUCCESS]: Customer account compiled and written to database." << endl;
            }
            system("pause");

        }
        else if (menuChoice == 2) {
            system("cls");
            string id, name, phone, loc;
            int capacity;
            cout << "==" << "====================================================================" << endl;
            cout << "||                      MANUAL RIDER LOG CAPTURE                    ||" << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tRider Fleet ID (e.g., RIDER4) : "; getline(cin, id);
            cout << "\tFull Name                      : "; getline(cin, name);
            cout << "\tPhone Number                   : "; getline(cin, phone);
            cout << "\tCurrent Base Station Location  : "; getline(cin, loc);
            cout << "\tMax Active Order Capacity      : "; cin >> capacity; cin.ignore();
            cout << "==" << "====================================================================" << endl;

            Rider* r = foodSystem->registerNewRider(id, name, phone, loc, capacity);
            if (r != nullptr) {
                cout << "\n\t[SUCCESS]: Rider added to linear optimization loops and file streams." << endl;
            }
            system("pause");
        }
    } while (menuChoice != 0);
}



void kitchenLoadMenu() {
    int menuChoice;
    do {
        system("cls");

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "                MODULE 2: KITCHEN LOAD BALANCING                  ||     " << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t 1.  View All Kitchen Queues and Restaurant Stats           ||" << endl;
        cout << "||" << "\t 2.  Rebalance Overloaded Kitchens (Automated Reroute)      ||" << endl;
        cout << "||" << "\t 3.  Register New Restaurant Profile (Admin Override)       ||" << endl;
        cout << "||" << "--------------------------------------------------------------------" << endl;
        cout << "||" << "\t 0.  Back to Main Menu                                      ||" << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "\tEnter Your Choice: ";
        cin >> menuChoice;
        cin.ignore();

        if (menuChoice == 1) {
            system("cls");

            cout << "==" << "====================================================================" << endl;
            cout << "||" << "                   LIVE RESTAURANT STATUS METRICS                 ||  " << endl;
            cout << "==" << "====================================================================" << endl;

            for (int restaurantIdx = 0; restaurantIdx < foodSystem->totalRestaurants; restaurantIdx++) {
                foodSystem->restaurantList[restaurantIdx]->display();
            }
            if (foodSystem->totalRestaurants == 0) {
                cout << "||" << "     No restaurant metrics found registered in core file logs.    ||" << endl;
                cout << "==" << "====================================================================" << endl;
            }

            cout << "\n";
            for (int queueIdx = 0; queueIdx < foodSystem->totalKitchenQueues; queueIdx++) {
                foodSystem->kitchenQueues[queueIdx].displayQueueContents();
                cout << "\n";
            }
            system("pause");

        }
        else if (menuChoice == 2) {
            system("cls");
            int overloadedQueueIndex = -1;
            int underloadedQueueIndex = -1;

            for (int queueIdx = 0; queueIdx < foodSystem->totalKitchenQueues; queueIdx++) {
                if (!foodSystem->kitchenQueues[queueIdx].isQueueEmpty() &&
                    foodSystem->kitchenQueues[queueIdx].getOrderCount() > 5) {
                    overloadedQueueIndex = queueIdx;
                }
                if (foodSystem->kitchenQueues[queueIdx].getOrderCount() < 2) {
                    underloadedQueueIndex = queueIdx;
                }
            }

            cout << "==" << "====================================================================" << endl;
            cout << "||" << "              AUTOMATED QUEUE LOAD REBALANCING ENGINE             ||      " << endl;
            cout << "==" << "====================================================================" << endl;

            if (overloadedQueueIndex != -1 && underloadedQueueIndex != -1 && overloadedQueueIndex != underloadedQueueIndex) {
                string sourceId = foodSystem->kitchenQueues[overloadedQueueIndex].getOwnerRestaurantId();
                string destId = foodSystem->kitchenQueues[underloadedQueueIndex].getOwnerRestaurantId();

                Order movedOrder = foodSystem->kitchenQueues[overloadedQueueIndex].dequeueOrder();

                movedOrder.setRestaurantIdentifier(destId);
                foodSystem->kitchenQueues[underloadedQueueIndex].enqueueOrder(movedOrder);

                foodSystem->historyStack.pushTransition(movedOrder.getOrderIdentifier(),
                    "queued", "rerouted", foodSystem->getCurrentTime());

                cout << "||" << "\t Order ID\t||\t -> " << movedOrder.getOrderIdentifier() << endl;
                cout << "||" << "\t Source Hub\t||\t -> " << sourceId << " [OVERLOADED]" << endl;
                cout << "||" << "\t Target Hub\t||\t -> " << destId << " [BALANCED]" << endl;
                cout << "||" << "----------------------------------------------------------------" << endl;
                cout << "\n\t[REBALANCE COMPLETE]: Order safely re-routed inside memory arrays." << endl;
            }
            else {
                cout << "||" << "\t System balancing confirmed. No active queues exceed thresholds. " << endl;
            }
            cout << "==" << "====================================================================" << endl;
            system("pause");

        }
        else if (menuChoice == 3) {
            system("cls");
            string restaurantIdInput, restaurantNameInput, restaurantLocationInput;
            int    restaurantCapacityInput;

            cout << "==" << "====================================================================" << endl;
            cout << "||" << "                   REGISTER NEW RESTAURANT HUB                    ||   " << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tRestaurant ID    : "; getline(cin, restaurantIdInput);
            cout << "\tRestaurant Name  : "; getline(cin, restaurantNameInput);
            cout << "\tLocation         : "; getline(cin, restaurantLocationInput);
            cout << "\tMax Capacity     : "; cin >> restaurantCapacityInput; cin.ignore();
            cout << "==" << "====================================================================" << endl;

            Restaurant* addedRestaurant = foodSystem->registerNewRestaurant(
                restaurantIdInput, restaurantNameInput, restaurantLocationInput,
                restaurantCapacityInput);

            if (addedRestaurant != nullptr) {
                cout << "\n==" << "====================================================================" << endl;
                cout << "||" << "                  RESTAURANT REGISTERED SUCCESSFULLY!               || " << endl;
                cout << "==" << "======================================================================" << endl;
                cout << "||" << "\t Unique ID\t||\t -> " << addedRestaurant->getRestaurantId() << endl;
                cout << "||" << "\t Hub Name\t||\t -> " << addedRestaurant->getRestaurantName() << endl;
                cout << "==" << "======================================================================" << endl;
            }
            system("pause");

        }
        else if (menuChoice != 0) {
            cout << "\t[INVALID CHOICE]: Please choose an option between 0 and 3." << endl;
            system("pause");
        }
    } while (menuChoice != 0);
}

void riderDispatchMenu() {
    int menuChoice;
    do {
        system("cls");

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "               MODULE 3: RIDER DISPATCH OPTIMIZATION              ||" << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t 1.  Auto-Dispatch Best Available Rider for Next Order      || " << endl;
        cout << "||" << "\t 2.  Mark Delivery Complete (Admin Override)                ||" << endl;
        cout << "||" << "\t 3.  View All Active Fleet Riders                           || " << endl;
        cout << "||" << "--------------------------------------------------------------------" << endl;
        cout << "||" << "\t 0.  Back to Main Menu                                      ||" << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "\tEnter Your Choice: ";
        cin >> menuChoice;
        cin.ignore();
        if (menuChoice == 1) {
            system("cls");
            if (foodSystem->orderScheduler.isEmpty()) {
                cout << "==" << "====================================================================" << endl;
                cout << "||" << "\t No pending orders remaining inside scheduler priority queue.    " << endl;
                cout << "==" << "====================================================================" << endl;
            }
            else {
                Order nextOrder = foodSystem->orderScheduler.extractHighestPriority();
                string restaurantLoc = "";
                for (int rIdx = 0; rIdx < foodSystem->totalRestaurants; rIdx++) {
                    if (foodSystem->restaurantList[rIdx]->getRestaurantId() == nextOrder.getRestaurantIdentifier()) {
                        restaurantLoc = foodSystem->restaurantList[rIdx]->getRestaurantLocation();
                        break;
                    }
                }
                Rider* bestRider = foodSystem->riderPool.findBestAvailableRider(restaurantLoc, foodSystem->cityRouteMap);

                if (bestRider == nullptr) {
                    cout << "==" << "====================================================================" << endl;
                    cout << "||" << "\t [CRITICAL]: Fleet capacity maxed out! No riders available.   " << endl;
                    cout << "==" << "====================================================================" << endl;

                    foodSystem->orderScheduler.insertOrder(nextOrder);
                }
                else {
                    bestRider->assignNewOrder();

                    foodSystem->updateOrderStatusInFile(nextOrder.getOrderIdentifier(), "assigned", bestRider->getRiderId());
                    foodSystem->riderPool.synchronizeRiderStatus(bestRider->getRiderId(), bestRider->getActiveDeliveryCount(), bestRider->getRiderAvailable());
                    foodSystem->persistRiderChanges(bestRider->getRiderId(), bestRider->getActiveDeliveryCount(), bestRider->getRiderAvailable());

                    for (int riderIdx = 0; riderIdx < foodSystem->totalRiders; riderIdx++) {
                        if (foodSystem->riderList[riderIdx]->getRiderId() == bestRider->getRiderId()) {
                            foodSystem->riderList[riderIdx]->setActiveDeliveryCount(bestRider->getActiveDeliveryCount());
                            foodSystem->riderList[riderIdx]->setRiderAvailable(bestRider->getRiderAvailable());
                            break;
                        }
                    }

                    cout << "==" << "====================================================================" << endl;
                    cout << "||" << "                DISPATCH OPTIMIZATION ENGINE RUN                  ||" << endl;
                    cout << "==" << "====================================================================" << endl;
                    cout << "||" << "\t Order ID\t||\t -> " << nextOrder.getOrderIdentifier() << endl;
                    cout << "||" << "\t Assigned Fleet\t||\t -> " << bestRider->getRiderName() << " (" << bestRider->getRiderId() << ")" << endl;
                    cout << "||" << "----------------------------------------------------------------" << endl;

                    bestRider->display();
                    cout << "\n\t[ROUTE LIVE]: Dispatch pipeline updated successfully." << endl;
                }
            }
            system("pause");

        }
        else if (menuChoice == 2) {
            system("cls");
            string targetRiderId;

            cout << "==" << "====================================================================" << endl;
            cout << "||" << "\t\t\t MARK DELIVERY COMPLETE   " << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tEnter Rider ID : "; getline(cin, targetRiderId);
            cout << "==" << "====================================================================" << endl;

            Rider* targetRider = foodSystem->riderPool.findRiderById(targetRiderId);
            if (targetRider == nullptr) {
                cout << "\n\t[ERROR]: Target Rider identifier code not matched inside database pool." << endl;
            }
            else {
                targetRider->markDeliveryComplete();

                foodSystem->persistRiderChanges(targetRiderId, targetRider->getActiveDeliveryCount(), targetRider->getRiderAvailable());

                for (int riderIdx = 0; riderIdx < foodSystem->totalRiders; riderIdx++) {
                    if (foodSystem->riderList[riderIdx]->getRiderId() == targetRiderId) {
                        foodSystem->riderList[riderIdx]->setActiveDeliveryCount(targetRider->getActiveDeliveryCount());
                        foodSystem->riderList[riderIdx]->setRiderAvailable(targetRider->getRiderAvailable());
                        break;
                    }
                }

                cout << "\n\t[METRIC LOGGED]: Workload decremented successfully." << endl;
                cout << "\tRemaining Deliveries in Queue: " << targetRider->getActiveDeliveryCount() << endl;
            }
            system("pause");

        }
        else if (menuChoice == 3) {
            system("cls");
            foodSystem->riderPool.displayAllRiders();
            system("pause");

        }
        else if (menuChoice != 0) {
            cout << "\t[INVALID CHOICE]: Select an options index code matching 0 to 3." << endl;
            system("pause");
        }
    } while (menuChoice != 0);
}

void routeOptimizationMenu() {
    int menuChoice;
    do {
        system("cls");

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "             MODULE 4: ROUTE OPTIMIZATION (DIJKSTRA)              ||" << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t 1.  Find Shortest Delivery Route (Point-to-Point)          || " << endl;
        cout << "||" << "\t 2.  Compare Two Alternative Routes (Waypoint Analysis)     ||  " << endl;
        cout << "||" << "\t 3.  Block / Unblock a Road Segment (Live Traffic)          ||" << endl;
        cout << "||" << "\t 4.  Display Full City Map & Connected Network Grid         ||" << endl;
        cout << "||" << "--------------------------------------------------------------------" << endl;
        cout << "||" << "\t 0.  Back to Main Menu                                      || " << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "\tEnter Your Choice: ";
        cin >> menuChoice;
        cin.ignore();

        if (menuChoice == 1) {
            system("cls");
            string sourceLocation, destinationLocation;

            foodSystem->cityRouteMap.displayCityMap();
            cout << "\n";

            cout << "\tFrom Location Name : ";
            getline(cin, sourceLocation);
            cout << "\tTo Location Name   : ";
            getline(cin, destinationLocation);
            cout << "\n";

            foodSystem->cityRouteMap.printShortestRoute(sourceLocation, destinationLocation);
            system("pause");

        }
        else if (menuChoice == 2) {
            system("cls");
            string sourceLocation, waypointLocation, destinationLocation;

            foodSystem->cityRouteMap.displayCityMap();
            cout << "\n";

            cout << "\tFrom Location Name : ";
            getline(cin, sourceLocation);
            cout << "\tVia Location Name  : ";
            getline(cin, waypointLocation);
            cout << "\tTo Location Name   : ";
            getline(cin, destinationLocation);
            cout << "\n";

            int sourceIdx = foodSystem->cityRouteMap.findLocationIndex(sourceLocation);
            int waypointIdx = foodSystem->cityRouteMap.findLocationIndex(waypointLocation);
            int destIdx = foodSystem->cityRouteMap.findLocationIndex(destinationLocation);

            if (sourceIdx == -1 || waypointIdx == -1 || destIdx == -1) {
                cout << "\t[âŒ ERROR]: One or More Location Labels Not Found inside Map Graph Data." << endl;
            }
            else {
                foodSystem->cityRouteMap.compareAlternativeRoutes(sourceIdx, waypointIdx, destIdx);
            }
            system("pause");

        }
        else if (menuChoice == 3) {
            system("cls");
            int fromLocationIdx, toLocationIdx, blockAction;

            foodSystem->cityRouteMap.displayCityMap();
            cout << "\n";

            cout << "==" << "====================================================================" << endl;
            cout << "||" << "            LIVE ROAD NETWORK TRAFFIC CONTROL DASHBOARD           || " << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tFrom Location Index Code : ";
            cin >> fromLocationIdx;
            cin.ignore();
            cout << "\tTo Location Index Code   : ";
            cin >> toLocationIdx;
            cin.ignore();

            cout << "\n\tSelect Trafficking Status Override Action:" << endl;
            cout << "\t1. Apply [BLOCKED] Restrictions" << endl;
            cout << "\t2. Clear Restrictions [OPERATIONAL]" << endl;
            cout << "\tEnter Action Code (1-2): "; cin >> blockAction; cin.ignore();
            cout << "==" << "====================================================================" << endl;

            int mapLimit = foodSystem->cityRouteMap.getTotalLocations();
            if (fromLocationIdx < 0 || toLocationIdx < 0 || fromLocationIdx >= mapLimit || toLocationIdx >= mapLimit) {
                cout << "\n\t[ERROR]: Node index constraints violated. Action aborted." << endl;
            }
            else if (blockAction == 1) {
                int reroutedCount = 0;
                for (int i = 0; i < foodSystem->totalOrders; i++) {
                    Order* ord = foodSystem->orderList[i];
                    if (!ord) continue;
                    string status = ord->getOrderStatus();
                    if (status == "placed" || status == "accepted" || status == "queued" || status == "assigned" || status == "picked") {
                        string restLoc = "";
                        for (int r = 0; r < foodSystem->totalRestaurants; r++) {
                            if (foodSystem->restaurantList[r]->getRestaurantId() == ord->getRestaurantIdentifier()) {
                                restLoc = foodSystem->restaurantList[r]->getRestaurantLocation();
                                break;
                            }
                        }
                        string custLoc = "";
                        for (int c = 0; c < foodSystem->totalCustomers; c++) {
                            if (foodSystem->customerList[c]->getCustomerId() == ord->getCustomerIdentifier()) {
                                custLoc = foodSystem->customerList[c]->getCustomerAddress();
                                break;
                            }
                        }
                        int restIdx = foodSystem->cityRouteMap.findLocationIndex(restLoc);
                        int custIdx = foodSystem->cityRouteMap.findLocationIndex(custLoc);
                        if (restIdx != -1 && custIdx != -1) {
                            double shortestDistances[MAXIMUM_CITY_LOCATIONS];
                            int previousNodeList[MAXIMUM_CITY_LOCATIONS];
                            foodSystem->cityRouteMap.runDijkstra(restIdx, shortestDistances, previousNodeList);
                            int curr = custIdx;
                            bool usesSegment = false;
                            while (curr != -1 && previousNodeList[curr] != -1) {
                                int prev = previousNodeList[curr];
                                if ((curr == fromLocationIdx && prev == toLocationIdx) ||
                                    (curr == toLocationIdx && prev == fromLocationIdx)) {
                                    usesSegment = true;
                                    break;
                                }
                                curr = prev;
                            }
                            if (usesSegment) {
                                ord->setOrderStatus("rerouted");
                                foodSystem->updateOrderStatusInFile(ord->getOrderIdentifier(), "rerouted");
                                reroutedCount++;
                                cout << "\t[REROUTE]: Active Order [" << ord->getOrderIdentifier() << "] route affected. Status updated to REROUTED." << endl;
                            }
                        }
                    }
                }
                foodSystem->cityRouteMap.blockRoad(fromLocationIdx, toLocationIdx);
                cout << "\n\t[TRAFFIC LIVE]: Adjacency values blocked successfully." << endl;
                if (reroutedCount > 0) {
                    cout << "\t[INFO]: " << reroutedCount << " active order(s) affected and flagged as 'rerouted' in logs." << endl;
                }
            }
            else if (blockAction == 2) {
                foodSystem->cityRouteMap.unblockRoad(fromLocationIdx, toLocationIdx);
                cout << "\n\t[TRAFFIC LIVE]: Adjacency values unblocked successfully." << endl;
            }
            else {
                cout << "\n\t[INVALID CHOICE]: Action aborted. Select code 1 or 2." << endl;
            }
            system("pause");

        }
        else if (menuChoice == 4) {
            system("cls");
            foodSystem->cityRouteMap.displayCityMap();
            system("pause");

        }
        else if (menuChoice != 0) {
            cout << "\t[âŒ INVALID CHOICE]: Please choose an option index between 0 and 4." << endl;
            system("pause");
        }
    } while (menuChoice != 0);
}

void searchRetrievalMenu() {
    int menuChoice;
    do {
        system("cls");
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "              MODULE 5: SEARCH & RETRIEVAL ENGINE                 ||  " << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t 1.  Search by ID                                           ||   " << endl;
        cout << "||" << "\t 2.  Filter Orders by Status                                ||  " << endl;
        cout << "||" << "\t 3.  Filter Customers by Tier Category                      ||   " << endl;
        cout << "||" << "\t 4.  View All Registered Customers                          ||   " << endl;
        cout << "||" << "\t 5.  View All Registered Restaurants                        ||   " << endl;
        cout << "||" << "\t 6.  Display Full Chained Hash Search Index Structural Map  ||" << endl;
        cout << "||" << "\t 7.  Filter Orders by Restaurant ID                         ||" << endl;
        cout << "||" << "\t 8.  Filter Orders by Price Range                           ||" << endl;
        cout << "||" << "\t 9.  Filter All Records by Keyword                          ||" << endl;
        cout << "||" << "--------------------------------------------------------------------" << endl;
        cout << "||" << "\t 0.  Back to Main Menu                                      ||  " << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "\tEnter Your Choice: ";
        cin >> menuChoice;
        cin.ignore();

        if (menuChoice == 1) {
            system("cls");
            string searchKeyInput;

            cout << "==" << "====================================================================" << endl;
            cout << "||" << "\t\t\t Search By Id   " << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tEnter Unique ID Asset String : ";
            getline(cin, searchKeyInput);
            cout << "==" << "====================================================================" << endl;

            string searchResult = foodSystem->searchIndex.searchRecord(searchKeyInput);

            if (searchResult.empty()) {
                cout << "\n\t[ERROR]: Record Identifier not matched inside active directory." << endl;
            }
            else {
                cout << "==" << "====================================================================" << endl;
                cout << "||" << "\t\t      INDEX REGISTRY MATCH Found   " << endl;
                cout << "==" << "====================================================================" << endl;
                cout << "||" << "\t Query Key\t||\t -> " << searchKeyInput << endl;
                cout << "||" << "\t Record Data\t||\t -> " << searchResult << endl;
                cout << "==" << "====================================================================" << endl;
            }
            system("pause");

        }
        else if (menuChoice == 2) {
            system("cls");
            string statusFilterInput;

            cout << "==" << "====================================================================" << endl;
            cout << "||" << "\t\t\t   ORDER HISTOGRAM STATUS FILTER   " << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tEnter Status Filter Code (placed/accepted/queued/cancelled) : ";
            getline(cin, statusFilterInput);
            cout << "==" << "====================================================================" << endl;

            ifstream orderReadFile(ordersFile);
            if (!orderReadFile.is_open()) {
                cout << "\n\t[ERROR]: Storage baseline data stream missing." << endl;
            }
            else {
                Order tempOrder;
                int matchCount = 0;

                while (tempOrder.loadFile(orderReadFile)) {
                    if (tempOrder.getOrderStatus() == statusFilterInput) {
                        tempOrder.display();
                        matchCount++;
                    }
                }
                orderReadFile.close();

                cout << "==" << "====================================================================" << endl;
                if (matchCount == 0) {
                    cout << "||" << "\t No active orders match specified parameter criteria.          " << endl;
                }
                else {
                    cout << "||" << "\t Operational Sync \t||\t -> " << matchCount << " Records Isolated" << endl;
                }
                cout << "==" << "====================================================================" << endl;
            }
            system("pause");

        }
        else if (menuChoice == 3) {
            system("cls");
            string categoryFilterInput;

            cout << "==" << "====================================================================" << endl;
            cout << "||" << "\t\t\t   CUSTOMER CATEGORIZATION FILTER   " << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tEnter Category (Regular/Premium/VIP) : "; getline(cin, categoryFilterInput);
            cout << "==" << "====================================================================" << endl;

            int matchCount = 0;
            for (int customerIdx = 0; customerIdx < foodSystem->totalCustomers; customerIdx++) {
                if (foodSystem->customerList[customerIdx]->getCustomerCategory() == categoryFilterInput) {
                    foodSystem->customerList[customerIdx]->display();
                    matchCount++;
                }
            }

            if (matchCount == 0) {
                cout << "==" << "====================================================================" << endl;
                cout << "||" << "\t No users categorized inside target group classification.       " << endl;
                cout << "==" << "====================================================================" << endl;
            }
            else {
                cout << "==" << "====================================================================" << endl;
            }
            system("pause");

        }
        else if (menuChoice == 4) {
            system("cls");
            cout << "==" << "====================================================================" << endl;
            cout << "||" << "                   COMPLETE CUSTOMER DIRECTORY                    ||" << endl;
            cout << "==" << "====================================================================" << endl;

            for (int customerIdx = 0; customerIdx < foodSystem->totalCustomers; customerIdx++) {
                foodSystem->customerList[customerIdx]->display();
            }

            if (foodSystem->totalCustomers == 0) {
                cout << "||" << "\t Directory database index returns null records.                " << endl;
            }
            cout << "==" << "====================================================================" << endl;
            system("pause");

        }
        else if (menuChoice == 5) {
            system("cls");
            cout << "==" << "====================================================================" << endl;
            cout << "||" << "                     COMPLETE RESTAURANT INDEX                    ||" << endl;
            cout << "==" << "====================================================================" << endl;

            for (int restaurantIdx = 0; restaurantIdx < foodSystem->totalRestaurants; restaurantIdx++) {
                foodSystem->restaurantList[restaurantIdx]->display();
            }

            if (foodSystem->totalRestaurants == 0) {
                cout << "||" << "\t Directory database index returns null records.                " << endl;
            }
            cout << "==" << "====================================================================" << endl;
            system("pause");

        }
        else if (menuChoice == 6) {
            system("cls");
            foodSystem->searchIndex.displayAllRecords();
            system("pause");

        }
        else if (menuChoice == 7) {
            system("cls");
            string restId;
            cout << "==" << "====================================================================" << endl;
            cout << "||" << "                FILTER ORDERS BY RESTAURANT ID                     ||" << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tEnter Restaurant ID (e.g. REST1) : ";
            getline(cin, restId);
            foodSystem->searchIndex.filterOrdersByRestaurant(restId);
            system("pause");

        }
        else if (menuChoice == 8) {
            system("cls");
            double minP, maxP;
            cout << "==" << "====================================================================" << endl;
            cout << "||" << "                FILTER ORDERS BY PRICE RANGE                       ||" << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tEnter Minimum Price : ";
            cin >> minP; cin.ignore();
            cout << "\tEnter Maximum Price : ";
            cin >> maxP; cin.ignore();
            foodSystem->searchIndex.filterOrdersByPriceRange(minP, maxP);
            system("pause");

        }
        else if (menuChoice == 9) {
            system("cls");
            string keyword;
            cout << "==" << "====================================================================" << endl;
            cout << "||" << "                FILTER ALL RECORDS BY KEYWORD                      ||" << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tEnter Keyword to Search : ";
            getline(cin, keyword);
            foodSystem->searchIndex.filterByKeyword(keyword);
            system("pause");

        }
        else if (menuChoice != 0) {
            cout << "\t[INVALID CHOICE]: Please choose an option index between 0 and 9." << endl;
            system("pause");
        }
    } while (menuChoice != 0);
}

void orderHistoryMenu() {
    int menuChoice;
    do {
        system("cls");
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "            MODULE 6: ORDER HISTORY & TRACKING (STACK)            ||  " << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t 1.  Update Order Status Manually (State Matrix Shift)      || " << endl;
        cout << "||" << "\t 2.  View Linear Progress Timeline for a Specific Order     ||  " << endl;
        cout << "||" << "\t 3.  Undo Last Logged Status Change                         ||  " << endl;
        cout << "||" << "\t 4.  View Complete Dynamic System History Log               ||  " << endl;
        cout << "||" << "\t 5.  View All Persistent Orders from Storage Baseline       ||  " << endl;
        cout << "||" << "--------------------------------------------------------------------" << endl;
        cout << "||" << "\t 0.  Back to Main Menu                                      ||" << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "\tEnter Your Choice: ";
        cin >> menuChoice;
        cin.ignore();

        if (menuChoice == 1) {
            system("cls");
            string targetOrderId, newStatusInput;

            cout << "==" << "====================================================================" << endl;
            cout << "||" << "\t\t\t MANUAL STATE TRANSITION CONTROL   " << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tOrder ID   : "; getline(cin, targetOrderId);
            cout << "\tNew Status : "; getline(cin, newStatusInput);
            cout << "==" << "====================================================================" << endl;

            if (foodSystem->updateOrderStatusInFile(targetOrderId, newStatusInput)) {
                cout << "\n\t[SUCCESS]: Status modified and pushed to stack tracking records." << endl;
            }
            else {
                cout << "\n\t[ERROR]: Specified Order identifier not found in repository." << endl;
            }
            system("pause");

        }
        else if (menuChoice == 2) {
            system("cls");
            string targetOrderId;

            cout << "==" << "====================================================================" << endl;
            cout << "||" << "\t\t\t TIMELINE PARAMETER QUERY ENTRY   " << endl;
            cout << "==" << "====================================================================" << endl;
            cout << "\tEnter Target Order ID : "; getline(cin, targetOrderId);
            cout << "==" << "====================================================================" << endl;
            cout << "\n";

            foodSystem->historyStack.displayOrderTimeline(targetOrderId);
            system("pause");

        }
        else if (menuChoice == 3) {
            system("cls");

            if (foodSystem->historyStack.isStackEmpty()) {
                cout << "==" << "====================================================================" << endl;
                cout << "||" << "\t State rollback aborted. Undo history stack is empty.          " << endl;
                cout << "==" << "====================================================================" << endl;
            }
            else {

                HistoryStackEntry lastAction = foodSystem->historyStack.popTopEntry();

                foodSystem->updateOrderStatusInFile(lastAction.orderIdentifier, lastAction.previousStatus);

                foodSystem->historyStack.popTopEntry();

                cout << "==" << "====================================================================" << endl;
                cout << "||" << "                       DISPATCH ENGINE METRICS                    ||" << endl;
                cout << "==" << "====================================================================" << endl;
                cout << "||" << "\t Rollback Target ||\t -> " << lastAction.orderIdentifier << endl;
                cout << "||" << "\t Stripped State  ||\t -> " << lastAction.newStatus << endl;
                cout << "||" << "\t Restored State  ||\t -> " << lastAction.previousStatus << endl;
                cout << "||" << "--------------------------------------------------------------------" << endl;
                cout << "\n\t[UNDO COMPLETE]: File assets and search directory sync recovered." << endl;
                cout << "==" << "====================================================================" << endl;
            }
            system("pause");

        }
        else if (menuChoice == 4) {
            system("cls");
            foodSystem->historyStack.displayCompleteHistory();
            system("pause");

        }
        else if (menuChoice == 5) {
            system("cls");

            ifstream orderReadFile(ordersFile);
            if (!orderReadFile.is_open()) {
                cout << "\n\t[âŒ ERROR]: Failed to construct data stream channel from storage." << endl;
            }
            else {
                Order tempOrder;
                int displayCount = 0;

                cout << "==" << "====================================================================" << endl;
                cout << "||" << "\t\t\t   ALL CURRENT LOGGED ORDERS   " << endl;
                cout << "==" << "====================================================================" << endl;

                while (tempOrder.loadFile(orderReadFile)) {
                    tempOrder.display();
                    displayCount++;
                }
                orderReadFile.close();

                if (displayCount == 0) {
                    cout << "||" << "\t Flat file storage structures contain no recorded logs.         " << endl;
                    cout << "==" << "====================================================================" << endl;
                }
                else {
                    cout << "==" << "====================================================================" << endl;
                }
            }
            system("pause");

        }
        else if (menuChoice != 0) {
            cout << "\t[âŒ INVALID CHOICE]: Please use an entry code index between 0 and 5." << endl;
            system("pause");
        }
    } while (menuChoice != 0);
}

void performanceAnalysisMenu() {
    int menuChoice;
    do {
        system("cls");

        cout << "==" << "====================================================================" << endl;
        cout << "||" << "            MODULE 7: ALGORITHMIC PERFORMANCE ANALYSIS            ||" << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t 1.  Heap Insertion Performance Test (Mathematical Log)     ||" << endl;
        cout << "||" << "\t 2.  Hash Table Search Performance Test (Load Balancing)    ||" << endl;
        cout << "||" << "\t 3.  Dijkstra Route Performance Test                        ||" << endl;
        cout << "||" << "\t 4.  Scalability Comparison Across Dataset Sizes            ||" << endl;
        cout << "||" << "\t 5.  Complexity Summary Matrix (All Dynamic Modules)        ||" << endl;
        cout << "||" << "--------------------------------------------------------------------" << endl;
        cout << "||" << "\t 0.  Back to Main Menu                                      ||" << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "\tEnter Your Choice: ";
        cin >> menuChoice;
        cin.ignore();

        if (menuChoice == 1) {
            system("cls");
            foodSystem->performanceAnalyzer.runHeapInsertionTest();
            system("pause");

        }
        else if (menuChoice == 2) {
            system("cls");
            foodSystem->performanceAnalyzer.runHashSearchTest();
            system("pause");

        }
        else if (menuChoice == 3) {
            system("cls");
            foodSystem->performanceAnalyzer.runDijkstraPerformanceTest();
            system("pause");

        }
        else if (menuChoice == 4) {
            system("cls");
            foodSystem->performanceAnalyzer.runScalabilityTest();
            system("pause");

        }
        else if (menuChoice == 5) {
            system("cls");
            foodSystem->performanceAnalyzer.displayComplexitySummary();
            system("pause");

        }
        else if (menuChoice != 0) {
            cout << "\t[INVALID CHOICE]: Please choose an operational index code between 0 and 5." << endl;
            system("pause");
        }
    } while (menuChoice != 0);
}

void scalabilitySimulationMenu() {
    system("cls");
    int simulationCount;
    cout << "==" << "====================================================================" << endl;
    cout << "||" << "              MODULE 8: SCALABILITY DATASET SIMULATION            ||" << endl;
    cout << "==" << "====================================================================" << endl;
    cout << "\tEnter number of simulated orders to insert (1-500): ";
    cin >> simulationCount;
    cin.ignore();

    if (simulationCount <= 0 || simulationCount > 500) {
        cout << "\n\t[âŒ ERROR]: Out of simulation bounds. Enter a value between 1 and 500." << endl;
        cout << "==" << "====================================================================" << endl;
        system("pause");
        return;
    }

    OrderPriorityQueue simulationHeap;
    cout << "\n\t[âš¡ RUNNING]: Constructing " << simulationCount << " simulated order nodes inside memory arrays..." << endl;

    for (int simIndex = 0; simIndex < simulationCount; simIndex++) {
        Order simulatedOrder;
        simulatedOrder.setOrderIdentifier("SIM" + intToString(simIndex + 1));
        simulatedOrder.setCustomerIdentifier("C" + intToString(simIndex % 10));
        simulatedOrder.setRestaurantIdentifier("R" + intToString(simIndex % 5));
        simulatedOrder.setOrderPriority((simIndex % 4) + 1);
        simulatedOrder.setPreparationTimeMinutes(10 + simIndex % 20);
        simulatedOrder.setDeliveryDeadlineMinutes(30 + simIndex % 60);
        simulatedOrder.setDeliveryCostAmount(50.0 + simIndex % 200);
        simulatedOrder.setOrderStatus("placed");

        simulationHeap.insertOrder(simulatedOrder);
    }

    cout << "\t[âœ… COMPLETE]: Mapped " << simulationHeap.getSize() << " operations into dynamic structures." << endl;
    cout << "\n";

    cout << "==" << "====================================================================" << endl;
    cout << "||" << "\t\t   TOP 5 EXTRACTED PRIORITY METRIC SLOTS            " << endl;
    cout << "==" << "====================================================================" << endl;

    for (int topIndex = 0; topIndex < 5 && !simulationHeap.isEmpty(); topIndex++) {
        Order topOrder = simulationHeap.extractHighestPriority();

        cout << "||" << "\t Slot [" << topIndex + 1 << "]\t||\t -> ID: " << topOrder.getOrderIdentifier() << endl;

        cout << "||" << "\t Weight Rank\t||\t -> Level " << topOrder.getOrderPriority() << endl;
        cout << "||" << "\t Deadline\t||\t -> " << topOrder.getDeliveryDeadlineMinutes() << " min remaining" << endl;

        if (topIndex < 4 && !simulationHeap.isEmpty()) {
            cout << "||" << "----------------------------------------------------------------" << endl;
        }
    }

    cout << "==" << "====================================================================" << endl;
    cout << "||" << "\t\t\t   SIMULATION RESULTS MATRIX   " << endl;
    cout << "==" << "====================================================================" << endl;
    cout << "||" << "\t Sample Size (N)||\t -> " << simulationCount << " Elements processed" << endl;
    cout << "||" << "\t Complexity\t||\t -> Max-Heap Bounds verified at O(N log N)" << endl;
    cout << "||" << "\t Remaining Queue||\t -> " << simulationHeap.getSize() << " Elements safely retained" << endl;
    cout << "==" << "====================================================================" << endl;

    system("pause");
}

void systemReportsMenu() {
    system("cls");

    cout << "==" << "====================================================================" << endl;
    cout << "||" << "                     FOODEXPRESS SYSTEM REPORT                    ||" << endl;
    cout << "==" << "====================================================================" << endl;
    cout << "||" << "\t Report Generated : " << foodSystem->getCurrentTime() << endl;
    cout << "==" << "====================================================================" << endl;

    cout << "||" << "\t\t\t   SYSTEM ENTITY AGGREGATIONS   " << endl;
    cout << "||" << "----------------------------------------------------------------" << endl;
    cout << "||" << "\t Total Customers   ||\t -> " << foodSystem->totalCustomers << " Users logged" << endl;
    cout << "||" << "\t Total Restaurants ||\t -> " << foodSystem->totalRestaurants << " Kitchen hubs" << endl;
    cout << "||" << "\t Total Riders      ||\t -> " << foodSystem->totalRiders << " Fleet units" << endl;
    cout << "||" << "\t Total Orders      ||\t -> " << foodSystem->totalOrders << " Total entries" << endl;
    cout << "||" << "\t Scheduler Heap    ||\t -> " << foodSystem->orderScheduler.getSize() << " Active in Max-Heap" << endl;
    cout << "||" << "\t Undo History Stack||\t -> " << foodSystem->historyStack.getStackSize() << " Transitions logged" << endl;

    ifstream orderReadFile(ordersFile);
    double totalRevenueAmount = 0.0;
    int    deliveredOrderCount = 0, cancelledOrderCount = 0, pendingOrderCount = 0;
    Order  tempOrder;

    if (orderReadFile.is_open()) {
        while (tempOrder.loadFile(orderReadFile)) {
            if (tempOrder.getOrderStatus() == "delivered") {
                totalRevenueAmount += tempOrder.getDeliveryCostAmount();
                deliveredOrderCount++;
            }
            else if (tempOrder.getOrderStatus() == "cancelled") {
                cancelledOrderCount++;
            }
            else {
                pendingOrderCount++;
            }
        }
        orderReadFile.close();
    }
    cout << "==" << "====================================================================" << endl;
    cout << "||" << "\t\t\t FINANCIAL AUDIT REVENUE SUMMARY   " << endl;
    cout << "==" << "====================================================================" << endl;
    cout << "||" << "\t Delivered Orders  ||\t -> " << deliveredOrderCount << " Drops completed" << endl;
    cout << "||" << "\t Cancelled Orders  ||\t -> " << cancelledOrderCount << " Drops dropped" << endl;
    cout << "||" << "\t Pending Active    ||\t -> " << pendingOrderCount << " Processing in queue" << endl;
    cout << "||" << "----------------------------------------------------------------" << endl;
    cout << "||" << "\t TOTAL NET REVENUE ||\t -> Rs. " << totalRevenueAmount << endl;

    cout << "==" << "====================================================================" << endl;
    cout << "||" << "\t\t     LIVE RESTAURANT KITCHEN WORKLOAD BALANCING     " << endl;
    cout << "==" << "====================================================================" << endl;

    if (foodSystem->totalRestaurants == 0) {
        cout << "||" << "\t No active restaurant hubs detected inside tracking vectors.     " << endl;
    }
    else {
        for (int restaurantIdx = 0; restaurantIdx < foodSystem->totalRestaurants; restaurantIdx++) {
            Restaurant* currentRestaurant = foodSystem->restaurantList[restaurantIdx];

            cout << "||" << "\t Hub Profile\t||\t -> " << currentRestaurant->getRestaurantName() << endl;
            cout << "||" << "\t Capacity Load\t||\t -> " << currentRestaurant->getRestaurantCurrentLoad()
                << " / " << currentRestaurant->getRestaurantCapacity() << " Orders assigned" << endl;

            if (currentRestaurant->isKitchenOverloaded()) {
                cout << "||" << "\t RUNTIME STATUS\t||\t -> [CRITICAL OVERLOADED]" << endl;
            }
            else {
                cout << "||" << "\t RUNTIME STATUS\t||\t -> [OPERATIONAL STABLE]" << endl;
            }

            if (restaurantIdx < foodSystem->totalRestaurants - 1) {
                cout << "||" << "----------------------------------------------------------------" << endl;
            }
        }
    }
    cout << "==" << "====================================================================" << endl;
    cout << "\n";

    foodSystem->riderPool.displayAllRiders();

    system("pause");
}

//  MAIN MENU  (FoodExpress Dispatch Optimization Engine)
void mainMenu() {
    int menuChoice;
    do {
        system("cls");
        cout << "==" << "====================================================================" << endl;
        cout << "||       FOODEXPRESS DISPATCH OPTIMIZATION ENGINE                   ||" << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "||" << "\t 1.  Dynamic Order Scheduling                               ||" << endl;
        cout << "||" << "\t 2.  Kitchen Load Analysis                                  ||" << endl;
        cout << "||" << "\t 3.  Rider Dispatch Optimization                            ||" << endl;
        cout << "||" << "\t 4.  Route Optimization                                     ||" << endl;
        cout << "||" << "\t 5.  Search and Retrieval Engine                            ||" << endl;
        cout << "||" << "\t 6.  Order History Tracking                                 ||" << endl;
        cout << "||" << "\t 7.  Algorithmic Performance Analysis                       ||" << endl;
        cout << "||" << "\t 8.  Scalability Simulation                                 ||" << endl;
        cout << "||" << "\t 9.  System Reports                                         ||" << endl;
        cout << "||" << "\t 10. Admin Database Management Hub (Add Customer/Rider)     ||" << endl;
        cout << "||" << "--------------------------------------------------------------------" << endl;
        cout << "||" << "\t 0.  Exit                                                   ||" << endl;
        cout << "==" << "====================================================================" << endl;
        cout << "\tEnter Your Choice: ";
        cin >> menuChoice;
        cin.ignore();

        switch (menuChoice) {
        case 1:  schedulerMenu();            break;
        case 2:  kitchenLoadMenu();          break;
        case 3:  riderDispatchMenu();        break;
        case 4:  routeOptimizationMenu();    break;
        case 5:  searchRetrievalMenu();      break;
        case 6:  orderHistoryMenu();         break;
        case 7:  performanceAnalysisMenu();  break;
        case 8:  scalabilitySimulationMenu(); break;
        case 9:  systemReportsMenu();        break;
        case 10: databaseManagementMenu();   break; 
        case 0:
            system("cls");
            cout << "==" << "====================================================================" << endl;
            cout << "||" << "    THANK YOU FOR USING FOODEXPRESS DISPATCH ENGINE!         ||" << endl;
            cout << "||" << "              Terminal Session Closed Safely.                ||" << endl;
            cout << "==" << "====================================================================" << endl;
            system("pause");
            break;
        default:
            cout << "\n\t[INVALID CHOICE]: Enter a number between 0 and 9." << endl;
            system("pause");
        }
    } while (menuChoice != 0);
}

// 🔥 GLOBAL FIXED HELPER TO INJECT 3 TEST RIDERS
//void forceLoadThreeTestRiders(FoodExpressSystem& sys) {
//
//
//
//
//    if (sys.totalCustomers == 0) {
//        Customer* c1 = new Customer("C1", "Ahmad Khan", "0300-1111111", "Gulberg", "Regular");
//        sys.customerList[sys.totalCustomers++] = c1;
//        sys.searchIndex.insertRecord("C1", "Customer|Ahmad Khan|Regular|Gulberg");
//
//        Customer* c2 = new Customer("C2", "Zainab Bibi", "0321-2222222", "Model Town", "Premium");
//        sys.customerList[sys.totalCustomers++] = c2;
//        sys.searchIndex.insertRecord("C2", "Customer|Zainab Bibi|Premium|Model Town");
//
//        Customer* c3 = new Customer("C3", "Hamza Ali", "0333-3333333", "Mall Road", "VIP");
//        sys.customerList[sys.totalCustomers++] = c3;
//        sys.searchIndex.insertRecord("C3", "Customer|Hamza Ali|VIP|Mall Road");
//
//        c1->saveFile();
//        c2->saveFile();
//        c3->saveFile();
//    }
//
//
//
//
//
//    if (sys.totalRiders == 0) {
//        
//        Rider* r1 = new Rider("RIDER1", "Ahmad Malik", "0300-1234567", "Gulberg", 3);
//        sys.riderList[sys.totalRiders++] = r1;
//        sys.riderPool.insertRiderAtEnd(*r1);
//        sys.searchIndex.insertRecord("RIDER1", "Rider|Ahmad Malik|Gulberg");
//
//        
//        Rider* r2 = new Rider("RIDER2", "Zain Ali", "0321-7654321", "Model Town", 3);
//        sys.riderList[sys.totalRiders++] = r2;
//        sys.riderPool.insertRiderAtEnd(*r2);
//        sys.searchIndex.insertRecord("RIDER2", "Rider|Zain Ali|Model Town");
//
//        
//        Rider* r3 = new Rider("RIDER3", "Hamza Dev", "0333-9876543", "Mall Road", 3);
//        sys.riderList[sys.totalRiders++] = r3;
//        sys.riderPool.insertRiderAtEnd(*r3);
//        sys.searchIndex.insertRecord("RIDER3", "Rider|Hamza Dev|Mall Road");
//
//        r1->saveFile();
//        r2->saveFile();
//        r3->saveFile();
//    }
//}
int main() {
    FoodExpressSystem systemInstance;
    foodSystem = &systemInstance;
    //forceLoadThreeTestRiders(systemInstance);
    mainMenu();
    return 0;
}