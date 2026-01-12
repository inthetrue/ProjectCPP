#include "FileManager.h"
#include <fstream>
#include <iostream>

void SaveToFile(const std::vector<Contact>& contacts, const std::string& filename) {
    // Если список пуст, не создаем пустой файл
    if (contacts.empty()) {
        std::cout << "Справочник пуст, сохранять нечего.\n";
        return;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи.\n";
        return;
    }

    file << contacts.size() << "\n";

    for (const auto& contact : contacts) {
        file << contact.name << "\n";
        file << contact.phone << "\n";
        file << contact.email << "\n";
    }

    std::cout << "Данные успешно сохранены в " << filename << " (" << contacts.size() << " зап.).\n";
    file.close();
}

void LoadFromFile(std::vector<Contact>& contacts, const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Файл " << filename << " не найден (справочник пуст).\n";
        return;
    }

    size_t count;
    
    if (!(file >> count)) {
        std::cout << "Файл " << filename << " пуст или поврежден (не удалось прочитать данные).\n";
        return;
    }
    
    file.ignore(); // Пропускаем перевод строки после числа

    if (count == 0) {
        std::cout << "Файл загружен, но список контактов пуст.\n";
        contacts.clear();
        return;
    }

    contacts.clear(); // Чистим старый список перед загрузкой
    for (size_t i = 0; i < count; ++i) {
        Contact c;
        std::getline(file, c.name);
        std::getline(file, c.phone);
        std::getline(file, c.email);
        
        // Защита от пустых строк
        if (!c.name.empty()) {
            contacts.push_back(c);
        }
    }

    std::cout << "Успешно загружено контактов: " << contacts.size() << ".\n";
    file.close();
}