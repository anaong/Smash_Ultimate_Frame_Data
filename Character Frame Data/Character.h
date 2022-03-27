#pragma once

#include "Linked_List.h"

#include <string>

class Character {
public:
	Character(int, std::string, std::string);
	~Character();

	int get_owner_id() const;
	std::string get_name() const;
	std::string get_display_name() const;
	Linked_List& get_linked_list() const;

	void set_linked_list(Linked_List& data_list);

	void print();
	void print_linked_list(int size);

private:
	int owner_id;
	std::string name;
	std::string display_name;
	Linked_List* move_set;
};
