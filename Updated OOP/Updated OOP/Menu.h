#pragma once
#include <string>
#include <iostream>

class Menu {
public:
    static void displayHeader(const std::string& title);
    static void showMenu();
    static void showMenuLoginAfter();
};
