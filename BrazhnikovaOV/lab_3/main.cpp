#include<iostream>
using namespace std;
class Dynamic_massive {
private:
	int cap = 0;
	int* Newarr; 
	int size;
	int i = 0;
public:
	Dynamic_massive(int nsize = 0) {
		size = 0;
		if (nsize == 0) {
			cap = 2;
		}
		else {
			cap = nsize * 2;
		delete[] Newarr;
	}
	void GetSize() {
		cout << "The size of your massive is ";
		cout << size << endl;
	}
    void Delete_element(int index) {
		if ((index > size) || (index < 0)) { cout << " Mistake, out of range. You tried to delete element: "<<index << endl; }
		 else {
			 for (int i = index; i < size; i++) {
				 Newarr[i] = Newarr[i+1];
			 }
			 size--;
		 }
		
      };
	void Add_element(int index, int value) {
		if ((index<=size) && (index>0)) {
			cap++;
			
			int* temporary = new int(cap);
			
			for (int i = 0; i < index; i++)
			{
				temporary[i] = Newarr[i];
			}
			temporary[index] = value;
			size++;
			for (int i = index; i < size+1; i++) {
				temporary[i+1] = Newarr[i];
			}
			Newarr = new int(cap);
			for (int i = 0; i < size; i++) {
				Newarr[i] = temporary[i];
			}
			delete[] temporary;
		}
		else {
			cout<< "Mistake/n";
		}
		
	};
	void push_back(const int &el) {
		if (size<cap) {
			Newarr[size] = el;
			size++;
         }
		else {
			int* head;
			head = Newarr;
			cap = size*2;
			Newarr = new int[cap];
			for (int i = 0; i < size; i++) {
				Newarr[i] = head[i];
			}
			Newarr[size] = el;
			size++;
			delete[] head;
			
		}
	}
	int& Get(int index) {
			return (Newarr[index]); 
		
	}
	void print() {
		cout << "Your massive: \n";
		for (int i = 0; i < size; i++) {
			 cout << Newarr[i] << endl; 
		}
	}
	
};
class My_List {
private:

	int size;
	struct My_Node {
		My_Node* next;
		int value;
		My_Node(int value = 0, My_Node* next = nullptr) {
			(*this).next = next;
			(*this).value = value;
		}
	} *head;

public:
	My_List() {
		size = 0;
		My_Node* head = nullptr;
	};
	~My_List() {};

	void push_back(int value);
	void print();
	void push_front(int value);
	void delete_el(int index);
	void add_el(int index, int value);
	void Get_size();
	int& Get_el(int index);

};

void My_List::push_back(int data)
{
	if (head == nullptr) {
		head = new My_Node(data);

	}
	else {
		My_Node* node_cur = head;
		for (node_cur = head; node_cur->next != nullptr; node_cur = node_cur->next) {};
		node_cur->next = new My_Node(data);

	}
	size++;
}
void My_List::print()
{
	My_Node* node_cur = head;
	for (int i = 0; i < size; i++) {
		cout << (*node_cur).value << endl;
		node_cur = (*node_cur).next;
	}
}
void My_List::push_front(int value)
{
	if (head == nullptr) {
		head = new My_Node(value);

	}
	else {
		My_Node* node_cur = head;
		head = new My_Node(value, node_cur);
		size++;
	}
}
void My_List::delete_el(int index)
{
	if ((index < 0) || (index >= size)) {
		cout << " Mistake. You tried to delete element (index: " << index << ") which is out of range.\n";
	}
	else {
		if (index == 0) {
			My_Node* node_cur = head;
			My_Node* temp = node_cur;
			node_cur = node_cur->next;
			head = node_cur;
			delete temp;
		}
		else {
			My_Node* node_cur = head;
			for (int i = 0; i < index - 1; i++) {
				node_cur = node_cur->next;
			};
			My_Node* temp = node_cur->next;
			node_cur->next = temp->next;

			delete temp;
		}
		size--;
	}
}
void My_List::add_el(int value, int index)
{
	if ((index > size) || (index < 0)) {
		cout << "You tried to add: " << value << " with index: " << index;
		cout << ". But adding new element is impossible, you are out of range." << endl;
	}
	else {
		My_Node* node_cur = head;
		for (int i = 0; i < index - 1; i++) {
			node_cur = node_cur->next;
		};
		My_Node* element = new My_Node(value, node_cur->next);
		node_cur->next = element;
		size++;
	}
}
void My_List::Get_size()
{
	cout << "The size of your list is " << size << endl;
}
int& My_List::Get_el(int index) {
	My_Node* node_cur = head;
	for (int i = 0; i < index; i++) {
		node_cur = node_cur->next;
	}
	return node_cur->value;
}
int main() {

}