using namespace std;
#include <iostream>
#include <map>
#include <string>
#include <cctype>
#pragma warning(disable : 4005)
#include <windows.h>
class Calculator {
	public:
		bool init();
	private:
		map<char, double> valuesKept;
		void storeValue();
		bool simpleCalc();
		bool clear();
};
bool Calculator::init() {
	int input;
	cout << "0: quit\n1: calculate\n2: store a value\n3: clear\nWhat would you like to do? ";
	cin >> input;
	cin.ignore(10000, '\n');
	while (input != 0) {
		if (input == 1) {
			simpleCalc();
		}
		else if (input == 2) {
			storeValue();
		}
		else if (input == 3) {
			clear();
		}
		else {
			cout << "invalid input" << endl;
			clear();
		}
		cout << "0: quit\n1: calculate\n2: store a value\n3: clear\nWhat would you like to do? ";
		cin >> input;
		cin.ignore(10000, '\n');
	}
	return true;
}
bool Calculator::clear() {
	// taken from stack overflow
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD upperLeft = { 0, 0 };
	DWORD dwCharsWritten;
	FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
		&dwCharsWritten);
	SetConsoleCursorPosition(hConsole, upperLeft);
	return true;
}
void Calculator::storeValue() {
	string stored;
	double value;
	cout << "Enter a letter: ";
	cin >> stored;
	while(!isalpha(stored[0]) || stored.size() > 1) {
		cout << "non-letter entered or more than one character entered" << endl;
		cout << "Enter a letter: ";
		cin >> stored;
	}
	cout << "Enter a number to store: ";
	cin >> value;
	valuesKept[stored[0]] = value;
}
bool Calculator::simpleCalc() {
	// accepts integers and floats returns false if invalid input e.g. entering an operation that is not on the calculator
	string val1;
	string val2;
	double sub1;
	double sub2;
	bool varUsed = false;
	char operation;
	int decimalCount = 0;
	if (!valuesKept.empty()) {
		cout << "If you stored a number in any letter such as 'R', you can use the value by typing that letter\n-------------------------------------" << endl;
	}
	cout << "What will be your first number? ";
	getline(cin, val1);
	//accounts for characters that aren't digits, '.'
	if (val1.size() == 0 || val1[0] == '\n') {
		cout << "[ERROR]: nothing was entered" << endl;
		return false;
	}
	if (val1.size() == 1 && isalpha(val1[0])) {
		if (valuesKept.count(val1[0]) == 0) {
			cout << "[ERROR]: letter does not have an assigned value";
			return false;
		}
		else if (valuesKept.count(val1[0]) == 1) {
			sub1 = valuesKept[val1[0]];
		}
	}
	else {
		for (int i = 0; i < val1.size(); i++) {
			if (val1[i] == '.')
				decimalCount++;
			if (val1[i] != '.' && !isdigit(val1[i])) {
				cout << "[ERROR]: non-digit character or decimal inputted " << "[" << val1[i] << "]" << endl;
				return false;
			}
			if (decimalCount > 1) {
				cout << "[ERROR]: more than one decimal point" << endl;
				return false;
			}
		}
		sub1 = stof(val1);
	}
	cout << "Do you want to multiply, add, divide, or subtract? (enter M, A, D, or S): ";
	cin >> operation;
	if (toupper(operation) != 'M' && toupper(operation) != 'A' && toupper(operation) != 'D' && toupper(operation) != 'S') {
		cout << "Invalid Operation" << endl;
		return false;
	}
	cin.ignore(10000, '\n');
	cout << "What will be your second number? ";
	getline(cin, val2);
	if (val2.size() == 0 || val2[0] == '\n') {
		cout << "[ERROR]: nothing was entered" << endl;
		return false;
	}
	if (val2.size() == 1 && isalpha(val2[0])) {
		if (valuesKept.count(val2[0]) == 0) {
			cout << "[ERROR]: letter does not have an assigned value";
			return false;
		}
		else if (valuesKept.count(val2[0]) == 1) {
			sub2 = valuesKept[val2[0]];
		}
	}
	else {
		decimalCount = 0;
		for (int i = 0; i < val2.size(); i++) {
			if (val2[i] == '.')
				decimalCount++;
			if (val2[i] != '.' && !isdigit(val2[i])) {
				cout << "[ERROR]: non-digit character or decimal inputted " << "[" << val2[i] << "]" << endl;
				return false;
			}
			if (decimalCount > 1) {
				cout << "[ERROR]: more than one decimal point" << endl;
				return false;
			}
		}
		sub2 = stof(val2);
	}
	//Calculation Phase
	if (toupper(operation) == 'M') {
		cout << "Equation: " << val1 << "*" << val2 << " = " << sub1 * sub2 << endl;
		return true;
	}
	else if (toupper(operation) == 'A') {
		cout << "Equation: " << val1 << "+" << val2 << " = " << sub1 + sub2 << endl;
		return true;
	}
	else if (toupper(operation) == 'D') {
		cout << "Equation: " << val1 << "/" << val2 << " = " << sub1 / sub2 << endl;
		return true;
	}
	else if (toupper(operation) == 'S') {
		cout << "Equation: " << val1 << "-" << val2 << " = " << sub1 - sub2 << endl;
		return true;
	}
}
int main() {
	Calculator clack;
	clack.init();
}