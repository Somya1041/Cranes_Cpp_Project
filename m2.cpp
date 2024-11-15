#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Structures to represent data entities
struct Customer {
    int userID;
    string customerID;
    string name;
    string type;
    string address;
    string city;
    string state;
    string country;
    string pinCode;
    string phoneNumber;
    string email;
    string pan;
    double balance;
};

struct Transaction {
    int transID;
    string type; // "Credit" or "Debit"
    int accountIDSrc;
    int accountIDDst;
    double amount;
};

// Global data structures
unordered_map<int, Customer> customers;
vector<Transaction> transactions;
int nextUserID = 1;
int nextTransID = 1;

// Function prototypes
void displayMenu();
void addCustomer();
void deleteCustomer();
void modifyCustomer();
void creditMoney();
void debitMoney();
void queryAccount();
void transferMoney();
void viewCustomerDetails();

// Utility functions
int generateUserID() {
    return nextUserID++;
}

int generateTransactionID() {
    return nextTransID++;
}

// Main function
int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                deleteCustomer();
                break;
            case 3:
                modifyCustomer();
                break;
            case 4:
                creditMoney();
                break;
            case 5:
                debitMoney();
                break;
            case 6:
                queryAccount();
                break;
            case 7:
                transferMoney();
                break;
            case 8:
                cout << "Exiting application." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}

// Function definitions
void displayMenu() {
    cout << "\n--- Core Banking System Menu ---\n";
    cout << "1. Add Customer\n";
    cout << "2. Delete Customer\n";
    cout << "3. Modify Customer Details\n";
    cout << "4. Credit Money\n";
    cout << "5. Debit Money\n";
    cout << "6. Query Account and Transactions\n";
    cout << "7. Transfer Money\n";
    cout << "8. Quit\n";
    cout << "Enter your choice: ";
}

void addCustomer() {
    Customer customer;
    customer.userID = generateUserID();

    cout << "Enter Customer ID: ";
    cin >> customer.customerID;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, customer.name);
    cout << "Enter Customer Type: ";
    cin >> customer.type;
    cout << "Enter Address: ";
    cin.ignore();
    getline(cin, customer.address);
    cout << "Enter City: ";
    cin >> customer.city;
    cout << "Enter State: ";
    cin >> customer.state;
    cout << "Enter Country: ";
    cin >> customer.country;
    cout << "Enter Pin Code: ";
    cin >> customer.pinCode;
    cout << "Enter Phone Number: ";
    cin >> customer.phoneNumber;
    cout << "Enter Email: ";
    cin >> customer.email;
    cout << "Enter PAN: ";
    cin >> customer.pan;
    cout << "Enter Initial Balance: ";
    cin >> customer.balance;

    customers[customer.userID] = customer;
    cout << "Customer added successfully with User ID: " << customer.userID << endl;
}

void deleteCustomer() {
    int userID;
    cout << "Enter User ID to delete: ";
    cin >> userID;

    if (customers.erase(userID)) {
        cout << "Customer deleted successfully." << endl;
    } else {
        cout << "Customer not found!" << endl;
    }
}

// Implement similar functions for modifying customer details, crediting, debiting, querying, and transferring money.