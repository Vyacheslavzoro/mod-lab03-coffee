#include "Automata.h"

int main() {
    Automata vending;
    
    vending.powerOn();
    vending.displayMenu();
    
    vending.insertCoin(50);
    vending.insertCoin(20);
    vending.selectDrink(2);
    
    vending.powerOff();
    
    return 0;
}