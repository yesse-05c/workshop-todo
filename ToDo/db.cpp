#include "db.hpp"
#include <algorithm>
#include <iomanip>

void Database::addItem(std::string description) {
	emplace_back(std::move(description), false);
}

void Database::eraseCompleted() {
	auto dst = begin();
	for (auto src = begin(); src != end(); ++src) {
		if (! src->done) {
			*dst++ = *src;
		}
	}
	erase(dst, end());
}

void Database::deserialize(std::istream& in) {
	bool completed;
	std::string description;
	in >> std::boolalpha;
	while (in >> completed && in.ignore() && getline(in, description)) {
		emplace_back(std::move(description), completed);
	}
}

void Database::serialize(std::ostream& out) const {
	out << std::boolalpha;
	for (auto& item : *this) {
		out << item.done << ' ' << item.description << '\n';
	}
}
