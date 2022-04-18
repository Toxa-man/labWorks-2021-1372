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
			max_size = 5;
		}
		else {
			max_size = start_size * capacity;
			
		}
		
		arr = new Type[max_size];
	}
	~vector() {
		delete[] arr;
	}
	Type& operator[](size_t index) {
		if (index < size) {
			return arr[index];
		}
		else {
			std::cout << "Index more than size of vector";
			exit;
		}
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
			delete[] curarr;
			return;
		}
	}

	void push_in(size_t index, const Type& element) {
		if (index <= size) {
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
				delete[] curarr;
				arr[index] = element;
				size++;
				return;
			}
		}
		else {
			std::cout << "Index more than size of vector";
			exit;
		}
	}

	void erase(size_t index) {
		if (index < size) {
			for (index; index < size - 1; index++) {
				arr[index] = arr[index + 1];
			}
			size--;
			return;
		}
		else {
			std::cout << "Index more than size of vector";
			exit;
		}
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
	list (size_t start_size = 0) {
		if (start_size != 0) {
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
		else {
			head = nullptr;
			last_node = nullptr;
		}
	}
	~list() {
		Node* next;
		while (head != nullptr) {
			next = head->nextadr;
			delete head;
			head = next;
		}
	}
	Type& operator[](size_t index) {
		if (index < size) {
			Node* cur = head;
			for (size_t i = 0; (i < index); i++) {
				cur = cur->nextadr;
			}
			return cur->data;
		}
		else {
			std::cout << "Index more than size of list" << std::endl;
			exit;
		}
	}

	void push_back(const Type& element) {
		if (size != 0) {
			Node* new_node = new Node;
			new_node->data = element;
			last_node->nextadr = new_node;
			last_node = new_node;
		}
		else {
			head = new Node;
			head->data = element;
			last_node = head;
		}
		size++;
		
	}

	void push_in(size_t index, const Type& element) {
		if (index < size) {
			if (index != 0) {
				Node* new_node = new Node;
				new_node->data = element;
				Node* cur = head;
				for (size_t i = 0; i < index - 1; i++) {
					cur = cur->nextadr;
				}
				new_node->nextadr = cur->nextadr;
				cur->nextadr = new_node;

			}
			else {
				Node* new_node = new Node;
				new_node->data = element;
				new_node->nextadr = head;
				head = new_node;
				
			}

			size++;
		}
		else {
			if (size != 0) {
				std::cout << "Index more than size of list" << std::endl;
				exit;
			}
			else {
				head = new Node;
				head->data = element;
				last_node = head;
				size++;
			}
		}
	}

	void push_front(const Type& element) {
		
		Node* new_node = new Node;
		new_node->data = element;
		new_node->nextadr = head;
		head = new_node;
		if (size == 0) {
			last_node = head;
		}
		size++;
	}

	void erase(size_t index) {
		if (index < size) {
			Node* cur = head;
			if (index == 0) {
				head = head->nextadr;
				delete cur;
			}
			else {
				for (size_t i = 0; i < index - 1; i++) {
					cur = cur->nextadr;
				}
				Node* node_to_delete = cur->nextadr;
				cur->nextadr = cur->nextadr->nextadr;
				delete node_to_delete;
			}
			size--;
		}
		else {
			std::cout << "Index more than size of list or list is empty" << std::endl;
			exit;
		}
	}

	size_t getsize() {
		return size;
	}
};

int main()
{
	return 0;
}
