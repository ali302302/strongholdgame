#include "Stronghold.h"
using namespace std;
Resources::Resources() : resourceCount(4) {
    resourceQuantities = new int[resourceCount];
    for (int i = 0; i < resourceCount; i++) resourceQuantities[i] = 100;
}
Resources::~Resources() {
    delete[] resourceQuantities;
}
void Resources::validateInputs() {
    for (int i = 0; i < resourceCount; i++)
        if (resourceQuantities[i] < 0)
            cout << "Negative resource quantities" << endl;
}
void Resources::gatherResources(int food, int wood, int stone, int iron) {
    if (food < 0 || wood < 0 || stone < 0 || iron < 0) {
        cout << "Negative resource amounts are invalid" << endl;
        return;
    }
    resourceQuantities[0] += food;
    resourceQuantities[1] += wood;
    resourceQuantities[2] += stone;
    resourceQuantities[3] += iron;
    validateInputs();
}
void Resources::consumeResources(int food, int wood, int stone, int iron) {
    if (food < 0 || wood < 0 || stone < 0 || iron < 0 || food > resourceQuantities[0] || wood > resourceQuantities[1] || stone > resourceQuantities[2] || iron > resourceQuantities[3]) {
        cout << "Invalid or insufficient resource amounts" << endl;
        return;
    }
    resourceQuantities[0] -= food;
    resourceQuantities[1] -= wood;
    resourceQuantities[2] -= stone;
    resourceQuantities[3] -= iron;
    validateInputs();
}
void Resources::tradeResources(int giveType, int giveAmount, int receiveType, int receiveAmount) {
    if (giveType < 0 || giveType >= resourceCount || receiveType < 0 || receiveType >= resourceCount || giveAmount < 0 || receiveAmount < 0 || giveAmount > resourceQuantities[giveType]) {
        cout << "Invalid trade parameters" << endl;
        return;
    }
    resourceQuantities[giveType] -= giveAmount;
    resourceQuantities[receiveType] += receiveAmount;
    validateInputs();
}
int Resources::getResource(int type) const {
    if (type < 0 || type >= resourceCount) {
        cout << "Invalid resource type" << endl;
        return 0;
    }
    return resourceQuantities[type];
}
void Resources::saveState(ofstream& outFile) const {
    if (!outFile)
        cout << "Failed to write to save file" << endl;
    else {
        outFile << resourceCount;
        for (int i = 0; i < resourceCount; i++)
            outFile << " " << resourceQuantities[i];
        outFile << endl;
    }
}
void Resources::loadState(ifstream& inFile) {
    if (!inFile)
        cout << "Failed to read from save file" << endl;
    else {
        inFile >> resourceCount;
        delete[] resourceQuantities;
        resourceQuantities = new int[resourceCount];
        for (int i = 0; i < resourceCount; i++)
            inFile >> resourceQuantities[i];
        if (inFile.fail())
            cout << "Failed to parse save file" << endl;
        validateInputs();
    }
}