#include "ATM.h"
#include "Menu.h"
#include "Transaction.h"
#include <iostream>
 

using namespace std;

ATM::ATM() : loggedInUser(nullptr) {
    // Tạo file `user.txt` nếu không tồn tại
    ofstream userFile("user.txt", ios::app);
    userFile.close(); // Đóng file sau khi mở

    // Tạo file `userHistory.txt` nếu không tồn tại
    ofstream historyFile("userHistory.txt", ios::app);
    historyFile.close(); // Đóng file sau khi mở
}

void ATM::run() {
    loadUsersFromFile();  // Load users from file at startup
    int choice;
    do {
        Menu::displayHeader("<<WELCOME TO W3O BANK>>");
        Menu::showMenu();
        cin >> choice;
        switch (choice) {
        case 1: registerUser(); 
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            break;
        case 2: login(); 
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            break;
        case 3: cout << "Goodbye!" << endl;
            break;
        default: cout << "Invalid choice, try again." << endl;
            cout << ">> Choose an option: ";
            break;
        }
    } while (choice != 3);
}

void ATM::registerUser() {
    Menu::displayHeader("Register");
    string username, password, pin;
    string numbers = inputPhoneNumber();
    if (numbers == "N/A") return;
    cout << "Your phone number is valid\n" << endl;
    cout << "Enter the user name: ";
    //cin.ignore();
    getline(cin, username);
    cout << endl;
    char ch;
    // Nhập mật khẩu với kiểm tra
    do {
        password.clear(); // Xóa mật khẩu để nhập lại nếu không hợp lệ
        bool showPassword = false;
        cout << "Enter password (Press '/' to toggle visibility): ";

        while ((ch = _getch()) != 13) { // Nhấn Enter để kết thúc nhập
            if (ch == 8) { // Nhấn Backspace để xóa ký tự
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b"; // Xóa dấu * trên màn hình
                }
            }
            else if (ch == 127) { // Nhấn Delete để xóa ký tự tiếp theo
                if (!password.empty()) {
                    cout << "\b \b"; // Xóa dấu * trên màn hình
                    password.pop_back();
                }
            }
            else if (ch == '/') { // Nhấn '/' để toggle hiển thị mật khẩu
                showPassword = !showPassword; // Chuyển đổi chế độ hiển thị
                cout << "\n" << (showPassword ? "Password: " : "Password: "); // In lại thông báo
                for (char p : password) {
                    cout << (showPassword ? p : '*'); // Hiển thị mật khẩu hoặc dấu *
                }
                cout << "\nEnter password (Press '/' to toggle visibility): ";
                cout << string(100, ' ') << "\r"; // Xóa dòng con trỏ
                cout << (showPassword ? "Password: " : "Password: "); // In lại thông báo
                for (char p : password) {
                    cout << (showPassword ? p : '*'); // Hiển thị mật khẩu hoặc dấu *
                }
            }
            else {
                password.push_back(ch);
                if (!showPassword) {
                    cout << '*'; // Hiển thị dấu *
                }
                else {
                    cout << ch; // Hiển thị ký tự thật
                }
            }
        }
        cout << endl; // Xuống dòng sau khi nhập xong

        // Kiểm tra mật khẩu sau khi nhập xong
    } while (!validatePassword(password));
    // Nếu đã nhập mật khẩu hợp lệ
    cout << "Password is valid. Password entered successfully!\n";

    cout << endl; // Xuống dòng

    int lent;
    do {
        cout << "Set your transaction PIN(6 digits): ";
        cin >> pin;
        lent = pin.size();
        if (lent != 6) cout << "Your pin just have 6 digits!\n";
    } while (lent != 6);

    cout << endl;

    UserAccount newUser(numbers, 0, username, numbers, password, pin);
    users.push_back(newUser);
    saveUserToFile(newUser);  // Lưu người dùng vào tệp

    cout << "User registered successfully!\n";
}

