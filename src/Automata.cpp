// Copyright 2025 Owner

#include <iostream>
#include <string>
#include <vector>
#include "Automata.h"

VendingMachine::VendingMachine() {
    currentState = POWERED_OFF;
    balance = 0;
    selectedIndex = -1;

    drinks = {"Black Tea", "Latte", "Espresso"};
    costs = {15, 30, 50};
}

MachineState VendingMachine::state() const {
    return currentState;
}

void VendingMachine::displayMenu() const {
    std::cout << "\nAvailable beverages:\n";
    for (size_t i = 0; i < drinks.size(); ++i) {
        std::cout << "[" << i << "] " << drinks[i] << " - " << costs[i] << "₽\n";
    }
}

void VendingMachine::powerOn() {
    if (currentState == POWERED_OFF) {
        currentState = IDLE;
        std::cout << "System online.\n";
    } else {
        std::cout << "Cannot power on: machine already active.\n";
    }
}

void VendingMachine::powerOff() {
    if (currentState == IDLE) {
        currentState = POWERED_OFF;
        std::cout << "System shutting down.\n";
    } else {
        std::cout << "Power off not allowed in current state.\n";
    }
}

void VendingMachine::insertMoney(int amount) {
    if (currentState == IDLE || currentState == MONEY_IN) {
        balance += amount;
        currentState = MONEY_IN;
        std::cout << "You added: " << amount << "₽. Balance: " << balance << "₽\n";
    } else {
        std::cout << "Can't insert money now.\n";
    }
}

void VendingMachine::abort() {
    if (currentState == MONEY_IN || currentState == VERIFY) {
        std::cout << "Transaction canceled. Refunding " << balance << "₽.\n";
        balance = 0;
        selectedIndex = -1;
        currentState = IDLE;
    } else {
        std::cout << "Nothing to cancel.\n";
    }
}

void VendingMachine::selectDrink(int index) {
    if (currentState == MONEY_IN) {
        if (index >= 0 && index < static_cast<int>(drinks.size())) {
            selectedIndex = index;
            currentState = VERIFY;
            std::cout << "You've chosen: " << drinks[index] << "\n";
        } else {
            std::cout << "Invalid selection.\n";
        }
    } else {
        std::cout << "Cannot select now.\n";
    }
}

void VendingMachine::validate() {
    if (currentState == VERIFY) {
        if (balance >= costs[selectedIndex]) {
            std::cout << "Payment confirmed.\n";
        } else {
            std::cout << "Not enough money for selected item.\n";
        }
    } else {
        std::cout << "No selection made yet.\n";
    }
}

void VendingMachine::brew() {
    if (currentState == VERIFY) {
        currentState = PREPARE;
        std::cout << "Preparing: " << drinks[selectedIndex] << "\n";
    } else {
        std::cout << "Cannot prepare yet.\n";
    }
}

void VendingMachine::complete() {
    if (currentState == PREPARE) {
        std::cout << "Your drink is ready.\n";
        int change = balance - costs[selectedIndex];
        if (change > 0) {
            std::cout << "Don't forget your change: " << change << "₽\n";
        }
        balance = 0;
        selectedIndex = -1;
        currentState = IDLE;
    } else {
        std::cout << "No drink is being made.\n";
    }
}
