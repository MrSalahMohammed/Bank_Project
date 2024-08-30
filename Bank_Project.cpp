#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include "C:\Users\NEW LAP\source\repos\C++_Level2\MyLib.h"
using namespace std;

enum enChoices { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transaction = 6, Exit = 7 };
enum enTChoice { Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenu = 4 };
const string FileName = "ClientsDetails.txt";

struct stClient
{

    string AccountNumber;
    string PINCode;
    string Name;
    string Phone;
    float Balance;
    bool Delete = false;

};

string SaveClientDataAsRecord(stClient ClientData, string Seperator = "#//#") {

    string S = "";

    S = S + ClientData.AccountNumber + Seperator;
    S = S + ClientData.PINCode + Seperator;
    S = S + ClientData.Name + Seperator;
    S = S + ClientData.Phone + Seperator;
    S = S + to_string(ClientData.Balance) + Seperator;

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

stClient ConvertLineDataToRecord(string LineData, string Seperator) {

    stClient Client;

    vector <string> ClientData = SplitWordsInString(LineData, Seperator);

    Client.AccountNumber = ClientData[0];
    Client.PINCode = ClientData[1];
    Client.Name = ClientData[2];
    Client.Phone = ClientData[3];
    Client.Balance = stof(ClientData[4]);

    return Client;

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
        return enChoices::Exit;
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

bool isAccountExist(string AccountNumber, vector <stClient> vClients) {

    for (stClient &Client : vClients) {

        if (Client.AccountNumber == AccountNumber)
            return true;

    }

    return false;

}

void CheckIfAccountExist(vector <stClient> &vClients, stClient &Client) {

    while (isAccountExist(Client.AccountNumber, vClients) == true) {

        cout << "Account Number Already Exist!" << endl;
        cout << "Enter Another Account Number  : ";
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

vector <stClient> LoadClientsDataFromFile(string FileName, string Seperator = "#//#") {

    vector <stClient> vClients;
    fstream ClientsFile;

    ClientsFile.open(FileName, ios::in);

    if (ClientsFile.is_open()) {

        stClient Client;
        string Line;
        while (getline(ClientsFile, Line)) {

            Client = ConvertLineDataToRecord(Line, Seperator);
            vClients.push_back(Client);
        }

        ClientsFile.close();

    }

    return vClients;

}

void MarkAccountAsDelete(stClient& Client) {

    Client.Delete = true;

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

void GoBackToMainMenu(vector <stClient>& vClients);
void GoBackToTransMenu(vector <stClient>& vClients);

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

void ApplyTChoice(enTChoice Choice, vector <stClient>& vClients) {

    switch (Choice)
    {
    case Deposit:
        ResetScreen();
        Deposits(vClients);
        GoBackToTransMenu(vClients);
        break;
    case Withdraw:
        ResetScreen();
        Withdraws(vClients);
        GoBackToTransMenu(vClients);
        break;
    case TotalBalances:
        ResetScreen();
        ShowTotalBalances(vClients);
        GoBackToTransMenu(vClients);
        break;
    case MainMenu:
        GoBackToMainMenu(vClients);
        break;
    default:
        break;
    }

}

void TransactionMenu(vector <stClient>& vClients) {

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

    ApplyTChoice((enTChoice)choice, vClients);

}

void GoBackToTransMenu(vector <stClient>& vClients) {

    cout << "\n\nPress Any Key To go back to Transaction menu...";
    system("pause>0");
    TransactionMenu(vClients);

}

void ApplyChoices(enChoices Choice, vector <stClient>& vClients) {

    switch (Choice)
    {
    case Show:
        ShowAllClients(vClients);
        GoBackToMainMenu(vClients);
        break;
    case Add:
        AddNewClient(vClients);
        GoBackToMainMenu(vClients);
        break;
    case Delete:
        DeleteClient(vClients);
        GoBackToMainMenu(vClients);
        break;
    case Update:
        UpdateClients(vClients);
        GoBackToMainMenu(vClients);
        break;
    case Find:
        FindClient(vClients);
        GoBackToMainMenu(vClients);
        break;
    case Transaction:
        TransactionMenu(vClients);
        break;
    case Exit:
        break;
    default:
        cout << "Invalid Choice!";
        break;
    }

}

void ShowMenueScreen(vector <stClient>& vClients) {

    ResetScreen();

    int Choice;

    cout << "==================================================" << endl;
    cout << "                     Main Menu                    " << endl;
    cout << "==================================================" << endl;
    cout << "              [1] Show Clients List.              " << endl;
    cout << "              [2] Add New Client.                 " << endl;
    cout << "              [3] Delete Client.                  " << endl;
    cout << "              [4] Update Client Info.             " << endl;
    cout << "              [5] Find Client                     " << endl;
    cout << "              [6] Transaction                     " << endl;
    cout << "              [7] Exit                            " << endl;
    cout << "==================================================" << endl;
    cout << "Choose What do you Want to do [1 to 7]? ";
    cin >> Choice;

    enChoices ClientChoice = MakeChoices(Choice);

    ApplyChoices(ClientChoice, vClients);

}

void GoBackToMainMenu(vector <stClient>& vClients) {

    cout << "\n\nPress Any Key To go back to main menu...";
    system("pause>0");
    ShowMenueScreen(vClients);

}

void StartSystem() {

    vector <stClient> vClients = LoadClientsDataFromFile(FileName);

    ShowMenueScreen(vClients);

    

}

int main()
{
    
    StartSystem();
    system("pause>0");

    return 0;
}
