#include "Stronghold.h"
using namespace std;
Bank::Bank() : reserves(5000.0), loanAmount(0.0) {}
Bank::~Bank() {}
void Bank::validateInputs() {
    if (reserves < 0 || loanAmount < 0 )
        cout << "Invalid bank values" << endl;
}
void Bank::takeLoan(double amount, Economy& economy, Population& population) {
    if (amount < 0 || amount > reserves) {
        cout << "Invalid or insufficient loan amount" << endl;
        return;
    }
    loanAmount += amount;
        reserves -= amount;
        economy.generateIncome((int)amount);
        population.setEmployment(population.getEmployment() + amount * 0.001);
    validateInputs();
}
void Bank::makeInvestment(double amount, Economy& economy, Population& population) {
    if (amount < 0 || amount > reserves) {
        cout << "Invalid or insufficient investment amount" << endl;
        return;
    }
    reserves -= amount;
    economy.generateIncome((int)(amount * 1.5));
    population.setEmployment(population.getEmployment() + amount * 0.002);
    validateInputs();
}
void Bank::repayLoan(double amount, Economy& economy) {
    if (amount < 0 || amount > loanAmount) {
        cout << "Invalid repayment amount" << endl;
        return;
    }
    loanAmount -= amount;
    reserves += amount;
    economy.generateIncome(-(int)(amount * 1.1));
    validateInputs();
}
double Bank::getReserves() const {
    return reserves;
}
double Bank::getLoanAmount() const {
    return loanAmount;
}
void Bank::saveState(ofstream& outFile) const {
    if (!outFile)
        cout << "Failed to write to save file" << endl;
    else
        outFile << reserves << " " << loanAmount << endl;
}
void Bank::loadState(ifstream& inFile) {
    if (!inFile)
        cout << "Failed to read from save file" << endl;
    else {
        inFile >> reserves >> loanAmount;
        if (inFile.fail())
            cout << "Failed to parse save file" << endl;
        validateInputs();
    }
}