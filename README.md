# Expense Management System

This project is an Expense Management System written in C++. It allows users to input and analyze their monthly budgets and expenses over a given number of months. The system generates detailed reports comparing budgeted amounts versus actual expenses.

## Features

- Input monthly budget for various categories (e.g., housing, utilities, food, etc.)
- Input actual monthly expenses for the same categories.
- Generate monthly reports that compare budgeted amounts to actual expenses.
- Calculate the remaining balance for each month.

## Classes and Methods

### `MonthlyBudget`
- `describeProgram()`: Displays a brief description of the program
- `getMonths(int &months)`: Gets the number of months to analyze from the user
- `getMonthlyBudget(fstream &budgetFile, int months)`: Records the budget for the specified number of months
- `getMonthlyExpenses(fstream &expenseFile, int months)`: Records the expenses for the specified number of months
- `getMonthlyReport(fstream &budgetFile, fstream &expenseFile, int months)`: Generates a report comparing budgeted amounts to actual expenses

### `MonthlyExpenses`
- Inherits from `MonthlyBudget` and stores the actual expenses for each category

## Files

- `main.cpp`: The main program file containing the implementation of the Expense Management System.
- `budget.bin`: Binary file storing the budget data.
- `expenses.bin`: Binary file storing the expense data.
- `results.txt`: Text file containing the generated reports for each month.

## How to Use

1. **Compile the program:**
    ```bash
    g++ -o expense_manager main.cpp
    ```

2. **Run the program:**
    ```bash
    ./expense_manager
    ```

3. **Follow the on-screen prompts** to enter the number of months, budget, and expense data.

## Requirements

- C++ compiler
- Standard C++ Library

## Author

- [Eshab Sachan](https://github.com/Eshab01)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
