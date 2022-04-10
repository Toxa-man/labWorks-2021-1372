#include <iostream>
using namespace std;

class Vector	 {
public:
	int* data;
	int size=0, dimensions=0;
	Vector(int nsize) {
		size = nsize;
		dimensions = size*2;
		data = new int[dimensions];
	}
	void insert(int i,int value) {
		if (size < i) {
			exit();
		}
		if (size < dimensions) {
			int* data2 = new int[dimensions];
			for (int k = 0; k < i; k++) {
				data2[k] = data[k];
			}
			data2[i] = value;
			for (int m = i; m < size++; m++) {
				data2[m + 1] = data[m];
			}
			delete[] data;
			data = data2;
		}
		else {
			dimensions = 2 * size;
			int* data2 = new int[dimensions];
			for (int k = 0; k < i; k++) {
				data2[k] = data[k];
			}
			data2[i] = value;
			for (int m = i; m < size++; m++) {
				data2[m + 1] = data[m];
			}
			delete[] data;
			data = data2;
		}
	}
	void del(int index) {
		if (index < size){
			int* data2 = new int[dimensions];
			for (int i = 0; i < index;i++) {
				data2[i] = data[i];
			}
			for (int c = index+1;c<size;c++) {
				data2[c] = data[c+1];
			}
			size--;
			delete[] data;
			data = data2;
		}
	}
	int* link(int idex) {
		if (idex < size) return (data + idex);
		else exit();
		return 0;
	}
	void push_back(int value) {
		if (size == 0) {
			size = 1;
			dimensions = size * 2;
			data = new int[dimensions];
			data[0] = value;
		}
		else if (size<dimensions){
			data[size] = value;
			size++;
		}
		else {
			dimensions = 2 * size;
			int* data2 = new int[dimensions];
			for (int i=0;i<size; i++) {
				data2[i] = data[i];
			}
			data2[size] = value;
			size++;
			delete[] data;
			data = data2;
}
	}
	int get_size() {
		return size;
	}
	void print() {
		for (int i = 0;i<size; i++) {
			cout << data[i] << endl;
		}
	}
	~Vector() {
		delete[] data;
	}
private:
	void exit() {
		cout << "Вы вышли за границы массива" << endl;
	}
};

class List {
private:
	class Node {
	public:
		int data;
		Node* next;
		Node(int data = 0, Node* next = nullptr) {
			this->data = data;
			this->next = next;
		}
	};
	int size;
	Node* head=nullptr;
public:
	//
	List() {
		size = 0;
		head = nullptr;
	}
	//
	~List() {
		while (size)
		{
			pop();
		}
		size = 0;
	}
	void insert(int data, int index) {
		if (index == 0) push_front(data);
		else {
			Node* current = this->head;
			for (int c = 0; c < index - 1; c++) current = current->next;
			current->next = new Node(data, current->next);
		}
		size++;
	}

	void clear(int index) {
		if (index==0) {
			pop();
		}
		else {
			Node* current = this->head;
			for (int i = 0; i < index - 1; i++) {
				current = current->next;
			}
			Node* f_del = current->next;
			current->next = f_del->next;
			delete f_del;
			size--;
		}
	}
	Node* link(unsigned int index) {
		if (index == 0) {
			return head;
		}
		else {
			int count = 0;
			Node* current = this->head;
			while (current != nullptr) {
				if (count == index) {
					return current;
				}
				else {
					current = current->next;
					count++;
				}
			}
			return current;
		}
	}
	void push_back(int data) {
		if (head == nullptr) {
			head = new Node(data);
		}
		else {
			Node* current =  this->head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = new Node(data);
		}
		size++;
	}
	//
	int get_size() {
		return size;
	}
	//
	void push_front(int data) {
		head = new Node(data, head);
		size++;
	}
	//
	void pop() {
		Node* temp = head;
		head = head->next;
		delete temp;
		size--;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
}