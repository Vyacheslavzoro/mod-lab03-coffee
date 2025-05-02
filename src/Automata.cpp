#include <iostream>
#include <vector>
#include "Automata.h"

Automata::Automata() {
    status = POWER_OFF;
    balance = 0;
    selected = -1;

    drinks = {"������� ���", "�����", "�����"};
    cost = {20, 45, 60};
}

STATES Automata::getState() {
    return status;
}

void Automata::displayMenu() {
    std::cout << "��������� �������:\n";
    for (size_t i = 0; i < drinks.size(); ++i) {
        std::cout << i << ") " << drinks[i] 
                  << " - " << cost[i] << " ���.\n";
    }
}

void Automata::powerOn() {
    if (status == POWER_OFF) {
        status = STANDBY;
        std::cout << "����� ����������!\n";
    }
}

void Automata::powerOff() {
    if (status == STANDBY) {
        status = POWER_OFF;
        std::cout << "������ ���������\n";
    }
}

void Automata::insertCoin(int amount) {
    if (status == STANDBY || status == PAYMENT) {
        status = PAYMENT;
        balance += amount;
        std::cout << "������: " << balance << " ���.\n";
    }
}

void Automata::cancelOrder() {
    if (status == PAYMENT || status == VALIDATION) {
        std::cout << "������. �������: " << balance << " ���.\n";
        balance = 0;
        selected = -1;
        status = STANDBY;
    }
}

void Automata::selectDrink(int index) {
    if (status == PAYMENT) {
        if (index >= 0 && static_cast<size_t>(index) < drinks.size()) {
            selected = index;
            std::cout << "�����: " << drinks[selected] << "\n";
            status = VALIDATION;
            validate();
        }
    }
}

void Automata::validate() {
    if (status == VALIDATION) {
        if (balance >= cost[selected]) {
            prepare();
        } else {
            std::cout << "������������ �������. ����� ���: " 
                      << cost[selected] - balance << " ���.\n";
        }
    }
}

void Automata::prepare() {
    if (status == VALIDATION) {
        status = PREPARING;
        std::cout << "������� " << drinks[selected] << "...\n";
        complete();
    }
}

void Automata::complete() {
    if (status == PREPARING) {
        std::cout << "��� " << drinks[selected] << " �����!\n";
        if (balance > cost[selected]) {
            std::cout << "�������� �����: " 
                      << balance - cost[selected] << " ���.\n";
        }
        balance = 0;
        selected = -1;
        status = STANDBY;
    }
}