#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include "C:\Users\NEW LAP\source\repos\C++_Level2\MyLib.h"
using namespace std;

enum enChoices { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transaction = 6, ManageUsers = 7, Logout = 8 };
enum enUserChoices { ShowUser = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, MainMenue = 6 };
enum enTChoice { Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenu = 4 };
enum enAccess { GiveAccess = 0, Denied = 1 };
enum enPermission { eAll = -1, pShow = 1, pAdd = 2, pDelete = 4, pUpdate = 8, pFind = 16, pTransaction = 32, pManageUsers = 64 };
const string FileName = "ClientsDetails.txt";
const string UsersFileName = "UsersDetails.txt";

void Login();


struct stClient
{

    string AccountNumber;
    string PINCode;
    string Name;
    string Phone;
    float Balance;
    bool Delete = false;

};

struct Accesses {

    enPermission ShowClientsList;
    enPermission AddNewClient;
    enPermission DeleteClient;
    enPermission UpdateClient;
    enPermission FindClient;
    enPermission Transaction;
    enPermission ManageUsers;

};

struct stUser {

    string Name;
    string Password;
    int Access;
    Accesses UserAccess;
    bool Delete = false;

};

void StartSystem(stUser User, vector <stUser>& vUser);
void ManageUser(stUser& User, vector <stUser>& vUser);

void GiveFullAccess(stUser& User) {

    User.UserAccess.AddNewClient = enPermission::eAll;

}

void GiveAccessToUser(stUser& User) {

    char Access;
    cout << "Do you want to give access to \n" << endl;
    cout << "Show Client List? (Y/N)? ";
    cin >> Access;
    if (Access == 'Y' || Access == 'y') {

        User.UserAccess.ShowClientsList = enPermission::pShow;

    }

    cout << "Add New Client? (Y/N)? ";
    cin >> Access;
    if (Access == 'Y' || Access == 'y') {

        User.UserAccess.AddNewClient = enPermission::pAdd;

    }

    cout << "Delete Client? (Y/N)? ";
    cin >> Access;
    if (Access == 'Y' || Access == 'y') {

        User.UserAccess.DeleteClient = enPermission::pDelete;

    }

    cout << "Update Client? (Y/N)? ";
    cin >> Access;
    if (Access == 'Y' || Access == 'y') {

        User.UserAccess.UpdateClient = enPermission::pUpdate;

    }

    cout << "Find Client? (Y/N)? ";
    cin >> Access;
    if (Access == 'Y' || Access == 'y') {

        User.UserAccess.FindClient = enPermission::pFind;

    }

    cout << "Transaction? (Y/N)? ";
    cin >> Access;
    if (Access == 'Y' || Access == 'y') {

        User.UserAccess.Transaction = enPermission::pTransaction;

    }

    cout << "Manage Users? (Y/N)? ";
    cin >> Access;
    if (Access == 'Y' || Access == 'y') {

        User.UserAccess.ManageUsers = enPermission::pManageUsers;

    }

}

void GetUserAccess(stUser& User) {

    int Access = 0;

    if (User.UserAccess.ShowClientsList == enPermission::pShow)
        Access += User.UserAccess.ShowClientsList;

    if (User.UserAccess.AddNewClient == enPermission::pAdd)
        Access += User.UserAccess.AddNewClient;

    if (User.UserAccess.DeleteClient == enPermission::pDelete)
        Access += User.UserAccess.DeleteClient;

    if (User.UserAccess.UpdateClient == enPermission::pUpdate)
        Access += User.UserAccess.UpdateClient;

    if (User.UserAccess.FindClient == enPermission::pFind)
        Access += User.UserAccess.FindClient;

    if (User.UserAccess.Transaction == enPermission::pTransaction)
        Access += User.UserAccess.Transaction;

    if (User.UserAccess.ManageUsers == enPermission::pManageUsers)
        Access += User.UserAccess.ManageUsers;

    User.Access = Access;

}

void ReadUserAccess(stUser &User) {

    char FullAccess;
    cout << "Do you want to give FULL Access? (Y/N)? ";
    cin >> FullAccess;
    if (FullAccess == 'Y' || FullAccess == 'y') {

        GiveFullAccess(User);
        User.Access = -1;

    }
    else {

        GiveAccessToUser(User);
        GetUserAccess(User);

    }

}

