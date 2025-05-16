// Copyright 2025 Owner

#include "Automata.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>


Automata::Automata() {
    cash = 0;
    state = OFF;
    chosen_index = -1;
    std::cout << "[Инициализация] Автомат создан и находится в выключенном состоянии.\n";
}

void Automata::on() {
    if (state == OFF) {
        state = ON;
        std::cout << "Автомат теперь включен и готов к работе.\n";
        std::cout << "Пожалуйста, внесите деньги, чтобы начать выбор напитка.\n";
    } else {
        std::cout << "Автомат уже включен и ожидает ваших действий.\n";
    }
}

void Automata::off() {
    if (state != OFF) {
        cash = 0;
        chosen_index = -1;
        state = OFF;
        std::cout << "Автомат выключается. Спасибо за использование!\n";
    } else {
        std::cout << "Автомат уже выключен, повторное выключение невозможно.\n";
    }
}

void Automata::coin(int amount) {
    if (state == ON || state == WAITING_FOR_MONEY) {
        cash += amount;
        state = WAITING_FOR_MONEY;
        std::cout << "Внесено " << amount << " монет. Текущий баланс: "
            << cash << " монет.\n";
        std::cout << "Вы можете выбрать напиток из меню.\n";
    } else {
        std::cout << "Извините, автомат сейчас не принимает деньги.\n";
    }
}

void Automata::setMenu(const std::vector<std::string>& drinks, const std::vector<int>& costs) {
    menu = drinks;
    prices = costs;

    std::cout << "Меню напитков обновлено и готово к просмотру:\n";
    for (size_t i = 0; i < menu.size(); ++i) {
        std::cout << "  " << i << ". " << menu[i] << " — стоимость: "
            << prices[i] << " монет.\n";
    }
    std::cout << "Пожалуйста, внесите деньги и выберите желаемый напиток.\n";
}

STATES Automata::getState() const {
    return state;
}

void Automata::choice(int index) {
    if (state == WAITING_FOR_MONEY) {
        if (index >= 0 && index < static_cast<int>(menu.size())) {
            chosen_index = index;
            state = CHECKING_MONEY;
            std::cout << "Вы выбрали напиток: " << menu[chosen_index] << ".\n";
            std::cout << "Проверяем наличие достаточной суммы для оплаты...\n";
        } else {
            std::cout << "Некорректный выбор. Пожалуйста, выберите напиток из меню.\n";
        }
    } else {
        std::cout << "Выбор напитка невозможен в текущем состоянии автомата.\n";
    }
}

bool Automata::check() {
    if (state == CHECKING_MONEY && chosen_index != -1) {
        if (cash >= prices[chosen_index]) {
            std::cout << "Средств достаточно для оплаты напитка.\n";
            return true;
        } else {
            int deficit = prices[chosen_index] - cash;
            std::cout << "Недостаточно средств. Необходимо добавить еще "
                << deficit << " монет.\n";
            return false;
        }
    } else {
        std::cout << "Проверка невозможна в текущем состоянии автомата.\n";
        return false;
    }
}

void Automata::cancel() {
    if (state == WAITING_FOR_MONEY || state == CHECKING_MONEY) {
        std::cout << "Отмена операции. Возвращаем внесённые деньги: "
            << cash << " монет.\n";
        cash = 0;
        chosen_index = -1;
        state = ON;
        std::cout << "Автомат готов к новой операции.\n";
    } else {
        std::cout << "Отмена невозможна: нет активной транзакции.\n";
    }
}

void Automata::cook() {
    if (state == CHECKING_MONEY && chosen_index != -1) {
        if (cash >= prices[chosen_index]) {
            std::cout << "Приготовление напитка \"" << menu[chosen_index] 
                << "\" началось.\n";
            state = COOKING;
            std::cout << "Пожалуйста, подождите...\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } else {
            std::cout << "Невозможно начать приготовление: недостаточно средств.\n";
        }
    } else {
        std::cout << "Приготовление невозможно в текущем состоянии.\n";
    }
}

void Automata::finish() {
    if (state == COOKING) {
        int change = cash - prices[chosen_index];
        if (change > 0) {
            std::cout << "Пожалуйста, заберите сдачу: " << change << " монет.\n";
        }
        std::cout << "Ваш напиток готов! Приятного аппетита!\n";
        cash = 0;
        chosen_index = -1;
        state = ON;
        std::cout << "Автомат готов к следующему клиенту.\n";
    } else {
        std::cout << "Завершение заказа невозможно в текущем состоянии.\n";
    }
}
