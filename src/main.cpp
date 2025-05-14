// Copyright 2025 Owner

#include "Automata.h"

int main() {
    VendingMachine machine;

    machine.powerOn();
    machine.displayMenu();
    machine.insertMoney(20);
    machine.insertMoney(40);
    machine.selectDrink(2);
    machine.validate();
    machine.brew();
    machine.complete();
    machine.powerOff();

    return 0;
}
