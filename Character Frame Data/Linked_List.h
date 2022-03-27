#pragma once

#include <string>

class Linked_List {
public:
	Linked_List();
	~Linked_List();

	void add_node(std::string* data_add[]);
	void delete_node(std::string* data_del[]);
	void print_list(int);

private:
	typedef struct Node {
		std::string* data_array;
		Node* next_node;
	}*node_ptr;

	node_ptr head;
	node_ptr current;
	node_ptr temp;
};