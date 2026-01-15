#include "FileManager.h"
#include "Utils.h"
#include "Directory.h"
#include <fstream>
#include <iostream>

void SaveToFile(const std::vector<Contact>& contacts, const std::string& filename) {
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
        return; 
    }

    size_t count;
    if (!(file >> count)) {
        return;
    }
    
    file.ignore(); // Пропускаем символ новой строки после числа count

    if (count == 0) {
        contacts.clear();
        return;
    }

    contacts.clear(); // Чистим старый список перед загрузкой
    
    int loadedCount = 0;
    int skippedCount = 0;

    for (size_t i = 0; i < count; ++i) {
        std::string tName, tPhone, tEmail;

        std::getline(file, tName);
        std::getline(file, tPhone);
        std::getline(file, tEmail);
        
        bool isNameOk = IsValidName(tName);
        bool isPhoneOk = IsValidPhone(tPhone);
        bool isEmailOk = IsValidEmail(tEmail);

        if (isNameOk && isPhoneOk && isEmailOk) {
            Contact c;
            c.name = tName;
            c.phone = tPhone;
            c.email = tEmail;
            contacts.push_back(c);
            loadedCount++;
        } else {
            // Если данные повреждены, мы их пропускаем
            skippedCount++;
        }
    }

    std::cout << "Загружено контактов: " << loadedCount << ".\n";
    
    if (skippedCount > 0) {
        std::cout << "Файл содержит ошибки\n";
    }
    
    file.close();
}