string SaveClientDataAsRecord(stClient ClientData, string Seperator = "#//#") {

    string S = "";

    S = S + ClientData.AccountNumber + Seperator;
    S = S + ClientData.PINCode + Seperator;
    S = S + ClientData.Name + Seperator;
    S = S + ClientData.Phone + Seperator;
    S = S + to_string(ClientData.Balance) + Seperator;

    return S.substr(0, S.length() - Seperator.length());

}

string SaveUserDataAsRecord(stUser UserData, string Seperator = "#//#") {

    string S = "";

    S = S + UserData.Name + Seperator;
    S = S + UserData.Password + Seperator;
    S = S + to_string(UserData.Access) + Seperator;

    return S.substr(0, S.length() - Seperator.length());

}

vector <string> SplitWordsInString(string S, string Delim) {

    vector <string> vString;

    short pos = 0;
    string sWord;

    while ((pos = S.find(Delim)) != string::npos)
    {

        sWord = S.substr(0, pos);
        if (sWord != "") {

            vString.push_back(sWord);

        }

        S.erase(0, pos + Delim.length());

    }

    if (S != "") {

        vString.push_back(S);

    }

    return vString;

}

stClient ConvertClientLineDataToRecord(string LineData, string Seperator) {

    stClient Client;

    vector <string> ClientData = SplitWordsInString(LineData, Seperator);

    Client.AccountNumber = ClientData[0];
    Client.PINCode = ClientData[1];
    Client.Name = ClientData[2];
    Client.Phone = ClientData[3];
    Client.Balance = stof(ClientData[4]);

    return Client;

}

stUser ConvertUserLineDataToRecord(string LineData, string Seperator) {

    stUser User;

    vector <string> vUserData = SplitWordsInString(LineData, Seperator);

    User.Name = vUserData[0];
    User.Password = vUserData[1];
    User.Access = stoi(vUserData[2]);

    return User;

}

enChoices MakeChoices(int Choice) {

    switch (Choice)
    {
    case 1:
        return enChoices::Show;
        break;
    case 2:
        return enChoices::Add;
        break;
    case 3:
        return enChoices::Delete;
        break;
    case 4:
        return enChoices::Update;
        break;
    case 5:
        return enChoices::Find;
        break;
    case 6:
        return enChoices::Transaction;
        break;
    case 7:
        return enChoices::ManageUsers;
        break;
    case 8:
        return enChoices::Logout;
        break;
    default:
        cout << "Invalid Choice!";
        break;
    }

}

void ResetScreen() {

    system("cls");

}

void PrintClientRecord(stClient Client) {

    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PINCode;
    cout << "| " << left << setw(20) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.Balance;

}

void PrintUserRecord(stUser User) {

    cout << "| " << left << setw(20) << User.Name;
    cout << "| " << left << setw(12) << User.Password;
    cout << "| " << left << setw(8) << User.Access;

}

void ShowAllClients(vector <stClient> vClients) {

    ResetScreen();

    cout << "\t\t\t\tClient List (" << vClients.size() << ") Clients(s)" << endl;

    cout << "___________________________________________________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(20) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n___________________________________________________________________________________\n" << endl;

    for (stClient Client : vClients) {

        PrintClientRecord(Client);
        cout << endl;

    }

    cout << "___________________________________________________________________________________\n" << endl;

}

void ShowAllUsers(vector <stUser> vUser) {

    ResetScreen();

    cout << "\t\t\t\tUsers List (" << vUser.size() << ") Clients(s)" << endl;

    cout << "_______________________________________________________\n" << endl;
    cout << "| " << left << setw(20) << "User Name";
    cout << "| " << left << setw(12) << "Password";
    cout << "| " << left << setw(8) << "Access";
    cout << "\n_______________________________________________________\n" << endl;

    for (stUser &User : vUser) {

        PrintUserRecord(User);
        cout << endl;

    }

    cout << "___________________________________________________________________________________\n" << endl;

}

bool isAccountExist(string AccountNumber, vector <stClient> vClients) {

    for (stClient &Client : vClients) {

        if (Client.AccountNumber == AccountNumber)
            return true;

    }

    return false;

}

