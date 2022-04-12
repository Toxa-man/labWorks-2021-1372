#include <iostream>
using std::cout;
using std::cin;
using std::endl;
template<typename T>
class personal_vector {
	T* parr;
	int size;
	int capacity;
	void add_capacity() {
		capacity *= 2;
		T* tmp = parr;
		parr = new T[capacity];
		for (int i = 0; i < size; i++) {
			parr[i] = tmp[i];
		}
		delete[] tmp;
	}
public:
	personal_vector() {
		size = 0;
		capacity = 2;
		parr = new T[2];
	}
	personal_vector(int amount) {
		size = amount;
		capacity = size*2;
		parr = new T[capacity];
	}
	~personal_vector() {
		delete[]parr;
		
	}
	int get_size() {
		return size;
	}
	void push_back(T val) {
		if (size == capacity) {
			add_capacity();
		}
		parr[size] = val;
		size += 1;
	}
	void insert(T val, int index) {
		if (index == size) {
			push_back(val);
		}
		else if (index < size) {
			if (size == capacity) {
				add_capacity();
			}
			size += 1;
			T* tmp = parr;
			parr = new T[capacity];
			for (int i = 0; i < index; i++) {
				parr[i] = tmp[i];
			}
			parr[index] = val;
			for (int j = index + 1; j < size; j++) {
				parr[j] = tmp[j - 1];
			}
			delete[]tmp;
		}
		else {
			cout << "Eror!!! You can't insert in dimension 'n' dimension 'n+k'!" << endl;
		}
	}
	int& get_reference(int index) {
		if (index >= size) {
			cout << "Eror!!! Index out of range !" << endl;
		}
		else {
			return parr[index];
		}
	}
	void erase(int index) {
		if (index >= size) {
			cout << "Eror!!! You index out of range!" << endl;
		}
		else {
			size -= 1;
			T* tmp = parr;
			parr = new T[capacity];
			for (int i = 0; i < index; i++) {
				parr[i] = tmp[i];
			}
			for (int j = index; j < size; j++) {
				parr[j] = tmp[j + 1];
			}
			delete[]tmp;
		}	
	}
	void print_parr() {
		for (int i = 0; i < size; i++) {
			cout << parr[i] << "  ";
		}
		cout << endl;
	}
};
//_________________________________________________//
template<typename T>
class pers_list {
	int size_list;
	template<typename T>
	class element_lista {
	public:
		element_lista* pnext;
		T data;
		element_lista(T data, element_lista* pnext = nullptr) {
			this->data = data;
			this->pnext = pnext;
		}
	};
	element_lista<T>* head;
	void pop_front() {
		element_lista<T>* tmp = head;
		head = head->pnext;
		delete tmp;
		size_list -= 1;
	}
	void clear() {
		while (size_list != 0) {
			pop_front();
		}
	}
public:
	pers_list() {
		int size_list = 0;
		head = nullptr;
	}
	~pers_list() {
		clear();
	}
	void push_back(T data) {
		if (head == nullptr) {
			head = new element_lista<T>(data);
			
		}
		else {
			element_lista<T>* tmp = this->head;
			while (tmp->pnext != nullptr) {
				tmp = tmp->pnext;
			}
			tmp->pnext = new element_lista<T>(data);
		}
		size_list += 1;
	}
	void push_front(T data) {
		//element_lista<T>* tmp = this->head;
		//tmp->pnext = head;
		//head=head->tmp;
		head = new element_lista<T>(data, head);
		size_list += 1;
	}
	int get_size() {
		return size_list;
	}
	T & get_reference(int index) {
		int count = 0;
		element_lista<T>* tmp = this->head;
		while (count != index) {
			tmp = tmp->pnext;
			count += 1;
		}
		return tmp->data;
			
	}
	void insert(T data,int index){
		if (index == 0) {
			push_front(data);
		}
		else{
			element_lista<T>* tmp = this->head;
			for (int i = 0; i < index - 1; ++i) {
				tmp = tmp->pnext;
			}
			element_lista<T>* new_element = new element_lista<T>(data, tmp->pnext);
			tmp->pnext = new_element;
			size_list += 1;
		}
	} 
	void erase(int index) {
		if (index == 0) {
			pop_front();
		}
		else {
			element_lista<T>* tmp = this->head;
			for (int i = 0; i < index - 1; ++i) {
				tmp = tmp->pnext;
			}
			element_lista<T>* delete_element = tmp->pnext;
			tmp->pnext = delete_element->pnext;
			delete delete_element;
			size_list -= 1;
		}
	}
};
