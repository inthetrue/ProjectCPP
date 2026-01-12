#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include "Contact.h"

void SaveToFile(const std::vector<Contact>& contacts, const std::string& filename);
void LoadFromFile(std::vector<Contact>& contacts, const std::string& filename);

#endif 