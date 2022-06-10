#include <iostream>

using namespace std;


class vector
{
private:
	unsigned size;
	int* imp;
	unsigned capacity;

public:
	void dob_capacity() {
		capacity *= 3;
		int* lit = imp;
		imp = new int[capacity];
		for (int i = 0; i < size; i++) {
			imp[i] = lit[i];
		}
		delete[] imp;
	}

	vector() {
		imp = nullptr;
		size = 0;
		capacity = 3;
		imp = new int[capacity];
	}
	~vector() {
		delete[]imp;
		imp = nullptr;
	}
	int conclusion_size() {
		return size;
	}
	vector(int quantity) {
		size = quantity;
		capacity = size * 3;
		imp = new int[capacity];
	}
	void pushback(int uvel) {
		if (size == capacity) {
			dob_capacity();
		}
		imp[size] = uvel;
		size++;
	}
	void wipe(int index) {
		if (index >= size) {
			cout << "Eror" << endl;
		}
		else {
			size -= 1;
			int* lit = imp;
			imp = new int[capacity];
			for (int i = 0; i < index; i++) {
				imp[i] = lit[i];
			}
			for (int p = index; p < size; p++) {
				imp[p] = lit[p + 1];
			}
			delete[]lit;
		}
	}
	int &get_a_link(int index) {
		if (index >= size) {
			cout << "Eror" << endl;
		}
		else {
			return imp[index];
		}
	}
	void insert(int val, int index) {
		if (index == size) {
			pushback(val);
		}
		else if (index < size) {
			if (size == capacity) {
				dob_capacity();
			}
			size += 1;
			int* lit = imp;
			imp = new int[capacity];
			for (int i = 0; i < index; i++) {
				imp[i] = lit[i];
			}
			imp[index] = val;
			for (int j = index + 1; j < size; j++) {
				imp[j] = lit[j - 1];
			}
			delete[]lit;
		}
		else {
			cout << "Eror" << endl;
		}
	}
	int vector_size() {
		return size;
	}
	
};
//______________________________________________________________________________________________________________________________________
//______________________________________________________________________________________________________________________________________
//______________________________________________________________________________________________________________________________________
//______________________________________________________________________________________________________________________________________
template<typename T>
class list {

public:
	list() {
		int sizel = 0;
		beginning = nullptr;
	}
	~list() {
		clear();
	}
	void pushfront(T data) {
		beginning = new ellist<T>(data, beginning);
		sizel += 1;
	}
	int getsize() {
		return sizel;
	}
	void pushback(T data) {
		if (beginning == nullptr) {
			beginning = new ellist<T>(data);

		}
		else {
			ellista<T>* tmp = this->beginning;
			while (tmp->pnext != nullptr) {
				tmp = tmp->pnext;
			}
			tmp->pnext = new ellist<T>(data);
		}
		sizel += 1;
	}
	
	T& getreference(int index) {
		int count = 0;
		ellist<T>* tmp = this->beginning;
		while (count != index) {
			tmp = tmp->pnext;
			count += 1;
		}
		return tmp->data;

	}
	void insert(T data, int index) {
		if (index == 0) {
			push_front(data);
		}
		else {
			ellist<T>* tmp = this->beginning;
			for (int i = 0; i < index - 1; ++i) {
				tmp = tmp->pnext;
			}
			ellist<T>* newel = new ellist<T>(data, tmp->pnext);
			tmp->pnext = newel;
			sizel += 1;
		}
	}
	void erase(int index) {
		if (index == 0) {
			pop_front();
		}
		else {
			ellist<T>* tmp = this->beginning;
			for (int i = 0; i < index - 1; ++i) {
				tmp = tmp->pnext;
			}
			ellist<T>* deleteel = tmp->pnext;
			tmp->pnext = deleteel->pnext;
			delete deleteel;
			sizel -= 1;
		}
	}
private:
	int sizel;
	template<typename T>
	class ellist {
		ellist* pnext;
		T data;
		ellist(T data, ellist* pnext = nullptr) {
			this->data = data;
			this->pnext = pnext;
		}
	};
	ellist<T>* beginning;
	void clear() {
		while (sizel != 0) {
			front();
		}
	}
	void front() {
		ellist<T>* tmp = beginning;
		beginning = beginning->pnext;
		delete tmp;
		sizel -= 1;
	}
};

int main() 
{

}
