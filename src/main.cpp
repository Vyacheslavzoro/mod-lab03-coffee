// Copyright 2025 Owner

#include "Automata.h"

int main() {
    Automata automata;

    automata.on();
    automata.getMenu();

    automata.coin(30);
    automata.coin(30);
    automata.choice(2);
    automata.check();

    automata.cook();
    automata.finish();

    automata.off();

    return 0;
}