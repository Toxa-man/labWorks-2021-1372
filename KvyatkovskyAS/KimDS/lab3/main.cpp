#include <iostream>
using namespace std;
class dynamic_array {
public:
	int size;
	int capacity;
	int* data;
	dynamic_array() {
		size = 0;
		capacity = 0;
		data = nullptr;
	}
	dynamic_array(int newsize) {
		size = newsize;
		capacity = size * 2;
		if (size != 0) {
			data = new int[capacity];
		}
		else {
			data = nullptr;
		}
	}

	~dynamic_array() {
		delete[] data;
	}
	dynamic_array(const dynamic_array& other) {
		data = new int[other.size];
		for (int i = 0; i < other.size; i++) {
			data[i] = other.data[i];
		}
		size = other.size;
		capacity = other.capacity;
	}

	void push_back(int val) {
		if (size == 0) {
			size++;
			capacity = size * 2;
			data = new int[capacity];
			data[0] = val;
		}
		else {
			if (size > capacity) {
				capacity = size * 2;
				int* new_data = data;
				data = new int[capacity];
				for (int i = 0;i < size; i++) {
					data[i] = new_data[i];
				}
				data[size] = val;
				size++;
				delete[] new_data;
			}
			else {
				data[size] = val;
				size++;
			}
		}
	}
	int getsize() {
		return size;
	}
	void insert(int val, int ind) {
			 if (ind == size) {
				push_back(val);
			 }
			 else {
				 if (ind < size) {
					 if (size > capacity) {
						 capacity = size * 2;
						 int* new_data = data;
						 data = new int[capacity];
						 for (int i = 0; i < size; i++) {
							 data[i] = new_data[i];
						 }
						 data[ind] = val;
						 size++;
						 for (int i = ind; i < size; i++) {
							 data[i + 1] = new_data[i];
						 }
						 delete[] new_data;
					 }

					 else {
						 int* new_data = data;
						 data = new int[capacity];
						 for (int i = 0; i < size; i++) {
							 data[i] = new_data[i];
						 }
						 data[ind] = val;
						 size++;
						 for (int i = ind; i < size; i++) {
							 data[i + 1] = new_data[i];
						 }
						 delete[] new_data;
					 }
				 }
			 }

	}
	void deletebyind(int ind) {
		if (ind < size) {
			int* new_data = data;
			data = new int[capacity];
			for (int i = 0; i < size; i++) {
				data[i] = new_data[i];
			}
			for (int i = ind + 1; i < size;i++) {
				data[i - 1] = new_data[i];
			}
			size--;
			delete[] new_data;
		}
	}
	int* get_reference(int ind) {
		return &data[ind];
	}
	void print_dynamic_array() {
		for (int i = 0;i < size; i++) {
			cout << data[i] << " ";
		}
	}
};
template<typename T>
class MyList {
public:
	MyList() {
		size = 0;
		head = nullptr;
	}
	~MyList() {
		clear();
	}
	T& operator[] (const int ind){
		int counter = 0;
		Node<T>* cur = this->head;
		while (cur != nullptr) {
			if (counter == ind) {
				return cur->data;
			}
			cur = cur->adrNext;
			counter++;
		}
	}
	void push_back(T data) {
		if (head == nullptr) {
			head = new Node<T>(data);
		}
		else {
			Node<T>* cur = this->head;
			while (cur->adrNext != nullptr) {
				cur = cur->adrNext;
			}
			cur->adrNext = new Node<T>(data);
		}
		size++;
	}
	int getsize() {
		return size;
	}

	void push_front(T data) {
		head = new Node<T>(data, head);
		size++;
	}
	void insert(T data, int ind) {
		if (ind == 0) {
			push_front(data);
		}
		else {
			Node<T>* tmp = this->head;
			for (int i = 0; i < ind - 1; i++) {
				tmp = tmp->adrNext;
			}
			tmp->adrNext = new Node<T>(data, tmp->adrNext);
			size++;
		}
	}
	void deletebyind(int ind) {
		if (ind == 0) {
			Node<T>* tmp = head;
			head = head->adrNext;
			delete tmp;
			size--;
		}
		else {
			Node <T>* tmp = this->head;
			for (int i = 0; i < ind - 1; i++) {
				tmp = tmp->adrNext;
			}
			Node <T>* todelete = tmp->adrNext;
			tmp->adrNext = todelete->adrNext;
			delete todelete;
			size--;
		}
	}
	void clear() {
		while (size) {
			Node<T>* tmp = head;
			head = head->adrNext;
			delete tmp;
			size--;
		}
	}
private:
	template<typename T>
	class Node {
	public:
		Node* adrNext;
		T data;
		Node(T data = T(), Node* adrNext = nullptr) {
			this->data = data;
			this->adrNext = adrNext;
		}
	};
	Node<T>* head;
	int size;
};

int main()
{

}