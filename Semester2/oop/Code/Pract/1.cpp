#include<iostream>
#include<map>
#include<ctime>     //FOR GENERATING RANDOM TOKEN NUMBERS
#include<fstream>     // FOR FILE HANDLING
#include<conio.h>     // FOR getch() (TO HIDE PASSWORD)
#include<windows.h>   // In this project, we use this only for loading() function
#include<iomanip>   
#include<limits>    //FOR VALIDATING INTEGER INPUT IN THE MENUES
using namespace std;

int count;

void loading()
{
    printf("\e[?25l");
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1=177,bar2=219;
    cout<<"\tLoading..."<<endl;
    cout<<"\t";
    for(int i=0;i<25;i++)
    {
        cout<<(char)bar1;
    }
    cout<<"\r";
    cout<<"\t";
    for(int i=0;i<25;i++)
    {
        cout<<(char)bar2;
        Sleep(150);
    }
    cout<<endl<<endl;
}

class Account
{
    friend class Loan;
    protected:
    int token;
    char password[4];
    string name;
    double balance;
    int numberofdeposits;
    int numberofwithdraws;
    int numberoftransfers;
    public:
    Account()
    {
        token=0;
        balance=0.0;
        numberofdeposits=0;
        numberofwithdraws=0;
        numberoftransfers=0;
    }
    void SetBalance(double b)
    {
        balance=b;
    }
    int GetToken() const
    {
        return token;
    }
    double GetBalance() const
    {
        return balance;
    }
    string GetName() const
    {
        return name;
    }
    int GetNumberOfDeposits() const
    {
        return numberofdeposits;
    }
    int GetNumberOfWithdraws() const
    {
        return numberofwithdraws;
    }
    int GetNumberofTransfers() const
    {
        return numberoftransfers;
    }
    friend ostream& operator<<(ostream& os, const Account& acc) 
    {
         os<<"      Token Number: "<<acc.GetToken()<<endl
         <<"      Name: "<<acc.GetName()<<endl
         <<"      Current Balance: "<<acc.GetBalance()<<endl
         <<"      Number of Deposits: "<<acc.GetNumberOfDeposits()<<endl
         <<"      Number of Withdraws: "<<acc.GetNumberOfWithdraws()<<endl
         <<"      Number of Transfers: "<<acc.GetNumberofTransfers()<<endl<<endl;
         return os; 
    }
    bool operator==(const Account& other) const 
    {
        return (this->token==other.token);  // Compare by token (unique ID)
    }
    bool operator==(int otherToken) const 
    {
        return (this->GetToken()==otherToken);
    }
    void SaveAccount();
    virtual bool LoadAccount(int tok, const char pass[4]);
    
    protected:
    int GenerateToken();
    bool checkingAccount(int find);
    void updateAccount();
    int GetFailedAttempts(int token);             // Helper function to count failed attempts
    void UpdateFailedAttempts(int token, bool reset=false);          // Helper function to update failed attempts
    bool IsAccountFrozen(int token);                // Helper function to check if account is frozen
    void InitializeFailedAttemptsFile();
    bool VerifyToken(int tok);
};

class ATM: public Account
{
    public:
    void Deposit();
    void WithDraw();
    void Receipt(Account A);
    void TransferMoney();
    void operator+=(double amount) 
    {
       balance+=amount;
    }
    void operator-=(double amount) 
    {
       balance-=amount;
    }
};

class Loan
{
    int borrowerToken;
    double loanAmount;
    double remainingAmount;
    string status;
    public:
    Loan()
    {
        borrowerToken=0;
        loanAmount=0;
        remainingAmount=0;
        status="none";
    }
    void ApplyLoan(int token);
    void SaveLoan();
    void ViewLoanStatus(int token);
    void PayLoan(int token);
    bool VerifyLoan(int tok);
    void ApproveLoan();
    void ViewAllLoans();
    void DeleteLoanInformation();
};

class UserAccount: public Account
{
    public:
    void CreateAccount();
    void LoginAccount();
    void Transaction();
};

class AdminAccount: public Account
{
    protected:
    Loan LoanManger;
    public:
    virtual void AdminMenu();
    void ViewAllAccounts();
    void AdminLogin();
    void DeleteAccount();
    void SearchAccount(int find);
    void ViewFrozenAccounts();
    void UnfreezeAccount(int token);
    protected:
    bool LoadAccount(string n,const char pass[4]);           // To fill the attributes of like name,token with the
};                                                           // current account information. Used multiple times in our project

class SuperAdmin: public AdminAccount
{
    public:
    void CreateAccount();
    void LoginAccount();
    void AdminLogin();
    void DeleteAdminAccount();
    void AdminMenu();
    protected:
    void SaveAccount();
};

int main()
{
    system("color 3F");
    srand(static_cast<unsigned int>(time(0)));
    int choice;
do
{
    system("cls");
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<"|************ BANKING MANAGEMENT SYSTEM *************|"<<endl;
    cout<<"|                                                    |"<<endl;
    cout<<"|____________________________________________________|"<<endl;
    cout<<"|                                                    |"<<endl;
    cout<<"|   1. Create New Account                            |"<<endl;
    cout<<"|                                                    |"<<endl;  
    cout<<"|   2. Login To your Account                         |"<<endl;  
    cout<<"|                                                    |"<<endl;
    cout<<"|   3. Admin                                         |"<<endl;
    cout<<"|                                                    |"<<endl;
    cout<<"|   4. Super Admin                                   |"<<endl;
    cout<<"|                                                    |"<<endl;
    cout<<"|   5. Exit                                          |"<<endl;
    cout<<"|                                                    |"<<endl;
    cout<<"|____________________________________________________|"<<endl;
    cout<<"|                                                    |"<<endl;
    cout<<"|****************************************************|"<<endl;
    cout<<"|----------------------------------------------------|"<<endl;
    cout<<endl;
    while(true)
    {
        cout<<"Enter your choice: ";
        cin>>choice;
        if(cin.fail())                                                         // If the input fail while runtime such as user input any string
        {                                                                      // it first clear the input buffers and again ready for input
            cout<<"Invalid Input...Please try again."<<endl;
        	cin.clear();
        	cin.ignore();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');                // this clear maximum buffers and clear until it find new lines means it clears all before the user press enter key
        	continue;                                                           // it skips the code after that and return to the start of the loop
		}
        else if(choice<1 || choice>5)
        {
            cout<<"Invalid Input...Please try again."<<endl;
        }
        else
		break;
    }
    switch(choice)
    {
        case 1:
        {
            UserAccount A;
            system("cls");
            A.CreateAccount();
            break;
        }
        case 2:
        {
            UserAccount A;
            system("cls");
            A.LoginAccount();
            break;
        }
        case 3:
        {
            AdminAccount A;
            A.AdminLogin();
            break;
        }
        case 4:
        {
            SuperAdmin SA;
            SA.AdminLogin();
            break;
        }
        case 5:
        {
            cout<<"Thank You for Using Bank System!"<<endl;
            cout<<"Exiting Program.........."<<endl;
            break;
        }
        default:
        {
            cout<<"Invalid Input...."<<endl;
            system("pause");
        } 
    }
}
while(choice!=5);
}

