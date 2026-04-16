#include <iostream>
#include <string>

class BankAccount
{
    private:
        double Balance = 0;
        std::string owner;
    public:
        void setOwner();
        string getOwner();
        void deposit(double);
        double withdraw(double);
        double getBalance();
        string getAccountInfo();
};

void setOwner()
{
    std::cout<<"Name eingeben";
    std::cin>>BankAccount.owner;
}
string getOwner()
{
    std::cout<<BankAccount.owner;
}
void desposit
