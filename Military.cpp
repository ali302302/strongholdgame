#include "Stronghold.h"
using namespace std;
Military::Military() : soldierCount(100), strength(10.0), weaponTypes(4) {
    weaponStock = new int[weaponTypes];
    for (int i = 0; i < weaponTypes; i++) weaponStock[i] = 50;
}
Military::~Military() {
    delete[] weaponStock;
}
void Military::validateInputs() {
    if (soldierCount < 0 || strength < 0) {
        cout << "Negative military values" << endl;
        return;
    }
    for (int i = 0; i < weaponTypes; i++)
        if (weaponStock[i] < 0)
            cout << "Negative weapon stock" << endl;
}
void Military::recruitSoldiers(int number, Population& population) {
    if (number < 0 || number > population.getTotalPopulation()) {
        cout << "Invalid soldier count" << endl;
        return;
    }
    soldierCount += number;
    strength += number * 0.1;
    population.reducePopulation(number);
    validateInputs();
}
void Military::equipWeapons(int ironAmount, Resources& resources) {
    if (ironAmount < 0 || ironAmount > resources.getResource(3)) {
        cout << "Invalid or insufficient iron amount" << endl;
        return;
    }
    resources.consumeResources(0, 0, 0, ironAmount);
    for (int i = 0; i < weaponTypes; i++)
        weaponStock[i] += (int)(ironAmount * 0.25);
    strength += ironAmount * 0.05;
    validateInputs();
}
void Military::defendAttack(double attackStrength) {
    if (attackStrength < 0) {
        cout << "Invalid attack strength" << endl;
        return;
    }
    strength -= attackStrength * 0.5;
    if (strength < 0.0) strength = 0.0;
    soldierCount -= (int)(attackStrength * 2.0);
    if (soldierCount < 0) soldierCount = 0;
    validateInputs();
}
int Military::getSoldierCount() const {
    return soldierCount;
}
double Military::getStrength() const {
    return strength;
}
void Military::saveState(ofstream& outFile) const {
    if (!outFile)
        cout << "Failed to write to save file" << endl;
    else {
        outFile << soldierCount << " " << strength << " " << weaponTypes;
        for (int i = 0; i < weaponTypes; i++)
            outFile << " " << weaponStock[i];
        outFile << endl;
    }
}
void Military::loadState(ifstream& inFile) {
    if (!inFile)
        cout << "Failed to read from save file" << endl;
    else {
        inFile >> soldierCount >> strength >> weaponTypes;
        delete[] weaponStock;
        weaponStock = new int[weaponTypes];
        for (int i = 0; i < weaponTypes; i++)
            inFile >> weaponStock[i];
        if (inFile.fail())
            cout << "Failed to parse save file" << endl;
        validateInputs();
    }
}