int Account::GenerateToken()
    {
       return rand()% (1000-1+1)+1;                               // Generate Token between 0 and 1000
    }                                                             // can be vary according to user need

void UserAccount::CreateAccount()
    {
        do
        {
            token=GenerateToken();
        }
        while(VerifyToken(token));
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|********************* SIGNUP ***********************|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;

        cout<<"   Your tokken number is "<<token<<endl;
        cout<<"   Remember your Token number to login"<<endl<<endl;
        cout<<"   Enter your Name: ";
        cin.ignore();
        getline(cin,name);
        cout<<"   Enter your Pin(4-Characters): ";
        for(int i=0;i<4;i++)
        {
            password[i]=getch();
            cout<<"*";
        }
        cout<<endl;
        do
        {
           cout<<"   Enter Initial Account Balance: ";
           cin>>balance;
           if(balance<10000)
           {
              cout<<"   Minimum Amount is 10000. Please enter again.."<<endl;
           }
        }
        while(balance<10000);
        SaveAccount();
        cout<<"\n   Your Account is Successfully created.."<<endl<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|****************************************************|"<<endl;
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<endl;
        system("pause");
    }

    void UserAccount::LoginAccount()
    {
        int tok;
        char pass[4];
        ifstream In("Account.txt"); 
        if(!In)
        {
        cout<<"No Data Found"<<endl;
        system("pause");
        return;
        }
        else
        {
        In.close();
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|************************LOGIN***********************|"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"    Enter your Token Number: ";
        cin>>tok;
        if(!checkingAccount(tok))
        {
            cout<<endl<<"     Account with token Number: "<<tok<<" does not exist"<<endl;
            system("pause");
            return;
        }
        if(IsAccountFrozen(tok))
        {
            cout<<"\nAccount is Frozen...Please Contact Admin"<<endl;
            system("pause");
            return;
        }

        cout<<"    Enter your Pin(4-Characters): ";
        for(int i=0;i<4;i++)
        {
            pass[i]=getch();
            cout<<"*";
        }
        if(LoadAccount(tok,pass))
        {
            UpdateFailedAttempts(tok,true);
            cout<<endl<<endl;
            cout<<"    Sucessfull Login to your Account"<<endl;
            cout<<"|____________________________________________________|"<<endl;
            cout<<"|                                                    |"<<endl;
            cout<<"|****************************************************|"<<endl;
            cout<<"|----------------------------------------------------|"<<endl;
            cout<<endl;
            system("pause");
            Transaction();
        }
        else
        {
            UpdateFailedAttempts(tok);
            int attemptsLeft=3-GetFailedAttempts(tok);
            if(attemptsLeft>0)
            {
            cout<<endl<<"    Invalid Token or Password ("<<attemptsLeft<<" attempts remaining) "<<endl;
            system("pause");
            }
        }
    }
    }

    void ATM::Deposit()
    {
        double amount;
        system("cls");
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|********************** DEPOSIT *********************|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<endl;
        do
        {
        cout<<"     Enter amount to Deposit: ";
        cin>>amount;
        if(amount<0)
        cout<<"     Invalid Input...Please try Again"<<endl;
        }
        while(amount<0);
        *this +=amount;
        numberofdeposits++;
        updateAccount();
        cout<<endl;
        loading();
        cout<<"     Amount Deposit Succesfully"<<endl;
        cout<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|****************************************************|"<<endl;
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<endl;
        system("pause");
    }

    void ATM::WithDraw()
    {
        double amount;
        if(balance<=0)
        {
            cout<<"Insufficient Balance..."<<endl;
            cout<<"Cannot Withdraw"<<endl;
            system("pause");
        }
        else
        {
            system("cls");
            cout<<"|----------------------------------------------------|"<<endl;
            cout<<"|********************* WITHDRAW *********************|"<<endl;
            cout<<"|                                                    |"<<endl;
            cout<<"|____________________________________________________|"<<endl;
            cout<<"|                                                    |"<<endl;
            cout<<endl;
            do{
            cout<<"    Enter amount to Withdraw: ";
            cin>>amount;
            if(amount<0 || amount>balance)
            {
                cout<<"    Invalid Input...Please try again"<<endl;
            }
        }
        while(amount<0 || amount>balance);
        *this-=amount;
        numberofwithdraws++;
        updateAccount();
        cout<<endl;
        loading();
        cout<<"    Amount WithDraw Successfully"<<endl<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|****************************************************|"<<endl;
        cout<<"|----------------------------------------------------|"<<endl<<endl;
        system("pause");
        }
    }

    void SuperAdmin::AdminLogin()
    {
        system("cls");
        string adminname;
        char adminpass[5];
        char adminsavepass[4]={'1','2','3','4'};
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|******************** ADMIN LOGIN *******************|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"   Enter your Name: ";
        cin.ignore();
        getline(cin,adminname);
        cout<<"   Enter your Password ";
        for(int i=0;i<4;i++)
        {
            adminpass[i]=getch();
            cout<<"*";
        }
        adminpass[4]='\0';
        bool check=true;
        for(int i=0;i<4;i++)
        {
            if(adminpass[i]!=adminsavepass[i])
            {
                check=false;
                break;
            }
        }
        if(adminname=="Admin" && check)
        {
            cout<<endl;
            cout<<"   Login Successfully"<<endl<<endl;
            cout<<"|____________________________________________________|"<<endl;
            cout<<"|                                                    |"<<endl;
            cout<<"|****************************************************|"<<endl;
            cout<<"|----------------------------------------------------|"<<endl<<endl;
            system("pause");
            AdminMenu();
        }
        else
        {
            cout<<endl;
            cout<<"   Wrong Admin Name or Password"<<endl<<endl;
            system("pause");
        }
    }

    void AdminAccount::ViewAllAccounts()
    {
        system("cls");
        ifstream InFile;
        InFile.open("Account.txt");
        int t;
        count=0;
        string nam;
        string savepass;
        double b;
        if(!InFile)
        cout<<"File does not Exist"<<endl;
        cout<<"|----------------------- LIST OF ACCOUNTS ----------------------|"<<endl;
        cout<<"|                                                               |"<<endl;
        while(InFile>>t)
        {
            InFile.ignore();
            getline(InFile,nam);
            getline(InFile,savepass);
            InFile>>b;
            cout<<"    Token No: "<<t<<endl;
            cout<<"    Name: "<<nam<<endl;
            cout<<"    Balance: "<<b<<endl;
            count++;
            cout<<endl;
        }
        InFile.close();
        cout<<"\nTotal number of accounts are: "<<count<<endl<<endl;
    }

    void AdminAccount::DeleteAccount()
    {
        system("cls");
        ViewAllAccounts();
        int d;
        do
        {
            cout<<"Enter the token Number to delete: ";
            cin>>d;
            if(d<=0)
            {
                cout<<"Invalid Input...Please try again"<<endl;
            }
        }
        while(d<0);
        ifstream InFile;
        InFile.open("Account.txt");
        ofstream Temp;
        Temp.open("Temp.txt");
        int t;
        string nam;
        char p[5];
        double b;
        bool found=false;
        while(InFile>>t)
        {
            InFile.ignore();
            getline(InFile,nam);
            for(int i=0;i<4;i++)
            {
                p[i]=InFile.get();
            }
            p[4]='\0';
            InFile.ignore();
            InFile>>b;
            InFile.ignore();
            if(t==d)
            {
                found=true;
                count--;
                continue;        //skip this record
            }
            Temp<<t<<endl;
            Temp<<nam<<endl;
            for(int i=0;i<4;i++)
            {
                Temp<<p[i];
            }
            Temp<<endl;
            Temp<<b<<endl;
        }
        InFile.close();
        Temp.close();
        remove("Account.txt");
        rename("Temp.txt","Account.txt");
        if(found)
        {
            cout<<"The Account with Token Number "<<d<<" has been successfully deleted"<<endl;
        }
        else
        cout<<"Token Number not found"<<endl;

        system("pause");
    }

    void Account::SaveAccount()
    {
        ofstream OutFile;
        OutFile.open("Account.txt",ios::app);
        OutFile<<token<<endl<<name<<endl;
        for(int i=0;i<4;i++)
        {
            OutFile<<password[i];
        }
        OutFile<<endl;
        OutFile<<balance<<endl;
        OutFile.close();
    }

    bool Account::LoadAccount(int tok, const char pass[4])
{
    ifstream InFile("Account.txt");
    if (!InFile)
        return false;

    int  savetok;
    string savename;
    char savepass[5];
    double savebal;
    while (InFile>>savetok)
    {
        InFile.ignore();
        getline(InFile,savename);
        for (int i=0;i<4;i++)
            savepass[i]=InFile.get();               //InFile>>savepass[i] can be used but it will skip whitespaces
        savepass[4]='\0';                           //'\0' it shows that the array of characters is completed
        InFile.get();
        InFile>>savebal;
        InFile.ignore();

        bool match=true;
        for(int i=0;i<4;i++)
        {
            if(pass[i]!=savepass[i])
            {
                match=false;
                break;
            }
        }

        if(savetok==tok && match)
        {
            token=savetok;
            name=savename;
            for(int i=0;i<4;i++)
                password[i]=savepass[i];
            balance=savebal;
            return true;
        }
    }
    return false;
}

