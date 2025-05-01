#ifndef STRONGHOLD_H
#define STRONGHOLD_H
#include <iostream>
#include <fstream>
using namespace std;
class SocialStructure;
class Population;
class Military;
class Leadership;
class Economy;
class Bank;
class Resources;
class EventHandler;
class SocialStructure 
{
private:
    double morale;
    double education;
    void validateInputs();
public:
    SocialStructure();
    ~SocialStructure();
    void improveMorale(double amount, Population& population, Economy& economy);
    void improveEducation(double amount, Population& population, Economy& economy);
    double getMorale() const;
    double getEducation() const;
    void saveState(ofstream& outFile) const;
    void loadState(ifstream& inFile);
};
class Population
{
private:
    int totalPopulation;
    double growthRate;
    double healthStatus;
    double revoltRisk;
    double employment;
    void validateInputs();
public:
    Population();
    ~Population();
    void updatePopulation(double foodSupply, double employment, double shelter);
    void triggerDisease(double severity);
    int checkRevolt();
    int getTotalPopulation() const;
    double getRevoltRisk() const;
    void saveState(ofstream& outFile) const;
    void loadState(ifstream& inFile);
    void setEmployment(double employment);
    double getEmployment() const;
    void reducePopulation(int number);
};
class Military
{
private:
    int soldierCount;
    double strength;
    int* weaponStock;
    int weaponTypes;
    void validateInputs();
public:
    Military();
    ~Military();
    void recruitSoldiers(int number, Population& population);
    void equipWeapons(int ironAmount, Resources& resources);
    void defendAttack(double attackStrength);
    int getSoldierCount() const;
    double getStrength() const;
    void saveState(ofstream& outFile) const;
    void loadState(ifstream& inFile);
};
class Leadership 
{
private:
    double influence;
    double taxRate;
    void validateInputs();
public:
    Leadership();
    ~Leadership();
    void setTaxRate(double rate, Economy& economy, Population& population);
    void boostInfluence(double amount, Economy& economy);
    void implementWelfare(Population& population, Economy& economy);
    double getInfluence() const;
    double getTaxRate() const;
    void saveState(ofstream& outFile) const;
    void loadState(ifstream& inFile);
};
class Economy
{
private:
    double wealth;
    double employmentRate;
    void validateInputs();
public:
    Economy();
    ~Economy();
    void generateIncome(int population);
    void tradeResources(int giveType, int giveAmount, int receiveType, int receiveAmount, Resources& resources);
    void adjustEmployment(double rate, Population& population);
    double getWealth() const;
    double getEmploymentRate() const;
    void saveState(ofstream& outFile) const;
    void loadState(ifstream& inFile);
};
class Bank
{
private:
    double reserves;
    double loanAmount;
    void validateInputs();
public:
    Bank();
    ~Bank();
    void takeLoan(double amount, Economy& economy, Population& population);
    void makeInvestment(double amount, Economy& economy, Population& population);
    void repayLoan(double amount, Economy& economy);
    double getReserves() const;
    double getLoanAmount() const;
    void saveState(ofstream& outFile) const;
    void loadState(ifstream& inFile);
};
class Resources
{
private:
    int* resourceQuantities;
    int resourceCount;
    void validateInputs();
public:
    Resources();
    ~Resources();
    void gatherResources(int food, int wood, int stone, int iron);
    void consumeResources(int food, int wood, int stone, int iron);
    void tradeResources(int giveType, int giveAmount, int receiveType, int receiveAmount);
    int getResource(int type) const;
    void saveState(ofstream& outFile) const;
    void loadState(ifstream& inFile);
};
class EventHandler 
{
private:
    int lastEventType;
    void validateInputs();
public:
    EventHandler();
    ~EventHandler();
    void triggerEvent(int eventType, Population& population, Resources& resources, Military& military, Economy& economy, Leadership& leadership, Bank& bank);
    int getLastEventType() const;
    void saveState(ofstream& outFile) const;
    void loadState(ifstream& inFile);
};
#endif