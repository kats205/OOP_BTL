#include "ATM.h"
#include <iostream>


using namespace std;

int main() {
    ATM atm;
    atm.run();

    // Th�m d�ng sau ?? d?ng l?i tr??c khi k?t th�c ch??ng tr�nh
    cout << "Press Enter to exit...";
    cin.ignore();  // B? qua k� t? enter tr??c ?� (n?u c�)
    cin.get();     // Ch? ng??i d�ng nh?n Enter ?? tho�t
    return 0;

}