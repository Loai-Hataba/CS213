#include <string>
#include <iostream>
using namespace std;
#define el endl

class Employee{
    protected:
        string name;
        int id;
        double netPay;
    public:
        Employee(string n, int id) : name(n), id(id){};
        
        void calculateSalary(){}
        void printEmployeeInfo(){
            cout << "Name: " << name << el << "ID: " << id << el << "Salary: " << netPay << el << el;
        }
        void setNetPay(double number) {netPay = number;}
};

class partTimeEmployee:public Employee{
    private:
        double ratePerHour;
        double workingHours;
    public:
        partTimeEmployee(string n, int id) : Employee(n, id){};

        void setRatePerHour(double number){ratePerHour = number;}

        void setWorkingHours(double number){workingHours = number;}
        void calculateSalary(){ setNetPay(ratePerHour*workingHours);
        }

};

class fullTimeEmployee:public Employee{
    private:
        double salary;
    public:
        fullTimeEmployee(string n, int id) : Employee(n, id){};

        void calculateSalary(){setNetPay(salary);
        }
};


int main(){
    partTimeEmployee hala("Hala", 12201);
    fullTimeEmployee ali("Ali", 12202);

    hala.setRatePerHour(20);
    hala.setWorkingHours(40);
    hala.calculateSalary();
    hala.printEmployeeInfo();

    ali.setNetPay(1500);
    ali.printEmployeeInfo();


}