// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

// Forward declarations
class User;
class Customer;
class Account;
class Transaction;
class BankingSystem;

// Utility functions
string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

// Class definitions
class User {
protected:
    int userID;
    string customerID;
    string password;
    char userType;
    int loginStatus;

public:
    User(int id, string custID, string pwd, char type)
        : userID(id), customerID(custID), password(pwd), userType(type), loginStatus(0) {}

    bool authenticate(const string& inputPassword) {
        return password == inputPassword && loginStatus == 0;
    }

    void login() { loginStatus = 1; }
    void logout() { loginStatus = 0; }
    
    char getUserType() const { return userType; }
    string getCustomerID() const { return customerID; }
    int getUserID() const { return userID; }
};

class Customer {
private:
    string customerID;
    string name;
    string type;
    string address1;
    string address2;
    string address3;
    string city;
    string state;
    string country;
    string pinCode;
    string phoneNumber;
    string email;
    string pan;

public:
    Customer(string id, string n, string t)
        : customerID(id), name(n), type(t) {}

    void setAddress(string a1, string a2, string a3, string c, string s, string country, string pin) {
        address1 = a1;
        address2 = a2;
        address3 = a3;
        city = c;
        state = s;
        this->country = country;
        pinCode = pin;
    }

    void setContactInfo(string phone, string mail, string p) {
        phoneNumber = phone;
        email = mail;
        pan = p;
    }

    string getCustomerID() const { return customerID; }
    string getName() const { return name; }
    
    void displayDetails() const {
        cout << "\nCustomer Details:" << endl;
        cout << "ID: " << customerID << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Address: " << address1 << ", " << city << ", " << state << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
    }
};

class Account {
private:
    int accountNumber;
    string type;
    string customerID;
    string status;
    double balance;
    string openingDate;

public:
    Account(int accNum, string t, string custID)
        : accountNumber(accNum), type(t), customerID(custID), 
          status("Enabled"), balance(0.0), openingDate(getCurrentDateTime()) {}

    bool credit(double amount) {
        if (amount > 0 && status == "Enabled") {
            balance += amount;
            return true;
        }
        return false;
    }

    bool debit(double amount) {
        if (amount > 0 && status == "Enabled" && balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    string getCustomerID() const { return customerID; }
    string getStatus() const { return status; }
    
    void displayDetails() const {
        cout << "\nAccount Details:" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Type: " << type << endl;
        cout << "Status: " << status << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "Opening Date: " << openingDate << endl;
    }
};

class Transaction {
private:
    int transID;
    char type;
    int accountIDSrc;
    int accountIDDst;
    double amount;
    string datetime;

public:
    Transaction(int id, char t, int src, int dst, double amt)
        : transID(id), type(t), accountIDSrc(src), accountIDDst(dst),
          amount(amt), datetime(getCurrentDateTime()) {}

    void displayDetails() const {
        cout << "\nTransaction Details:" << endl;
        cout << "ID: " << transID << endl;
        cout << "Type: " << type << endl;
        cout << "Source Account: " << accountIDSrc << endl;
        if (accountIDDst != -1) {
            cout << "Destination Account: " << accountIDDst << endl;
        }
        cout << "Amount: $" << fixed << setprecision(2) << amount << endl;
        cout << "DateTime: " << datetime << endl;
    }
};

class BankingSystem {
private:
    vector<User> users;
    vector<Customer> customers;
    vector<Account> accounts;
    vector<Transaction> transactions;
    int currentUserID;
    int nextUserID;
    int nextAccountNumber;
    int nextTransactionID;

public:
    BankingSystem() : currentUserID(-1), nextUserID(1), nextAccountNumber(1000), nextTransactionID(1) {
        // Add default bank clerk
        addUser("CLERK001", "admin123", 'A');
    }

    bool login(string customerID, string password) {
        for (size_t i = 0; i < users.size(); i++) {
            if (users[i].getCustomerID() == customerID && users[i].authenticate(password)) {
                users[i].login();
                currentUserID = users[i].getUserID();
                return true;
            }
        }
        return false;
    }

    void logout() {
        if (currentUserID != -1) {
            for (auto& user : users) {
                if (user.getUserID() == currentUserID) {
                    user.logout();
                    break;
                }
            }
            currentUserID = -1;
        }
    }

    bool addUser(string customerID, string password, char userType) {
        users.emplace_back(nextUserID++, customerID, password, userType);
        return true;
    }

    bool addCustomer(string name, string type, string address1, string city, string state,
                    string phone, string email, string pan) {
        string customerID = "CUST" + to_string(nextUserID);
        
        // Add customer user
        addUser(customerID, "default123", 'U');
        
        // Add customer details
        customers.emplace_back(customerID, name, type);
        Customer& cust = customers.back();
        cust.setAddress(address1, "", "", city, state, "Country", "");
        cust.setContactInfo(phone, email, pan);
        
        // Create default savings account
        accounts.emplace_back(nextAccountNumber++, "Savings", customerID);
        
        return true;
    }

    bool createTransaction(char type, int sourceAcc, int destAcc, double amount) {
        Account* srcAccount = nullptr;
        Account* dstAccount = nullptr;

        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == sourceAcc) srcAccount = &acc;
            if (acc.getAccountNumber() == destAcc) dstAccount = &acc;
        }

        if (!srcAccount || (destAcc != -1 && !dstAccount)) return false;

        bool success = false;
        if (type == 'D') {
            success = srcAccount->debit(amount);
        } else if (type == 'C') {
            success = srcAccount->credit(amount);
        } else if (type == 'T' && dstAccount) {
            if (srcAccount->debit(amount)) {
                success = dstAccount->credit(amount);
                if (!success) srcAccount->credit(amount); // Rollback if destination credit fails
            }
        }

        if (success) {
            transactions.emplace_back(nextTransactionID++, type, sourceAcc, destAcc, amount);
            return true;
        }
        return false;
    }

