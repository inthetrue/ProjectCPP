#include "Directory.h"
#include "Utils.h"
#include <iostream>
#include <string>


// Проверка: является ли символ русской буквой?
bool IsRussianChar(char c) {
    return static_cast<unsigned char>(c) > 127;
}

// Проверка: является ли символ английской буквой?
bool IsEnglishChar(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// ПРОВЕРКА ИМЕНИ
bool IsValidName(const std::string& name) {
    if (name.empty()) return false;
    
    for (char c : name) {
        bool isSpace = (c == ' ');
        bool isEn = IsEnglishChar(c);
        bool isRu = IsRussianChar(c);

        if (!isSpace && !isEn && !isRu) {
            return false;
        }
    }
    return true;
}

// ПРОВЕРКА ТЕЛЕФОНА
bool IsValidPhone(const std::string& phone) {
    if (phone.empty()) return false;
    if (phone == "-") return true;

    for (char c : phone) {
        if (IsEnglishChar(c)) return false;
        if (IsRussianChar(c)) return false;
    }
    return true;
}

// ПРОВЕРКА EMAIL
bool IsValidEmail(const std::string& email) {
    if (email.empty()) return false;
    if (email == "-") return true;

    if (email.find('@') == std::string::npos) return false;

    for (char c : email) {
        if (IsRussianChar(c)) return false;
    }
    
    return true;
}

void PrintContact(int index, const Contact& c) {
    std::cout << "[" << index + 1 << "] "
              << "Имя: " << c.name
              << " | Тел: " << c.phone
              << " | Email: " << c.email << "\n";
}


void AddContact(std::vector<Contact>& contacts) {
    std::cout << "--- Добавление ---\n";
    Contact c;

    while (true) {
        std::string input = GetLineInput("Введите имя: ");
        if (IsValidName(input)) {
            c.name = input;
            break;
        } else {
            std::cout << "Ошибка: Имя должно содержать только буквы (рус/англ).\n";
        }
    }

    while (true) {
        std::string input = GetLineInput("Введите телефон (или '-' если нет): ");
        if (IsValidPhone(input)) {
            c.phone = input;
            break;
        } else {
            std::cout << "Ошибка: Телефон не должен содержать букв.\n";
        }
    }

    while (true) {
        std::string input = GetLineInput("Введите email (или '-' если нет): ");
        if (IsValidEmail(input)) {
            c.email = input;
            break;
        } else {
            std::cout << "Ошибка: Email должен содержать '@' и быть без русских букв.\n";
        }
    }

    contacts.push_back(c);
    std::cout << "Контакт добавлен.\n";
}

void EditContact(std::vector<Contact>& contacts) {
    ShowAll(contacts);
    if (contacts.empty()) return;

    int index = GetIntInput("Редактировать № (0 - отмена): ");
    if (index > 0 && index <= (int)contacts.size()) {
        Contact& c = contacts[index - 1];
        
        while (true) {
            std::string input = GetLineInput("Имя (" + c.name + "): ");
            if (input.empty()) break;

            if (IsValidName(input)) {
                c.name = input;
                break;
            } else {
                std::cout << "Ошибка: Имя должно содержать только буквы.\n";
            }
        }

        while (true) {
            std::string input = GetLineInput("Тел (" + c.phone + ") или '-': ");
            if (input.empty()) break;

            if (IsValidPhone(input)) {
                c.phone = input;
                break;
            } else {
                std::cout << "Ошибка: Телефон не должен содержать букв.\n";
            }
        }

        while (true) {
            std::string input = GetLineInput("Email (" + c.email + ") или '-': ");
            if (input.empty()) break;

            if (IsValidEmail(input)) {
                c.email = input;
                break;
            } else {
                std::cout << "Ошибка: Некорректный email (нужна '@', без кириллицы).\n";
            }
        }
        
        std::cout << "Обновлено.\n";
    }
}

void ShowAll(const std::vector<Contact>& contacts) {
    if (contacts.empty()) {
        std::cout << "Справочник пуст.\n";
        return;
    }
    std::cout << "--- Список ---\n";
    for (size_t i = 0; i < contacts.size(); ++i) {
        PrintContact(i, contacts[i]);
    }
}

void SearchByName(const std::vector<Contact>& contacts) {
    std::string query = GetLineInput("Поиск (введите имя или часть имени): "); 
    bool found = false;

    for (size_t i = 0; i < contacts.size(); ++i) {
        if (contacts[i].name.find(query) != std::string::npos) {
            PrintContact(i, contacts[i]);
            found = true;
        }
    }
    if (!found) std::cout << "Ничего не найдено.\n";
}

void DeleteContact(std::vector<Contact>& contacts) {
    ShowAll(contacts);
    if (contacts.empty()) return;

    while (true) {
        int index = GetIntInput("Удалить № (0 - отмена): ");

        if (index == 0) {
            std::cout << "Удаление отменено.\n";
            return;
        }

        // Проверка на выход за границы (меньше 1 или больше размера списка)
        if (index < 1 || index > static_cast<int>(contacts.size())) {
            std::cout << "Ошибка: Контакта с номером " << index << " не существует.\n";
            std::cout << "Пожалуйста, введите число от 1 до " << contacts.size() << ".\n";
        } 
        else {
            contacts.erase(contacts.begin() + index - 1);
            std::cout << "Контакт удален.\n";
            break;
        }
    }
}

void SortByName(std::vector<Contact>& contacts) {
    if (contacts.empty()) {
        std::cout << "Справочник пуст.\n";
        return;
    }

    std::cout << "Выберите тип сортировки:\n";
    std::cout << "1. По алфавиту (А-Я)\n";
    std::cout << "2. В обратном порядке (Я-А)\n";
    int choice = GetIntInput("Ваш выбор: ");

    bool descending = (choice == 2);

    bool swapped;
    size_t n = contacts.size();
    for (size_t i = 0; i < n - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
            
            bool needSwap = false;

            if (descending) {
                // Если Я-А: меняем, если текущий МЕНЬШЕ следующего
                if (contacts[j].name < contacts[j + 1].name) {
                    needSwap = true;
                }
            } else {
                // Если А-Я: меняем, если текущий БОЛЬШЕ следующего
                if (contacts[j].name > contacts[j + 1].name) {
                    needSwap = true;
                }
            }

            if (needSwap) {
                Contact temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    if (descending) std::cout << "Список отсортирован в обратном порядке (Я-А).\n";
    else            std::cout << "Список отсортирован по алфавиту (А-Я).\n";
}