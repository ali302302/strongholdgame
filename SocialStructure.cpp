#include "Stronghold.h"
using namespace std;
SocialStructure::SocialStructure() : morale(50.0), education(50.0) {}
SocialStructure::~SocialStructure() {}
void SocialStructure::validateInputs() {
    if (morale < 0 || education < 0)
        cout << "Negative social values" << endl;
}
void SocialStructure::improveMorale(double amount, Population& population, Economy& economy) {
    if (amount < 0) {
        cout << "Invalid morale amount" << endl;
        return;
    }
    morale += amount;
    if (morale > 100.0) morale = 100.0;
    population.setEmployment(population.getEmployment() + amount * 0.1);
    economy.generateIncome((int)(amount * 10.0));
    validateInputs();
}
void SocialStructure::improveEducation(double amount, Population& population, Economy& economy) {
    if (amount < 0) {
        cout << "Invalid education amount" << endl;
        return;
    }
    education += amount;
    if (education > 100.0) education = 100.0;
    population.setEmployment(population.getEmployment() + amount * 0.05);
    economy.generateIncome((int)(amount * 5.0));
    validateInputs();
}
double SocialStructure::getMorale() const {
    return morale;
}
double SocialStructure::getEducation() const {
    return education;
}
void SocialStructure::saveState(ofstream& outFile) const {
    if (!outFile)
        cout << "Failed to write to save file" << endl;
    else
        outFile << morale << " " << education << endl;
}
void SocialStructure::loadState(ifstream& inFile) {
    if (!inFile)
        cout << "Failed to read from save file" << endl;
    else {
        inFile >> morale >> education;
        if (inFile.fail())
            cout << "Failed to parse save file" << endl;
        validateInputs();
    }
}