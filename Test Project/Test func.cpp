#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

// Hàm tạo mã giao dịch ngẫu nhiên 6 chữ số
string generateTransactionID() {
    int transactionID = rand() % 900000 + 100000; // Tạo số ngẫu nhiên từ 100000 đến 999999
    return to_string(transactionID);
}

// Hàm lấy ngày giờ hiện tại theo định dạng dd/MM/yy hh:mm
string getCurrentDateTime() {
    time_t now = time(0); 
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << setw(2) << setfill('0') << ltm->tm_mday << "/"
       << setw(2) << setfill('0') << (ltm->tm_mon + 1) << "/"
       << setw(2) << setfill('0') << (ltm->tm_year % 100) << " "
       << setw(2) << setfill('0') << ltm->tm_hour << ":"
       << setw(2) << setfill('0') << ltm->tm_min;
    return ss.str();
}

// Hàm thông báo biến động số dư
void notifyTransaction(const string& accountNumber, int amount, int balance, 
                       const string& receiverName, const string& receiverPhone, 
                       const string& senderName, bool isTransfer) {
    string maskedAccount = accountNumber.substr(0, 2) + "xxxxx" + accountNumber.substr(accountNumber.size() - 3);
    string amountStr = (amount < 0 ? "-" : "+") + to_string(abs(amount)) + "VND";
    string balanceStr = to_string(balance) + "VND";
    string dateTime = getCurrentDateTime();
    string transactionType = senderName + (isTransfer ? " chuyen tien" : " nhan tien");
    string transactionID = generateTransactionID();

    cout << "TK " << maskedAccount << " | GD: " << amountStr << " " << dateTime 
         << " | SD: " << balanceStr << endl;
    cout << "Den: " << receiverName << " - " << receiverPhone << endl;
    cout << "ND: " << transactionType << " - Ma giao dich/ " << transactionID << endl;
}

int main() {
    // Thiết lập seed cho hàm tạo số ngẫu nhiên
    srand(time(0));

    // Ví dụ về dữ liệu giao dịch
    string accountNumber = "0301234510";
    int amount = -10000; // Số tiền giao dịch (âm nếu chuyển tiền, dương nếu nhận tiền)
    int balance = 450304; // Số dư còn lại trong tài khoản sau giao dịch
    string receiverName = "NGUYEN VUONG KHANG";
    string receiverPhone = "0935405515";
    string senderName = "NGUYEN PHAM BAO KHANH";
    bool isTransfer = true; // true nếu là chuyển tiền, false nếu là nhận tiền

    // Gọi hàm để hiển thị thông báo giao dịch
    notifyTransaction(accountNumber, amount, balance, receiverName, receiverPhone, senderName, isTransfer);

    return 0;
}
