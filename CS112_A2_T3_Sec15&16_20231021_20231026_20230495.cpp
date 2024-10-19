// Name: Asmaa Hussein Omar
// asmaahlal123456789a@gmail.com
// Purpose: Calculator that takes fractions and performs basic operations on them.

#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

// Function to convert a fraction to a mixed number
string toMixedNumber(int numerator, int denominator) {
    if (denominator == 0) {
        return "Error: Denominator cannot be zero. Please enter a new expression."; // Prevent division by zero
    }

    int wholePart = numerator / denominator; // Integer part of the mixed number
    int remainderPart = numerator % denominator; // Remainder after division

    // Construct the mixed number string
    stringstream mixedStream;
    mixedStream << wholePart; // Append the integer part

    if (remainderPart != 0) {
        mixedStream << " " << remainderPart << "/" << denominator; // Append the fractional part if the remainder is not zero
    }

    return mixedStream.str();
}

// Function to perform multiplication of two fractions
void multiplyFractions(int numerator1, int denominator1, int numerator2, int denominator2) {
    int resultNumerator = numerator1 * numerator2;
    int resultDenominator = denominator1 * denominator2;
    cout << numerator1 << "/" << denominator1 << " * " << numerator2 << "/" << denominator2 << " = " << toMixedNumber(resultNumerator, resultDenominator) << endl;
}

// Function to perform addition of two fractions
void addFractions(int numerator1, int denominator1, int numerator2, int denominator2) {
    int resultNumerator, resultDenominator;
    if (denominator1 == denominator2) {
        resultNumerator = numerator1 + numerator2;
        resultDenominator = denominator1;
    } else {
        resultNumerator = (numerator1 * denominator2) + (numerator2 * denominator1);
        resultDenominator = denominator1 * denominator2;
    }
    cout << numerator1 << "/" << denominator1 << " + " << numerator2 << "/" << denominator2 << " = " << toMixedNumber(resultNumerator, resultDenominator) << endl;
}

// Function to perform subtraction of two fractions
void subtractFractions(int numerator1, int denominator1, int numerator2, int denominator2) {
    int resultNumerator, resultDenominator;
    if (denominator1 == denominator2) {
        resultNumerator = numerator1 - numerator2;
        resultDenominator = denominator1;
    } else {
        resultNumerator = (numerator1 * denominator2) - (numerator2 * denominator1);
        resultDenominator = denominator1 * denominator2;
    }
    cout << numerator1 << "/" << denominator1 << " - " << numerator2 << "/" << denominator2 << " = " << toMixedNumber(resultNumerator, resultDenominator) << endl;
}

// Function to perform division of two fractions
void divideFractions(int numerator1, int denominator1, int numerator2, int denominator2) {
    int resultNumerator = numerator1 * denominator2;
    int resultDenominator = denominator1 * numerator2;

    cout << numerator1 << "/" << denominator1 << " / " << numerator2 << "/" << denominator2 << " = " << toMixedNumber(resultNumerator, resultDenominator) << endl;
}

// Function to extract operands from the matched string
void extractOperands(const string& operand, int& numerator, int& denominator) {
    stringstream ss(operand);
    string numeratorPart, denominatorPart;
    getline(ss, numeratorPart, '/');
    getline(ss, denominatorPart);

    if (!denominatorPart.empty()) {
        numerator = stoi(numeratorPart);
        denominator = stoi(denominatorPart);
    } else {
        numerator = stoi(numeratorPart);
        denominator = 1; // Set denominator to 1 for integers
    }
}

// Function to validate and handle user input
void processUserInput(const string& input) {
    // Define regex pattern to match rational numbers and operations
    regex regexPattern("([-+]?[0-9]+(?:/[0-9]+)?)\\s+([-+*/])\\s+([-+]?[0-9]+(?:/[0-9]+)?)");

    // Match input against regex pattern
    smatch match;
    if (regex_match(input, match, regexPattern)) {
        string operand1 = match[1];
        string operand2 = match[3];
        char operation = match[2].str()[0];

        int numerator1, denominator1, numerator2, denominator2;
        extractOperands(operand1, numerator1, denominator1);
        extractOperands(operand2, numerator2, denominator2);

        if (denominator1 == 0 || denominator2 == 0) {
            cout << "Error: Denominator cannot be zero. Please enter a new expression." << endl;
            return;
        }

        switch (operation) {
            case '+':
                addFractions(numerator1, denominator1, numerator2, denominator2);
                break;
            case '-':
                subtractFractions(numerator1, denominator1, numerator2, denominator2);
                break;
            case '*':
                multiplyFractions(numerator1, denominator1, numerator2, denominator2);
                break;
            case '/':
                divideFractions(numerator1, denominator1, numerator2, denominator2);
                break;
            default:
                cout << "Invalid operation. Try again." << endl;
        }
    } else {
        cout << "Invalid operand or operation. Try again." << endl;
    }
}

// Function to display the main menu
void displayMenu() {
    cout << "================\n";
    cout << "      Menu:\n";
    cout << "================\n";
    cout << "ENTER 1:: To use the calculator\n";
    cout << "ENTER 2:: To exit\n";
}

// Main function
int main() {
    while (true) {
        int userChoice;
        displayMenu();
        cout << "Enter your choice (1-2): ";
        cin >> userChoice;

        if (cin.fail()) {
            // Clear error state
            cin.clear();
            // Ignore invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Display error message
            cout << "Invalid input. Please enter a number between 1 and 2.\n";
            continue; // Skip to the next iteration of the loop
        }
        if (userChoice != 1 && userChoice != 2) {
            cout << "Invalid input. Please enter a number between 1 and 2." << endl;
            continue;
        }
        if (userChoice == 2) {
            cout << "Thank you for using the rational number calculator." << endl;
            break; // Exit the program
        }
        if (userChoice == 1) {
            string userInput;
            cout << "Enter your expression, please: ";
            cin.ignore(); // Clear the newline character from the buffer
            getline(cin, userInput);
            processUserInput(userInput);
        }
    }
    return 0;
}
