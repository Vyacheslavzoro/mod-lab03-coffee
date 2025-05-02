#include <iostream>
#include <string>
#include <vector>
#include "Automata.h"

Automata::Automata() {
    state = OFF;
    cash = 0;
    currentDrink = -1;

    menu.push_back("���");
    menu.push_back("���� � �������");
    menu.push_back("������� ��������");

    prices.push_back(15);
    prices.push_back(30);
    prices.push_back(50);
}

STATES Automata::getState() {
    return state;
}

void Automata::getMenu() {
    std::cout << "����:" << std::endl;
    for (size_t i = 0; i < menu.size(); i++) {
        std::cout << i << ": " << menu[i] 
                  << " - " << prices[i] << std::endl;
    }
}

void Automata::on() {
    if (state == OFF) {
        state = WAIT;
        std::cout << "������� �������" << std::endl;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::off() {
    if (state == WAIT) {
        state = OFF;
        std::cout << "������� ��������" << std::endl;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::coin(int sum) {
    if (state == WAIT || state == ACCEPT) {
        state = ACCEPT;
        cash += sum;
        std::cout << "�� ������ " << sum
                  << ", ������� ������: " << cash << std::endl;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::cancel() {
    if (state == ACCEPT || state == CHECK) {
        std::cout << "����� ������, �������: " << cash << std::endl;
        cash = 0;
        state = WAIT;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::choice(int drinkIndex) {
    if (state == ACCEPT) {
        if (drinkIndex >= 0 && drinkIndex < static_cast<int>(menu.size())) {
            std::cout << "�� �������: " << menu[drinkIndex] << std::endl;
            currentDrink = drinkIndex;
            state = CHECK;
        } else {
            std::cout << "�������� ������ �������" << std::endl;
        }
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::check() {
    if (state == CHECK) {
        if (cash >= prices[currentDrink]) {
            std::cout << "����� ����������, �������� �������������" << std::endl;
        } else {
            std::cout << "������������ �����" << std::endl;
        }
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::cook() {
    if (state == CHECK) {
        state = COOK;
        std::cout << "������������� �������: " 
                  << menu[currentDrink] << std::endl;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::finish() {
    if (state == COOK) {
        std::cout << "������� �����" << std::endl;
        if (cash > prices[currentDrink]) {
            std::cout << "�����: " 
                      << cash - prices[currentDrink] << std::endl;
        }
        cash = 0;
        state = WAIT;
        currentDrink = -1;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}