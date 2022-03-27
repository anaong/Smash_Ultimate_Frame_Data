#include "Character.h"
#include "Linked_List.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>

const int ROSTER_SIZE = 74;

std::string** read_character_file_data(std::string file);
void check_if_file_open(bool state);
void delete_2d_array(std::string** array, int size);
int hash_name(std::string name);
void get_user_input(std::string& input);
void put_in_frame_data(Character& character);
Linked_List& read_file_frame_data(std::string file, Character& character);

int main() {
	std::string** character_values = read_character_file_data("Character Data/character_values.csv");

	Character* characters[ROSTER_SIZE];
	std::unordered_map<int, Character*> character_map;
	for (int i = 0; i < ROSTER_SIZE; i++) {
		characters[i] = new Character(std::stoi(character_values[i][0]), character_values[i][1], character_values[i][2]);
		character_map[hash_name(characters[i]->get_name())] = characters[i];
	}
	delete_2d_array(character_values, ROSTER_SIZE + 1);

	for (int i = 0; i < ROSTER_SIZE; i++) {
		put_in_frame_data(*characters[i]);
	}

	std::string user_input;
	get_user_input(user_input);

	if (!character_map[hash_name(user_input)]) {
		std::cout << "Input does not exist" << std::endl;
	}
	else {
		character_map[hash_name(user_input)]->print_linked_list(6);
	}

	return 0;
}

std::string** read_character_file_data(std::string file) {
	std::ifstream input_file;
	input_file.open(file);
	check_if_file_open(input_file.is_open());

	std::string** character_values = new std::string* [ROSTER_SIZE + 1];

	std::string value;
	std::getline(input_file, value);//header

	int num = 0;
	while (std::getline(input_file, value, ',')) {
		character_values[num] = new std::string[3];

		value.erase(std::remove(value.begin(), value.end(), '\n'), value.end());
		character_values[num][0] = value;//ownerid

		std::getline(input_file, value, ',');
		character_values[num][1] = value;//name

		std::getline(input_file, value, ',');
		character_values[num][2] = value;//display name

		num++;
	}

	return character_values;
}

void check_if_file_open(bool check) {
	if (!check) {
		std::cout << "Error opening file" << std::endl;
		system("exit");
	}
}


//I created this function
int hash_name(std::string name) {
	int hash_value = 1;

	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
	name.erase(std::remove(name.begin(), name.end(), '.'), name.end());

	for (int i = 0; i < (int)name.length(); i++) {
		hash_value *= name.at(i);
	}

	return hash_value / name.length();
}

void delete_2d_array(std::string** array, int size) {
	for (int i = 0; i < size; i++)
		delete[] array[i];
	delete[] array;
}

void put_in_frame_data(Character& character) {
	std::string frame_data_path = "Character Data/" + character.get_name() + "/" + character.get_name() + "_frame_data.csv";

	character.set_linked_list(read_file_frame_data(frame_data_path, character));
}

Linked_List& read_file_frame_data(std::string file, Character& character) {
	std::ifstream input_file;
	input_file.open(file);
	check_if_file_open(input_file.is_open());

	Linked_List* move_list = new Linked_List();
	std::string* move_values;

	std::string value;

	while (std::getline(input_file, value, ',')) {
		move_values = new std::string[6];

		value.erase(std::remove(value.begin(), value.end(), '\n'), value.end());
		move_values[0] = value;//move type

		std::getline(input_file, value, ',');
		move_values[1] = value;//name

		std::getline(input_file, value, ',');
		move_values[2] = value;//hitbox active

		std::getline(input_file, value, ',');
		move_values[3] = value;//FAF

		std::getline(input_file, value, ',');
		move_values[4] = value;//landing lag

		std::getline(input_file, value, ',');
		move_values[5] = value;//auto cancel

		move_list->add_node(&move_values);
	}

	return *move_list;
}

//I created this function
void get_user_input(std::string& input) {
	std::cout << "Enter a Smash Ultimate Character to look up: ";
	std::getline(std::cin, input);
	input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
	input.erase(std::remove(input.begin(), input.end(), '.'), input.end());
}