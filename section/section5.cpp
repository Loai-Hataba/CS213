#include <iostream>
using namespace std;

class BankAccount{
        private:
            double *balance;
            double *transactions;
            int count;
        public:
            BankAccount() {
                balance = new double(0);
                transactions = new double[100];
                count = 0;
            };
            BankAccount(double initialBalance){
                balance = new double(initialBalance);
                transactions = new double[100];
                count = 0;
            };
            BankAccount(const BankAccount& other){
                // cout << "=\n";
                balance = new double(*other.balance);
                transactions = new double[other.count];
                for (int i = 0; i < other.count; i++){
                    transactions[i] = other.transactions[i];
                }
                count = other.count;

            };
            // ~BankAccount();
            void operator=(const BankAccount& other)
            {
                balance = new double(*other.balance);
                transactions = new double[100];
                for (int i = 0; i < other.count; i++){
                    transactions[i] = other.transactions[i];
                }
                count = other.count;
            };
            void addTransaction(double amount)
            {
                transactions[count] = amount;
                *balance = (amount + *balance);
                count++;
            };
            void printInfo() const
            {
                cout << "Balance: $" << *balance << endl;
                cout << "Number of transactions: " << count << endl;
                cout << "Transactions: [ ";
                for(int i = 0; i < count; i++){
                    cout << transactions[i] << "$ ";
                }
                cout <<"]" <<  endl;
            };
};

int main()
{
    BankAccount *account1 = new BankAccount( 100.0);
    account1->addTransaction( 50.0 ) ;
    account1->addTransaction( -20.0 ) ;
    cout << "\nAccount 1 details: \n";
    account1->printInfo();

    BankAccount account2 = *account1;
    cout << "\nAccount 2 details: \n";
    account2.printInfo();

    account1->addTransaction(30.0);
    cout << "\nAccount 1 details: \n";
    account1->printInfo();
    
    cout << "\nAccount 2 details: \n";
    account2.printInfo();

    BankAccount *account3 = new BankAccount(*account1);
    cout << "\nAccount 3 details: \n";
    account3->printInfo();

    account1->addTransaction(-10.0);
    cout << "\nAccount 1 details: \n";
    account1->printInfo();

    cout << "\nAccount 3 details: \n";
    account3->printInfo();
    return 0;
}