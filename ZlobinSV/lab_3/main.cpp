#include <iostream>
using namespace std;

class MyVector {
public:
    int* data;
    int size;
    int capacity;
    MyVector() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }
    MyVector(int newsize) {
        size = newsize;
        capacity = size * 2;
        data = new int[capacity];
    }
    ~MyVector() {
        delete[] data;
    }
    void push_back(int val) {
        if (size == 0) {
            size = 1;
            capacity = size * 2;
            data = new int[capacity];
            data[0] = val;
        }
        else {
            if (size < capacity) {
                data[size] = val;
                size++;
            }
            else {
                capacity = size * 2;
                int* tmp = data;
                data = new int[capacity];
                for (int i = 0; i < size; i++) {
                    data[i] = tmp[i];
                }
                data[size] = val;
                size++;
                delete[] tmp;
            }
        }
    }
    void insert(int num, int val) {
        if (num < size) {
            if (size < capacity) {
                int* tmp = data;
                data = new int[capacity];
                for (int i = 0; i < num; i++) {
                    data[i] = tmp[i];
                }
                data[num] = val;
                size++;
                for (int i = num + 1; i < size; i++) {
                    data[i] = tmp[i - 1];
                }
                delete[] tmp;
            }
            else {
                capacity = size * 2;
                int* tmp = data;
                data = new int[capacity];
                for (int i = 0; i < num; i++) {
                    data[i] = tmp[i];
                }
                data[num] = val;
                size++;
                for (int i = num + 1; i < size; i++) {
                    data[i] = tmp[i - 1];
                }
                delete[] tmp;
            }
        }
        else if (num == size) {
            push_back(val);
        }
        else { cout << "Error, out of vector" << endl; }
    }
    void delete_a(int num) {
        if (num < size) {
            int* tmp = data;
            data = new int[capacity];
            for (int i = 0; i < num; i++) {
                data[i] = tmp[i];
            }
            for (int i = num + 1; i < size; i++) {
                data[i - 1] = tmp[i];
            }
            size--;
            delete[] tmp;
        }
        else { cout << "Error, out of vector" << endl; }
    }
    int* get_reference(int num) {
        if (num < size) {

            return (data + num);
        }
        else {
            cout << "Error, out of vector" << endl; return nullptr;
        }
    }
    int get_size() {
        return size;
    }
    void print_data() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << "  ";
        }
        cout << endl;
    }
};

class MyList {
public:
    class MyNode {
    public:
        int data=0;
        MyNode* next = nullptr;
    };
    MyNode* head = nullptr;
    int size = 0;
    MyNode* end = nullptr;

    MyList(int new_size) {
        Create_List(new_size);
    }
    ~MyList() {
        Delete_List();
    }

    void Create_List(int new_size) {
        head = new MyNode;
        MyNode* tmp = head;

        for (int i = 1; i < new_size; i++) {
            tmp->next = new MyNode;
            tmp = tmp->next;
        }
        size = new_size;
        end = tmp;
    }
    int Get_Size() {
        int c_size = 0;
        MyNode* tmp = head;
        while (tmp != nullptr) {
            c_size++;
            tmp = tmp->next;
        }
        return c_size;
    }
    void Print_Data() {
        MyNode* tmp = head;
        while (tmp != nullptr) {
            cout << tmp->data << "  ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    void Delete_List() {
        MyNode* tmp;
        while (head != nullptr) {
            tmp = head->next;
            delete head;
            head = tmp;
        }
    }
    void Push_Front(int val) {
        MyNode* tmp = head;
        head = new MyNode;
        head->next = tmp;
        head->data = val;
        size++;
    }
    void Push_Back(int val) {
        end->next = new MyNode;
        end = end->next;
        end->data = val;
        size++;
    }
    void Insert_To_List(int num, int val) {
        MyNode* tmp = head;
        if (num == 0) {
            Push_Front(val);
        }
        else if (num < size) {
            for (int i = 0; i < (num - 1); i++) {
                tmp = tmp->next;
            }
            MyNode* tmp2;
            tmp2 = tmp->next;
            tmp->next = new MyNode;
            tmp->next->data = val;
            tmp->next->next = tmp2;
            size++;
        }
        else if (num == size) {
            Push_Back(val);
        }
        else { cout << "Error, out of list" << endl; }
    }
    void Delete_Element(int num) {
        MyNode* tmp = head;
        for (int i = 0; i < num - 1; i++) {
            tmp = tmp->next;
        }
        if (num == 0) {
            head = tmp->next;
            delete tmp;
            size--;
        }
        else if (num < size - 1) {
            MyNode* tmp2 = tmp->next->next;
            delete tmp->next;
            tmp->next = tmp2;
            size--;
        }
        else if (num == size - 1) {
            delete tmp->next;
            tmp->next = nullptr;
            end = tmp;
            size--;
        }
        else { cout << "Error, out of list" << endl; }
    }
    MyNode* Get_Referense(int num) {
        if (num < size) {
            MyNode* tmp = head;
            for (int i = 0; i < num; i++) {
                tmp = tmp->next;
            }
            return tmp;
        }
        else { cout << "Error, out of List"; return nullptr; }
    }
};



int main()
{
   
}