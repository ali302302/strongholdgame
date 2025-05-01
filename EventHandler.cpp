#include "Stronghold.h"
using namespace std;
EventHandler::EventHandler() : lastEventType(-1) {}
EventHandler::~EventHandler() {}
void EventHandler::validateInputs() {
    if (lastEventType < -1)
        cout << "Invalid event type" << endl;
}
void EventHandler::triggerEvent(int eventType, Population& population, Resources& resources, Military& military, Economy& economy, Leadership& leadership, Bank& bank) {
    if (eventType < 0 || eventType > 3) {
        cout << "Invalid event type" << endl;
        return;
    }
    lastEventType = eventType;
    if (eventType == 0) {
        population.triggerDisease(30.0);
        resources.consumeResources(50, 0, 0, 0);
    }
    else if (eventType == 1) {
        resources.gatherResources(100, 50, 50, 20);
        economy.generateIncome(500);
    }
    else if (eventType == 2) {
        population.setEmployment(population.getEmployment() - 10.0);
        military.defendAttack(20.0);
    }
    else if (eventType == 3) {
        economy.tradeResources(0, 50, 1, 30, resources);
        bank.makeInvestment(200.0, economy, population);
    }
    validateInputs();
}
int EventHandler::getLastEventType() const {
    return lastEventType;
}
void EventHandler::saveState(ofstream& outFile) const {
    if (!outFile)
        cout << "Failed to write to save file" << endl;
    else
        outFile << lastEventType << endl;
}
void EventHandler::loadState(ifstream& inFile) {
    if (!inFile)
        cout << "Failed to read from save file" << endl;
    else {
        inFile >> lastEventType;
        if (inFile.fail())
            cout << "Failed to parse save file" << endl;
        validateInputs();
    }
}