void Account::updateAccount()
{
    ifstream InFile;
    InFile.open("Account.txt");
    ofstream Temp;
    Temp.open("temp.txt");
    int t;
    string n;
    char p[5];
    double b;
    while(InFile>>t)
    {
        InFile.ignore();
        getline(InFile,n);
        for(int i=0;i<4;i++)
        {
            p[i]=InFile.get();
        }
        p[4]='\0';
        InFile.ignore();
        InFile>>b;
        InFile.ignore();
        if(t==token)
        {
            Temp<<token<<endl;
            Temp<<name<<endl;
            for(int i=0;i<4;i++)
            {
                Temp<<password[i];
            }
            Temp<<endl;
            Temp<<balance<<endl;
        }
        else
        {
            Temp<<t<<endl;
            Temp<<n<<endl;
            for(int i=0;i<4;i++)
            {
                Temp<<p[i];
            }
            Temp<<endl<<b<<endl;
        }
    }
    InFile.close();
    Temp.close();
    remove("Account.txt");
    rename("temp.txt","Account.txt");
}

void AdminAccount::SearchAccount(int find)
{
    ifstream InFile;
    InFile.open("Account.txt");
    char pass[5];
    int t;
    bool f=false;
    while(InFile>>t)
    {
            InFile.ignore();
            getline(InFile,name);
            InFile.ignore();
            for(int i=0;i<4;i++)
            {
                pass[i]=InFile.get();
            }
            pass[4]='\0';
            InFile>>balance;
            if(find==t)
            {
                f=true;
               cout<<endl;
               cout<<"      Token Number: "<<t<<endl;
               cout<<"      Name: "<<name<<endl;
               cout<<"      Balance: "<<balance<<endl;
               cout<<endl;
               cout<<"|____________________________________________________|"<<endl;
               cout<<"|                                                    |"<<endl;
               cout<<"|****************************************************|"<<endl;
               cout<<"|----------------------------------------------------|"<<endl;
               break;
            }
    }
    if(!f)
    cout<<"The Account not found"<<endl;
    InFile.close();
}

void ATM::Receipt(Account A)
{
    system("cls");
            cout<<"|----------------------------------------------------|"<<endl;
            cout<<"|************** TRANSACTION RECEIPT *****************|"<<endl;
            cout<<"|                                                    |"<<endl;
            cout<<"|____________________________________________________|"<<endl;
            cout<<"|                                                    |"<<endl;
            cout<<A;                                                                            // overload the operator "<<" which now used to show recipts data
            cout<<"|____________________________________________________|"<<endl;
            cout<<"|                                                    |"<<endl;
            cout<<"|****************************************************|"<<endl;
            cout<<"|----------------------------------------------------|"<<endl<<endl;
    system("pause");
}

