# Advanced Banking System

A C++ banking application that simulates a real-world banking system with account management, PIN security, and transaction processing.

## Features

### 🏦 Account Management
- Create new bank accounts (Savings/Checking)
- Login with account number and PIN
- View all accounts (admin view)
- Account information display

### 🔒 Security Features
- 4-digit PIN authentication for all transactions
- PIN change functionality
- Secure balance inquiries
- Account number masking for privacy

### 💰 Banking Operations
- Deposit money (with PIN verification)
- Withdraw money (with PIN verification)
- Transfer money between accounts
- Check account balance
- View detailed account information

### 🛡️ Data Protection
- Private member variables for sensitive data
- Input validation and error handling
- Buffer overflow prevention
- Secure transaction processing

## Project Structure

```
BankingSystem/
├── Main Program
│   ├── BankAccount Class
│   │   ├── Private Members: accountNumber, balance, pin, accountType
│   │   └── Public Methods: deposit(), withdraw(), transferTo(), verifyPin(), etc.
│   ├── BankingSystem Class
│   │   ├── Vector of BankAccount objects
│   │   └── Methods: createAccount(), login(), displayAllAccounts(), etc.
│   └── Main Function with Menu System
```

## Classes

### BankAccount Class
Represents individual bank accounts with:
- **Private Data**: Account number, balance, PIN, account type
- **Public Methods**: 
  - Transaction methods (deposit, withdraw, transfer)
  - Security methods (verifyPin, changePin)
  - Information display methods

### BankingSystem Class
Manages multiple bank accounts with:
- **Account Storage**: Vector of BankAccount objects
- **Account Management**: Create, login, find accounts
- **System Operations**: Display all accounts, count accounts

## Installation & Compilation

### Prerequisites
- C++ Compiler (GCC, Clang, or MSVC)
- C++11 or higher

### Compilation
```bash
# Using g++
g++ -o banking_system banking_system.cpp -std=c++11

# Using clang++
clang++ -o banking_system banking_system.cpp -std=c++11
```

### Running the Program
```bash
./banking_system
```

## Usage Guide

### 1. Creating an Account
```
1. Select "Create New Account"
2. Enter account number (e.g., AC123)
3. Enter account holder name
4. Select account type (Savings/Checking)
5. Set 4-digit PIN (1000-9999)
```

### 2. Logging In
```
1. Select "Login to Account"
2. Enter account number
3. Enter 4-digit PIN
```

### 3. Performing Transactions
Once logged in, you can:
- **Deposit**: Add money to account (requires PIN)
- **Withdraw**: Remove money from account (requires PIN)
- **Transfer**: Send money to another account (requires PIN)
- **Check Balance**: View current balance (requires PIN)
- **Change PIN**: Update your security PIN

### 4. Admin View
Select "View All Accounts" to see:
- All registered accounts
- Account holder names
- Account types
- Current balances

## Code Features

### Input Validation
- Validates PIN format (4 digits)
- Checks for sufficient funds before withdrawal
- Prevents duplicate account numbers
- Validates transfer amounts

### Security Measures
- PIN required for all sensitive operations
- Private data members for sensitive information
- Account number masking in displays
- No direct access to balance without PIN

### Error Handling
- Invalid input detection
- Account not found messages
- Insufficient funds warnings
- Invalid PIN notifications

## Sample Session

```
=== ADVANCED BANKING SYSTEM ===

=== MAIN MENU ===
1. Create New Account
2. Login to Account
3. View All Accounts
4. Exit
Enter choice (1-4): 1

=== Create New Account ===
Enter account number: AC123
Enter account holder name: John Doe
Enter account type (Savings/Checking): Savings
Set 4-digit PIN: 1234

Account created successfully!
```

## Future Enhancements

### Planned Features
1. **Transaction History**: Record all transactions with timestamps
2. **Interest Calculation**: Automatic interest for savings accounts
3. **File Storage**: Save accounts to file for persistence
4. **Admin Controls**: Delete accounts, reset PINs
5. **Multiple Users**: Joint accounts, beneficiary management
6. **Loan System**: Apply for and manage loans
7. **Bill Payments**: Utility bill payments through accounts

### Technical Improvements
1. **Database Integration**: SQLite for data persistence
2. **Encryption**: Secure PIN and data storage
3. **GUI Interface**: Graphical user interface
4. **Network Support**: Multi-user banking system
5. **Report Generation**: Monthly statements

## Learning Objectives

This project demonstrates:
- Object-Oriented Programming principles
- Class design and implementation
- Data encapsulation and abstraction
- Input validation and error handling
- Menu-driven program design
- Vector data structure usage
- Memory management in C++

## Common Issues & Solutions

### Issue: Infinite loop when entering account number
**Solution**: The program now properly clears input buffers using `cin.ignore()`

### Issue: Transfer not working between accounts
**Solution**: Added proper account lookup and validation in transfer function

### Issue: PIN verification failing
**Solution**: Ensure PIN is exactly 4 digits (1000-9999)

## Contributing

Feel free to fork this project and add features:
1. Add transaction history
2. Implement file I/O for data persistence
3. Create a graphical interface
4. Add interest calculation features
5. Implement overdraft protection

## License

This project is for educational purposes. Feel free to use and modify as needed.

## Acknowledgments

- Created as a learning project for C++ classes and OOP concepts
- Designed to demonstrate real-world banking system principles
- Focus on security and data protection practices
---

**Note**: This is a simulation for educational purposes. No real financial transactions are processed.
