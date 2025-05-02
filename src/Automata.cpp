// src/Automata.cpp

#include <iostream>
#include <string>
#include <vector>
#include "Automata.h"

Automata::Automata() {
    this->state = STATES::OFF;
    this->cash = 0;
    this->currentDrink = -1;

    this->menu.push_back("���");
    this->menu.push_back("���� � �������");
    this->menu.push_back("������� ��������");

    this->prices.push_back(15);
    this->prices.push_back(30);
    this->prices.push_back(50);
}

STATES Automata::getState() {
    return this->state;
}

void Automata::getMenu() {
    std::cout << "����:" << std::endl;
    for (size_t i = 0; i < menu.size(); i++) {
        std::cout << i << ": " << menu[i]
                  << " - " << prices[i] << std::endl;
    }
}

void Automata::on() {
    if (this->state == STATES::OFF) {
        this->state = STATES::WAIT;
        std::cout << "������� �������" << std::endl;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::off() {
    if (this->state == STATES::WAIT) {
        this->state = STATES::OFF;
        std::cout << "������� ��������" << std::endl;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::coin(int sum) {
    if (this->state == STATES::WAIT || this->state == STATES::ACCEPT) {
        this->state = STATES::ACCEPT;
        this->cash += sum;
        std::cout << "�� ������ " << sum
                  << ", ������� ������: " << this->cash << std::endl;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::cancel() {
    if (this->state == STATES::ACCEPT || this->state == STATES::CHECK) {
        std::cout << "����� ������, �������: " << this->cash << std::endl;
        this->cash = 0;
        this->state = STATES::WAIT;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::choice(int drinkIndex) {
    if (this->state == STATES::ACCEPT) {
        if (drinkIndex >= 0 && drinkIndex < static_cast<int>(menu.size())) {
            std::cout << "�� �������: " << menu[drinkIndex] << std::endl;
            this->currentDrink = drinkIndex;
            this->state = STATES::CHECK;
        } else {
            std::cout << "�������� ������ �������" << std::endl;
        }
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::check() {
    if (this->state == STATES::CHECK) {
        if (this->cash >= prices[this->currentDrink]) {
            std::cout << "����� ����������, �������� �������������" << std::endl;
        } else {
            std::cout << "������������ �����" << std::endl;
        }
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::cook() {
    if (this->state == STATES::CHECK) {
        this->state = STATES::COOK;
        std::cout << "������������� �������: "
                  << menu[this->currentDrink] << std::endl;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}

void Automata::finish() {
    if (this->state == STATES::COOK) {
        std::cout << "������� �����" << std::endl;
        if (this->cash > prices[this->currentDrink]) {
            std::cout << "�����: " 
                      << this->cash - prices[this->currentDrink] << std::endl;
        }
        this->cash = 0;
        this->state = STATES::WAIT;
        this->currentDrink = -1;
    } else {
        std::cout << "������������ ���������" << std::endl;
    }
}