#ifndef UTILS_H
#define UTILS_H

#include <string>

int GetIntInput(const std::string& prompt);
std::string GetLineInput(const std::string& prompt);
void PauseConsole();
void ClearConsole();

#endif