#include <iostream>
using namespace std;

class HospitalResource{
    protected:
        bool isAvailable;
        int timesUsed;
    public:
        HospitalResource(){
            isAvailable = false;
            timesUsed = 0;
        }

        void useResource(){
            timesUsed++;
            isAvailable = false; // when one person using then not available..
        }

        void releaseresource(){
            isAvailable = true;
        }

        virtual void displayStatus(){
            cout << "Resource Availability: " << (isAvailable ? "Yes" : "in Use") << endl; // i used here ternary operator like if condition
        }

        virtual double calculateUsageCost()=0;

        virtual ~HospitalResource(){
            cout << "Hospital resource called. " << endl; 
        }
};


class DiagnosticUnit: virtual public HospitalResource {
    protected:
     int testsPerformed;
    public:
     DiagnosticUnit(int tests){
        testsPerformed = tests;
     }

     double calculateUsageCost(){
        return testsPerformed*500; // let perTest  = 500
     }

     void displayStatus() {
        cout << "Resource Type: Diagnostic Unit" << endl;
        HospitalResource::displayStatus();
        cout << "Resource ID: 101" << endl; // fixed ID
        cout << "Costs for test Perormed: " << calculateUsageCost() << endl;
     }
};

class CareUnit: virtual public HospitalResource{
    protected:
        int careHours;
    public:
     CareUnit(int hours){
        careHours = hours;
     }

     double calculateUsageCost() {
        return careHours*300; // let per hour for care = 300
     }

     void displayStatus() {
        cout << "Resource Type: Care Unit" << endl;
        HospitalResource::displayStatus();
        cout << "Resource ID: 202" << endl;
        cout << "Cost for Care Hours: " << calculateUsageCost() << endl;
     }
};

class SmartCareUnit: public DiagnosticUnit, public CareUnit{
    public: 
     SmartCareUnit(int tests, int hours): DiagnosticUnit(tests), CareUnit(hours) {}
     double calculateUsageCost(){
        return (DiagnosticUnit::calculateUsageCost() < CareUnit::calculateUsageCost() )? DiagnosticUnit::calculateUsageCost(): CareUnit::calculateUsageCost();
     }
     void displayStatus() {
        cout << "Resource Type: Smart Care Unit" << endl;
        cout << "Resource ID: 303" << endl;
        HospitalResource::displayStatus();
        cout << "Usage Cost for 3 uses/hours: " << calculateUsageCost() << endl;
    }
};

int main(){
    HospitalResource* hospitalResources[3];

    hospitalResources[0] = new DiagnosticUnit(2);

    hospitalResources[1] = new CareUnit(3);

    hospitalResources[2] = new SmartCareUnit(2,3);
    for(int i =0;i<3;i++){
        hospitalResources[i]->useResource();
        hospitalResources[i]->displayStatus();
        cout << endl;
    }
    
    // releasing sources
    for(int i = 0;i<3;i++){
        hospitalResources[i]->releaseresource();
    }
    return 0;
}