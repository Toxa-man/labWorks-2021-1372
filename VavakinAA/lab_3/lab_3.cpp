#include <iostream>
template <typename T>

class MyVector {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize() {
        T* current_data = data;
        capacity = size * 2;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = current_data[i];
        }
        delete current_data;
    }

public:
    MyVector(size_t new_size = 0) {
        size = new_size;
        if (new_size == 0) {
            capacity = 1;
        }
        else {
            capacity = new_size * 2;
        }
        data = new T[capacity];
    }

    ~MyVector() {
        delete [] data;
    }

    MyVector(const MyVector& other) {
        data = new T[other.capacity];
        for (int i = 0; i < other.size; i++) {
            data[i] = other.data[i];
        }
        size = other.size;
        capacity = other.capacity;
    }

    MyVector& operator=(const MyVector &other) {
        if (this == &other) {
            return *this;
        }
        delete [] data;
        data = new T[other.capacity];
        for (int i = 0; i < other.size; i++) {
            data[i] = other.data[i];
        }
        size = other.size;
        capacity = other.capacity;
        return *this;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    void insert(T element, size_t index) {
        if (size == capacity) {
            resize();
        }
        for (int i = size - 1; i != index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = element;
        size++;
    }

    void push_back(T element) {
        if (size == capacity) {
            resize();
        }
        data[++size] = element;
    }

    void erase(size_t index) {
        for (index; index != size - 1; index++) {
            data[index] = data[index + 1];
        }
        size--;
    }

    size_t getsize(){
        return size;
    }

    T& get_element(size_t index) {
        return data[index];
    }
};

template <typename T>

class LinkedList {
private:
    struct Node {
        T data;
        Node* next = nullptr;
        Node(T data, Node* next = nullptr)
        {
            this->data = data;
            this->next = next;
        }
    };
    size_t size;
    Node* head;
    Node* tail;

public:
    LinkedList() {
        size = 0;
        head = tail = nullptr;
    }

    ~LinkedList() {
        Node* current;
        do {
            current = head->next;
            delete head;
            head = current;
        } while (head != nullptr);
    }

    T& operator[](size_t index) {
        Node* current = head;
        for (size_t i = 0; (index < size) && (i < index); i++) {
            current = current->next;
        }
        return current->data;
    }

    T& getdata(size_t index) {
        Node* current = head;
        for (size_t i = 0; (index < size) && (i < index); i++) {
            current = current->next;
        }
        return current->data;
    }

    void push_front(T data) {
        head = new Node(data, head);
        if (size == 0) {
            tail = head;
        }
        size++;
    }

    void push_back(T data) {
        if (size == 0) {
            tail = head = new Node(data, head);
        }
        else {
            Node* current = new Node(data, nullptr);
            tail->next = current;
            tail = current;
        }
        size++;
    }
    
    void insert(T data, size_t index) {
        if (index == 0)
        {
            push_front(data);
        }
        else if (index == size) {
            push_back(data);
        }
        else
        {
            Node* previous = head;

            for (int i = 0; i < index - 1; i++)
            {
                previous = previous->next;
            }

            Node* current = new Node(data, previous->next);

            previous->next = current;

            size++;
        }
    }

    void erase(size_t index) {
        Node* current = head;
        Node* previous = current;

        for (size_t i = 0; i < index; i++) {
            previous = current;
            current = current->next;
        }

        if (index == 0) {
            head = current->next;
            delete current;
        }
        else if (index == size - 1) {
            delete current;
            previous->next = nullptr;
            tail = previous;
        }
        else {
            previous->next = current->next;
            delete current;
        }

        size--;
    }

    size_t getsize(){
        return size;
    }

};

int main()
{
    
}