void ATM::login() {
    Menu::displayHeader("Login");

    string numbers, password;
    cout << "Enter your account's number: ";
    cin >> numbers;
    cout << "Enter your account's password: ";
    char ch;
    while ((ch = _getch()) != 13) { // Nhấn Enter để kết thúc nhập
        if (ch == 8) { // Nhấn Backspace để xóa ký tự
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Xóa dấu * trên màn hình
            }
        }
        else if (ch == 127) { // Nhấn Delete để xóa ký tự tiếp theo
            // Không thực hiện gì nếu không có ký tự nào để xóa
            if (!password.empty()) {
                // Xóa ký tự cuối cùng
                cout << "\b \b"; // Xóa dấu * trên màn hình
                password.pop_back();
            }
        }
        else {
            password.push_back(ch);
            cout << '*'; // Hiển thị dấu *
        }
    }
    cout << endl; // Xuống dòng

    for (UserAccount& user : users) {
        if (user.getPhoneNumber() == numbers && user.getPassword(password)) {
            loggedInUser = &user;
            cout << "Login successful!\n";
            // Thêm dòng sau ?? d?ng l?i tr??c khi k?t thúc ch??ng trình
            cout << "Press Enter to login...";
            cin.ignore();  // B? qua ký t? enter tr??c ?ó (n?u có)
            cin.get();     // Ch? ng??i dùng nh?n Enter ?? thoát
            system("cls");
            loginAfter();
            return;
        }
    }
    cout << "Invalid phone numbers or password.\n";
}

void ATM::loginAfter() {
    int choice;
    do {
        Menu::displayHeader("User Login Account");
        Menu::showMenuLoginAfter();
        cin >> choice;

        switch (choice) {
        case 1: deposit();
            cout << "Press Enter to return to menu...";
            cin.ignore();  
            cin.get();
            break;
        case 2: withdraw();
            cout << "Press Enter to return to menu...";
            cin.ignore(); 
            cin.get();
            break;
        case 3: transfer();
            cout << "Press Enter to return to menu...";
            cin.ignore();  
            cin.get();
            break;
        case 4: checkBalance();
            cout << "Press Enter to return to menu...";
            cin.ignore();  
            cin.get();
            break;
        case 5: transactionHistory(); // Thêm tùy chọn này
            cout << "\nPress Enter to return to menu...";
            cin.ignore();
            cin.get();
            break;
        case 6: logout();
            break;
        default: cout << "Invalid choice, try again." << endl; break;
        }

    } while (choice != 6);
}


void ATM::logout() {
    Menu::displayHeader("Logout");
    if (loggedInUser == nullptr) {
        cout << "You are not logged in.\n";
        return;
    }
    loggedInUser = nullptr;
    cout << "Logged out successfully.\n";
}

void ATM::deposit() {
    Menu::displayHeader("Deposit");
    string pin;
    do {
        cout << "Enter your transaction PIN: ";
        cin >> pin;

        if (!loggedInUser->getTransactionPIN(pin)) {
            cout << "Incorrect PIN. Transaction failed, please try again!\n";
        }
    } while (!loggedInUser->getTransactionPIN(pin));

    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    if (amount < 0) {
        cout << "Sorry, the transfer amount cannot be negative, please try again!\n";
        return;
    }

    loggedInUser->deposit(amount);
    cout << "Deposit successful! Your new balance is: " << loggedInUser->getBalance() << "\n";

    // Tạo giao dịch và thêm vào lịch sử
    Transaction txn;
    txn.dateTime = getCurrentDateTime();
    txn.type = "Deposit";
    txn.amount = amount;
    txn.balanceAfter = loggedInUser->getBalance();
    txn.details = "N/A";
    loggedInUser->addTransaction(txn);

    // Ghi giao dịch vào file lịch sử
    balanceFluctuation(*loggedInUser, txn);

    saveAllUsersToFile();
}


