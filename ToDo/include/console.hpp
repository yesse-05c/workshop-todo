#pragma once
#include <iostream>
#include <variant>
#include "types.hpp"


class Console {
public:
	Console(
		std::istream& in = std::cin, 
		std::ostream& out = std::cout,
		std::ostream& err = std::cerr
	) : _in{ in }, _out{ out }, _err{ err } {
	}

	void printInstructions();
	Command readCommand();
	void report(SuccessResult result);
	void report(OutOfBoundsResult result);
	void report(QuitResult);

	template <typename T>
	void operator()(T&& result) {
		return report(std::forward<T>(result));
	}

private:
	std::istream& _in;
	std::ostream& _out;
	std::ostream& _err;
};