    void displayCustomerDetails(string customerID) {
        for (const auto& customer : customers) {
            if (customer.getCustomerID() == customerID) {
                customer.displayDetails();
                for (const auto& account : accounts) {
                    if (account.getCustomerID() == customerID) {
                        account.displayDetails();
                    }
                }
                return;
            }
        }
        cout << "Customer not found." << endl;
    }

    void displayTransactions(int accountNumber) {
        cout << "\nTransaction History for Account " << accountNumber << ":" << endl;
        for (const auto& trans : transactions) {
            trans.displayDetails();
        }
    }

    // Main menu functions
    void displayClerkMenu() {
        while (true) {
            cout << "\nBank Clerk Menu:" << endl;
            cout << "1. Add Customer" << endl;
            cout << "2. View Customer Details" << endl;
            cout << "3. Credit Money" << endl;
            cout << "4. Debit Money" << endl;
            cout << "5. View Transactions" << endl;
            cout << "6. Logout" << endl;
            
            int choice;
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string name, type, address, city, state, phone, email, pan;
                    cout << "Enter customer name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter customer type (Individual/Corporate): ";
                    getline(cin, type);
                    cout << "Enter address: ";
                    getline(cin, address);
                    cout << "Enter city: ";
                    getline(cin, city);
                    cout << "Enter state: ";
                    getline(cin, state);
                    cout << "Enter phone: ";
                    getline(cin, phone);
                    cout << "Enter email: ";
                    getline(cin, email);
                    cout << "Enter PAN: ";
                    getline(cin, pan);

                    if (addCustomer(name, type, address, city, state, phone, email, pan)) {
                        cout << "Customer added successfully!" << endl;
                    }
                    break;
                }
                case 2: {
                    string customerID;
                    cout << "Enter customer ID: ";
                    cin >> customerID;
                    displayCustomerDetails(customerID);
                    break;
                }
                case 3: {
                    int accountNum;
                    double amount;
                    cout << "Enter account number: ";
                    cin >> accountNum;
                    cout << "Enter amount to credit: ";
                    cin >> amount;
                    if (createTransaction('C', accountNum, -1, amount)) {
                        cout << "Amount credited successfully!" << endl;
                    }
                    break;
                }
                case 4: {
                    int accountNum;
                    double amount;
                    cout << "Enter account number: ";
                    cin >> accountNum;
                    cout << "Enter amount to debit: ";
                    cin >> amount;
                    if (createTransaction('D', accountNum, -1, amount)) {
                        cout << "Amount debited successfully!" << endl;
                    }
                    break;
                }
                case 5: {
                    int accountNum;
                    cout << "Enter account number: ";
                    cin >> accountNum;
                    displayTransactions(accountNum);
                    break;
                }
                case 6:
                    logout();
                    return;
                default:
                    cout << "Invalid choice!" << endl;
            }
        }
    }

    void displayCustomerMenu(string customerID) {
        while (true) {
            cout << "\nCustomer Menu:" << endl;
            cout << "1. View Details" << endl;
            cout << "2. Transfer Money" << endl;
            cout << "3. View Transactions" << endl;
            cout << "4. Logout" << endl;
            
            int choice;
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayCustomerDetails(customerID);
                    break;
                case 2: {
                    int sourceAcc, destAcc;
                    double amount;
                    cout << "Enter source account number: ";
                    cin >> sourceAcc;
                    cout << "Enter destination account number: ";
                    cin >> destAcc;
                    cout << "Enter amount to transfer: ";
                    cin >> amount;
                    if (createTransaction('T', sourceAcc, destAcc, amount)) {
                        cout << "Transfer successful!" << endl;
                    }
                    break;
                }
                case 3: {
                    int accountNum;
                    cout << "Enter account number: ";
                    cin >> accountNum;
                    displayTransactions(accountNum);
                    break;
                }
                case 4:
                    logout();
                    return;
                default:
                    cout << "Invalid choice!" << endl;
            }
        }
    }
};

int main() {
    BankingSystem bank;
    string customerID, password;

    while (true) {
        cout << "\nWelcome to Core Banking System" << endl;
        cout << "Enter Customer ID: ";
        cin >> customerID;
        cout << "Enter Password: ";
        cin >> password;

        if (bank.login(customerID, password)) {
            if (customerID == "CRK1") {
                bank.displayClerkMenu();
            } else {
                bank.displayCustomerMenu(customerID);
            }
        } else {
            cout << "Invalid credentials!" << endl;
        }
    }

    return 0;
}