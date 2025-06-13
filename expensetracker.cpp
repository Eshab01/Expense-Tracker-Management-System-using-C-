
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <string>

using namespace std;

class MonthlyBudget {
public:
    double housing = 0;
    double utilities = 0;
    double household = 0;
    double transportation = 0;
    double food = 0;
    double medical = 0;
    double insurance = 0;
    double entertainment = 0;
    double clothing = 0;
    double misc = 0;

    void describeProgram();
    void getMonths(int &months);
    void getMonthlyBudget(fstream &budgetFile, int months);
    void getMonthlyExpenses(fstream &expenseFile, int months);
    void getMonthlyReport(fstream &budgetFile, fstream &expenseFile, int months);
    
private:
    double inputBudget();
};

class MonthlyExpenses : public MonthlyBudget {
public:
    double housingEx = 0;
    double utilitiesEx = 0;
    double householdEx = 0;
    double transportationEx = 0;
    double foodEx = 0;
    double medicalEx = 0;
    double insuranceEx = 0;
    double entertainmentEx = 0;
    double clothingEx = 0;
    double miscEx = 0;
};

// Function to display program description
void MonthlyBudget::describeProgram() {
    cout << "--------------------------------------------------------------------\n";
    cout << "|                       EXPENSE MANAGEMENT SYSTEM                    |\n";
    cout << "--------------------------------------------------------------------\n";
}

// Function to get number of months to analyze
void MonthlyBudget::getMonths(int &months) {
    cout << "How many months would you like to analyze? ";
    while (!(cin >> months) || months <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid positive number of month: ";
    }
    cout << "-------------------------------------------------------------------\n";
}

// Function to read a budget or expense value with validation
double MonthlyBudget::inputBudget() {
    double value;
    while (true) {
        cin >> value;
        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid non-negative number: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Function to enter monthly budget data
void MonthlyBudget::getMonthlyBudget(fstream &budgetFile, int months) {
    budgetFile.open("budget.bin", ios::out | ios::binary);
    if (!budgetFile) {
        cerr << "Error opening file: budget.bin\n";
        return;
    }

    for (int month = 1; month <= months; ++month) {
        cout << "Enter monthly BUDGET for month " << month << "\n";
        cout << "--------------------------------------------------------------------\n";
        housing = inputBudget();
        utilities = inputBudget();
        household = inputBudget();
        transportation = inputBudget();
        food = inputBudget();
        medical = inputBudget();
        insurance = inputBudget();
        entertainment = inputBudget();
        clothing = inputBudget();
        misc = inputBudget();
        cout << "--------------------------------------------------------------------\n";

        budgetFile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    budgetFile.close();
}

// Function to enter monthly expense data
void MonthlyBudget::getMonthlyExpenses(fstream &expenseFile, int months) {
    MonthlyExpenses expenses;
    expenseFile.open("expenses.bin", ios::out | ios::binary);
    if (!expenseFile) {
        cerr << "Error opening file: expenses.bin\n";
        return;
    }

    for (int month = 1; month <= months; ++month) {
        cout << "Enter monthly EXPENSES for month " << month << "\n";
        cout << "--------------------------------------------------------------------\n";
        expenses.housingEx = inputBudget();
        expenses.utilitiesEx = inputBudget();
        expenses.householdEx = inputBudget();
        expenses.transportationEx = inputBudget();
        expenses.foodEx = inputBudget();
        expenses.medicalEx = inputBudget();
        expenses.insuranceEx = inputBudget();
        expenses.entertainmentEx = inputBudget();
        expenses.clothingEx = inputBudget();
        expenses.miscEx = inputBudget();
        cout << "--------------------------------------------------------------------\n";

        expenseFile.write(reinterpret_cast<char*>(&expenses), sizeof(expenses));
    }
    expenseFile.close();
}

// Function to generate monthly budget report
void MonthlyBudget::getMonthlyReport(fstream &budgetFile, fstream &expenseFile, int months) {
    MonthlyBudget budget;
    MonthlyExpenses expenses;
    ofstream toFile("results.txt", ios::app);

    budgetFile.open("budget.bin", ios::in | ios::binary);
    expenseFile.open("expenses.bin", ios::in | ios::binary);
    if (!budgetFile || !expenseFile) {
        cerr << "Error opening report files.\n";
        return;
    }

    for (int month = 1; month <= months; ++month) {
        budgetFile.read(reinterpret_cast<char*>(&budget), sizeof(budget));
        expenseFile.read(reinterpret_cast<char*>(&expenses), sizeof(expenses));
        
        if (budgetFile.eof() || expenseFile.eof()) {
            cout << "End of file reached before expected.\n";
            break;
        }

        toFile << "Month " << month << " Report:\n";
        toFile << "Budget:\n";
        toFile << "Housing: " << budget.housing << "\n";
        toFile << "Utilities: " << budget.utilities << "\n";
        toFile << "Household: " << budget.household << "\n";
        toFile << "Transportation: " << budget.transportation << "\n";
        toFile << "Food: " << budget.food << "\n";
        toFile << "Medical: " << budget.medical << "\n";
        toFile << "Insurance: " << budget.insurance << "\n";
        toFile << "Entertainment: " << budget.entertainment << "\n";
        toFile << "Clothing: " << budget.clothing << "\n";
        toFile << "Misc: " << budget.misc << "\n";

        toFile << "Expenses:\n";
        toFile << "Housing: " << expenses.housingEx << "\n";
        toFile << "Utilities: " << expenses.utilitiesEx << "\n";
        toFile << "Household: " << expenses.householdEx << "\n";
        toFile << "Transportation: " << expenses.transportationEx << "\n";
        toFile << "Food: " << expenses.foodEx << "\n";
        toFile << "Medical: " << expenses.medicalEx << "\n";
        toFile << "Insurance: " << expenses.insuranceEx << "\n";
        toFile << "Entertainment: " << expenses.entertainmentEx << "\n";
        toFile << "Clothing: " << expenses.clothingEx << "\n";
        toFile << "Misc: " << expenses.miscEx << "\n";

        double totalBudget = budget.housing + budget.utilities + budget.household + budget.transportation +
                             budget.food + budget.medical + budget.insurance + budget.entertainment +
                             budget.clothing + budget.misc;

        double totalExpenses = expenses.housingEx + expenses.utilitiesEx + expenses.householdEx +
                               expenses.transportationEx + expenses.foodEx + expenses.medicalEx +
                               expenses.insuranceEx + expenses.entertainmentEx + expenses.clothingEx +
                               expenses.miscEx;

        toFile << "Total Budget:  " << totalBudget << "\n";
        toFile << "Total Expenses:  " << totalExpenses << "\n";
        toFile << "Remaining Balance:  " << (totalBudget - totalExpenses) << "\n";
        toFile << "--------------------------------------------------------------------\n";
    }

    budgetFile.close();
    expenseFile.close();
    toFile.close();
}

int main() {
    MonthlyBudget budgetManager;
    fstream budgetFile, expenseFile;
    int months;

    budgetManager.describeProgram();
    budgetManager.getMonths(months);
    budgetManager.getMonthlyBudget(budgetFile, months);
    budgetManager.getMonthlyExpenses(expenseFile, months);
    budgetManager.getMonthlyReport(budgetFile, expenseFile, months);

    return 0;
}