void ATM::withdraw() {
    Menu::displayHeader("Withdraw");

    string pin;
    do {
        cout << "Enter your transaction PIN: ";
        cin >> pin;

        if (!loggedInUser->getTransactionPIN(pin)) {
            cout << "Incorrect PIN. Transaction failed, please try again!\n";
        }
    } while (!loggedInUser->getTransactionPIN(pin));

    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    if (amount < 0) {
        cout << "Sorry, the transfer amount cannot be negative, please try again!\n";
        return;
    }

    if (loggedInUser->withdraw(amount)) {
        cout << "Withdrawal successful! Your new balance is: " << loggedInUser->getBalance() << "\n";

        // Tạo giao dịch và thêm vào lịch sử
        Transaction txn;
        txn.dateTime = getCurrentDateTime();
        txn.type = "Withdraw";
        txn.amount = amount;
        txn.balanceAfter = loggedInUser->getBalance();
        txn.details = "N/A";
        loggedInUser->addTransaction(txn);

        // Ghi giao dịch vào file lịch sử
        balanceFluctuation(*loggedInUser, txn);

        saveAllUsersToFile();
    }
    else {
        cout << "Insufficient balance.\n";
    }
}


void ATM::transfer() {
    Menu::displayHeader("Transfer");

    string receiverNumbers, pin;
    double amount;

    cout << "Enter recipient's phone number: ";
    cin >> receiverNumbers;
    cout << "Enter amount to transfer: ";
    cin >> amount;
    if (amount < 0) {
        cout << "Sorry, the transfer amount cannot be negative, please try again!\n";
        return;
    }

    do {
        cout << "Enter your transaction PIN: ";
        cin >> pin;

        if (!loggedInUser->getTransactionPIN(pin)) {
            cout << "Incorrect PIN. Transaction failed, please re-enter!\n";
        }
    } while (!loggedInUser->getTransactionPIN(pin));

    // Kiểm tra nhập OTP được gửi về máy
    int otp = generateOTP(); // Tạo mã OTP
    cout << "An OTP has been sent to your registered device: " << setw(6) << setfill('0') << otp << endl; // Đảm bảo mã OTP luôn có 6 chữ số
    int userInput;
    do {
        cout << "Enter OTP code to confirm money transfer: ";
        cin >> userInput;
        if (userInput == otp) {
            // Kiểm tra người nhận có tồn tại hay không
            bool recipientFound = false;
            for (UserAccount& user : users) {
                if (user.getPhoneNumber() == receiverNumbers) {
                    recipientFound = true;

                    // Kiểm tra nếu người gửi có đủ tiền để chuyển
                    if (loggedInUser->withdraw(amount)) {
                        user.deposit(amount);
                        cout << "\033[1;35m";
                        cout << "\n|=======================================================================================================================================|" << "\n";
                        cout << "\033[1;37m" << "                                      Transfer to " << user.getUserName() << " successful! -" << amount << " VND\n";
                        cout << "\033[1;35m";
                        cout << "|---------------------------------------------------------------------------------------------------------------------------------------|" << "\n";
                        cout << "                                               >>[Receiver]:      " << "\033[1;37m" << user.getPhoneNumber() << "\n";
                        cout << "\033[1;35m";
                        cout << "|---------------------------------------------------------------------------------------------------------------------------------------|" << "\n";
                        cout << "                                               >>[Recipient Name]:      " << "\033[1;37m" << user.getUserName() << "\n";
                        cout << "\033[1;35m";
                        cout << "|---------------------------------------------------------------------------------------------------------------------------------------|" << "\n";
                        cout << "                                               >>[Amount]:       " << "\033[1;37m" << loggedInUser->getBalance() << " VND\n";
                        cout << "\033[1;35m";
                        cout << "|=======================================================================================================================================|" << "\n\n";
                        cout << "\033[0m";

                        // Tạo giao dịch gửi tiền
                        Transaction txnSent;
                        txnSent.dateTime = getCurrentDateTime();
                        txnSent.type = "Transfer Sent";
                        txnSent.amount = amount;
                        txnSent.balanceAfter = loggedInUser->getBalance();
                        txnSent.details = "To: " + user.getPhoneNumber() + " (" + user.getUserName() + ")";
                        loggedInUser->addTransaction(txnSent);

                        // Ghi giao dịch gửi tiền vào file lịch sử
                        balanceFluctuation(*loggedInUser, txnSent);

                        // Tạo giao dịch nhận tiền cho người nhận
                        Transaction txnReceived;
                        txnReceived.dateTime = getCurrentDateTime();
                        txnReceived.type = "Transfer Received";
                        txnReceived.amount = amount;
                        txnReceived.balanceAfter = user.getBalance();
                        txnReceived.details = "From: " + loggedInUser->getPhoneNumber() + " (" + loggedInUser->getUserName() + ")";
                        user.addTransaction(txnReceived);

                        // Ghi giao dịch nhận tiền vào file lịch sử
                        balanceFluctuation(user, txnReceived);

                        saveAllUsersToFile();
                    }
                    else {
                        cout << "Insufficient balance.\n";
                    }
                    return;
                }
            }
            // Nếu không tìm thấy người nhận
            if (!recipientFound) {
                cout << "Recipient not found.\n";
                return;
            }
        }
        if (userInput != otp) {
            cout << "Incorrect OTP code, please try again..." << endl;
        }
    } while (userInput != otp);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void ATM::transactionHistory() {
    if (loggedInUser == nullptr) {
        cout << "You need to log in first to view the transaction history.\n";
        return;
    }

    ifstream inFile("userHistory.txt");
    if (!inFile) {
        cout << "Error opening userHistory.txt!" << endl;
        return;
    }

    string line;
    bool hasTransaction = false;

    Menu::displayHeader("Transaction History");

    cout << "\033[1;37m";
    cout << "\n+=======================================================================================================================================+\n";
    cout << "|" << "\033[1;33m" << "888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"<< "\033[1;37m" <<"|\n";
    cout << "|---------------------------------------------------------------------------------------------------------------------------------------|\n";
    cout << "| Date & Time\t\tType\t\t\tAmount\t\t\tBalance After\t\tDetails                                 |\n";
    cout << "|---------------------------------------------------------------------------------------------------------------------------------------|";

    int y = 11;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string phoneNumber, userName, dateTime, type, details;
        double amount, balanceAfter;

        // Tách các trường bằng istringstream
        getline(iss, phoneNumber, '\t');
        getline(iss, userName, '\t');
        getline(iss, dateTime, '\t');
        getline(iss, type, '\t');
        iss >> amount >> balanceAfter;
        iss.ignore(); // Bỏ qua tab hoặc khoảng trắng sau balanceAfter
        getline(iss, details); // Lấy phần còn lại của dòng làm chi tiết
        
        // Kiểm tra nếu số điện thoại trùng với người dùng hiện tại
        if (phoneNumber == loggedInUser->getPhoneNumber()) {
      /*      hasTransaction = true;
            cout << "| " << dateTime << "\t" << type << "\t\t" << amount << "\t\t"
                << balanceAfter << "\t\t" << details << " |\n";*/
           hasTransaction = true;
            gotoxy(0, y);
            cout << "|";
            gotoxy(2, y); // X đặt một vị trí phù hợp để căn chỉnh
            cout << dateTime;
            gotoxy(24, y); // Thay đổi X để đặt vị trí cho 'Type'
            cout << type;
            gotoxy(48, y); // Thay đổi X để đặt vị trí cho 'Amount'
            cout << amount;
            gotoxy(72, y); // Thay đổi X để đặt vị trí cho 'Balance After'
            cout << balanceAfter;
            gotoxy(96, y); // Thay đổi X để đặt vị trí cho 'Details'
            cout << details;
            gotoxy(136, y);
            cout << "|"<<endl;
            cout << "|---------------------------------------------------------------------------------------------------------------------------------------|\n";

            y=y+2; // Di chuyển xuống hàng tiếp theo */
        }
    }
    int y2 = 11;
    if (!hasTransaction) {
        gotoxy(0, y2);
        cout << "|";
        gotoxy(2, y2); // X đặt một vị trí phù hợp để căn chỉnh
        cout << "No transactions found for your account";
        gotoxy(136, y2);
        cout << "|" << endl;
        cout << "|---------------------------------------------------------------------------------------------------------------------------------------|\n";
    }

    cout << "|"<<"\033[1;33m"<<"888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888" << "\033[1;37m" << "|\n";
    cout << "+=======================================================================================================================================+\n";
    cout << "\033[0m";
    inFile.close();
}