bool isUserExist(string UserName, vector <stUser> vUsers) {

    for (stUser &User : vUsers) {

        if (User.Name == UserName)
            return true;

    }

    return false;

}

void CheckIfUserExist(vector <stUser> &vUser, stUser &User) {

    while (isUserExist(User.Name, vUser)) {

        cout << "User Name Already Exist!" << endl;
        cout << "Enter Another User Name  : ";
        getline(cin >> ws, User.Name);

    }

}

void CheckIfUserNotExist(vector <stUser>& vUser, stUser& User) {

    while (!isUserExist(User.Name, vUser)) {

        cout << "User Name Not Exist!" << endl;
        cout << "Enter Another User Name  : ";
        getline(cin >> ws, User.Name);

    }

}

void CheckIfAccountExist(vector <stClient>& vClients, stClient &Client) {

    while (isAccountExist(Client.AccountNumber, vClients) == true) {

        cout << "User Name Already Exist!" << endl;
        cout << "Enter Another User Name  : ";
        getline(cin >> ws, Client.AccountNumber);

    }

}


void AddClient(stClient &Client, vector <stClient> &vClients) {

    cout << "--------------------------------------" << endl;
    cout << "            Add New Clients           " << endl;
    cout << "--------------------------------------" << endl;
    cout << "Adding New Client:                  \n" << endl;
    cout << "Enter Account Number  : ";
    getline(cin >> ws, Client.AccountNumber);
    CheckIfAccountExist(vClients, Client);
    cout << "Enter PIN Code        : ";
    getline(cin, Client.PINCode);
    cout << "Enter Name            : ";
    getline(cin, Client.Name);
    cout << "Enter Phone Number    : ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance : ";
    cin >> Client.Balance;

    cout << endl;

}

void AddRecordToFile(string FileName, string record) {

    fstream ClientsFile;

    ClientsFile.open(FileName, ios::out | ios::app);

    if (ClientsFile.is_open()) {

        ClientsFile << record << endl;

    }

    ClientsFile.close();

}

