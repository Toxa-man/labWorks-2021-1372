#include <windows.h>
#include <iostream>
using namespace std;
class mylist {
private:
    void u_error() {
        cout << "Ошибка! Вы вышли за диапазон списка" << endl;
    }
    class node {
    public:
        node* p_next_element;
        int element;
        node(int u_element = 0, node* u_p_next_el = nullptr) {
            element = u_element;
            p_next_element = u_p_next_el;
        }
    };
    node* the_heading_element;
    int m_size;
public:
    mylist() {
        m_size = 0;
        the_heading_element = nullptr;
    }

    void push_back(int u_element) {
        if (m_size == 0) {
            node* temp = new node;
            temp->element = u_element;
            temp->p_next_element = the_heading_element;
            the_heading_element = temp;
        }
        else {
            node* copy = the_heading_element;
            while (copy->p_next_element != nullptr) {
                copy = copy->p_next_element;
            }
            copy->p_next_element = new node(u_element);
        }
        ++m_size;
    }
    void push_front(int u_element) {
        node* temp = new node;
        temp->element = u_element;
        temp->p_next_element = the_heading_element;
        the_heading_element = temp;
        ++m_size;
    }
    void insert(int u_element, int position) {
        if (position >= 0 && position <= m_size) {
            if (position > 0) {
                node* copy_el = new node;
                copy_el->element = u_element;
                node* cur = the_heading_element;
                for (int i = 0; i < (position - 1); i++) {
                    cur = cur->p_next_element;
                }
                copy_el->p_next_element = cur->p_next_element;
                cur->p_next_element = copy_el;
                ++m_size;
            }
            else
            {
                push_front(u_element);
            }
        }
        else {
            u_error();
        }
    }
    void u_delete(int position) {
        if (position >= 0 && position <= m_size) {
            if (position > 0) {
                node* cur = the_heading_element;
                for (int i = 0; i < (position - 1); i++) {
                    cur = cur->p_next_element;
                }
                node* temp_el = cur->p_next_element;
                cur->p_next_element = cur->p_next_element->p_next_element;
                delete temp_el;
                --m_size;
            }
            else {
                node* cur = the_heading_element;
                the_heading_element = cur->p_next_element;
                delete cur;
                m_size--;
            }
        }
        else {
            u_error();
        }
    };
    node* elemntadress(int position) {
        if (position >= 0 && position < (m_size - 1)) {
            node* current = the_heading_element;
            for (int i = 0; i < position; i++) {
                current = current->p_next_element;
            }
            return current;
        }
        else {
            u_error();
            return nullptr;
        }

    }
    void getsize() {
        cout << "Размер списка: " << m_size << endl;
    }
    void print() {
        if (m_size > 0) {
            cout << "Ваш список в настоящий момент:" << endl;
            node* temp = the_heading_element;
            for (int i = 0; i < m_size; i++) {
                cout << temp->element << " ";
                temp = temp->p_next_element;
            }
            cout << "\n________" << endl;
        }
        else {
            cout << "Ваш список состоит из 0 элементов" << endl;
        }
    }
    ~mylist() {
        node* temp = the_heading_element;
        while (the_heading_element != nullptr) {
            temp = the_heading_element->p_next_element;
            delete the_heading_element;
            the_heading_element = temp;
        }
        m_size = 0;
    }
};

int main() {
    setlocale(0, "");
    //all checks are done.
    return 0;
}