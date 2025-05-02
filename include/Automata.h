// Copyright 2025 Owner

#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <string>
#include <vector>

enum STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};

class Automata {
 private:
    int cash;
    std::vector<std::string> menu;
    std::vector<int> prices;
    STATES state;
    int currentDrink;

 public:
    Automata();
    STATES getState();
    void getMenu();
    void on();
    void off();
    void coin(int);
    void cancel();
    void choice(int);
    void check();
    void cook();
    void finish();
};

#endif  // INCLUDE_AUTOMATA_H_
