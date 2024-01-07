#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <chrono>
#include <thread>
#include <fstream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;
struct InfoPersonal
{
    string IDPersonal;
    string name;
    string dateOfBirth;
};
struct AccountInfo
{
    string numberAccount;
    string pinCode;
    int balance;
};
void Continue()
{
    cout << "Do you want to process another function Y/N ?" << endl;
    char kitu;
    cin >> kitu;
    if (kitu == 'Y')
    {
    }
    else
    {
        cout << "=============Thank for using my service=============" << endl;
        exit(0);
    }
}
void Loading(string s)
{
    cout << s;
    cout.flush();
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            cout.flush();
            // Sử dụng std::this_thread::sleep_for để thay thế _sleep
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        cout << "\b\b\b   \b\b\b";
    }
    cout << " successful..." << endl;
}
std::string gen_random(const int len)
{
    static const char alphanum[] = "0123456789";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
    {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

class PersonalAccount
{
private:
    struct InfoPersonal infoPersonal;
    struct AccountInfo accountInfo;

public:
    PersonalAccount()
    {
        accountInfo.balance = 0;
    }
    string getName()
    {
        return infoPersonal.name;
    }
    void setName(string _name)
    {
        infoPersonal.name = _name;
    }
    string getIDPersonal()
    {
        return infoPersonal.IDPersonal;
    }
    void setIDPersonal(string _IDPersonal)
    {
        infoPersonal.IDPersonal = _IDPersonal;
    }
    string getDOB()
    {
        return infoPersonal.dateOfBirth;
    }
    void setDOB(string _DOB)
    {
        infoPersonal.dateOfBirth = _DOB;
    }
    string getPinCode()
    {
        return accountInfo.pinCode;
    }
    void setPinCode(string _pinCode)
    {
        accountInfo.pinCode = _pinCode;
    }
    string getNumAccount()
    {
        return accountInfo.numberAccount;
    }
    void setNumAccount(string _numAccount)
    {
        accountInfo.numberAccount = _numAccount;
    }
    int getBalance()
    {
        return accountInfo.balance;
    }
    void setBalance(int _balance)
    {
        accountInfo.balance = _balance;
    }
};
class BankManagement
{
private:
    static std::vector<PersonalAccount> userInfor;

public:
    BankManagement()
    {
    }
    ~BankManagement() = default;
    static void CreateAccountBank(PersonalAccount &personalAccount)
    {
        cin.ignore();
        string name;
        cout << "Type Name:";
        getline(cin, name);
        // std::istream::getline()
        personalAccount.setName(name);
        string IDPersonal;
        cout << "Type ID Personal:";
        getline(cin, IDPersonal);
        personalAccount.setIDPersonal(IDPersonal);
        string dob;
        cout << "Type Date Of Birth:";
        getline(cin, dob);
        personalAccount.setDOB(dob);
        // personalAccount.setBalance(0);
        personalAccount.setPinCode((gen_random(6)));
        personalAccount.setNumAccount((gen_random(12)));
        Loading("Creating account");
        cout << personalAccount.getNumAccount() << " " << personalAccount.getPinCode() << endl;
        userInfor.push_back(personalAccount);
    }
    static void Deposite()
    {
        cout << "=============Welcome to my service=============" << endl;
        cout << "Please to type the number money you want to deposite to your account: ";
        int numDeposite;
        cin >> numDeposite;
        cin.ignore();
        string numAccount;
        cout << "Please type the your number account: ";
        getline(cin, numAccount);
        for (int i = 0; i < userInfor.size(); i++)
        {
            if (numAccount == userInfor[i].getNumAccount())
            {
                int nowMoney = userInfor[i].getBalance();
                nowMoney += numDeposite;
                userInfor[i].setBalance(nowMoney);
                break;
            }
        }
        Loading("Depositing");
    }
    static void Withdraw()
    {
        cin.ignore();
        string numAccount;
        cout << "Please type your number account: ";
        getline(cin, numAccount);
        for (int i = 0; i < userInfor.size(); i++)
        {
            if (numAccount == userInfor[i].getNumAccount())
            {
                cout << "Please type the money you want to withdraw: ";
                int numWithDraw;
                cin >> numWithDraw;
                while (numWithDraw > userInfor[i].getBalance())
                {
                    cout << "The balance is not enough. Please type money you want to withdraw again: ";
                    cin >> numWithDraw;
                }
                cin.ignore();
                cout << "Please type your pin code: ";
                string pinCode;
                getline(cin, pinCode);
                int cnt = 0;
                while (pinCode != userInfor[i].getPinCode())
                {
                    if (cnt < 5)
                    {
                        cout << "Incorrect Pin Code. Please type again: ";
                        getline(cin, pinCode);
                    }
                    else
                    {
                        cout << "Your transaction cannot be processed" << endl;
                        exit(0);
                    }
                    cnt++;
                }
                int moneyRemain = userInfor[i].getBalance();
                moneyRemain -= numWithDraw;
                userInfor[i].setBalance(moneyRemain);
                break;
            }
        }
        Loading("Withdrawing");
    }
    static void ChangePINCode()
    {
        cin.ignore();
        string numAccount;
        cout << "Please type your number account: ";
        getline(cin, numAccount);
        for (int i = 0; i < userInfor.size(); i++)
        {
            if (numAccount == userInfor[i].getNumAccount())
            {
                cout << "Please type your old pin code: ";
                string oldPinCode;
                getline(cin, oldPinCode);
                int cnt = 0;
                while (oldPinCode != userInfor[i].getPinCode())
                {
                    if (cnt < 5)
                    {
                        cout << "Incorrect Pin Code. Please type again: ";
                        getline(cin, oldPinCode);
                    }
                    else
                    {
                        cout << "Your transaction cannot be processed" << endl;
                        exit(0);
                    }
                    cnt++;
                }
                cout << "Please type the pincode you want to change: ";
                string newPinCode;
                getline(cin, newPinCode);
                userInfor[i].setPinCode(newPinCode);
                break;
            }
        }
        Loading("Changing");
    }
    static void Transfer()
    {
        cin.ignore();
        string numAccount;
        cout << "Please type your number account: ";
        getline(cin, numAccount);
        for (int i = 0; i < userInfor.size(); i++)
        {
            if (numAccount == userInfor[i].getNumAccount())
            {
                cout << "Please type the account you want to transfer: ";
                string numAccountTransfer;
                getline(cin, numAccountTransfer);
                cout << "Please type your pin code: ";
                string pinCode;
                getline(cin, pinCode);
                int cnt = 0;
                while (pinCode != userInfor[i].getPinCode())
                {
                    if (cnt < 5)
                    {
                        cout << "Incorrect Pin Code. Please type again: ";
                        getline(cin, pinCode);
                    }
                    else
                    {
                        cout << "Your transaction cannot be processed" << endl;
                        exit(0);
                    }
                    cnt++;
                }
                for (int j = 0; j < userInfor.size(); j++)
                {
                    if (numAccountTransfer == userInfor[j].getNumAccount())
                    {
                        cout << "Please type the money you want transfer: ";
                        int moneyTransfer;
                        cin >> moneyTransfer;
                        while (moneyTransfer > userInfor[i].getBalance())
                        {
                            cout << "Sorry! Your balance is not enough to transfer!!!" << endl;
                        }
                        int newMoney = userInfor[j].getBalance();
                        newMoney += moneyTransfer;
                        userInfor[j].setBalance(newMoney);
                        int oldMoney = userInfor[i].getBalance();
                        oldMoney -= moneyTransfer;
                        userInfor[i].setBalance(oldMoney);
                        break;
                    }
                }
                break;
            }
        }
    }
    std::vector<PersonalAccount> getVector()
    {
        return userInfor;
    }
    void setVector(std::vector<PersonalAccount> _vt)
    {
        userInfor = _vt;
    }
};
std::vector<PersonalAccount> BankManagement::userInfor = {};

class HandleJson
{
private:
    BankManagement *a;

public:
    HandleJson()
    {
        a = new BankManagement();
    }
    void LoadDataFromFile(const char *fileName)
    {
        std::ifstream ifs(fileName);

        json j = json::parse(ifs);
        vector<PersonalAccount> vt;
        for (int i = 0; i < j.size(); i++)
        {
            PersonalAccount pa;
            pa.setBalance(j[i]["Balance"]);
            pa.setDOB(j[i]["DOB"]);
            pa.setIDPersonal(j[i]["IDPersonal"]);
            pa.setName(j[i]["Name"]);
            pa.setNumAccount(j[i]["NumAccount"]);
            pa.setPinCode(j[i]["PinCode"]);
            vt.push_back(pa);
        }
        a->setVector(vt);
    }
    void SaveDataToFile(const char *fileName)
    {
        json data = json::array();

        for (int i = 0; i < a->getVector().size(); i++)
        {
            json j = {
                {"Name", a->getVector()[i].getName()},
                {"IDPersonal", a->getVector()[i].getIDPersonal()},
                {"DOB", a->getVector()[i].getDOB()},
                {"NumAccount", a->getVector()[i].getNumAccount()},
                {"PinCode", a->getVector()[i].getPinCode()},
                {"Balance", a->getVector()[i].getBalance()}};
            data.push_back(j);
        }
        std::ofstream f(fileName);
        f << data;
    }
    BankManagement *getA()
    {
        return a;
    }
};
int main()
{
    cout << "===========Welcome to my bank===========" << endl;
    Loading("Data Loading");
    const char *fileName = "test.json";
    HandleJson handleJson;
    handleJson.LoadDataFromFile(fileName);
    while (1)
    {
        /* code */
        cout << endl;
        cout << "\t============Menu===========" << endl;
        cout << "\t\033[33m1. \033[0mCreate new account" << endl;
        cout << "\t\033[33m2. \033[0mDeposite" << endl;
        cout << "\t\033[33m3. \033[0mWithdraw" << endl;
        cout << "\t\033[33m4. \033[0mChange PIN code" << endl;
        cout << "\t\033[33m5. \033[0mTransfer" << endl;
        cout << "\t\033[33m6. \033[0mExit" << endl;
        cout << "\t============================" << endl;
        int choice;
        cout << endl;
        cout << "Please type your choice:";
        cin >> choice;
        if (choice == 0)
        {
        }
        else if (choice == 1)
        {
            cout << "Thank you for believing our banking. We need some your personal information. Please type carefully!!!" << endl;
            PersonalAccount a;
            BankManagement::CreateAccountBank(a);
            handleJson.SaveDataToFile(fileName);
            Continue();
        }
        else if (choice == 2)
        {
            BankManagement::Deposite();
            handleJson.SaveDataToFile(fileName);
            Continue();
        }
        else if (choice == 3)
        {
            BankManagement::Withdraw();
            handleJson.SaveDataToFile(fileName);
            Continue();
        }
        else if (choice == 4)
        {
            BankManagement::ChangePINCode();
            handleJson.SaveDataToFile(fileName);
            Continue();
        }
        else if (choice == 5)
        {
            BankManagement::Transfer();
            handleJson.SaveDataToFile(fileName);
            Continue();
        }
        else
        {
        }
    }
    return 0;
}