// Copyright 2025 Owner

#include "Automata.h"

int main() {
    Automata automata;

    automata.on();

    automata.setMenu({
        "Tea", "Coffee", "Milk",
        "Cocoa", "Green tea", "Espresso"
    }, {
        15, 25, 10,
        30, 20, 40
    });

    automata.coin(20);
    automata.coin(15);
    automata.coin(10);

    automata.choice(3);

    if (automata.check()) {
        automata.cook();
        automata.finish();
    } else {
        automata.cancel();
    }

    automata.coin(50);

    automata.choice(5);

    if (automata.check()) {
        automata.cook();
        automata.finish();
    } else {
        automata.cancel();
    }

    automata.off();

    return 0;
}
