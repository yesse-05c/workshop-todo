#include "console.hpp"
#include "todo.hpp"
#include <fstream>
#include <variant>

int main(int argc, char* argv[]) {
	ToDo todo;
	Console console;
	Command cmd;

	console.printInstructions();

	if (argc > 1) {
		std::ifstream fin(argv[1]);
		auto result = todo.load(fin);
		std::visit(console, result);
	}

	do {
		cmd = console.readCommand();
		auto result = std::visit(todo, cmd);
		std::visit(console, result);
	} while (!std::holds_alternative<QuitCommand>(cmd));

	if (argc > 1) {
		std::ofstream fout(argv[1]);
		todo.store(fout);
	}
}