void AddNewClient(vector <stClient> &vClients) {

    ResetScreen();

    char AddMore = 'Y';

    do
    {
        stClient Client;
        AddClient(Client, vClients);
        vClients.push_back(Client);

        string Record = SaveClientDataAsRecord(Client);
        AddRecordToFile(FileName, Record);

        cout << "Client Added Successfully!" << endl;
        cout << "Do you Want to add more clients? (Y/N)? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');


}

void AddUsers(stUser& User, vector <stUser>& vUser) {

    cout << "--------------------------------------" << endl;
    cout << "            Add New User              " << endl;
    cout << "--------------------------------------" << endl;
    cout << "Adding New Usewr:                   \n" << endl;
    cout << "Enter User Name  : ";
    getline(cin >> ws, User.Name);
    CheckIfUserExist(vUser, User);
    cout << "Enter Password        : ";
    getline(cin, User.Password);
    cout << "Enter Premission Type : ";
    ReadUserAccess(User);

    cout << endl;

}


void AddNewUser(vector <stUser>& vUser) {

    ResetScreen();

    char AddMore = 'Y';

    do
    {
        stUser User;
        AddUsers(User, vUser);
        vUser.push_back(User);

        string Record = SaveUserDataAsRecord(User);
        AddRecordToFile(UsersFileName, Record);

        cout << "User Added Successfully!" << endl;
        cout << "Do you Want to add more clients? (Y/N)? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');


}

vector <stClient> LoadClientsDataFromFile(string FileName, string Seperator = "#//#") {

    vector <stClient> vClients;
    fstream ClientsFile;

    ClientsFile.open(FileName, ios::in);

    if (ClientsFile.is_open()) {

        stClient Client;
        string Line;
        while (getline(ClientsFile, Line)) {

            Client = ConvertClientLineDataToRecord(Line, Seperator);
            vClients.push_back(Client);
        }

        ClientsFile.close();

    }

    return vClients;

}

bool CheckAccessPermission(stUser User, enPermission Permission) {

    if (User.Access == enPermission::eAll) {
        return true;
    }

    if ((Permission & User.Access) == Permission) {

        return true;

    }
    else {
        return false;
    }

}


vector <stUser> LoadUsersDataFromFile(string FileName, string Seperator = "#//#") {

    vector <stUser> vUser;
    fstream UsersFile;

    UsersFile.open(FileName, ios::in);

    if (UsersFile.is_open()) {

        stUser User;
        string Line;
        while (getline(UsersFile, Line)) {

            User = ConvertUserLineDataToRecord(Line, Seperator);
            
            vUser.push_back(User);
        }

        UsersFile.close();

    }

    return vUser;

}

void MarkAccountAsDelete(stClient& Client) {

    Client.Delete = true;

}

void MarkUserAsDelete(stUser &User) {

    User.Delete = true;

}

vector <stClient> SaveClientsDataToFile(vector <stClient> vClients, string FileName) {

    fstream ClientsFile;

    ClientsFile.open(FileName, ios::out);

    string DataLine;

    if (ClientsFile.is_open()) {

        for (stClient& Client : vClients) {

            if (Client.Delete == false) {

                DataLine = SaveClientDataAsRecord(Client);
                ClientsFile << DataLine << endl;

            }

        }

        ClientsFile.close();

    }

    return vClients;

}

vector <stUser> SaveUsersDataToFile(vector <stUser> vUser, string FileName) {

    fstream UsersFile;

    UsersFile.open(FileName, ios::out);

    string DataLine;

    if (UsersFile.is_open()) {

        for (stUser& User : vUser) {

            if (User.Delete == false) {

                DataLine = SaveUserDataAsRecord(User);
                UsersFile << DataLine << endl;

            }

        }

        UsersFile.close();

    }

    return vUser;

}

void PrintUserData(stUser User) {

    cout << "User Name : " << User.Name << endl;
    cout << "Password  : " << User.Password << endl;
    cout << "Access    : " << User.Access << endl;

}


void PrintClientData(stClient Client) {

    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "PinCode        : " << Client.PINCode << endl;
    cout << "Name           : " << Client.Name << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Balance        : " << Client.Balance << endl;

}

void DeleteClient(vector <stClient>& vClients) {

    ResetScreen();

    string AccountNumber;
    char DeleteOrNot;

    cout << "--------------------------------------" << endl;
    cout << "            Delete Client             " << endl;
    cout << "--------------------------------------" << endl;
    cout << "\nPlease Enter Account Number: ";
    cin >> AccountNumber;

    if (isAccountExist(AccountNumber, vClients)) {

        for (stClient& Client : vClients) {

            if (AccountNumber == Client.AccountNumber) {

                cout << "\nThe following are Client details: \n\n";
                PrintClientData(Client);
                cout << "Are you sure to delete this client? (Y/N)? ";
                cin >> DeleteOrNot;
                if (toupper(DeleteOrNot) == 'Y') {

                    MarkAccountAsDelete(Client);
                    SaveClientsDataToFile(vClients, FileName);

                    vClients = LoadClientsDataFromFile(FileName);

                    cout << "\nAccount Deleted Successfully!" << endl;

                }

            }

        }


    }
    else {

        cout << "\nClient With Accout Number (" 
            << AccountNumber << ") is Not Found!" << endl;

    }

}

void DeleteUsers(vector <stUser>& vUser, stUser Users) {

    ResetScreen();

    string UserName;
    char DeleteOrNot;

    cout << "--------------------------------------" << endl;
    cout << "            Delete User               " << endl;
    cout << "--------------------------------------" << endl;
    cout << "\nPlease Enter UserName: ";
    cin >> UserName;

    if (UserName == "Admin") {

        cout << "You Cannot Delete This User" << endl;

    }else if (isUserExist(UserName, vUser)) {

        for (stUser &User : vUser) {

            if (UserName == User.Name) {

                cout << "\nThe following are User details: \n\n";
                PrintUserData(User);
                cout << "Are you sure to delete this User? (Y/N)? ";
                cin >> DeleteOrNot;
                if (toupper(DeleteOrNot) == 'Y') {

                    MarkUserAsDelete(User);
                    SaveUsersDataToFile(vUser, UsersFileName);

                    vUser = LoadUsersDataFromFile(UsersFileName);

                    cout << "\nUser Deleted Successfully!" << endl;

                }

            }

        }


    }
    else {

        cout << "\nUser With Name ("
            << UserName << ") is Not Found!" << endl;

    }

}

void UpdateClient(stClient& Client) {

    cout << "Enter Your PinCode    : ";
    getline(cin >> ws, Client.PINCode);
    cout << "Enter Your Name       : ";
    getline(cin, Client.Name);
    cout << "Enter Phone Number    : ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance : ";
    cin >> Client.Balance;

}

void UpdateClients(vector <stClient>& vClients) {

    ResetScreen();

    string AccountNumber;
    char UpdateOrNot;

    cout << "--------------------------------------" << endl;
    cout << "            Update Client             " << endl;
    cout << "--------------------------------------" << endl;
    cout << "\nPlease Enter Account Number: ";
    cin >> AccountNumber;

    if (isAccountExist(AccountNumber, vClients)) {

        for (stClient& Client : vClients) {

            if (AccountNumber == Client.AccountNumber) {

                cout << "\nThe following are Client details: \n\n";
                PrintClientData(Client);
                cout << "Are you sure to Update this client? (Y/N)? ";
                cin >> UpdateOrNot;
                if (toupper(UpdateOrNot) == 'Y') {

                    UpdateClient(Client);
                    SaveClientsDataToFile(vClients, FileName);

                    cout << "\nAccount Updated Successfully!" << endl;

                }

            }

        }


    }
    else {

        cout << "\nClient With Accout Number ("
            << AccountNumber << ") is Not Found!" << endl;

    }

}

void UserUpdate(stUser& User) {

    cout << "Enter User Password   : ";
    getline(cin >> ws, User.Password);
    cout << "Enter Premission Type : ";
    ReadUserAccess(User);

}

void UpdateUsers(vector <stUser>& vUser) {

    ResetScreen();

    string UserName;
    char UpdateOrNot;

    cout << "--------------------------------------" << endl;
    cout << "            Update User               " << endl;
    cout << "--------------------------------------" << endl;
    cout << "\nPlease Enter UserName: ";
    cin >> UserName;

    if (isUserExist(UserName, vUser)) {

        for (stUser &User : vUser) {

            if (UserName == User.Name) {

                cout << "\nThe following are User details: \n\n";
                PrintUserData(User);
                cout << "Are you sure to Update this User? (Y/N)? ";
                cin >> UpdateOrNot;
                if (toupper(UpdateOrNot) == 'Y') {

                    cout << endl;
                    UserUpdate(User);
                    cout << endl;
                    SaveUsersDataToFile(vUser, UsersFileName);

                    cout << "\nUser Updated Successfully!" << endl;

                }

            }

        }


    }
    else {

        cout << "\nUser With UserName ("
            << UserName << ") is Not Found!" << endl;

    }

}

void FindClient(vector <stClient>& vClients) {

    ResetScreen();

    string AccountNumber;


    cout << "--------------------------------------" << endl;
    cout << "              Find Client             " << endl;
    cout << "--------------------------------------" << endl;
    cout << "\nPlease Enter Account Number: ";
    cin >> AccountNumber;

    if (isAccountExist(AccountNumber, vClients)) {

        for (stClient& Client : vClients) {

            if (AccountNumber == Client.AccountNumber) {

                cout << "\nThe following are Client details: \n\n";
                PrintClientData(Client);

            }

        }


    }
    else {

        cout << "\nClient With Accout Number ("
            << AccountNumber << ") is Not Found!" << endl;

    }

}

void FindUsers(vector <stUser>& vUser) {

    ResetScreen();

    string UserName;


    cout << "--------------------------------------" << endl;
    cout << "              Find User               " << endl;
    cout << "--------------------------------------" << endl;
    cout << "\nPlease Enter UserName: ";
    cin >> UserName;

    if (isUserExist(UserName, vUser)) {

        for (stUser &User : vUser) {

            if (UserName == User.Name) {

                cout << "\nThe following are User details: \n\n";
                PrintUserData(User);

            }

        }


    }
    else {

        cout << "\nUser With UserName ("
            << UserName << ") is Not Found!" << endl;

    }

}

void GoBackToMainMenu(stUser User, vector <stUser>& vUser);
void GoBackToTransMenu(vector <stClient>& vClients, stUser User, vector <stUser>& vUser);

void DepositClient(stClient &Client) {

    float Amount = 0;
    char DepositOrNot = 'Y';
    cout << "\nEnter Deposit Amount: ";
    cin >> Amount;
    cout << "\nAre you sure to Deposit? (Y/N)? ";
    cin >> DepositOrNot;
    if (toupper(DepositOrNot) == 'Y') {

        Client.Balance += Amount;

        cout << "\nBalance Updated Successfully!" << endl;

    }

}

void Deposits(vector <stClient>& vClients) {

    string AccountNumber;

    cout << "--------------------------------------" << endl;
    cout << "              Deposit                 " << endl;
    cout << "--------------------------------------" << endl;
    cout << "\nPlease Enter Account Number: ";
    cin >> AccountNumber;

    if (isAccountExist(AccountNumber, vClients)) {

        for (stClient& Client : vClients) {

            if (AccountNumber == Client.AccountNumber) {

                cout << "\nThe following are Client details: \n\n";
                PrintClientData(Client);
                
                DepositClient(Client);
                SaveClientsDataToFile(vClients, FileName);

            }

        }


    }
    else {

        cout << "\nClient With Accout Number ("
            << AccountNumber << ") is Not Found!" << endl;

    }

}

void WithdrawClient(stClient& Client) {

    float Amount = 0;
    char DepositOrNot = 'Y';
    cout << "\nEnter Withdraw Amount: ";
    cin >> Amount;

    while (Amount > Client.Balance)
    {

        cout << "\nAmount Exceeds Balance, You can withdraw up to : " << Client.Balance;
        cout << "\nEnter Withdraw Amount: ";
        cin >> Amount;

    }

    cout << "\nAre you sure to Withdraw? (Y/N)? ";
    cin >> DepositOrNot;
    if (toupper(DepositOrNot) == 'Y') {

        Client.Balance -= Amount;

        cout << "\nBalance Updated Successfully!" << endl;

    }

}

void Withdraws(vector <stClient>& vClients) {

    string AccountNumber;

    cout << "--------------------------------------" << endl;
    cout << "              Withdraw                " << endl;
    cout << "--------------------------------------" << endl;
    cout << "\nPlease Enter Account Number: ";
    cin >> AccountNumber;

    if (isAccountExist(AccountNumber, vClients)) {

        for (stClient& Client : vClients) {

            if (AccountNumber == Client.AccountNumber) {

                cout << "\nThe following are Client details: \n\n";
                PrintClientData(Client);

                WithdrawClient(Client);
                SaveClientsDataToFile(vClients, FileName);

            }

        }


    }
    else {

        cout << "\nClient With Accout Number ("
            << AccountNumber << ") is Not Found!" << endl;

    }

}

void PrintClientTotalBalance(stClient Client) {

    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(20) << Client.Name;
    cout << "| " << left << setw(12) << Client.Balance;

}

void ShowTotalBalances(vector <stClient>& vClients) {

    cout << "\t\t\t\tClient List (" << vClients.size() << ") Clients(s)" << endl;

    cout << "____________________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(20) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n____________________________________________________\n" << endl;

    for (stClient Client : vClients) {

        PrintClientTotalBalance(Client);
        cout << endl;

    }

    cout << "___________________________________________________\n" << endl;


}

void ApplyTChoice(enTChoice Choice, vector <stClient>& vClients, stUser User, vector <stUser>& vUser) {

    switch (Choice)
    {
    case Deposit:
        ResetScreen();
        Deposits(vClients);
        GoBackToTransMenu(vClients, User, vUser);
        break;
    case Withdraw:
        ResetScreen();
        Withdraws(vClients);
        GoBackToTransMenu(vClients, User, vUser);
        break;
    case TotalBalances:
        ResetScreen();
        ShowTotalBalances(vClients);
        GoBackToTransMenu(vClients, User, vUser);
        break;
    case MainMenu:
        GoBackToMainMenu(User, vUser);
        break;
    default:
        break;
    }

}

void TransactionMenu(vector <stClient>& vClients, stUser User, vector <stUser>& vUser) {

    ResetScreen();
    int choice;

    cout << "==================================================" << endl;
    cout << "                Transaction Menu                  " << endl;
    cout << "==================================================" << endl;
    cout << "                [1] Deposit.                      " << endl;
    cout << "                [2] Withdraw.                     " << endl;
    cout << "                [3] Total Balances.               " << endl;
    cout << "                [4] Main Menu.                    " << endl;
    cout << "==================================================" << endl;
    cout << "Choose What do you Want to do [1 to 4]? ";
    cin >> choice;

    ApplyTChoice((enTChoice)choice, vClients, User, vUser);

}

void GoBackToTransMenu(vector <stClient>& vClients, stUser User, vector <stUser>& vUser) {

    cout << "\n\nPress Any Key To go back to Transaction menu...";
    system("pause>0");
    TransactionMenu(vClients, User, vUser);

}

void ShowMainMenuScreen() {

    ResetScreen();

    cout << "==================================================" << endl;
    cout << "                     Main Menu                    " << endl;
    cout << "==================================================" << endl;
    cout << "              [1] Show Clients List.              " << endl;
    cout << "              [2] Add New Client.                 " << endl;
    cout << "              [3] Delete Client.                  " << endl;
    cout << "              [4] Update Client Info.             " << endl;
    cout << "              [5] Find Client                     " << endl;
    cout << "              [6] Transaction                     " << endl;
    cout << "              [7] Manage Users                    " << endl;
    cout << "              [8] Logout                          " << endl;
    cout << "==================================================" << endl;
    cout << "Choose What do you Want to do [1 to 8]? ";
    
}

void GoBackToMainMenu(stUser User, vector <stUser>& vUser) {

    cout << "\n\nPress Any Key To go back to main menu...";
    system("pause>0");
    StartSystem(User, vUser);

}

void GoBackToManageUsersScreen(stUser& User, vector <stUser>& vUser) {

    cout << "\n\nPress Any Key To go back to Manage User Screen...";
    system("pause>0");
    ManageUser(User, vUser);

}

void CheckIfUserEnterCorrectPassword(vector <stUser> vUsers, stUser& User) {

    for (stUser& Users : vUsers) {

        if (Users.Name == User.Name) {

            while (Users.Password != User.Password) {

                cout << "Invalid Password!" << endl;
                cout << "Please Enter the CORRECT Password: " << endl;
                cin >> User.Password;

            }

        }

    }

}

stUser ReadUserInfo(vector <stUser> &vUsers) {

    stUser User;
    User.Name = Strings::ReadText("Enter UserName: ");
    CheckIfUserNotExist(vUsers, User);
    User.Password = Strings::ReadText("Enter Password: ");
    CheckIfUserEnterCorrectPassword(vUsers, User);
    for (stUser& UserA : vUsers) {

        if (User.Name == UserA.Name) {

            return UserA;

        }

    }

}

void ShowManageUsersScreen() {

    ResetScreen();

    cout << "==================================================" << endl;
    cout << "                   Manage Users                   " << endl;
    cout << "==================================================" << endl;
    cout << "              [1] Show Users List.                " << endl;
    cout << "              [2] Add New User.                   " << endl;
    cout << "              [3] Delete User.                    " << endl;
    cout << "              [4] Update User Info.               " << endl;
    cout << "              [5] Find User                       " << endl;
    cout << "              [6] Main Menu                       " << endl;
    cout << "==================================================" << endl;
    cout << "Choose What do you Want to do [1 to 6]? ";

}

enUserChoices MakeUserChoice() {

    int Choice;
    cin >> Choice;

    switch (Choice)
    {
    case 1:
        return enUserChoices::ShowUser;
    case 2:
        return enUserChoices::AddUser;
    case 3:
        return enUserChoices::DeleteUser;
    case 4:
        return enUserChoices::UpdateUser;
    case 5:
        return enUserChoices::FindUser;
    case 6:
        return enUserChoices::MainMenue;
    default:
        cout << "Invalid Choice";
        break;
    }

}

void ApplyUserChoice(enUserChoices UserChoice, stUser User, vector <stUser>& vUser) {

    switch (UserChoice)
    {
    case ShowUser:
        ShowAllUsers(vUser);
        GoBackToManageUsersScreen(User, vUser);
        break;
    case AddUser:
        AddNewUser(vUser);
        GoBackToManageUsersScreen(User, vUser);
        break;
    case DeleteUser:
        DeleteUsers(vUser, User);
        GoBackToManageUsersScreen(User, vUser);
        break;
    case UpdateUser:
        UpdateUsers(vUser);
        GoBackToManageUsersScreen(User, vUser);
        break;
    case FindUser:
        FindUsers(vUser);
        GoBackToManageUsersScreen(User, vUser);
        break;
    case MainMenue:
        StartSystem(User, vUser);
        break;
    default:
        cout << "Invalid Choice";
        break;
    }

}

void ManageUser(stUser &User, vector <stUser> &vUser) {

    ShowManageUsersScreen();
    enUserChoices UserChoice = MakeUserChoice();
    ApplyUserChoice(UserChoice, User, vUser);
    
}

enChoices GetChoice(vector <stClient> vClients) {

    int Choice;
    cin >> Choice;

    enChoices ClientChoice = MakeChoices(Choice);
    
    return ClientChoice;

}

void ShowAccessDeniedScreen() {

    ResetScreen();

    cout << "___________________________________________\n" << endl;
    cout << "Access Denied!" << endl;
    cout << "Please Contact Admin to Solve This Problem!\n" << endl;
    cout << "___________________________________________" << endl;

}

void ApplyChoices(enChoices Choice, vector <stClient>& vClients, stUser User, vector <stUser>& vUser) {

    switch (Choice)
    {
    case Show:
        if (!CheckAccessPermission(User, enPermission::pShow)) {
            ShowAccessDeniedScreen();
            GoBackToMainMenu(User, vUser);
            break;
        }
        ShowAllClients(vClients);
        GoBackToMainMenu(User, vUser);
        break;
    case Add:
        if (!CheckAccessPermission(User, enPermission::pAdd)) {
            ShowAccessDeniedScreen();
            GoBackToMainMenu(User, vUser);
            break;
        }
        AddNewClient(vClients);
        GoBackToMainMenu(User, vUser);
        break;
    case Delete:
        if (!CheckAccessPermission(User, enPermission::pDelete)) {
            ShowAccessDeniedScreen();
            GoBackToMainMenu(User, vUser);
            break;
        }
        DeleteClient(vClients);
        GoBackToMainMenu(User, vUser);
        break;
    case Update:
        if (!CheckAccessPermission(User, enPermission::pUpdate)) {
            ShowAccessDeniedScreen();
            GoBackToMainMenu(User, vUser);
            break;
        }
        UpdateClients(vClients);
        GoBackToMainMenu(User, vUser);
        break;
    case Find:
        if (!CheckAccessPermission(User, enPermission::pFind)) {
            ShowAccessDeniedScreen();
            GoBackToMainMenu(User, vUser);
            break;
        }
        FindClient(vClients);
        GoBackToMainMenu(User, vUser);
        break;
    case Transaction:
        if (!CheckAccessPermission(User, enPermission::pTransaction)) {
            ShowAccessDeniedScreen();
            GoBackToMainMenu(User, vUser);
            break;
        }
        TransactionMenu(vClients, User, vUser);
        break;
    case ManageUsers:
        if (!CheckAccessPermission(User, enPermission::pManageUsers)) {
            ShowAccessDeniedScreen();
            GoBackToMainMenu(User, vUser);
            break;
        }
        ManageUser(User, vUser);
        break;
    case Logout:
        Login();
        break;
    default:
        cout << "Invalid Choice!";
        break;
    }

}

void StartSystem(stUser User, vector <stUser>& vUser) {

    vector <stClient> vClients = LoadClientsDataFromFile(FileName);

    ShowMainMenuScreen();
    enChoices ClientChoice = GetChoice(vClients);
    ApplyChoices(ClientChoice, vClients, User, vUser);
}

void Login() {

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    ResetScreen();
    cout << "=============================================" << endl;
    cout << "                     Login                   " << endl;
    cout << "=============================================" << endl;
    stUser User = ReadUserInfo(vUsers);
    StartSystem(User, vUsers);
    
}

int main()
{
    
    Login();
    system("pause>0");

    return 0;
}
