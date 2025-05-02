#include <iostream>
#include <string>
#include <vector>
#include "Automata.h"

Automata::Automata() {
    state = OFF;
    cash = 0;
    currentDrink = -1;

    menu.push_back("Чай");
    menu.push_back("Кофе с молоком");
    menu.push_back("Двойное эспрессо");

    prices.push_back(15);
    prices.push_back(30);
    prices.push_back(50);
}

STATES Automata::getState() {
    return state;
}

void Automata::getMenu() {
    std::cout << "Меню:" << std::endl;
    for (size_t i = 0; i < menu.size(); i++) {
        std::cout << i << ": " << menu[i] 
                  << " - " << prices[i] << std::endl;
    }
}

void Automata::on() {
    if (state == OFF) {
        state = WAIT;
        std::cout << "Автомат включён" << std::endl;
    } else {
        std::cout << "Некорректное состояние" << std::endl;
    }
}

void Automata::off() {
    if (state == WAIT) {
        state = OFF;
        std::cout << "Автомат выключен" << std::endl;
    } else {
        std::cout << "Некорректное состояние" << std::endl;
    }
}

void Automata::coin(int sum) {
    if (state == WAIT || state == ACCEPT) {
        state = ACCEPT;
        cash += sum;
        std::cout << "Вы внесли " << sum
                  << ", текущий баланс: " << cash << std::endl;
    } else {
        std::cout << "Некорректное состояние" << std::endl;
    }
}

void Automata::cancel() {
    if (state == ACCEPT || state == CHECK) {
        std::cout << "Заказ отменён, возврат: " << cash << std::endl;
        cash = 0;
        state = WAIT;
    } else {
        std::cout << "Некорректное состояние" << std::endl;
    }
}

void Automata::choice(int drinkIndex) {
    if (state == ACCEPT) {
        if (drinkIndex >= 0 && drinkIndex < static_cast<int>(menu.size())) {
            std::cout << "Вы выбрали: " << menu[drinkIndex] << std::endl;
            currentDrink = drinkIndex;
            state = CHECK;
        } else {
            std::cout << "Неверный индекс напитка" << std::endl;
        }
    } else {
        std::cout << "Некорректное состояние" << std::endl;
    }
}

void Automata::check() {
    if (state == CHECK) {
        if (cash >= prices[currentDrink]) {
            std::cout << "Денег достаточно, начинаем приготовление" << std::endl;
        } else {
            std::cout << "Недостаточно денег" << std::endl;
        }
    } else {
        std::cout << "Некорректное состояние" << std::endl;
    }
}

void Automata::cook() {
    if (state == CHECK) {
        state = COOK;
        std::cout << "Приготовление напитка: " 
                  << menu[currentDrink] << std::endl;
    } else {
        std::cout << "Некорректное состояние" << std::endl;
    }
}

void Automata::finish() {
    if (state == COOK) {
        std::cout << "Напиток готов" << std::endl;
        if (cash > prices[currentDrink]) {
            std::cout << "Сдача: " 
                      << cash - prices[currentDrink] << std::endl;
        }
        cash = 0;
        state = WAIT;
        currentDrink = -1;
    } else {
        std::cout << "Некорректное состояние" << std::endl;
    }
}