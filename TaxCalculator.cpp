#include <iostream>
#include <cstring>
using namespace std;

class DeductionNode {
public:
    char deductionName[50];
    double deductionAmount;
    DeductionNode* next;

    DeductionNode(const char* name, double amount) : deductionAmount(amount), next(nullptr) {
        strncpy(deductionName, name, sizeof(deductionName) - 1);
    }
};

class DeductionList {
public:
    DeductionNode* head;

    DeductionList() : head(nullptr) {}

    void addDeduction(const char* name, double amount) {
        DeductionNode* newNode = new DeductionNode(name, amount);
        newNode->next = head;
        head = newNode;
    }

    double calculateTotalDeductions() const {
        double total = 0.0;
        DeductionNode* current = head;
        while (current != nullptr) {
            total += current->deductionAmount;
            current = current->next;
        }
        return total;
    }

    double calculateTotalDeductionsRecursive(DeductionNode* current) const {
        if (current == nullptr) {
            return 0.0;
        }
        return current->deductionAmount + calculateTotalDeductionsRecursive(current->next);
    }
};

class TaxCalculator {
private:
    double income;
    DeductionList deductions;

public:
    TaxCalculator(double initialIncome) : income(initialIncome) {}

    void addDeduction(const char* name, double amount) {
        deductions.addDeduction(name, amount);
    }

    double calculateTax() const {
        double totalDeductions = deductions.calculateTotalDeductions();
        return 0.15 * (income - totalDeductions);
    }

    double calculateTaxRecursive() const {
        double totalDeductions = deductions.calculateTotalDeductionsRecursive(deductions.head);
        return (income - totalDeductions);
    }
};

int main() {
    double userIncome;
    cout << "Enter your income: $";
    cin >> userIncome;
    cin.ignore();  // Consume the newline character in the input buffer

    TaxCalculator taxCalc(userIncome);

    int deductionCount;
    cout << "Enter the number of deductions: ";
    cin >> deductionCount;
    cin.ignore();  // Consume the newline character in the input buffer

    for (int i = 0; i < deductionCount; ++i) {
        char deductionName[50];
        double deductionAmount;

        cout << "Enter deduction name: ";
        cin.getline(deductionName, sizeof(deductionName));

        cout << "Enter deduction amount: $";
        cin >> deductionAmount;
        cin.ignore();  // Consume the newline character in the input buffer

        taxCalc.addDeduction(deductionName, deductionAmount);
    }

    double taxAmount = taxCalc.calculateTax();
    cout << "Tax amount: $" << taxAmount << endl;

    double taxAmountRecursive = taxCalc.calculateTaxRecursive();
    cout << "Tax amount (recursive): $" << taxAmountRecursive << endl;

    return 0;
}
