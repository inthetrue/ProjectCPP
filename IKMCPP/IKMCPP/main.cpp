#include <iostream>
#include <vector>
#include "Contact.h"
#include "Directory.h"
#include "FileManager.h"
#include "Utils.h"

const std::string DB_FILENAME = "phonebook_data.txt";

int main() {
    setlocale(LC_ALL, "");

    std::vector<Contact> myContacts;

    LoadFromFile(myContacts, DB_FILENAME);

    bool running = true;
    while (running) {
        ClearConsole();
        std::cout << "--- Телефонный справочник ---\n";
        std::cout << "1. Список\n";
        std::cout << "2. Добавить\n";
        std::cout << "3. Найти\n";
        std::cout << "4. Изменить\n";
        std::cout << "5. Удалить\n";
        std::cout << "6. Сортировать\n";
        std::cout << "7. Сохранить\n";
        std::cout << "8. Загрузить заново\n";
        std::cout << "0. Выход\n";
        std::cout << "------------------------------\n";

        int choice = GetIntInput("Выбор: ");

        switch (choice) {
            case 1: ShowAll(myContacts); break;
            case 2: AddContact(myContacts); break;
            case 3: SearchByName(myContacts); break;
            case 4: EditContact(myContacts); break;
            case 5: DeleteContact(myContacts); break;
            case 6: SortByName(myContacts); break;
            case 7: SaveToFile(myContacts, DB_FILENAME); break;
            case 8: LoadFromFile(myContacts, DB_FILENAME); break;
            case 0:
                {
                    std::string ans = GetLineInput("Сохранить? (y/n): ");
                    if (ans == "y" || ans == "Y") {
                        SaveToFile(myContacts, DB_FILENAME);
                    }
                }
                running = false;
                break;
            default: std::cout << "Неверный ввод.\n";
        }

        if (running) PauseConsole();
    }

    return 0;
}