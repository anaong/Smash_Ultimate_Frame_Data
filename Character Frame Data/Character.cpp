////////
//I created this object
////////

#include "Character.h"
#include "Linked_List.h"

#include <iostream>
#include <string>

Character::Character(int owner_id, std::string name, std::string display_name) {
	this->owner_id = owner_id;
	this->name = name;
	this->display_name = display_name;
	move_set = new Linked_List();
}

Character::~Character() {
	
}

int Character::get_owner_id() const {
	return owner_id;
}

std::string Character::get_name() const {
	return name;
}

std::string Character::get_display_name() const {
	return display_name;
}

Linked_List& Character::get_linked_list() const {
	return *move_set;
}

void Character::set_linked_list(Linked_List& data_list) {
	move_set = &data_list;
}

//Used for debuging and testing
void Character::print() {
	std::cout << "Owner ID: " << owner_id << " Name: " << name << " Display Name: " << display_name << std::endl;
}

void Character::print_linked_list(int size) {
	move_set->print_list(size);
}