void ATM::checkBalance() {
    Menu::displayHeader("Check Balance");
    cout << "\033[1;35m";
    cout << "\n|=======================================================================================================================================|" << "\n";
    cout << "                                        >>[Account]:         " << "\033[1;37m" << loggedInUser->getPhoneNumber() << "\n";
    cout << "\033[1;35m";
    cout << "|---------------------------------------------------------------------------------------------------------------------------------------|" << "\n";
    cout << "                                        >>[User Name]:         " << "\033[1;37m" << loggedInUser->getUserName() << "\n";
    cout << "\033[1;35m";
    cout << "|---------------------------------------------------------------------------------------------------------------------------------------|" << "\n";
    cout << "                                        >>[Your balance is]:         " << "\033[1;37m" << loggedInUser->getBalance() << "VND\n";
    cout << "\033[1;35m";
    cout << "|=======================================================================================================================================|" << "\n\n";
    cout << "\033[0m";
}

string ATM::getCurrentDateTime() {
    time_t now = time(0); // Lấy thời gian hiện tại
    tm ltm;
    localtime_s(&ltm, &now); // Sử dụng localtime_s thay vì localtime

    stringstream ss;
    ss << setw(2) << setfill('0') << ltm.tm_mday << "/"
        << setw(2) << setfill('0') << (ltm.tm_mon + 1) << "/"
        << setw(2) << setfill('0') << (ltm.tm_year % 100) << " "
        << setw(2) << setfill('0') << ltm.tm_hour << ":"
        << setw(2) << setfill('0') << ltm.tm_min << ":"
        << setw(2) << setfill('0') << ltm.tm_sec;

    return ss.str();
}

