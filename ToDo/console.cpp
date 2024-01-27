#include "console.hpp"
#include "db.hpp"
#include <string>
#include <iomanip>
using std::endl;

void clearLine(std::istream& in) {
	while (in && in.get() != '\n');
}

char readAction(std::istream& in) {
	char action;
	in >> action;
	while (in.peek() == ' ' || in.peek() == '\t') {
		in.get();
	}
	return action;
}

AddCommand readAdd(std::istream& in) {
	std::string description;
	std::getline(in, description);
	return { description };
}

ToggleCommand readToggle(std::istream& in) {
	int i;
	in >> i;
	clearLine(in);
	return { i };
}

ClearCommand readClear(std::istream& in) {
	clearLine(in);
	return ClearCommand{};
}

Command Console::readCommand() {
	while (_in) {
		char action = readAction(_in);
		switch (action) {
		case 'a':
		case 'A': 
			return readAdd(_in);
		case 't':
		case 'T': 
			return readToggle(_in);
		case 'c':
		case 'C':
			return readClear(_in);
		case 'q':
		case 'Q': 
			return QuitCommand{};
		default:  
			_err << "Command '" << action << "' is not valid; skipping..." << endl;
			clearLine(_in);
		}
	}
	return QuitCommand{};
}

void Console::report(SuccessResult result) {
	int i = 1;
	_out << endl;
	for (auto& item : result.db.get()) {
		_out << std::setw(3)
			<< i++ << ". ["
			<< (item.done ? 'X' : ' ')
			<< "] " << item.description << endl;
	}
	_out << endl;
}

void Console::report(OutOfBoundsResult result) {
	_err << "No item numbered " << result.i << "; skipping..." << endl;
}

void Console::report(QuitResult) {
	_out << "\nSo long!" << endl;
}

void Console::printInstructions() {
	_err << "Instructions:\n"
		<< "  Enter one command per line.\n"
		<< "  Indexes start at 1 (as labeled).\n"
		<< "Valid commands:\n"
		<< "  a [description] - Add new item\n"
		<< "  t [index]       - Toggle specified item\n"
		<< "  c               - Remove all completed items\n"
		<< "  q               - Quit the program\n"
		<< endl;
}
