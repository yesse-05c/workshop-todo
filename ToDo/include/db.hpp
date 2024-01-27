#pragma once
#include <istream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

struct Item {
	std::string description;
	bool done;
};

class Database : private std::vector<Item> {
public:
	using std::vector<Item>::iterator;
	using std::vector<Item>::const_iterator;
	using std::vector<Item>::begin;
	using std::vector<Item>::end;
	using std::vector<Item>::size;
	using std::vector<Item>::operator[];

	void addItem(std::string description);
	void eraseCompleted();
	void deserialize(std::istream& in);
	void serialize(std::ostream& out) const;
};