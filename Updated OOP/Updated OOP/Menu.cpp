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
    // Hiển thị tiêu đề lớn "W3O MENU" bằng ASCII Art với màu cầu vồng
    string title[] = {
           " __          __ ____    ____    __  __  ______  _   _  _    _ ",
           " \\ \\        / /|___ \\  / __ \\  |  \\/  ||  ____|| \\ | || |  | |",
           "  \\ \\  /\\  / /   __) || |  | | | \\  / || |__   |  \\| || |  | |",
           "   \\ \\/  \\/ /   |__ < | |  | | | |\\/| ||  __|  | . ` || |  | |",
           "    \\  /\\  /    ___) || |__| | | |  | || |____ | |\\  || |__| |",
           "     \\/  \\/    |____/  \\____/  |_|  |_||______||_| \\_| \\____/ "
    };

    // Khung vàng sáng bao quanh tiêu đề
    cout << "\033[1;33m"; // Màu vàng sáng
    cout << "                                        +---------------------------------------------------------------+\n";

    // Hiển thị tiêu đề với màu sắc cầu vồng
    srand(time(0)); // Seed ngẫu nhiên cho màu sắc
    for (string line : title) {
        cout << "\033[1;33m                                        |";
        for (char c : line) {
            int colorCode = rand() % 6 + 31; // Mã màu từ 31 đến 36 (đỏ, xanh lá, vàng, xanh lam, tím, xanh ngọc)
            cout << "\033[1;" << colorCode << "m" << c; // Áp dụng màu ngẫu nhiên cho từng ký tự
        }
        cout << "\033[0m"; // Reset màu về mặc định
        cout << "\033[1;33m |\n";
    }

    cout << "\033[1;33m"; // Màu vàng sáng cho khung
    cout << "                                        +---------------------------------------------------------------+\n";
    cout << "\033[0m"; // Reset màu sắc

    // Khung lựa chọn với các ký tự khác và ngắn hơn
    cout << "\033[1;32m";  // Màu xanh lá sáng cho khung
    cout << "                                                   +-------------------------------------+\n";
    cout << "                                                   |          [==>] 1. Register          |\n";
    cout << "                                                   +-------------------------------------+\n";
    cout << "                                                   |          [==>] 2. Login             |\n";
    cout << "                                                   +-------------------------------------+\n";
    cout << "                                                   |          [==>] 3. Exit              |\n";
    cout << "                                                   +-------------------------------------+\n";
    cout << "\033[0m"; // Reset lại màu sắc

    cout << ">> Choose an option: ";
}

void Menu::showMenuLoginAfter() {
    // Hiển thị tiêu đề lớn "W3O MENU" bằng ASCII Art với màu cầu vồng
    string title[] = {
           " __          __ ____    ____    __  __  ______  _   _  _    _ ",
           " \\ \\        / /|___ \\  / __ \\  |  \\/  ||  ____|| \\ | || |  | |",
           "  \\ \\  /\\  / /   __) || |  | | | \\  / || |__   |  \\| || |  | |",
           "   \\ \\/  \\/ /   |__ < | |  | | | |\\/| ||  __|  | . ` || |  | |",
           "    \\  /\\  /    ___) || |__| | | |  | || |____ | |\\  || |__| |",
           "     \\/  \\/    |____/  \\____/  |_|  |_||______||_| \\_| \\____/ "
    };

    // Khung vàng sáng bao quanh tiêu đề
    cout << "\033[1;33m"; // Màu vàng sáng
    cout << "                                        +---------------------------------------------------------------+\n";

    // Hiển thị tiêu đề với màu sắc cầu vồng
    srand(time(0)); // Seed ngẫu nhiên cho màu sắc
    for (string line : title) {
        cout << "                                        |";
        for (char c : line) {
            int colorCode = rand() % 6 + 31; // Mã màu từ 31 đến 36 (đỏ, xanh lá, vàng, xanh lam, tím, xanh ngọc)
            cout << "\033[1;" << colorCode << "m" << c; // Áp dụng màu ngẫu nhiên cho từng ký tự
        }
        cout << "\033[0m"; // Reset màu về mặc định
        cout << " |\n";
    }

    cout << "\033[1;33m"; // Màu vàng sáng cho khung
    cout << "                                        +---------------------------------------------------------------+\n";
    cout << "\033[0m"; // Reset màu sắc

    // Phần menu giữ nguyên
    cout << "\033[1;32m";  // Màu xanh lá sáng cho dấu |
    cout << "                                                   +---------------------------------------+\n";
    cout << "                                                   |\033[0m";
    cout << "\033[1;37m     [==>] 1. Deposit                  "; // Mũi tên → phía trước
    cout << "\033[1;32m|\n"; // Đóng màu xanh lá
    cout << "                                                   +---------------------------------------+\n";
    cout << "                                                   |\033[0m";
    cout << "\033[1;37m     [==>] 2. Withdraw                 ";
    cout << "\033[1;32m|\n";
    cout << "                                                   +---------------------------------------+\n";
    cout << "                                                   |\033[0m";
    cout << "\033[1;37m     [==>] 3. Transfer                 ";
    cout << "\033[1;32m|\n";
    cout << "                                                   +---------------------------------------+\n";
    cout << "                                                   |\033[0m";
    cout << "\033[1;37m     [==>] 4. Check Balance            ";
    cout << "\033[1;32m|\n";
    cout << "                                                   +---------------------------------------+\n";
    cout << "                                                   |\033[0m";
    cout << "\033[1;37m     [==>] 5. Transaction History      ";
    cout << "\033[1;32m|\n";
    cout << "                                                   +---------------------------------------+\n";
    cout << "                                                   |\033[0m";
    cout << "\033[1;37m     [==>] 6. Logout                   ";
    cout << "\033[1;32m|\n";
    cout << "                                                   +---------------------------------------+\n";
    cout << "\033[0m";  // Reset lại màu sắc

    cout << ">> Choose an option: ";
}