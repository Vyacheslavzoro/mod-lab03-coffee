// Copyright 2025 Owner

#include "Automata.h"
#include <iostream>

void demonstrateWorkflow() {
    BeverageDispenser machine;
    std::cout << "Demo 1: Successful purchase with change" << std::endl;
    machine.activate();
    machine.showOptions();
    machine.addFunds(70);
    machine.makeSelection(2);
    machine.checkPayment();
    machine.processOrder();
    machine.finishOrder();
    std::cout << "\nDemo 2: Insufficient funds scenario" << std::endl;
    machine.addFunds(20);
    machine.makeSelection(1);
    machine.checkPayment();
    machine.cancelTransaction();
    std::cout << "\nDemo 3: Full cancellation" << std::endl;
    machine.addFunds(40);
    machine.cancelTransaction();
    std::cout << "\nDemo 4: Exact amount purchase" << std::endl;
    machine.addFunds(15);
    machine.makeSelection(0);
    machine.checkPayment();
    machine.processOrder();
    machine.finishOrder();
    machine.shutdown();
}

int main() {
    demonstrateWorkflow();
    std::cout << "\nAll demonstrations completed" << std::endl;
    return 0;
}