void ATM::balanceFluctuation(const UserAccount& user, const Transaction& txn) {
    ofstream outFile("userHistory.txt", ios::app);
    if (!outFile) {
        cout << "Error opening userHistory.txt for writing!" << endl;
        return;
    }

    // Ghi thông tin giao dịch với định dạng: Số điện thoại, Tên người dùng, Thời gian, Loại giao dịch, Số tiền, Số dư sau giao dịch, Chi tiết
    outFile << user.getPhoneNumber() << "\t"
        << user.getUserName() << "\t"
        << txn.dateTime << "\t"
        << txn.type << "\t"
        << txn.amount << "\t"
        << txn.balanceAfter << "\t"
        << txn.details << "\n";

    outFile.close();
}

string ATM::inputPhoneNumber() {
    string phone;
    cin.ignore();
    bool firstAttempt = true; // Biến để theo dõi nếu là lần nhập đầu tiên
    do {
        if (!firstAttempt) {
            cout << "Invalid phone number format, please try again." << endl;
        }
        cout << "Enter your phone number: ";
        getline(cin, phone);
        firstAttempt = false; // Sau lần nhập đầu tiên

        // Kiểm tra xem số điện thoại đã được đăng ký chưa
        if (isPhoneNumberRegistered(phone)) {
            cout << "This phone number has already been registered. Please try a different one." << endl;
            cout << "Do you want to login or continue register? (Y/N)\n";
            char YN;
            cin >> YN;
            if (YN == 'Y' || YN == 'y') return "N/A";
            firstAttempt = true; // Để tiếp tục yêu cầu nhập lại
            cin.ignore();
        }
    } while (!isValidPhoneNumber(phone) || isPhoneNumberRegistered(phone));

    return phone;
}


