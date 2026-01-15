#include "Utils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>

int GetIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            // Очищаем буфер после ввода числа, чтобы следующий getline не считал пустую строку
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cout << "Ошибка: введите число.\n";
            std::cin.clear(); // Сброс флага ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
        }
    }
}

std::string GetLineInput(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

void PauseConsole() {
    std::cout << "\nНажмите Enter, чтобы продолжить...";
    std::cin.get();
}

void ClearConsole() {
    // Простой способ очистки для большинства систем
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
// то есть, чтобы текст не полз вниз, а очищался как приложение