#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>  // Added for numeric_limits

using namespace std;

class BankAccount {
private:
    string accountNumber;
    double balance;
    int pin;
    string accountType;
    
public:
    string name;
    
    // Constructor
    BankAccount(string accNum, string ownerName, int accountPin, string type = "Savings") {
        accountNumber = accNum;
        name = ownerName;
        pin = accountPin;
        accountType = type;
        balance = 0.0;
    }
    
    // Verify PIN
    bool verifyPin(int inputPin) {
        return pin == inputPin;
    }
    
    // Change PIN
    bool changePin(int oldPin, int newPin) {
        if(verifyPin(oldPin) && newPin >= 1000 && newPin <= 9999) {
            pin = newPin;
            cout << "PIN changed successfully!" << endl;
            return true;
        }
        cout << "PIN change failed!" << endl;
        return false;
    }
    
    // Deposit with PIN verification
    void deposit(double amount, int inputPin) {
        if(!verifyPin(inputPin)) {
            cout << "Invalid PIN! Transaction failed." << endl;
            return;
        }
        
        if(amount > 0) {
            balance += amount;
            cout << fixed << setprecision(2);
            cout << "Deposited: $" << amount << endl;
            cout << "Total Balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }
    
    // Withdraw with PIN verification
    void withdraw(double amount, int inputPin) {
        if(!verifyPin(inputPin)) {
            cout << "Invalid PIN! Transaction failed." << endl;
            return;
        }
        
        if(amount > 0 && amount <= balance) {
            balance -= amount;
            cout << fixed << setprecision(2);
            cout << "Withdrawn: $" << amount << endl;
            cout << "Remaining Balance: $" << balance << endl;
        } else if (amount > balance) {
            cout << "Insufficient funds! You have only $" << balance << endl;
        } else {
            cout << "Invalid withdrawal amount!" << endl;
        }
    }
    
    // Transfer between accounts
    bool transferTo(BankAccount &receiver, double amount, int inputPin) {
        if(!verifyPin(inputPin)) {
            cout << "Invalid PIN! Transaction failed." << endl;
            return false;
        }
        
        if(amount > 0 && amount <= balance) {
            balance -= amount;
            receiver.balance += amount;
            cout << fixed << setprecision(2);
            cout << "Transferred $" << amount << " to " << receiver.name << endl;
            cout << "Your new balance: $" << balance << endl;
            return true;
        }
        cout << "Transfer failed!" << endl;
        return false;
    }
    
    // Display account info
    void displayAccountInfo(int inputPin) {
        if(!verifyPin(inputPin)) {
            cout << "Invalid PIN!" << endl;
            return;
        }
        
        cout << fixed << setprecision(2);
        cout << "\n=== Account Information ===" << endl;
        cout << "Name: " << name << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Account Number: " << "****" << accountNumber.substr(accountNumber.length()-4) << endl;
        cout << "Balance: $" << balance << endl;
        cout << "==========================" << endl;
    }
    
    // Display basic info (no PIN required)
    void displayBasicInfo() {
        cout << fixed << setprecision(2);
        cout << name << " - " << accountType 
             << " Account (Balance: $" << balance << ")" << endl;
    }
    
    // Get balance (with PIN)
    double getBalance(int inputPin) {
        if(verifyPin(inputPin)) {
            return balance;
        }
        cout << "Invalid PIN!" << endl;
        return -1;
    }
    
    // Get account number
    string getAccountNumber() {
        return accountNumber;
    }
    
    // Get account type
    string getAccountType() {
        return accountType;
    }
};

class BankingSystem {
private:
    vector<BankAccount> accounts;
    
    // Find account by account number
    int findAccount(string accNum) {
        for(int i = 0; i < accounts.size(); i++) {
            if(accounts[i].getAccountNumber() == accNum) {
                return i;
            }
        }
        return -1;  // Not found
    }
    
public:
    // Create new account - FIXED
    void createAccount() {
        string accNum, name, type;
        int pin;
        
        cout << "\n=== Create New Account ===" << endl;
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        
        cout << "Enter account number: ";
        getline(cin, accNum);
        
        // Check if account already exists
        if(findAccount(accNum) != -1) {
            cout << "Account already exists!" << endl;
            return;
        }
        
        cout << "Enter account holder name: ";
        getline(cin, name);
        
        cout << "Enter account type (Savings/Checking): ";
        getline(cin, type);
        
        cout << "Set 4-digit PIN: ";
        cin >> pin;
        
        // Clear input buffer after reading int
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // Validate PIN
        while(pin < 1000 || pin > 9999) {
            cout << "PIN must be 4 digits! Enter again: ";
            cin >> pin;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        // Create account
        BankAccount newAccount(accNum, name, pin, type);
        accounts.push_back(newAccount);
        
        cout << "\nAccount created successfully!" << endl;
        cout << "Account Details:" << endl;
        cout << "Name: " << name << endl;
        cout << "Account Number: " << accNum << endl;
        cout << "Account Type: " << type << endl;
        cout << "Welcome, " << name << "!" << endl;
    }
    
    // Login to account - FIXED
    BankAccount* login() {
        string accNum;
        int pin;
        
        cout << "\n=== Login ===" << endl;
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Enter account number: ";
        getline(cin, accNum);
        
        int index = findAccount(accNum);
        if(index == -1) {
            cout << "Account not found!" << endl;
            return nullptr;
        }
        
        cout << "Enter PIN: ";
        cin >> pin;
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if(accounts[index].verifyPin(pin)) {
            cout << "Login successful! Welcome, " << accounts[index].name << "!" << endl;
            return &accounts[index];
        } else {
            cout << "Invalid PIN!" << endl;
            return nullptr;
        }
    }
    
    // Find account for transfer
    BankAccount* findAccountForTransfer(string accNum) {
        int index = findAccount(accNum);
        if(index != -1) {
            return &accounts[index];
        }
        return nullptr;
    }
    
    // Display all accounts (for admin view)
    void displayAllAccounts() {
        if(accounts.empty()) {
            cout << "\nNo accounts exist!" << endl;
            return;
        }
        
        cout << "\n=== All Accounts ===" << endl;
        cout << "Total Accounts: " << accounts.size() << endl;
        for(int i = 0; i < accounts.size(); i++) {
            cout << i+1 << ". ";
            accounts[i].displayBasicInfo();
        }
    }
    
    // Get number of accounts
    int getAccountCount() {
        return accounts.size();
    }
};

// Main banking operations - IMPROVED
void performBankingOperations(BankAccount* account, BankingSystem& bankSystem) {
    if(account == nullptr) return;
    
    int choice, pin;
    double amount;
    string receiverAcc;
    
    while(true) {
        cout << "\n=== Banking Menu ===" << endl;
        cout << "Account: " << account->name << endl;
        cout << "1. Deposit Money" << endl;
        cout << "2. Withdraw Money" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Transfer Money" << endl;
        cout << "5. View Account Info" << endl;
        cout << "6. Change PIN" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if(choice == 7) {
            cout << "Logged out successfully!" << endl;
            break;
        }
        
        switch(choice) {
            case 1:
                cout << "Enter amount to deposit: $";
                cin >> amount;
                cout << "Enter PIN: ";
                cin >> pin;
                account->deposit(amount, pin);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
                
            case 2:
                cout << "Enter amount to withdraw: $";
                cin >> amount;
                cout << "Enter PIN: ";
                cin >> pin;
                account->withdraw(amount, pin);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
                
            case 3: {
                cout << "Enter PIN: ";
                cin >> pin;
                double balance = account->getBalance(pin);
                if(balance >= 0) {
                    cout << fixed << setprecision(2);
                    cout << "Your balance: $" << balance << endl;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
                
            case 4: {
                cout << "Enter receiver's account number: ";
                getline(cin, receiverAcc);
                
                BankAccount* receiver = bankSystem.findAccountForTransfer(receiverAcc);
                if(receiver == nullptr) {
                    cout << "Receiver account not found!" << endl;
                    break;
                }
                
                if(receiver->getAccountNumber() == account->getAccountNumber()) {
                    cout << "Cannot transfer to yourself!" << endl;
                    break;
                }
                
                cout << "Transfer to: " << receiver->name << endl;
                cout << "Enter amount to transfer: $";
                cin >> amount;
                cout << "Enter PIN: ";
                cin >> pin;
                
                account->transferTo(*receiver, amount, pin);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
                
            case 5: {
                cout << "Enter PIN: ";
                cin >> pin;
                account->displayAccountInfo(pin);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
                
            case 6: {
                int oldPin, newPin;
                cout << "Enter old PIN: ";
                cin >> oldPin;
                cout << "Enter new 4-digit PIN: ";
                cin >> newPin;
                account->changePin(oldPin, newPin);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
                
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

int main() {
    BankingSystem bankSystem;
    int choice;
    
    cout << "=== ADVANCED BANKING SYSTEM ===" << endl;
    cout << "===============================" << endl;
    
    while(true) {
        cout << "\n=== MAIN MENU ===" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Login to Account" << endl;
        cout << "3. View All Accounts" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice (1-4): ";
        
        // Check if input is valid
        if(!(cin >> choice)) {
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue;
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
        
        switch(choice) {
            case 1:
                bankSystem.createAccount();
                break;
                
            case 2: {
                BankAccount* loggedAccount = bankSystem.login();
                if(loggedAccount != nullptr) {
                    performBankingOperations(loggedAccount, bankSystem);
                }
                break;
            }
                
            case 3:
                bankSystem.displayAllAccounts();
                break;
                
            case 4:
                cout << "\nThank you for using our banking system!" << endl;
                cout << "Goodbye!" << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Please enter 1-4." << endl;
        }
    }
    
    return 0;
}