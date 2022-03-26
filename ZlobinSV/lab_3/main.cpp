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
        if (size == 0){
             size = 1;
            capacity = size * 2;
            data = new int[capacity];
         data[0]=val;
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
                for (int i = num+1; i < size; i++) {
                    data[i] = tmp[i-1];
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
                for (int i = num+1; i < size; i++) {
                    data[i] = tmp[i - 1];
                }
                delete[] tmp;
            }
        }
        else if(num == size){
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
                for (int i = num+1; i < size; i++) {
                    data[i-1] = tmp[i];
                }
                size--;
                delete[] tmp;
        }
        else { cout << "Error, out of vector" << endl; }
    }
    int* get_reference(int num) {
        if (num < size) {
            
            return (data+num);
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
    int data;
    MyList* next = nullptr;
    int size = 0;
    MyList* end = nullptr;

    ~MyList() {
        
    }
};

MyList* Create_List(int size) {
    MyList* head = new MyList;
    MyList* tmp = head;

    for (int i = 1; i < size; i++) {
        tmp->next = new MyList;
        tmp = tmp->next;
        head->end = tmp;
    }
    head->size = size;
    return head;
}
int Get_Size(MyList* head) {
    int size=0;
    MyList* tmp = head;
    while (tmp != nullptr) {
        size++;
        tmp = tmp->next;
    }
    return size;
}
void Print_Data(MyList* head) {
    MyList* tmp = head;
    while (tmp != nullptr) {
        cout << tmp->data << "  ";
        tmp = tmp->next;
    }
    cout << endl;
}
void Delete_List(MyList* head) {
    MyList* tmp;
    while (head != nullptr) {
        tmp = head->next;
        delete head;
        head = tmp;
    }
}
void Push_Front(MyList*& head) {
    MyList* tmp = head;
    head = new MyList;
    head->next = tmp;
    head->size++;
}
void Push_Back(MyList*& head) {
    head->end->next = new MyList;
    head->end = head->end->next;
    head->size++;
}
void Insert_To_List(MyList*& head,int num) {
    MyList* tmp = head;
    if (num == 0) {
        Push_Front(head);
    }
    else if (num < head->size) {
        for (int i = 0; i < (num-1); i++) {
            tmp = tmp->next;
        }
        MyList* tmp2;
        tmp2 = tmp->next;
        tmp->next = new MyList;
        tmp->next->next = tmp2;
        head->size++;
    }
    else if (num == head->size) {
        Push_Back(head);
    }
    else { cout << "Error, out of list" << endl; }
}
void Delete_Element(MyList*& head, int num) {
    MyList* tmp = head;
    for (int i = 0; i < num - 1; i++) {
        tmp = tmp->next;
    }
    if (num == 0) {
        head->next->size = head->size;
        head = tmp->next;
        delete tmp;
        head->size--;
    }
    else if (num < (head->size)-1) {
        MyList* tmp2 = tmp->next->next;
        delete tmp->next;
        tmp->next = tmp2;
        head->size--;
    }
    else if (num == (head->size) - 1) {
        delete tmp->next;
        tmp->next = nullptr;
        head->end = tmp;
        head->size--;
    }
    else { cout << "Error, out of list" << endl; }
}
MyList* Get_Referense(MyList* head, int num) {
    if (num < head->size) {
        MyList* tmp = head;
        for (int i = 0; i < num; i++) {
            tmp = tmp->next;
        }
        return tmp;
    }
    else { cout << "Error, out of List"; return nullptr; }
}


int main()
{
    // All checks done
}