bool ATM::isValidPhoneNumber(const string& phone) {
    // Kiểm tra nếu số bắt đầu bằng '0' và có độ dài 10 số
    if (phone.length() == 10 && phone[0] == '0') {
        string index2 = phone.substr(0, 2); // Substr dùng để trích chuỗi string với độ dài của chuổi từ vị trí k
        string index3 = phone.substr(0, 3);

        if (index2 == "08" || index2 == "09" || index2 == "03" || index2 == "07" ||
            index3 == "052" || index3 == "056" || index3 == "058" || index3 == "059") {
            return true;
        }
    }
    // Kiểm tra nếu số bắt đầu bằng "+84" và có độ dài 12 số
    else if (phone.length() == 12 && phone.substr(0, 3) == "+84") {
        string index2 = phone.substr(3, 2);
        string index3 = phone.substr(3, 3);

        if (index2 == "08" || index2 == "09" || index2 == "03" || index2 == "07" ||
            index3 == "052" || index3 == "056" || index3 == "058" || index3 == "059") {
            return true;
        }
    }
    return false;
}

// Hàm kiểm tra xem số điện thoại đã được đăng ký hay chưa
bool ATM::isPhoneNumberRegistered(const string& phone){
    for (const UserAccount& user : users) {
        if (user.getPhoneNumber() == phone) {
            return true; // Số điện thoại đã được đăng ký
        }
    }
    return false; // Số điện thoại chưa được đăng ký
}

bool ATM::validatePassword(const string& password) {
    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    if (password.length() < 10) {
        cout << "Password must be at least 10 characters.\n";
        return false;
    }

    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        if (isdigit(c)) hasDigit = true;
        if (ispunct(c)) hasSpecial = true;  // Ký tự đặc biệt
    }

    if (!hasUpper || !hasDigit || !hasSpecial) {
        cout << "Password must contain at least 1 uppercase character, number and special character. Please try again!\n";
        return false;
    }

    return true;
}

int ATM::generateOTP(){
    srand(static_cast<unsigned int>(time(0))); // Khởi tạo số ngẫu nhiên gồm 6 chữ số
    return rand() % 900000 + 100000;
}

void ATM::loadUsersFromFile() {
    ifstream inFile("user.txt");
    if (!inFile) {
        cout << "Error opening user.txt!" << endl;
        return;
    }

    string phoneNumber, userName, password, pin;
    double balance;

    while (getline(inFile, phoneNumber, '\t') && inFile >> balance) {
        inFile.ignore(); // Bỏ qua ký tự xuống dòng hoặc dấu cách sau balance
        getline(inFile, userName, '\t');
        getline(inFile, password, '\t');
        getline(inFile, pin);

        UserAccount user(phoneNumber, balance, userName, phoneNumber, password, pin);
        users.push_back(user);
    }

    inFile.close();
}


void ATM::saveUserToFile(const UserAccount& user) {
    ofstream outFile("user.txt", ios::app);  // Mở tệp ở chế độ thêm
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    outFile << user.getPhoneNumber() << "\t"
        << user.getBalance() << "\t"
        << user.getUserName() << "\t"
        << user.getPassword() << "\t"
        << user.getTransactionPIN() << endl;

    outFile.close();
}

void ATM::saveAllUsersToFile() {
    ofstream outFile("user.txt");
    if (!outFile) {
        cout << "Error opening user.txt for writing!" << endl;
        return;
    }

    for (const UserAccount& user : users) {
        outFile << user.getPhoneNumber() << "\t"
            << user.getBalance() << "\t"
            << user.getUserName() << "\t"
            << user.getPassword() << "\t"
            << user.getTransactionPIN() << "\n";
    }

    outFile.close();
}

