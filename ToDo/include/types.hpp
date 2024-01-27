#pragma once
#include <string>
#include <variant>

struct QuitCommand {
};

struct AddCommand {
	std::string description;
};

struct ToggleCommand {
	int i;
};

struct ClearCommand {
};

using Command = std::variant<
	QuitCommand, 
	AddCommand, 
	ToggleCommand, 
	ClearCommand
>;

//==========================================================

struct QuitResult {
};

struct SuccessResult {
	std::reference_wrapper<const class Database> db;
};

struct OutOfBoundsResult {
	int i;
};

using Result = std::variant<
	QuitResult, 
	SuccessResult, 
	OutOfBoundsResult
>;
