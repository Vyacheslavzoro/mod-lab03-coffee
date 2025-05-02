#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <string>
#include <vector>

enum STATES {
    POWER_OFF,
    STANDBY,
    PAYMENT,
    VALIDATION,
    PREPARING
};

class Automata {
 private:
    int balance;
    std::vector<std::string> drinks;
    std::vector<int> cost;
    STATES status;
    int selected;

 public:
    Automata();
    STATES getState();
    void displayMenu();
    void powerOn();
    void powerOff();
    void insertCoin(int);
    void cancelOrder();
    void selectDrink(int);
    void validate();
    void prepare();
    void complete();
};

#endif