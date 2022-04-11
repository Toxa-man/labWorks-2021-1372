#include <iostream>

using namespace std;



//template<typename T>
class _List {
private:
	struct _Node {
		int val;
		_Node* next;
	};
	_Node * head;
public:
	_List() {
		head = nullptr;
	}
	_List(int size) {
		head = new _Node;
		head->next = nullptr;
		_Node* temp = head;
		for (int i = 0; i < size - 1; i++) {
			temp->next = new _Node;
			temp = temp->next;

		}
		temp->next = nullptr;
	}
	_List(int size, int data) {
		head = new _Node;
		head->next = nullptr;
		_Node* temp = head;
		for (int i = 0; i < size-1; i++) {
			temp->next = new _Node;
			temp->val = data;
			temp = temp->next;

		}
		temp->next = nullptr;
		temp->val = data;
	}
	int getVal() {
		return head->val;
	}
	_Node* operator[](int index) {
		_Node* temp = head;
		int cnt = 0;
		while(temp!=nullptr){
			if (cnt == index) { return temp; }
			temp = temp->next;
			cnt++;
		}
	}

	

	void printList() {
		_Node* temp = head;
		while (temp!= nullptr) {
			cout << temp->val<<" ";
			temp= temp->next;
		}
	}
	void printNode(int index) {
		_Node* temp = this->head;
		int cnt = 0;
		while (temp != nullptr) {
			if (cnt == index) { cout << temp->val; }
			cnt++;
			temp = temp->next;
		}
	}

	int getSize() {
		_Node* temp = this->head;
		int cnt = 0;
		while (temp != nullptr) {
			cnt++;
			temp = temp->next;
		}
		return cnt;
	}
	bool is_empty() {
		if (head == nullptr) { return true; }
		else { return false; }
	}
	
	void push_back(int data) {
		if (is_empty()) {
			head = new _Node;
			head->val = data;
			head->next = nullptr;
		}
		else{
			_Node* temp = head;
			while (temp->next != nullptr) { temp = temp->next; }
			_Node* newNode = new _Node;
			newNode->next = nullptr;
			newNode->val = data;
			temp->next = newNode;
		}
		
	}

	void push_front(int data) {
		if (is_empty()) {
			head = new _Node;
			head->val = data;
			head->next = nullptr;
		}
		else {
			_Node* newNode = new _Node;
			newNode->next = head;
			newNode->val = data;
			head = newNode;
		}
	}

	void push(int index, int data) {
		if (index >= 0 && index < getSize()) {
			if (index == 0) {
				push_front(data);
			}
			else if (index == getSize() - 1) {
				push_back(data);
			}
			else {
				_Node* temp = head;
				_Node* ptr;
				_Node* newNode = new _Node;
				newNode->next = nullptr;
				newNode->val = data;
				int cnt = 0;
				while (temp != nullptr) {
					if (cnt == index - 1) {
						ptr = temp->next;
						temp->next = newNode;
						newNode->next = ptr;
						return;
					}
					cnt++;
					temp = temp->next;
				}
			}
		}
		else { cout << "Error:out of the list"; }

	}

	void deleteNode(int index) {
		if (index >= 0 && index < getSize()) {
			if (index == 0) {
				_Node* ptr = head->next;
				delete head;
				head = ptr;
			}
			else if (index==getSize()-1) {
				int cnt = 0;
				_Node *temp = head;
				while (temp != nullptr) {
					if (cnt == index - 1) {
						_Node* ptr = temp;
						temp = temp->next;
						delete temp;
						ptr->next = nullptr;
						return;
					}
					cnt++;
					temp = temp->next;
				}
			}
			else {
				_Node* temp = head;
				_Node* ptr_priv;
				_Node* ptr_next;
				int cnt = 0;
				while (temp != nullptr) {
					if (cnt == index - 1) {
						ptr_priv = temp;
						temp = temp->next;
						ptr_next = temp->next;
						delete temp;
						ptr_priv->next = ptr_next;
						return;
					}
					cnt++;
					temp = temp->next;
				}

			}
		}
		else{ cout << "Error:out of the list"; }
	}

	~_List() {
		int size = getSize();
		for (int i = 0; i < size; i++) {
			deleteNode(0);
		}
	}
};


int main() {
	_List list(3, 5);
	list.printList();
	cout << endl << "----------------" << endl;
	list.printNode(1);
	cout << endl << "--------" << endl;
	cout <<list.getSize();
	cout << endl << "--------" << endl;
	cout << list.is_empty();
	cout << endl << "--------" << endl;
	_List list1;
	cout << list1.is_empty();
	cout << endl << "--------" << endl;
	list1.push_back(24);
	list1.printList();
	cout << endl << "--------" << endl;
	list.push_back(24);
	list.printList();
	cout << endl << "--------" << endl;
	list.push_front(1);
	list.printList();
	cout << endl << "--------" << endl;
	list.push(1, 100);
	list.printList();
	cout << endl << "--------" << endl;
	list.push(0, 200);
	list.printList();
	cout << endl << "--------" << endl;
	list.deleteNode(0);
	list.printList();
	cout << endl << "--------" << endl;
	list.deleteNode(1);
	list.printList();
	cout << endl << "--------" << endl;
	list.deleteNode(5);
	cout << endl;
	list.printList();
	cout << endl << "--------" << endl;
	list.deleteNode(4);
	list.printList();
	cout << endl << "--------" << endl;
	system("pause");
	return 0;
}