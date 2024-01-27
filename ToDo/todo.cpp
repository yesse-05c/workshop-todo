#include "todo.hpp"

Result ToDo::execute(QuitCommand) {
	return QuitResult{};
}

Result ToDo::execute(AddCommand cmd) {
	db.addItem(std::move(cmd.description));
	return SuccessResult{ db };
}

Result ToDo::execute(ToggleCommand cmd) {
	if (cmd.i > 0 && cmd.i <= db.size()) {
		Item& item = db[cmd.i - 1];
		item.done = !item.done;
	}
	else {
		return OutOfBoundsResult{ cmd.i };
	}
	return SuccessResult{ db };
}

Result ToDo::execute(ClearCommand cmd) {
	db.eraseCompleted();
	return SuccessResult{ db };
}