void UserAccount::Transaction()
    {
        ATM A;
        int choice1;
        do
        {
        system("cls");
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|****************** TRANSACTIONS ********************|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   1. Deposit                                       |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   2. Withdraw                                      |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   3. Check Balance                                 |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   4. Transfer Balance                              |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   5. Apply For Loan                                |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   6. View Loan Status                              |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   7. Pay Loan                                      |"<<endl;        
        cout<<"|                                                    |"<<endl;        
        cout<<"|   8. Log Out                                       |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|****************************************************|"<<endl;
        cout<<"|----------------------------------------------------|"<<endl;
        while(true)
        {
        cout<<"Enter your choice: ";
        cin>>choice1;
        if(cin.fail())
        {
            cout<<"Invalid Input...Please try again"<<endl;
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	continue;
		}
        else if(choice1<1 || choice1>8)
        {
            cout<<"Invalid Input...Please try again."<<endl;
        }
        else
		break;
        }
        switch(choice1)
        {
            case 1:
            {
                A.LoadAccount(token,password);
                A.Deposit();
                break;
            }
            case 2:
            {
                A.LoadAccount(token,password);
                A.WithDraw();
                break;
            }
            case 3:
            {
                system("cls");
                A.LoadAccount(token,password);
                cout<<"|----------------------------------------------------|"<<endl;
                cout<<"|***************** Account Details ******************|"<<endl;
                cout<<"|____________________________________________________|"<<endl;
                cout<<"|                                                    |"<<endl;
                cout<<endl;
                cout<<"    Token Number: "<<A.GetToken()<<endl;
                cout<<"    Name: "<<A.GetName()<<endl;
                cout<<"    Current Balance: "<<A.GetBalance()<<endl;
                cout<<endl;
                cout<<"|____________________________________________________|"<<endl;
                cout<<"|                                                    |"<<endl;
                cout<<"|****************************************************|"<<endl;
                cout<<"|----------------------------------------------------|"<<endl;
                system("pause");
                break;
            }
            case 4:
            {
                A.LoadAccount(token,password);
                A.TransferMoney();
                break;
            }
            case 5:
            {
                Loan L;
                L.ApplyLoan(token);
                break;
            }

            case 6:
            {
                Loan L;
                L.ViewLoanStatus(token);
                break;
            }

            case 7:
            {
                Loan L;
                L.PayLoan(token);
                break;
            }

            case 8:
            {
                A.LoadAccount(token,password);
                char c;
                do
                {
                    cout<<"Do you want a Transaction Reciept(Y/N): ";
                    cin>>c;
                }
                while(c!='Y' && c!='y' && c!='N' && c!='n');
                if(c=='Y' || c=='y')
                {
                    A.Receipt(A);
                }
                break;
            }
            default:
            {
                cout<<"Invalid Input"<<endl;
                system("pause");
            }
        }
        }
        while(choice1!=8);
    }

    void AdminAccount::AdminMenu()
    {
        int choice2;
        do
        {
        system("cls");
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|******************* ADMIN Menu   *******************|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   1. View All Accounts                             |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   2. Delete Account                                |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   3. Search Account                                |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   4. UnFreeze Account                              |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   5. View Frozen Accounts                          |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   6. Approve Loan                                  |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   7. View All Loan Information                     |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   8. Delete Paid Loan Account Record               |"<<endl;
        cout<<"|                                                    |"<<endl;  
        cout<<"|   9. Log Out                                       |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|****************************************************|"<<endl;
        cout<<"|----------------------------------------------------|"<<endl<<endl;
        
        while(true)
        {
        cout<<"Enter your choice: ";
        cin>>choice2;
        if(cin.fail())
        {
            cout<<"Invalid Input...Please try again"<<endl;
        	cin.clear();
        	cin.ignore();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	continue;
		}
        else if(choice2<1 || choice2>9)
        {
            cout<<"Invalid Input...Please try again."<<endl;
        }
		else
		    break;
        }
        switch(choice2)
        {
            case 1:
            {
                AdminAccount A;
                A.ViewAllAccounts();
                system("pause");
                break;
            }
            case 2:
            {
                AdminAccount A;
                A.DeleteAccount();
                break;
            }
            case 3:
            {
                AdminAccount A;
                system("cls");
                int search;
                cout<<"|----------------------------------------------------|"<<endl;
                cout<<"|******************* SEARCH ACCOUNT *****************|"<<endl;
                cout<<"|                                                    |"<<endl;
                cout<<"|____________________________________________________|"<<endl;
                cout<<"|                                                    |"<<endl;
                do
                {
                    cout<<"      Enter the token number to find: ";
                    cin>>search;
                    if(search<=0)
                    {
                        cout<<"Invalid Input...Please try again"<<endl;
                    }
                }
                while(search<=0);
                A.SearchAccount(search);
                system("pause");
                break;
            }
            case 4:
            {
                AdminAccount A;
                system("cls");
                int tok;
                cout<<"|----------------------------------------------------|"<<endl;
                cout<<"|***************** UNFREEZE ACCOUNT *****************|"<<endl;
                cout<<"|____________________________________________________|"<<endl;
                cout<<"|                                                    |"<<endl;
                cout<<"    Enter token number to unfreeze: ";
                cin>>tok;
                A.UnfreezeAccount(tok);
                system("pause");
                break;
            }
            case 5:
            {
                ViewFrozenAccounts();
                break;
            }

            case 6:
            {
                LoanManger.ApproveLoan();
                break;
            }

            case 7:
            {
                AdminAccount A;
                LoanManger.ViewAllLoans();
                break;
            }
            case 8:
            {
                AdminAccount A;
                LoanManger.DeleteLoanInformation();
                break;
            }
            case 9:
            {
                cout<<"\nLogging Out.."<<endl;
                system("pause");
                break;
            }
            default:
            {
                cout<<"Invalid Input..."<<endl;
                system("pause");
                break;
            }
        }
        }
        while(choice2!=9);
    }

