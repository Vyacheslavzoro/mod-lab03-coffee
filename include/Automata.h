// Copyright 2025 Owner

#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <string>
#include <vector>

enum STATES {
  OFF,
  ON,
  WAITING_FOR_MONEY,
  CHECKING_MONEY,
  COOKING
};

class Automata {
 private:
  int cash;
  std::vector<std::string> menu;
  std::vector<int> prices;
  STATES state;
  int chosen_index;

 public:
  Automata();

  void on();
  void off();
  void coin(int amount);
  void setMenu(const std::vector<std::string>& drinks,
               const std::vector<int>& costs);
  STATES getState() const;
  void choice(int index);
  bool check();
  void cancel();
  void cook();
  void finish();
};

#endif  // INCLUDE_AUTOMATA_H_
