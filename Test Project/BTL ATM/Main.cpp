#include<iostream>
#include "ATM.h"

using namespace std;

int main() {
    ATM atm;
    atm.run();

    // Thêm dòng sau để dừng lại trước khi kết thúc chương trình
    cout << "Press Enter to exit...";
    cin.ignore();  // Bỏ qua ký tự enter trước đó (nếu có)
    cin.get();     // Chờ người dùng nhấn Enter để thoát
    return 0;

}