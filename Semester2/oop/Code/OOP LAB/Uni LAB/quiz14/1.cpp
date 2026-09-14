#include<iostream>
using namespace std;

class BiometricLock{
    private:
     string fingerprintData;
    protected:
     void verifyScan(string verification){
        if(fingerprintData == verification){
            cout << "Biometric Lock Verified." << endl;
        }
        else{
            cout << "Lock Locked!. "<< endl;
        }
     }

    public:
     BiometricLock(){
        fingerprintData = "";
     }
     BiometricLock(string f){
        fingerprintData = f;
     }

};

class PasscodeLock{
    private:
     int code;
    public:
     PasscodeLock(){
        code = 0;
     }
     PasscodeLock(int c){
        code = c;
     }

     void checkCode(int c){
        if(code == c){
            cout << " Code Passed. " << endl;
        }
        else {
            cout << "Lock locked." << endl;
        }
     }
};

class SecuityAudit: public BiometricLock, PasscodeLock{
    public:
     SecuityAudit(string f, int c): BiometricLock(f) , PasscodeLock(c) {}
     
     void DigitVault(string f, int c){
        verifyScan(f);
        checkCode(c);
     }
};


int main(){
    string f = "!12we";
    int c = 123456;
    SecuityAudit s1(f, c);
    s1.DigitVault(f,c);

    return 0;
}