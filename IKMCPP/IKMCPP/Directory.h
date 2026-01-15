#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <vector>
#include <string> 
#include "Contact.h"


void AddContact(std::vector<Contact>& contacts);
void ShowAll(const std::vector<Contact>& contacts);
void SearchByName(const std::vector<Contact>& contacts);
void DeleteContact(std::vector<Contact>& contacts);
void EditContact(std::vector<Contact>& contacts);
void SortByName(std::vector<Contact>& contacts);


void PrintContact(int index, const Contact& c);
bool IsValidEmail(const std::string& email);
bool IsValidName(const std::string& name);
bool IsValidPhone(const std::string& phone);
bool IsRussianChar(char c);
bool IsEnglishChar(char c);

#endif