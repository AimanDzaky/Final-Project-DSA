#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class TaxCalculator {
private:
    double userIncome;
    double totalDeductions;
    vector<pair<string, double>> deductions;

public:
    TaxCalculator(double income, double deductions)
        : userIncome(income), totalDeductions(deductions) {}

    void addDeduction(string deductionName, double deductionAmount) {
    totalDeductions += deductionAmount;
    deductions.push_back(make_pair(deductionName, deductionAmount));
}

    void sortDeductions() {
        sort(deductions.begin(), deductions.end());
    }

    void printDeductions() const {
        for (const auto& deduction : deductions) {
            cout << setw(20) << left << deduction.first + ":" << setw(10) << right << "$" << deduction.second << endl;
        }
    }

    double calculateTax(double income, double totalDeductions, int recursiveLevel) const {
        if (recursiveLevel <= 0) {
            return 0.0;
        }

        double IncomeTax = 0.15 * income;
        double taxAmount = IncomeTax - (0.10 * totalDeductions);

        return taxAmount;
    }

    double calculateTaxRecursive() const {
        return calculateTax(userIncome, totalDeductions, 5);
    }

    // getter and setter methods
    double getTotalDeductions() const {
        return totalDeductions;
    }

    void setTotalDeductions(double totalDeductions) {
        TaxCalculator::totalDeductions = totalDeductions;
    }
};

int main() {
    while (true) {
    double userIncome = 0;
    double deductionAmount = 0;
    string command, deductionName;

    cout << "Welcome to our Tax Calculator!\n";
    cout << "=========================\n";

    cout << "Enter your income: ";
    cin >> userIncome;

    TaxCalculator taxCalc(userIncome, 0);

    while (true) {
        cout << "\nEnter a deduction (or 'done' to finish): ";
        cin >> deductionName;

        if (deductionName == "done") {
            break;
        }

        cout << "\nEnter the amount for the " << deductionName << " deduction: ";
        cin >> deductionAmount;

        taxCalc.addDeduction(deductionName, deductionAmount);
        taxCalc.sortDeductions();
        taxCalc.printDeductions();
    }

    cout << setw(20) << left << "Total Deductions:" << setw(10) << right << "$" << taxCalc.getTotalDeductions() << endl;

    double taxAmount = taxCalc.calculateTaxRecursive();

    cout << setw(20) << left << "Tax Amount:" << setw(10) << right << "$" << taxAmount << endl;

    // Ask the user if they want to calculate another tax
    cout << "\nWould you like to calculate another tax? (y/n): ";
    char choice;
    cin >> choice;

    if (choice != 'y' && choice != 'Y') {
        break;
    }
}

return 0;
}
