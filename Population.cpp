#include "Stronghold.h"
using namespace std;
Population::Population() {
    totalPopulation = 1000;
    growthRate = 0.02;
    healthStatus = 80.0;
    revoltRisk = 10.0;
    employment = 70.0;
}
Population::~Population() {}
void Population::validateInputs() {
    if (totalPopulation < 0 || healthStatus < 0 || revoltRisk < 0 || employment < 0 || employment > 100)
        cout << "Negative or invalid population values" << endl;
}
void Population::updatePopulation(double foodSupply, double employment, double shelter) {
    if (foodSupply < 0 || employment < 0 || shelter < 0) {
        cout << "Negative supply values are invalid" << endl;
        return;
    }
    growthRate = (foodSupply * 0.01 + employment * 0.005 + shelter * 0.005) - 0.01;
    totalPopulation += (int)(totalPopulation * growthRate);
    healthStatus = healthStatus + foodSupply * 0.1 + shelter * 0.05 - 5.0;
    if (healthStatus > 100.0) healthStatus = 100.0;
    revoltRisk = revoltRisk + (100.0 - healthStatus) * 0.02 + (100.0 - employment) * 0.03;
    if (revoltRisk > 100.0) revoltRisk = 100.0;
    validateInputs();
}
void Population::triggerDisease(double severity) {
    if (severity < 0 || severity > 100) {
        cout << "Invalid disease severity" << endl;
        return;
    }
    healthStatus = healthStatus - severity;
    if (healthStatus < 0.0) healthStatus = 0.0;
    totalPopulation -= (int)(totalPopulation * (severity / 200.0));
    revoltRisk = revoltRisk + severity * 0.1;
    if (revoltRisk > 100.0) revoltRisk = 100.0;
    validateInputs();
}
int Population::checkRevolt() {
    return revoltRisk > 80.0 ? 1 : 0;
}
int Population::getTotalPopulation() const {
    return totalPopulation;
}
double Population::getRevoltRisk() const {
    return revoltRisk;
}
void Population::saveState(ofstream& outFile) const {
    if (!outFile)
        cout << "Failed to write to save file" << endl;
    else
        outFile << totalPopulation << " " << growthRate << " " << healthStatus << " " << revoltRisk << " " << employment << endl;
}
void Population::loadState(ifstream& inFile) {
    if (!inFile)
        cout << "Failed to read from save file" << endl;
    else {
        inFile >> totalPopulation >> growthRate >> healthStatus >> revoltRisk >> employment;
        if (inFile.fail())
            cout << "Failed to parse save file" << endl;
        validateInputs();
    }
}
void Population::setEmployment(double employment) {
    if (employment < 0 || employment > 100) {
        cout << "Invalid employment" << endl;
        return;
    }
    this->employment = employment;
    revoltRisk += (100.0 - employment) * 0.03;
    if (revoltRisk > 100.0) revoltRisk = 100.0;
    validateInputs();
}
double Population::getEmployment() const {
    return employment;
}
void Population::reducePopulation(int number) {
    if (number < 0 || number > totalPopulation) {
        cout << "Invalid population reduction" << endl;
        return;
    }
    totalPopulation -= number;
    validateInputs();
}