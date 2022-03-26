#include <iostream>
#include <cstdlib>


class Vector {
private:

	unsigned size;
	int* data;
	unsigned all_size;

public:

	Vector() {                                    //standart constructor
		data = nullptr;
		size = 0;
		all_size = 0;
	}

	Vector(const unsigned input_size) {          //create the array of the 'input_size' size
		all_size = input_size * 1.5;
		data = new int [all_size];
	}

	void push_back(const int last_obj);         //add the 'last_obj' to the end of the array
	void insert(const unsigned position, const int value);          //add the 'value' with index 'position' to the array
	void print();                                                  //print the array
	void erase(const unsigned position);                           //delete the element with index 'position' from the array
	int& get_element(const unsigned position);                     //get the link to an element with index 'position'
	int get_size();                                                //get the size of the array

	~Vector() {                                                   //destructor
		delete[] data;
		data = nullptr;
	}

};

void Vector::print() {
	for (int i = 0; i < size; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}


void Vector::push_back(const int last_obj) {
	if (size >= all_size) {
		int* temp = data;
		all_size *= 1.5;
		data = new int[all_size];
		for (int i = 0; i < size; i++) {
			data[i] = temp[i];
		}
		data[size] = last_obj;
		size++;
		delete[] temp;
		temp = nullptr;
	}
	else {
		data[size] = last_obj;
		size++;
	}
}



void Vector::insert(const unsigned position, const int value) {
	if (position >= size) {
		std::cout << "The function 'insert' was not completed, index out of range." << std::endl;
		std::exit(0);
	}
	else {
		all_size++;
		int* temp = data;
		data = new int[all_size];
		for (int i = 0; i < position; i++) {
			data[i] = temp[i];
		}
		data[position] = value;
		size++;
		for (int i = position + 1; i < size; i++) {
			data[i] = temp[i - 1];
		}
		delete[] temp;
		temp = nullptr;
	}
}


void Vector::erase(const unsigned position) {
	if (position >= size) {
		std::cout << "The function 'erase' was not completed, index out of range." << std::endl;
		std::exit(0);
	}
	else {
		int* temp = data;
		data = new int[all_size];
		for (int i = 0; i < position; i++) {
			data[i] = temp[i];
		}
		size--;
		for (int i = position; i < size; i++) {
			data[i] = temp[i + 1];
		}
		delete[] temp;
		temp = nullptr;
	}
}


int& Vector::get_element(const unsigned position) {
	if (position >= size) {
		std::cout << "The function 'get_element' was not completed, index out of range." << std::endl;
		std::exit(0);
	}
	else {
		return data[position];
	}
}

int Vector::get_size() {
	return size;
}

//_____________________________________________________________________________________________________________________________________________________


class List {
public:
	List() {
		size = 0;
		head = nullptr;
	}


	int GetSize();
	void push_back(const int data);
	int& get_element(const unsigned position);
	void print();
	void clear();
	void push_front(const int data);
	void insert(const unsigned position, const int data);
	void ereas(const unsigned position);

	~List() {
		clear();
	}

private:

	class Node {

	public:
		Node* pNext;
		int data;
		Node(int data = 0, Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};
	Node* head;
	int size;

};

void List::push_back(int data) {
	if (head == nullptr) {
		head = new Node(data);
	}
	else {
		Node* temp = head;
		while (temp->pNext != nullptr) {
			temp = temp->pNext;
		}
		temp->pNext = new Node(data);
	}
	size++;
}

int List::GetSize() {
	return size;
}

int& List::get_element(const unsigned position)
{
	int count = 0;
	Node* temp = head;
	while (count != position) {
		temp = temp->pNext;
		count++;
	}
	return temp->data;
}

void List::print() {
	Node* temp = head;
	for (int i = 0; i < size; i++) {
		std::cout << temp->data << ' ';
		temp = temp->pNext;
	}
	std::cout << std::endl;
}

void List::clear() {
	Node* temp = head;
	while (head != nullptr) {
		temp = head->pNext;
		delete head;
		head = temp;
	}
	size = 0;
}

void List::push_front(const int data) {
	head = new Node(data, head);
	size++;
}

void List::insert(const unsigned position, const int data) {
	if (position == 0) {
		push_front(data);
	}
	else {
		int count = 0;
		Node* prev = head;
		for(int i = 0; i < position - 1; i++){
			prev = prev->pNext;
		}
		Node* new_element = new Node(data, prev->pNext);
		new_element = prev->pNext;
		size++;
	}
}

void List::ereas(const unsigned position) {
	if (position == 0) {
		Node* temp = head;
		head = temp->pNext;
		delete temp;
		size--;
	}
	else {
		int count = 0;
		Node* prev = head;
		for (int i = 0; i < position - 1; i++) {
			prev = prev->pNext;
		}
		Node* temp = prev->pNext;
		prev->pNext = temp->pNext;
		delete temp;
		size--;
	}
}




int main() {
	return 0;
}