void ATM::TransferMoney()
{
    system("cls");
    int receiverToken;
    double amount;
    cout<<"|-------------------------------------------------------|\n";
    cout<<"|****************** TRANSFER BALANCE *******************|\n";
    cout<<"|                                                       |\n";
    cout<<"|_______________________________________________________|\n";
    cout<<"|                                                       |\n";
    cout<<endl;
    cout<<"     Enter receiver's token number: ";
    cin>>receiverToken;

    if(!checkingAccount(receiverToken))
    {
        cout<<"     Receiver Token not found"<<endl;
        system("pause");
        return;
    }

    if(*this==receiverToken) 
	{
        cout<<"     You cannot transfer to your own account.\n";
        system("pause");
        return;
    }
    cout<<"     Enter amount to transfer: ";
    cin>>amount;
    if(amount<=0) 
	{
        cout<<"     Invalid amount!\n";
        system("pause");
        return;
    }
    if(!LoadAccount(token, password)) {
        cout<<"     Error loading sender account data."<<endl;
        system("pause");
        return;
    }
    if(balance<amount) 
	{
        cout<<"     Insufficient balance!\n";
        system("pause");
        return;
    }
    int senderToken=token;
    string senderName=name;
    char senderPass[4];
    for(int i=0;i<4;i++) 
	{
        senderPass[i]=password[i];
    }
    double senderBalance=balance;
    ifstream InFile("Account.txt");
    if(!InFile)
    {
        cout<<"     Account data file missing!"<<endl;
        system("pause");
        return;
    }
    ofstream Temp("temp.txt");
    int t;
    string n;
    char p[5];
    double b;
    bool receiverFound=false;
    while(InFile>>t)
    {
        InFile.ignore();
        getline(InFile, n);
        for(int i=0; i<4; i++)
        {
            p[i]=InFile.get();
        }
        p[4]='\0';
        InFile.ignore();
        InFile>>b;
        InFile.ignore();
        if(t==senderToken)
        {
            senderBalance -= amount;
            balance = senderBalance; // Update current object's balance for consistency
            numberoftransfers++;
            Temp<<t<<endl;
            Temp<<senderName<<endl;
            for(int i=0;i<4;i++)
            {
                Temp<<senderPass[i];
            }
            Temp<<endl;
            Temp<<senderBalance<<endl;
        }
        else if(t==receiverToken)
        {
            b+=amount;
            receiverFound=true;
            Temp<<t<<endl;
            Temp<<n<<endl;
            for(int i=0;i<4;i++)
            {
                Temp<<p[i];
            }
            Temp<<endl;
            Temp<<b<<endl;     
        }
        else
        {
            Temp<<t<<endl;
            Temp<<n<<endl;
            for(int i=0;i<4;i++)
            {
                Temp<<p[i];
            }
            Temp<<endl;
            Temp<<b<<endl;
        }
    }
    InFile.close();
    Temp.close();
    if(!receiverFound)
    {
        cout<<"     Receiver account not found. Transfer failed.\n";
        remove("temp.txt");
        system("pause");
        return;
    }
    else
    {
        remove("Account.txt");
        rename("temp.txt", "Account.txt");
        updateAccount();
        cout<<endl;
        loading();
        cout<<endl;
        cout<<"     Amount transferred successfully.\n";
    }
    cout<<"\n|_______________________________________________________|\n";
    cout<<"|                                                       |\n";
    cout<<"|*******************************************************|\n";
    cout<<"|-------------------------------------------------------|\n\n";
    system("pause");
}

void SuperAdmin::AdminMenu()
    {
        int choice2;
        do
        {
        system("cls");
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|*************** SUPER ADMIN Menu *******************|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   1. View All Users Accounts                       |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   2. Delete Users Account                          |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   3. Search Users Account                          |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   4. Create Admin Account                          |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   5. Delete Admin Account                          |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   6. Unfreeze User Account                         |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   7. View Freezed User Accounts                    |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   8. Approve Loan                                  |"<<endl;
        cout<<"|                                                    |"<<endl;        
        cout<<"|   9. View All Loan Information                     |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|   10. Delete Paid Loan Account Record              |"<<endl;
        cout<<"|                                                    |"<<endl;         
        cout<<"|   11. Log Out                                      |"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|****************************************************|"<<endl;
        cout<<"|----------------------------------------------------|"<<endl<<endl;
        while(true)
        {
        cout<<"Enter your choice: ";
        cin>>choice2;
        if(cin.fail())
        {
            cout<<"Invalid Input...Please try again"<<endl;
        	cin.clear();
        	cin.ignore();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	continue;
		}
        else if(choice2<1 || choice2>11)
        {
            cout<<"Invalid Input...Please try again."<<endl;
        }
		else
		    break;
        }
        switch(choice2)
        {
            case 1:
            {
                SuperAdmin A;
                A.ViewAllAccounts();
                system("pause");
                break;
            }
            case 2:
            {
                SuperAdmin A;
                A.DeleteAccount();
                break;
            }
            case 3:
            {
                SuperAdmin A;
                system("cls");
                int search;
                cout<<"|----------------------------------------------------|"<<endl;
                cout<<"|******************* SEARCH ACCOUNT *****************|"<<endl;
                cout<<"|                                                    |"<<endl;
                cout<<"|____________________________________________________|"<<endl;
                cout<<"|                                                    |"<<endl;
                do
                {
                    cout<<"      Enter the token number to find: ";
                    cin>>search;
                    if(search<=0)
                    {
                        cout<<"Invalid Input...Please try again"<<endl;
                    }
                }
                while(search<=0);
                A.SearchAccount(search);
                system("pause");
                break;
            }
            case 4:
            {
                SuperAdmin SP;
                SP.CreateAccount();
                break;
            }
            case 5:
            {
                SuperAdmin SP;
                SP.DeleteAdminAccount();
                break;
            }
            case 6:
            {
                SuperAdmin SP;
                system("cls");
                int tok;
                cout<<"|----------------------------------------------------|"<<endl;
                cout<<"|***************** UNFREEZE ACCOUNT *****************|"<<endl;
                cout<<"|____________________________________________________|"<<endl;
                cout<<"|                                                    |"<<endl;
                cout<<"    Enter token number to unfreeze: ";
                cin>>tok;
                SP.UnfreezeAccount(tok);
                system("pause");
                break;
            }
            case 7:
            {
                SuperAdmin SP;
                SP.ViewFrozenAccounts();
                break;
            }
            case 8:
            {
                SuperAdmin SP;
                LoanManger.ApproveLoan();
                break;
            }
            case 9:
            {
                SuperAdmin SP;
                LoanManger.ViewAllLoans();
                break;
            }
            case 10:
            {
                SuperAdmin SP;
               LoanManger.DeleteLoanInformation();
                break;
            }
            case 11:
            {
                cout<<"\nLogging Out.."<<endl;
                system("pause");
                break;
            }
            default:
            {
                cout<<"Invalid Input..."<<endl;
                system("pause");
                break;
            }
        }
        }
        while(choice2!=11);
    }

    void SuperAdmin::CreateAccount()
    {
        system("cls");
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|********************* SIGNUP ***********************|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"   Enter your Name: ";
        cin.ignore();
        getline(cin,name);
        cout<<"   Enter your password(4-Characters): ";
        for(int i=0;i<4;i++)
        {
            password[i]=getch();
            cout<<"*";
        }
        cout<<endl;
        SaveAccount();
        cout<<"\n   Your Account is Successfully created.."<<endl<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|****************************************************|"<<endl;
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<endl;
        system("pause");
    }

    void SuperAdmin::LoginAccount()
    {
        string n;
        char pass[4];
        ifstream In("Admin.txt"); 
        if(!In)
        {
        cout<<"No Data Found"<<endl;
        system("pause");
        return;
        }
        else
        {
        In.close();
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|*********************** LOGIN **********************|"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"    Enter your Name: ";
        getline(cin,n);
        cout<<"    Enter your Password(4-Characters): ";
        for(int i=0;i<4;i++)
        {
            pass[i]=getch();
            cout<<"*";
        }
        if(LoadAccount(n,pass))
        {
            cout<<endl<<endl;
            cout<<"    Sucessfull Login to your Account"<<endl;
            cout<<"|____________________________________________________|"<<endl;
            cout<<"|                                                    |"<<endl;
            cout<<"|****************************************************|"<<endl;
            cout<<"|----------------------------------------------------|"<<endl;
            cout<<endl;
            system("pause");
        }
        else
        {
            cout<<endl<<"    Invalid Token or Password"<<endl;
            system("pause");
        }
    }
    }

    void SuperAdmin::SaveAccount()
    {
        ofstream OutFile;
        OutFile.open("Admin.txt",ios::app);
        OutFile<<name<<endl;
        for(int i=0;i<4;i++)
        {
            OutFile<<password[i];
        }
        OutFile<<endl;
        OutFile.close();
    }

    bool AdminAccount::LoadAccount(string n, const char pass[4])
{
    ifstream InFile;
    InFile.open("Admin.txt"); 
    if (!InFile)
    {
        InFile.close();
        return false;
    }
    string savename;
    string savepass;
    while (getline(InFile,savename))
    {
        InFile>>savepass;
        InFile.ignore();

        bool match=true;
        for(int i=0;i<4;i++)
        {
            if(pass[i]!=savepass[i])
            {
                match=false;
                break;
            }
        }

        if(savename==n && match)
        {
            name=savename;
            for(int i=0;i<4;i++)
                password[i]=savepass[i];
            return true;
        }
    }
    return false;
}

