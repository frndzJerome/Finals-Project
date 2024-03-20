#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class Account {
private:
    string first_name;
    string last_name;
    string middle_name;
    string address;
    string birthday;
    char gender;
    string account_type;
    double balance;
    int account_number;
    int pin;
    bool account_exists;

public:
    Account() {
        account_exists = false;
    }

    Account(string first, string last, string middle, string addr, string dob, char gen, string type, int pin) {
        first_name = first;
        last_name = last;
        middle_name = middle;
        address = addr;
        birthday = dob;
        gender = gen;
        account_type = type;
        balance = 0.0;
        account_number = generate_account_number();
        this->pin = pin;
        account_exists = true;
    }

    int generate_account_number() {
        srand(time(0));
        return rand() % 900000 + 100000; // Generate a random 6-digit number
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful. New balance: $" << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: $" << balance << endl;
        } else {
            cout << "Insufficient funds." << endl;
        }
    }

    void display_account_info() {
        cout << "Account Information:" << endl;
        cout << "Account Number: " << account_number << endl;
        cout << "Name: " << first_name << " " << middle_name << " " << last_name << endl;
        cout << "Address: " << address << endl;
        cout << "Birthday: " << birthday << endl;
        cout << "Gender: " << gender << endl;
        cout << "Account Type: " << account_type << endl;
        cout << "Balance: $" << balance << endl;
    }

    double get_balance() {
        return balance;
    }

    int get_account_number() {
        return account_number;
    }

    bool validate_pin(int input_pin) {
        return pin == input_pin;
    }

    void set_pin(int new_pin) {
        pin = new_pin;
    }

    bool exists() {
        return account_exists;
    }
};

int main() {
    string first_name, last_name, middle_name, address, birthday, account_type;
    char gender;
    double initial_deposit;
    int pin;

    Account new_account;

    cout << "Welcome to Our Bank!" << endl;

    int choice;
    double amount;
    int input_pin;
    while (true) {
        // Display menu
        cout << "\nMenu:" << endl;
        cout << "1. Open a New Account" << endl;
        cout << "2. Balance Inquiry" << endl;
        cout << "3. Deposit" << endl;
        cout << "4. Withdraw" << endl;
        cout << "5. View Account Information" << endl;
        cout << "6. Change PIN" << endl;
        cout << "7. Exit Program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                if (new_account.exists()) {
                    cout << "An account already exists. You cannot open a new one." << endl;
                } else {
                    cout << "Enter first name: ";
                    cin >> first_name;
                    cout << "Enter middle name: ";
                    cin >> middle_name;
                    cout << "Enter last name: ";
                    cin >> last_name;
                    cout << "Enter address: ";
                    cin.ignore();
                    getline(cin, address);
                    cout << "Enter birthday (MM/DD/YYYY): ";
                    cin >> birthday;
                    cout << "Enter gender (M/F): ";
                    cin >> gender;
                    cout << "Enter account type (Savings/Current): ";
                    cin >> account_type;
                    cout << "Enter initial deposit amount: $";
                    cin >> initial_deposit;
                    cout << "Enter PIN number (4 digits): ";
                    cin >> pin;

                    new_account = Account(first_name, last_name, middle_name, address, birthday, gender, account_type, pin);
                    cout << "Account created successfully." << endl;
                    cout << "Your account number is: " << new_account.get_account_number() << endl;
                    new_account.deposit(initial_deposit);
                }
                break;
            }
            case 2:
            case 3:
            case 4:
            case 5:
            case 6: {
                if (!new_account.exists()) {
                    cout << "No account exists. Please open a new account first." << endl;
                    break;
                }
                cout << "Enter PIN number: ";
                cin >> input_pin;
                while (!new_account.validate_pin(input_pin)) {
                    cout << "Invalid PIN number. Please try again: ";
                    cin >> input_pin;
                }
                switch (choice) {
                    case 2:
                        cout << "Current balance: $" << new_account.get_balance() << endl;
                        break;
                    case 3:
                        cout << "Enter deposit amount: $";
                        cin >> amount;
                        new_account.deposit(amount);
                        break;
                    case 4:
                        cout << "Enter withdrawal amount: $";
                        cin >> amount;
                        new_account.withdraw(amount);
                        break;
                    case 5:
                        new_account.display_account_info();
                        break;
                    case 6:
                        cout << "Enter new PIN number: ";
                        cin >> pin;
                        new_account.set_pin(pin);
                        cout << "PIN number changed successfully." << endl;
                        break;
                }
                break;
            }
            case 7:
                cout << "Exiting program. Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

