# include <iostream>
# include <vector>
# include <string>
using namespace std;

class BankAccount{
	private:
		string name;
		int accountNum;
		double balance;
	public:
		BankAccount(string n, int ac, double bal){
			name = n;
			accountNum = ac;
			balance = bal;
		}

		string getName(){
			return name;
		}

		int getAccountNum(){
			return accountNum;
		}

		double getBalance(){
			return balance;
		}

		void deposit(double amount){
			balance = balance + amount;
		}

		void withdraw(double amount){
			if(balance >= amount){
				balance = balance - amount;
				cout << "\t\tWithdrawn Successfully!!!" << endl;
			}
			
			else{
				cout << "\t\tInsufficient Balance!!!" << endl;
			}
		}	
};

class BankManagement{
	private:
		vector<BankAccount> accounts;
	public:
		void AddAccount(string name,int accountNum,double balance){
			accounts.push_back(BankAccount(name,accountNum,balance));
		}

		void showAllAccounts(){
			cout << "\t\tAll Account Holders:- " << endl;
			for(int i = 0; i < accounts.size(); i++){
				cout << "\t\t" << i + 1 << ". Account Holder Name: " << accounts[i].getName() << " Account Number: "<< accounts[i].getAccountNum() <<
				" Balance: " << accounts[i].getBalance() << endl;
			}
		}

		void searchAccount(int account){
			cout << "\t\tAccount Holder:- " << endl;
			for(int i = 0; i < accounts.size(); i++){
				if(accounts[i].getAccountNum() == account){
				cout << "\t\t" << "Name: " << accounts[i].getName() << " Account Number: " <<accounts[i].getAccountNum() << 
				" Balance: "<< accounts[i].getBalance() << endl;	
				}
			}
		}

		BankAccount* findAccount(int accountNum){
			for(int i = 0; i < accounts.size(); i++){
				if(accounts[i].getAccountNum() == accountNum){
					return &accounts[i];
				}
			}

			return &accounts[0];
		}
};

int main(){
	BankManagement bank;
	int choice;
	char op;

	do{
		cout<<"\n\t\t::Core Banking System::\n"<<endl;
		cout<<"\t\t\tMain Menu"<<endl;
		cout<<"\t\t1. Create New Account"<<endl;
		cout<<"\t\t2. Show All Account"<<endl;
		cout<<"\t\t3. Search Account"<<endl;
		cout<<"\t\t4. Deposit Money"<<endl;
		cout<<"\t\t5. Withdraw Money"<<endl;
		cout<<"\t\t6. Exit\n"<<endl;
		cout<<"\t\tEnter Your Choice: ";
		cin>>choice;
		cout << endl;

		switch(choice){
			case 1:{
				string name;
				int accountNum;
				double balance;
				cout<<"\t\tEnter Name: ";
				cin>>name;
				cout<<"\t\tEnter Account Number: ";
				cin>>accountNum;
				cout<<"\t\tEnter Initial Balance: ";
				cin>>balance;
				bank.AddAccount(name,accountNum,balance);
				cout<<"\t\tAccount Created Successfully!!!\n"<<endl;
				break;
			}

			case 2:{
				bank.showAllAccounts();
				break;
			}

			case 3:{
				int accountNum;
				cout<<"\t\tEnter Account Number: ";
				cin>>accountNum;
				bank.searchAccount(accountNum);
				break;
			}

			case 4:{
				int accountNum;
				double amount;
				cout<<"\t\tEnter Account Number to Deposit Money: ";
				cin>>accountNum;
				BankAccount* account = bank.findAccount(accountNum);
				if(account !=NULL){
					cout<<"\t\tEnter Amount to be deposited: ";
					cin>>amount;
					account->deposit(amount);
					cout<<"\t\t"<<amount<<"Amount Deposited Successfully!!!\n"<<endl;
				}
				
				else{
					cout<<"\t\tAcount Not Found!!!"<<endl;
				}
				break;
			}

			case 5:{
				int accountNum;
				double amount;
				cout<<"\t\tEnter Account Number to Withdraw Money: ";
				cin>>accountNum;
				BankAccount* account = bank.findAccount(accountNum);
				if(account !=NULL){
					cout<<"\t\tEnter Amount to be withdrawn: ";
					cin>>amount;
					account->withdraw(amount);
					cout<<"\t\t"<<amount<<"Amount Withdrawn Successfully!!!\n"<<endl;
					
				}
				
				else{
					cout<<"\t\tAcount Not Found!!!"<<endl;
				}
				break;
			}

			case 6:{
				cout << "\t\tClosing!!!" << endl;
				exit(1);
				break;
			}
		}

	    cout<<"\t\tDo You Want to Continue or Exit [Yes / No]?: ";
	    cin>>op;
		
	}while(op == 'y'||op =='Y');

    return 0;
}