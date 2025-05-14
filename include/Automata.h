// Copyright 2025 Owner

#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <string>
#include <vector>

enum MachineState {
    POWERED_OFF,
    IDLE,
    MONEY_IN,
    VERIFY,
    PREPARE
};

class VendingMachine {
 private:
    int balance;
    std::vector<std::string> drinks;
    std::vector<int> costs;
    MachineState currentState;
    int selectedIndex;

 public:
    VendingMachine();
    MachineState state() const;
    void displayMenu() const;
    void powerOn();
    void powerOff();
    void insertMoney(int amount);
    void abort();
    void selectDrink(int index);
    void validate();
    void brew();
    void complete();
};

#endif  // INCLUDE_AUTOMATA_H_
