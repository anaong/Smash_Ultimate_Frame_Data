#include "Linked_List.h"

#include <iostream>
#include <string>
#include <cstdio>

Linked_List::Linked_List() {
	head = nullptr;
	current = nullptr;
	temp = nullptr;
}

Linked_List::~Linked_List() {

}

void Linked_List::add_node(std::string* data_add[]) {
	node_ptr node = new Node;
	node->next_node = nullptr;
	node->data_array = *data_add;

	if (head != nullptr) {
		current = head;

		while (current->next_node)
			current = current->next_node;

		current->next_node = node;
	}
	else {
		head = node;
	}
}

void Linked_List::delete_node(std::string* data_del[]) {
	node_ptr delete_ptr = nullptr;
	temp = head;
	current = head;

	while (current != nullptr && current->data_array != *data_del) {
		temp = current;
		current = current->next_node;
	}

	if (current == nullptr) {
		std::cout << "Data not found" << std::endl;
		delete delete_ptr;
	}
	else if (current == head) {
		head = head->next_node;
		temp = nullptr;
		delete delete_ptr;
	}
	else {
		delete_ptr = current;
		current = current->next_node;
		temp->next_node = current;
		delete delete_ptr;
	}
}

void Linked_List::print_list(int size) {
	current = head;

	while (current != nullptr) {
		for (int i = 0; i < size; i++) {
			std::cout << "|" << current->data_array[i] << "|" << "  ";
		}

		std::cout << std::endl;
		current = current->next_node;
	}
}