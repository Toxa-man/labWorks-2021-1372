template <typename Type>

class vector {
private:
	float capacity = 2;
	size_t size, max_size;
	Type* arr;
public:

	vector(size_t start_size = 0) {
		size = start_size;
		if (start_size == 0) {
			max_size = 1;
		}
		else {
			max_size = start_size * capacity;
		}	
		arr = new Type[max_size];
	}
  
	~vector() {
		delete arr;
	}
  
	Type& operator[](size_t index) {
		return arr[index];
	}
  
	size_t getsize() {
		return size;
	}
  
	void push_back(const Type& element) {
		if (size != max_size) {
			arr[size++] = element;
			return;
		}
		else {
			Type* curarr = arr;
			max_size = size * capacity;
			arr = new Type[max_size];
			for (size_t i = 0; i < size; i++) {
				arr[i] = curarr[i];
			}
			arr[size++] = element;
			delete curarr;
			return;
		}
	}

	void push_in(size_t index, const Type& element) {
		if (size != max_size) {
			for (size_t i = size; i > index; i--) {
				arr[i] = arr[i - 1];
			}
			arr[index] = element;
			size++;
			return;
		}
		else {
			Type* curarr = arr;
			max_size = size * capacity;
			arr = new Type[max_size];
			for (size_t i = 0; i < index; i++) {
				arr[i] = curarr[i];
			}
			for (size_t i = size; i > index; i--) {
				arr[i] = curarr[i - 1];
			}
			delete curarr;
			arr[index] = element;
			size++;
			return;
		}
	}

	void erase(size_t index) {
		for (index ; index < size - 1; index++) {
			arr[index] = arr[index + 1];
		}
		size--;
		return;
	}
	

};

template <typename Type>

class list {
private:
	struct Node {
		Type data;
		Node* nextadr = nullptr;
	};
	size_t size;
	Node* head, * last_node;

public:
	list(size_t start_size = 1) {
		head = new Node;
		last_node = head;
		size = start_size;
		Node* cur = head;
		Node* next;
		for (size_t i = 1; i < start_size; i++) {
			next = new Node;
			cur->nextadr = next;
			cur = next;
			last_node = cur;
		}
	}
  
	~list() {
		Node* next ;
		do {
			next = head->nextadr;
			delete head;
			head = next;
		} while (head != nullptr);
	}
  
	Type& operator[](size_t index) {
		Node* cur = head;
		for(size_t i = 0; (i < index)&&(index < size); i++) {
			cur = cur->nextadr;
		}
		return cur->data;
	}

	void push_back(const Type& element) {
		Node* new_node = new Node;
		new_node->data = element;
		last_node->nextadr = new_node;
		last_node = new_node;
		size++;
	}

	void push_in(size_t index, const Type& element) {
		Node* new_node = new Node;
		new_node->data = element;
		Node* cur = head;
		for (size_t i = 0; i < index-1; i++) {
			cur = cur->nextadr;
		}
		new_node->nextadr = cur->nextadr;
		cur->nextadr = new_node;
		size++;
	}

	void push_front(const Type& element) {
		Node* new_node = new Node;
		new_node->data = element;
		new_node->nextadr = head;
		head = new_node;
		size++;
	}

	void erase(size_t index) {
		Node* cur = head;
		for (size_t i = 0; i < index - 1; i++) {
			cur = cur->nextadr;
		}
		Node* node_to_delete = cur->nextadr;
		cur->nextadr = cur->nextadr->nextadr;
		delete node_to_delete;
		size--;
	}

	size_t getsize() {
		return size;
	}
};

int main()
{
	return 0;
}
