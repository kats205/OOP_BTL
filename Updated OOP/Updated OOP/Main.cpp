#include "ATM.h"
#include <iostream>


using namespace std;

int main() {
    ATM atm;
    atm.run();
    cout << "Press Enter to exit...";
    cin.ignore();  
    cin.get();    
    return 0;

}