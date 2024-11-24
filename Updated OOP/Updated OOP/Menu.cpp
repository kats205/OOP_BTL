#include "Menu.h"
#include <iostream>
using namespace std;

void Menu::displayHeader(const string& title) {
#ifndef DEBUG
    system("cls");  // Reset màn hình
#endif
    // Sử dụng màu sắc dễ nhìn, ít "màu mè"
    cout << "\033[1;34m";  // Màu xanh dương đậm cho phần tiêu đề và khung

    // In khung bao quanh
    cout << "=========================================================================================================================================\n";

    // In tên ngân hàng với font đẹp mắt
    string bankName = "W3O BANK";
    int width = 140; // Điều chỉnh độ rộng khung phù hợp
    int bankPadding = (width - bankName.length()) / 2;
    cout << "||" << string(bankPadding, ' ') << "\033[1;32m" << bankName << "\033[1;34m"
        << string(width - bankPadding - bankName.length() - 7, ' ') << "||\n";  // Dùng màu xanh lá cho tên ngân hàng

    // In đường viền dưới tên ngân hàng
    cout << "=========================================================================================================================================\n";

    // In tiêu đề, có màu khác biệt để làm nổi bật
    int titlePadding = (width - title.length()) / 2;
    cout << "||" << string(titlePadding, ' ') << "\033[1;33m" << title << "\033[1;34m"
        << string(width - titlePadding - title.length() - 7, ' ') << "||\n";  // Dùng màu vàng cho tiêu đề

    // In đường viền dưới tiêu đề
    cout << "=========================================================================================================================================\n";

    // Reset lại màu sắc sau khi in khung
    cout << "\033[0m";  // Đặt lại màu sắc cho phần còn lại
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

    // Khung xanh dương đậm bao quanh tiêu đề
    cout << "\033[1;34m"; // Màu xanh dương đậm
    cout << "                                        +---------------------------------------------------------------+\n";

    // Hiển thị tiêu đề với màu sắc cầu vồng
    srand(time(0)); // Seed ngẫu nhiên cho màu sắc
    for (string line : title) {
        cout << "\033[1;34m                                        |";
        for (char c : line) {
            cout << "\033[1;33m" << c; // Áp dụng màu vàng cho từng ký tự
        }

        cout << "\033[0m"; // Reset màu về mặc định
        cout << "\033[1;34m |\n";
    }

    cout << "\033[1;34m"; // Màu xanh dương đậm cho khung
    cout << "                                        +---------------------------------------------------------------+\n";
    cout << "\033[0m"; // Reset màu sắc


    // Khung lựa chọn với các ký tự khác và ngắn hơn
    cout << "\033[1;32m";  // Màu xanh lá sáng cho khung
    cout << "                                                   +-------------------------------------+\n";
    cout << "                                                   |          ";
    cout << "\033[1;37m[==>] 1. Register          " << "\033[1;32m| \n";
    cout << "                                                   +-------------------------------------+\n";
    cout << "                                                   |          ";
    cout << "\033[1;37m[==>] 2. Login             " << "\033[1;32m| \n";
    cout << "                                                   +-------------------------------------+\n";
    cout << "                                                   |          ";
    cout << "\033[1;37m[==>] 3. Exit              " << "\033[1;32m| \n";
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