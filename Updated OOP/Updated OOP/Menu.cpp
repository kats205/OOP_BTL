#include "Menu.h"
#include <iostream>
using namespace std;

void Menu::displayHeader(const string& title) {
#ifndef DEBUG
    system("cls");  // Reset màn hình
#endif
    cout << "\033[1;36m";  // Màu xanh dương sáng
    cout << "=========================================================================================================================================\n";

    string bankName = "W3O BANK";
    int width = 140; // Độ rộng của khung
    int bankPadding = (width - bankName.length()) / 2;
    cout << "||" << string(bankPadding, ' ') << bankName
        << string(width - bankPadding - bankName.length() - 7, ' ') << "||\n";

    cout << "=========================================================================================================================================\n";

    int titlePadding = (width - title.length()) / 2;
    cout << "||" << string(titlePadding, ' ') << title
        << string(width - titlePadding - title.length() - 7, ' ') << "||\n";

    cout << "=========================================================================================================================================\n";
    cout << "\033[0m";  // Reset lại màu sắc
}

void Menu::showMenu() {
    cout << "\033[1;34m"; // Màu xanh dương sáng cho tiêu đề

    // Căn giữa khung tiêu đề bằng cách thêm khoảng trắng
    cout << "                                                            +---------------------+\n";
    cout << "                                                            |    W3O BANK MENU    |\n";
    cout << "                                                            +---------------------+\n";

    cout << "\033[0m"; // Reset lại màu sắc

    // Khung lựa chọn với các ký tự khác và ngắn hơn
    cout << "\033[1;32m";  // Màu xanh lá sáng cho khung
    cout << "                                                    +-------------------------------------+\n";
    cout << "                                                    | 1. Register                         |\n";
    cout << "                                                    +-------------------------------------+\n";
    cout << "                                                    | 2. Login                            |\n";
    cout << "                                                    +-------------------------------------+\n";
    cout << "                                                    | 3. Exit                             |\n";
    cout << "                                                    +-------------------------------------+\n";
    cout << "\033[0m"; // Reset lại màu sắc

    cout << ">> Choose an option: ";
}

void Menu::showMenuLoginAfter() {
    cout << "\033[1;34m"; // Màu xanh dương sáng cho tiêu đề

    // Căn giữa khung tiêu đề bằng cách thêm khoảng trắng
    cout << "                                                            +---------------------+\n";
    cout << "                                                            |    W3O BANK MENU    |\n";
    cout << "                                                            +---------------------+\n";

    cout << "\033[0m"; // Reset lại màu sắc

    // Khung lựa chọn với các ký tự khác và ngắn hơn
    cout << "\033[1;32m";  // Màu xanh lá sáng cho khung
    cout << "                                                    +---------------------------------------+\n";
    cout << "                                                    | 1. Deposit                            |\n";
    cout << "                                                    +---------------------------------------+\n";
    cout << "                                                    | 2. Withdraw                           |\n";
    cout << "                                                    +---------------------------------------+\n";
    cout << "                                                    | 3. Transfer                           |\n";
    cout << "                                                    +---------------------------------------+\n";
    cout << "                                                    | 4. Check Balance                      |\n";
    cout << "                                                    +---------------------------------------+\n";
    cout << "                                                    | 5. Transaction History                |\n"; // Thêm tùy chọn này
    cout << "                                                    +---------------------------------------+\n";
    cout << "                                                    | 6. Logout                             |\n";
    cout << "                                                    +---------------------------------------+\n";
    cout << "\033[0m"; // Reset lại màu sắc

    cout << ">> Choose an option: ";
}
