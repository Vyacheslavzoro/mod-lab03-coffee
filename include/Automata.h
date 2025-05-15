// Copyright 2025 Owner

#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <string>
#include <vector>
#include <utility>

enum SystemStatus {
    OFF,
    STANDBY,
    ACCEPTING_CASH,
    CHECKING,
    DISPENSING
};

class BeverageDispenser {
 private:
    int user_credit;
    std::vector<std::pair<std::string, int>> beverage_options;
    SystemStatus current_mode;
    int chosen_option;

    void resetTransaction();

 public:
    BeverageDispenser();
    SystemStatus getCurrentMode() const;
    void showOptions() const;
    void activate();
    void shutdown();
    void addFunds(int cash);
    void cancelTransaction();
    void makeSelection(int choice);
    void checkPayment();
    void processOrder();
    void finishOrder();
};


#endif  // INCLUDE_AUTOMATA_H_
