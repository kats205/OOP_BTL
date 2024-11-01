#include "ATM.h"
#include <iostream>


using namespace std;

int main() {
    ATM atm;
    atm.run();

    // Thêm dòng sau ?? d?ng l?i tr??c khi k?t thúc ch??ng trình
    cout << "Press Enter to exit...";
    cin.ignore();  // B? qua ký t? enter tr??c ?ó (n?u có)
    cin.get();     // Ch? ng??i dùng nh?n Enter ?? thoát
    return 0;

}