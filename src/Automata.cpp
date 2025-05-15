// Copyright 2025 Owner

#include <iostream>
#include <string>
#include <vector>
#include "Automata.h"

BeverageDispenser::BeverageDispenser() {
    current_mode = OFF;
    user_credit = 0;
    chosen_option = -1;
    beverage_options = {
        {"Classic Tea", 15},
        {"Milky Coffee", 30},
        {"Strong Coffee", 50}
    };
}

SystemStatus BeverageDispenser::getCurrentMode() const {
    return current_mode;
}

void BeverageDispenser::showOptions() const {
    std::cout << "\nMenu Options:\n";
    for (size_t idx = 0; idx < beverage_options.size(); ++idx) {
        std::cout << idx << ") " << beverage_options[idx].first
                  << " - " << beverage_options[idx].second << " coins\n";
    }
}

void BeverageDispenser::activate() {
    if (current_mode == OFF) {
        current_mode = STANDBY;
        std::cout << "Welcome! System ready\n";
    } else {
        std::cout << "Already operational\n";
    }
}

void BeverageDispenser::shutdown() {
    if (current_mode == STANDBY) {
        current_mode = OFF;
        std::cout << "Powering down\n";
    } else {
        std::cout << "Cannot shutdown now\n";
    }
}

void BeverageDispenser::addFunds(int cash) {
    if (current_mode == STANDBY || current_mode == ACCEPTING_CASH) {
        user_credit += cash;
        current_mode = ACCEPTING_CASH;
        std::cout << "Added " << cash << " coins. Total: "
                  << user_credit << "\n";
    } else {
        std::cout << "Deposit not available\n";
    }
}

void BeverageDispenser::cancelTransaction() {
    if (current_mode == ACCEPTING_CASH || current_mode == CHECKING) {
        std::cout << "Canceling. Refunding " << user_credit << " coins\n";
        resetTransaction();
    } else {
        std::cout << "No active transaction\n";
    }
}

void BeverageDispenser::makeSelection(int choice) {
    if (current_mode == ACCEPTING_CASH) {
        if (choice >= 0 && choice < static_cast<int>(beverage_options.size())) {
            chosen_option = choice;
            current_mode = CHECKING;
            std::cout << "Selected: " << beverage_options[choice].first << "\n";
        } else {
            std::cout << "Invalid option\n";
        }
    } else {
        std::cout << "Selection unavailable\n";
    }
}

void BeverageDispenser::checkPayment() {
    if (current_mode == CHECKING) {
        if (user_credit >= beverage_options[chosen_option].second) {
            std::cout << "Payment accepted\n";
        } else {
            std::cout << "Insufficient funds. Need "
                      << (beverage_options[chosen_option].second - user_credit)
                      << " more coins\n";
        }
    }
}

void BeverageDispenser::processOrder() {
    if (current_mode == CHECKING &&
        user_credit >= beverage_options[chosen_option].second) {
        current_mode = DISPENSING;
        std::cout << "Making your "
                  << beverage_options[chosen_option].first << "...\n";
    }
}

void BeverageDispenser::finishOrder() {
    if (current_mode == DISPENSING) {
        int change = user_credit - beverage_options[chosen_option].second;
        if (change > 0) {
            std::cout << "Take change: " << change << " coins\n";
        }
        std::cout << "Enjoy your drink!\n\n";
        resetTransaction();
    }
}

void BeverageDispenser::resetTransaction() {
    user_credit = 0;
    chosen_option = -1;
    current_mode = STANDBY;
}
