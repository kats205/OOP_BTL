#pragma once
#include <string>

using namespace std;

struct Transaction {
    string dateTime;      // Th?i gian giao d?ch
    string type;          // Lo?i giao d?ch: "Deposit", "Withdraw", "Transfer Sent", "Transfer Received"
    double amount;             // S? ti?n giao d?ch
    double balanceAfter;       // S? d? sau giao d?ch
    string details;       // Chi ti?t giao d?ch (ví d?: s? ?i?n tho?i ng??i nh?n/ g?i)
};