void SuperAdmin::DeleteAdminAccount()
    {
        system("cls");
        ifstream InFile;
        InFile.open("Admin.txt", ios::ate); //open and move to end
        if(!InFile)
        {
            cout<<"   File not Found..."<<endl;
            system("pause");
            InFile.close();
            return;
        }
        if(InFile.tellg()==0)
        {
            cout<<"   File is empty..."<<endl;
            system("pause");
            InFile.close();
            return;
        }
        InFile.seekg(0);   //move back to start
        string line;
        count=0;
        cout<<"|------------ Admin Account Holder's Name -------------|"<<endl;
        cout<<"|                                                      |"<<endl;
        while(getline(InFile,line))
        {
            cout<<"   "<<line<<endl<<endl;
            InFile.ignore(4);
            InFile.ignore();
            count++;
        }
        InFile.close();
        cout<<endl;
        cout<<"   Total Number of Admin Accounts: "<<count<<endl<<endl;
        string named;
        cin.ignore();
        cout<<"   Enter the name of the Account Holder: ";
        getline(cin,named);
        InFile.open("Admin.txt");
        ofstream Temp;
        Temp.open("Temp.txt");
        string nam;
        char p[5];
        bool found=false;
        while(getline(InFile,nam))
        {
            for(int i=0;i<4;i++)
            {
                p[i]=InFile.get();
            }
            p[4]='\0';
            InFile.ignore();
            if(named==nam)
            {
                found=true;
                continue;        //skip this record and go to the start of the loop
            }
            Temp<<nam<<endl;
            for(int i=0;i<4;i++)
            {
                Temp<<p[i];
            }
            Temp<<endl;
        }
        InFile.close();
        Temp.close();
        remove("Admin.txt");
        rename("Temp.txt","Admin.txt");
        if(found)
        {
            cout<<"   The Account with Holder name "<<named<<" has been successfully deleted"<<endl;
            count--;
        }
        else
        cout<<endl<<"   Holder Name not found"<<endl<<endl;
        system("pause");
    }

    void AdminAccount::AdminLogin()
    {
        system("cls");
        ifstream InFile;
        InFile.open("Admin.txt");
        string nam;
        char pass[5];
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|********************* ADMIN LOGIN ******************|"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"     Enter your Name: ";
        cin.ignore();
        getline(cin,nam);
        cout<<"     Enter your password(4 character): ";
        for(int i=0;i<4;i++)
        {
            pass[i]=getch();
            cout<<"*";
        }
        pass[4]='\0';
        cout<<endl;
        if(LoadAccount(nam,pass))
        {
            cout<<"     Login Successfully to your account."<<endl<<endl;
            cout<<"|____________________________________________________|"<<endl;
            cout<<"|                                                    |"<<endl;
            cout<<"|****************************************************|"<<endl;
            cout<<"|----------------------------------------------------|"<<endl<<endl;
            system("pause");
            AdminMenu();
        }
        else
        {
            cout<<"     Invalid Name or password...Please try again"<<endl<<endl;
            system("pause");
        }
    }

    bool Account::checkingAccount(int find)
    {
        ifstream InFile;
        InFile.open("Account.txt");
        char pass[5];
        int t;
        bool f=false;;
        while(InFile>>t)
        {
            InFile.ignore();
            getline(InFile,name);
            InFile.ignore();
            for(int i=0;i<4;i++)
            {
                pass[i]=InFile.get();
            }
            pass[4]='\0';
            InFile>>balance;
            if(find==t)
            {
                f=true;
                break;
            }
        }
        InFile.close();
        return f;
    }

    int Account::GetFailedAttempts(int token) 
    {
    InitializeFailedAttemptsFile();
    ifstream failFile("FailedAttempts.txt");
    int t,attempts;
    while(failFile>>t>>attempts) 
    {
        if(t==token) 
        {
            failFile.close();
            return attempts;
        }
    }
    failFile.close();
    return 0;
    }

    void Account::UpdateFailedAttempts(int token, bool reset) 
    {
    InitializeFailedAttemptsFile();
    ifstream inFile("FailedAttempts.txt");
    map<int,int> attemptsMap;
    int t,a;                              // Read existing data
    while(inFile>>t>>a) 
    {
        attemptsMap[t]=a;
    }
    inFile.close();
    
    if(reset)                            // Update or add the token
    {
        attemptsMap.erase(token);
    } 
    else
    {
        attemptsMap[token]++;
    }
    ofstream outFile("FailedAttempts.txt");                 // Write back to file
    for(const auto& entry:attemptsMap)                      // Here we use For each loop with auto datatype
    {
        outFile<<entry.first<<" "<<entry.second<<endl;      // mapping store value like a pair in which eentry.first shows the first part of pair and so on
    }
    outFile.close();
    }

    bool Account::IsAccountFrozen(int token) 
    {
    InitializeFailedAttemptsFile();
    return GetFailedAttempts(token)>=3;
    }

    void AdminAccount::ViewFrozenAccounts() 
    {
       system("cls");
       cout<<"|----------------------------------------------------|"<<endl;
       cout<<"|*************** FROZEN ACCOUNTS LIST ***************|"<<endl;
       cout<<"|____________________________________________________|"<<endl;
       cout<<"|                                                    |"<<endl;
       ifstream file("FailedAttempts.txt");
       if(!file) 
       {
          cout<<"    No frozen accounts found"<<endl;
          system("pause");
          return;
       }
       int token,attempts;
       bool anyFrozen=false;
       while(file>>token>>attempts) 
       {
       if(attempts>=3) 
        {
            cout<<"    Token: "<<token<<" (Failed attempts: "<<attempts<<")"<<endl;
            anyFrozen = true;
        }
       }
       if(!anyFrozen) 
       {
        cout<<"    No frozen accounts found"<<endl;
       }
       cout<<"|____________________________________________________|"<<endl;
       cout<<"|                                                    |"<<endl;
       cout<<"|****************************************************|"<<endl;
       cout<<"|----------------------------------------------------|"<<endl;
       system("pause");
    }

    void AdminAccount::UnfreezeAccount(int token) 
    {
       if(!VerifyToken(token))
       {
          cout<<"Account does not exist!"<<endl;
       }
       else if(!IsAccountFrozen(token))
       {
          cout<<"Account is not Frozen"<<endl;
       } 
       else
       {
          UpdateFailedAttempts(token, true);
          cout<<"Account with token number "<< token<<" is unfrozed.\n";
       }
    }

    void Account::InitializeFailedAttemptsFile()
    {
        ifstream test("FailedAttempts.txt");
        if(!test) 
        {
           ofstream create("FailedAttempts.txt");
           create.close();
        }
        test.close();
    }

    bool Account::VerifyToken(int tok)
    {
        ifstream InFile("Account.txt");
        if (!InFile)
        return false;
        bool match=false;
        int  savetok;
        string savename;
        char savepass[5];
        double savebal;
        while(InFile>>savetok)
        {
            InFile.ignore();
            getline(InFile,savename);
            for(int i=0;i<4;i++)
            savepass[i]=InFile.get();               //InFile>>savepass[i] can be used but it will skip whitespaces
            savepass[4]='\0';                           //'\0' it shows that the array of characters is completed
            InFile.get();                               // '\0' called the null terminator
            InFile>>savebal;
            InFile.ignore();

            if(tok==savetok)
            {
               match=true;
               break;
            }
        }
        InFile.close();
        return match;
    }

    void Loan::SaveLoan()
    {
        ofstream Write("Loan.txt",ios::app);
        Write<<borrowerToken<<endl;
        Write<<loanAmount<<endl;
        Write<<remainingAmount<<endl;
        Write<<status<<endl;
        Write.close();
    }

    bool Loan::VerifyLoan(int tok)
    {
        bool f=false;
        ifstream Read("Loan.txt");
        while(Read>>borrowerToken>>loanAmount>>remainingAmount>>status)
        {
            if(borrowerToken==tok){
            f=true;
            break;
            }
        }
        Read.close();
        return f;
    }

    void Loan::ApplyLoan(int token)
    {
        system("cls");
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|********************* APPLY LOAN *******************|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl<<endl;
        if(VerifyLoan(token))
        {
            cout<<"      You can apply loan one at a time."<<endl;
            system("pause");
            return;
        }
        borrowerToken=token;
        do
        {
            cout<<"      Enter loan amount: ";
            cin>>loanAmount;
            if(loanAmount<=0)
            cout<<"      Loan Amount cannot be smaller than zero"<<endl;
        }
        while(loanAmount<=0);
        remainingAmount=loanAmount;
        status="pending";
        SaveLoan();
        cout<<"      Loan Application submitted. "<<endl<<"      Please wait for approval."<<endl;
       cout<<"|____________________________________________________|"<<endl;
       cout<<"|                                                    |"<<endl;
       cout<<"|****************************************************|"<<endl;
       cout<<"|----------------------------------------------------|"<<endl;
       system("pause");
    }

    void Loan::ViewLoanStatus(int token)
    {
        system("cls");
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|******************** LOAN Record *******************|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl<<endl;
        ifstream Read("Loan.txt");
        if(!Read)
        {
            cout<<"      No Loan File found..."<<endl;
            system("pause");
            return;
        }
        bool found=false;
        while(Read>>borrowerToken>>loanAmount>>remainingAmount>>status)
        {
            if(borrowerToken==token)
            {
                found=true;
                cout<<"       Loan Amount :   "<<loanAmount<<endl;
                cout<<"       Remaining   :   "<<remainingAmount<<endl;
                cout<<"       Status      :   "<<status<<endl;
                break;
            }
        }
        Read.close();
        if(!found)
        {
            cout<<"       No Loan found for your account."<<endl;
        }
       cout<<"|____________________________________________________|"<<endl;
       cout<<"|                                                    |"<<endl;
       cout<<"|****************************************************|"<<endl;
       cout<<"|----------------------------------------------------|"<<endl;
       system("pause");
    }

    void Loan::PayLoan(int token)
    {
        double pay;
        ifstream Read("Loan.txt");
        ofstream temp("Temp.txt");
        bool found=false;
        double paymentAmount=0;
        system("cls");
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|******************* LOAN PAYMENT *******************|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl<<endl;
        while(Read>>borrowerToken>>loanAmount>>remainingAmount>>status)
        {
            if(borrowerToken == token && status == "approved")
            {
                do
                {
                    cout<<"    Enter amount to pay: ";
                    cin>>pay;
                    if(pay<=0)
                    cout<<"    Payment cannot be below zero."<<endl;
                    if(pay>remainingAmount)
                    cout<<"    Amount Exceeded from Remaining Amount.."<<endl;
                }
                while(pay<=0 || pay>remainingAmount);
                paymentAmount=pay;
                remainingAmount-=pay;
                cout<<endl;
                loading();
                if(remainingAmount<=0)
                {
                    remainingAmount=0;
                    status="paid";
                    cout<<"    Loan fully paid"<<endl;
                }
                else
                {
                    cout<<"    Payment Successful"<<endl;
                }
                found=true;
            }
            temp<<borrowerToken<<endl;
            temp<<loanAmount<<endl;
            temp<<remainingAmount<<endl;
            temp<<status<<endl;
        }
        Read.close();
        temp.close();
        remove("Loan.txt");
        rename("Temp.txt","Loan.txt");
        if(found && paymentAmount>0)
        {
            ifstream accIn("Account.txt");
            ofstream accTemp("AccTemp.txt");
            int t;
            string n;
            char p[5];
            double b;
            while(accIn>>t)
            {
                accIn.ignore();
                getline(accIn,n);
                for(int i=0;i<4;i++)
                {
                    p[i] = accIn.get();
                }
                p[4]='\0';
                accIn.ignore();
                accIn>>b;
                accIn.ignore();
                if(t==token)
                {
                    if(b>=paymentAmount)
                    {
                        b-=paymentAmount;
                    }
                    else
                    {
                        cout<<"    Warning: Account balance was insufficient, payment not processed!"<<endl;
                        system("pause");
                    }
                }
                accTemp<<t<<endl;
                accTemp<<n<<endl;
                for(int i=0;i<4;i++)
                {
                    accTemp<<p[i];
                }
                accTemp<<endl;
                accTemp<<b<<endl;
            }
            accIn.close();
            accTemp.close();
            remove("Account.txt");
            rename("AccTemp.txt", "Account.txt");
        }
        else if(!found)
        {
            cout<<"    No Approved loan found for your account."<<endl;
        }
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|****************************************************|"<<endl;
        cout<<"|----------------------------------------------------|"<<endl;
        system("pause");
    }

    void Loan::ApproveLoan()
    {
        system("cls");
        Account A;
        int tok;
        cout<<"|--------------------------------------------------------------|"<<endl;
        cout<<"|*********************** LOAN APPROVAL ************************|"<<endl;
        cout<<"|                                                              |"<<endl;
        cout<<"     Enter token number to approve loan: ";
        cin>>tok;
        if(!A.VerifyToken(tok))
        {
            cout<<"     Account does not exist..."<<endl;
            system("pause");
            return;
        }
        ifstream Read("Loan.txt");
        ofstream temp("Temp.txt");
        bool found=false;
        double approvedLoanAmount=0;
        while(Read>>borrowerToken>>loanAmount>>remainingAmount>>status)
        {
            if(borrowerToken==tok && status=="pending")
            {
                status="approved";
                found=true;
                approvedLoanAmount=loanAmount;
                cout<<"     Loan approved! Amount: "<<approvedLoanAmount<<" added to account."<<endl;
            }
            temp<<borrowerToken<<endl;
            temp<<loanAmount<<endl;
            temp<<remainingAmount<<endl;
            temp<<status<<endl;
        }
        Read.close();
        temp.close();
        remove("Loan.txt");
        rename("Temp.txt","Loan.txt");
        if(found)
        {
            ifstream accIn("Account.txt");
            ofstream accTemp("AccTemp.txt");
            int t;
            string n;
            char p[5];
            double b;
            while(accIn>>t)
            {
                accIn.ignore();
                getline(accIn,n);
                for(int i=0;i<4;i++)
                {
                    p[i]=accIn.get();
                }
                p[4]='\0';
                accIn.ignore();
                accIn>>b;
                accIn.ignore();
                if(t==tok)
                {
                    b+=approvedLoanAmount;
                }
                accTemp<<t<<endl;
                accTemp<<n<<endl;
                for(int i=0;i<4;i++)
                {
                    accTemp<<p[i];
                }
                accTemp<<endl;
                accTemp<<b<<endl;
            }
            accIn.close();
            accTemp.close();
            remove("Account.txt");
            rename("AccTemp.txt","Account.txt");
        }
        else
        {
            cout<<"     No pending loan found for this account..."<<endl;
        }
        cout<<"|______________________________________________________________|"<<endl;
        cout<<"|                                                              |"<<endl;
        cout<<"|**************************************************************|"<<endl;
        cout<<"|--------------------------------------------------------------|"<<endl;
        system("pause");
    }

    void Loan::ViewAllLoans()
    {
        system("cls");
        cout<<"|----------------------------------------------------|"<<endl;
        cout<<"|******************* LOAN RECORDS *******************|"<<endl;
        cout<<"|                                                    |"<<endl<<endl;        
        ifstream Read("Loan.txt");
        if(!Read)
        {
            cout<<"      No Loan data File found"<<endl;
            return;
        }
        int n=1;
        while(Read>>borrowerToken>>loanAmount>>remainingAmount>>status)
        {
            cout<<n<<"- Token: "<<borrowerToken<<endl;
            cout<<"   Total Amount: "<<loanAmount<<endl;
            cout<<"   Remaining Amount: "<<remainingAmount<<endl;
            cout<<"   Status: "<<status<<endl<<endl;
            n++;
        }
        Read.close();
        cout<<"|____________________________________________________|"<<endl;
        cout<<"|                                                    |"<<endl;
        cout<<"|****************************************************|"<<endl;
        cout<<"|----------------------------------------------------|"<<endl<<endl;
        system("pause");
    }

    void Loan::DeleteLoanInformation()
    {
        int find;
        system("cls");
        cout<<"|--------------------------------------------------------------|"<<endl;
        cout<<"|******************* DELETE PAID LOAN RECORD ******************|"<<endl;
        cout<<"|                                                              |"<<endl<<endl; 
        ifstream Read("Loan.txt");
        if(!Read)
        {
            cout<<"      No Loan data File found"<<endl;
            return;
        }
        int n=1;
        bool anyPaid=false;
        while(Read>>borrowerToken>>loanAmount>>remainingAmount>>status)
        {
            if(status=="paid")
            {
                cout<<n<<"- Token: "<<borrowerToken<<endl;
                cout<<"   Total Amount: "<<loanAmount<<endl;
                cout<<"   Remaining Amount: "<<remainingAmount<<endl;
                cout<<"   Status: "<<status<<endl<<endl;
                anyPaid=true;
                n++;
            }
        }
        Read.close();
        if(!anyPaid)
        {
            cout<<"    No paid Loans found."<<endl;
            system("pause");
            return;
        }
        do
        {
            cout<<"    Enter the token number to delete details: ";
            cin>>find;
            if(find<0)
            cout<<"    Invalid Input..."<<endl;
        }
        while(find<0);
        ifstream Infile("Loan.txt");
        ofstream temp("Temp.txt");
        bool deleted=false;
        while(Infile>>borrowerToken>>loanAmount>>remainingAmount>>status)
        {
            if(borrowerToken==find && status=="paid")
            {
                deleted=true;
                continue;
            }
            else
            {
                temp<<borrowerToken<<endl;
                temp<<loanAmount<<endl;
                temp<<remainingAmount<<endl;
                temp<<status<<endl;
            }
        } 
        Infile.close();
        temp.close();
        remove("Loan.txt");
        rename("Temp.txt","Loan.txt");
        if(deleted)
        cout<<"    The loan details of the selected account has been successfully deleted."<<endl<<endl;    
        else
        cout<<"    No paid loan token match found."<<endl;
        cout<<"|______________________________________________________________|"<<endl;
        cout<<"|                                                              |"<<endl;
        cout<<"|**************************************************************|"<<endl;
        cout<<"|--------------------------------------------------------------|"<<endl;
        system("pause");
    }