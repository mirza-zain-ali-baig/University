// #include <iostream>
// using namespace std;

// TAsk (2) a
// class CoreAI{
//     public:
//      void startup(){
//         cout << "Startup Started. ";
//      }
// };

// class WareHouseHub{
//     CoreAI coreAI;
//     public:
//      WareHouseHub(){
//         cout << "Hub Created. " << endl;
//         coreAI.startup();
//      }
// };

// int main(){
//     WareHouseHub *w1 = new WareHouseHub(); 
//     delete w1;
//     // core ai also deleted.
//     return 0;
// }

// task 02 b

// class Robot{
//     private:
//      int robotID;
//     public:
//      Robot(int r){
//         robotID = r;
//      }

//      int getRobotID(){
//         return robotID;
//      }

// };

// class WareHouseHubb{
//     Robot* r[10];
//     int count;

//     public:
//     WareHouseHubb(){
//         count = 0;
//     }
//      void assignRobot(Robot *r1){
//         r[count++] = r1;
//      }
// };

// int main(){
//     WareHouseHubb *w1 = new WareHouseHubb();
//     Robot r1(1);

//     delete w1;

//     cout << r1.getRobotID() << endl;
//     // robot still exists
// }


// task 03

// class Satellite{
//     string weather;
//     public:
//      Satellite(string w){
//         weather = w;
//      }
//      string getWaether() const{
//         return weather;
//      }


// };

// class WareHouseHubbb{
//     public:
//      void CheckSafety(Satellite *s){
//         cout << s->getWaether() << endl;
//         cout << "Weather condition is okay!" << endl;
//      }
// };

// int main(){
//     WareHouseHubbb w1;
//     Satellite s1("Winter");
//     w1.CheckSafety(&s1);

//     return 0;
// }