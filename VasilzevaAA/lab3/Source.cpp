#include <vector>
#include <iostream>

using namespace std;

template <class Type>
class Vector
{
private:
    Type* ArrName;
    Type* NewArrName;
    int img = 0;
    int size = 0;

    void NewMemory() {
        NewArrName = new Type[size + size / 2]; // выделяем память под "расширенный" массив
        img = size + size / 2; // запоминаем его видимый и полный размер

        for (int i = 0; i < size; i++) {
            NewArrName[i] = ArrName[i];
        }

        delete[] ArrName; // удаляем исходный полный массив
        ArrName = NewArrName; // привязывваем старый указатель к новому массиву
        NewArrName = NULL; // удаляем новый указатель
    }

public:

    Vector() {}

    Vector(unsigned int num) {
        ArrName = new Type[num];
        size = num;
        img = num;
    };

    //функция для создания весктора
    void Creat(unsigned int num) {

        ArrName = new Type[num];
        size = num;
        img = num;
    }; 

    // вывод массива на экран с \n
    void Out() { 
        for (unsigned int i = 0; i < Size(); i++) {
            std::cout << ArrName[i] << ' ';
        }
        std::cout << '\n';
    };

    // количество элементов
    int Size() { 
        return size;
    };

    void Add(unsigned int index, Type element) {
        if (size == img) {
            NewMemory();
        }

        for (unsigned int i = 0; i < size - index; i++) { // переносим элементы на новое место, освобождая место под индекс
            ArrName[size - i] = ArrName[size - i - 1];
        }
        ArrName[index] = element;
        size++;
    };

    void Delete(unsigned int index) {
        for (unsigned int i = index; i < size - 1; i++) {
            ArrName[i] = ArrName[i + 1];
        }
        ArrName[size - 1] = 0;
        size--;
    };

    void AddToTheEnd(Type element) {
        if (size == img) {
            NewMemory();
        }

        ArrName[size] = element;
        size++;
    };

    Type* Link(unsigned int index) {
        if (index < Size()) {
            return ArrName + index * sizeof(Type);
        }
        else {
            std::cout << "Выход за пределы массива" << std::endl; 
            return 0;
        }
    };

    Type& operator[](unsigned int index) {
        return ArrName[index];
    }

    ~Vector() {
        delete[]ArrName;
    };
};

template <class Type>
class List
{
private:

    unsigned int size;

    struct Leaf {
        Type element;
        Leaf* adr = NULL;
    };

    Leaf* next = NULL;
    Leaf* cur = NULL;
    Leaf* list_head = cur;

public:

    List() {};
    List(unsigned int num) {
        for (unsigned int i = 0; i < num; i++) {
            cur = new Leaf;
            cur->adr = next;
            next = cur;

        }

        list_head = cur;
        size = num;
    }

    void Creat(unsigned int num) { 
        for (unsigned int i = 0; i < num; i++) {
            cur = new Leaf;
            cur->adr = next;
            next = cur;

        }

        list_head = cur;
        size = num;
    };

    void Fill() { 
        cur = list_head;

        for (unsigned int i = 0; i < Size(); i++) {
            cur->element = i;
            cur = cur->adr;
        }
    };

    // вывод на экран
    void Out() { 
        cur = list_head;
        for (unsigned int i = 0; i < Size(); i++) {
            std::cout << cur->element << ' ';
            cur = cur->adr;
        }
        std::cout << '\n';
    };

    // размер (кол-во элементов)
    int Size() { 
        return size;
    };

    void Add(unsigned int index, Type element) {
        cur = list_head;
        Leaf* newleaf = new Leaf;
        for (unsigned int i = 0; i < index-1; i++) {
            cur = cur->adr;
        }
        newleaf->adr = cur->adr;
        newleaf->element = element;

        cur->adr = newleaf;

        size++;
    }

    void Delete(unsigned int index) {
        cur = list_head;
        Leaf* pre = NULL;
        for (unsigned int i = 0; i < index; i++) {
            pre = cur;
            cur = cur->adr;
        }

        next = cur->adr;
        delete cur;
        pre->adr = next;

        size--;
    };

    void AddToTheEnd(Type element) {
        cur = list_head;
        Leaf* newleaf = new Leaf;
        for (unsigned int i = 0; i < Size()-1; i++) {
            cur = cur->adr;
        }
        newleaf->adr = cur->adr;
        newleaf->element = element;

        cur->adr = newleaf;

        size++;
    };

    void AddInTheBegin(Type element) {
        cur = list_head;
        Leaf* newleaf = new Leaf;
        
        newleaf->adr = cur;
        newleaf->element = element;

        list_head = newleaf;

        size++;
    };

    Leaf* Link(unsigned int index) {
        cur = list_head;
        for (unsigned int i = 0; i < index; i++) {
            cur = cur->adr;
        }

        return cur;
    };

    ~List() {
        for (int i = 0; i < Size(); i++) {
            cur = list_head->adr;
            delete list_head;
            list_head = cur;
        }
    };

    Type& operator[](unsigned int index) {
        cur = list_head;
        for (int i = 0; i < index; i++) {
            cur = cur->adr;
        }
        return cur->element;
    }

};


int main() {

    setlocale(0, "ru");
    std::cout << "Проверка работы вектора:" << std::endl;
    std::cout << '\n';

    // создание и заполнение

    //Vector<int> my(5);
    Vector<int> my;
    my.Creat(5);
    std::cout << "Размер: " << my.Size() << std::endl;

    for (int i = 0; i < my.Size(); i++) {
        my[i] = i;
    }

    std::cout << "Созданный вектор: " << std::endl;
    for (int i = 0; i < my.Size(); i++) {
        std::cout << my[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << '\n';

    // добавление элемента по индексу (индекс-элемент)

    std::cout << "Вставка 10 на место элемента с идексом 3:" << std::endl;
    my.Add(3, 10);
    my.Out();
    std::cout << "Размер: " << my.Size() << std::endl;
    std::cout << '\n';

    // удаление элемента по индексу
    
    std::cout << "Удаление элемента с индексом 2:" << std::endl;

    my.Delete(2); 
    my.Out();
    std::cout << "Размер: " << my.Size() << std::endl;
    std::cout << '\n';

    // вставка вконец

    std::cout << "Добавление 0 вконец: " << std::endl;
    my.AddToTheEnd(0);
    my.Out();    
    std::cout << '\n';

    // получение ссылок

    for (int i = 0; i < my.Size(); i++) {
        std::cout << my.Link(i) << '\n';
    }
    std::cout << '\n';


    std::cout << "\n**********\n";

    std::cout << "Проверка работы списка:" << std::endl;
    std::cout << '\n';

    // создание списка
    std::cout << "Сoзданный список: " << std::endl;

    //List<int> li;
    //li.Creat(5);
    //li.Fill();

    List<int> li(9);
    for (int i = 0; i < li.Size(); i++) {
        li[i] = i;
    }
    li.Out();

    std::cout << "Размер: " << li.Size() << std::endl;
    std::cout << '\n';

    // добавление элемента
    std::cout << "Вставка 9 на место элемента с индексом 3:" << std::endl;
    li.Add(3, 9);
    li.Out();
    std::cout << '\n';

    // удаление элемента 
    std::cout << "Удаление элемемнта с индексом 2:" << std::endl;
    li.Delete(2);
    li.Out();
    std::cout << '\n';

    // втавка в конец
    std::cout << "Вставка вконец 12:" << std::endl;
    li.AddToTheEnd(12);
    li.Out();
    std::cout << '\n';

    // вставка в начало
    std::cout << "Вставка вначало 199:" << std::endl;
    li.AddInTheBegin(199);
    li.Out();
    std::cout << '\n';

    // получение ссылок
    std::cout << "Получение ссылок:" << std::endl;
    for (unsigned int i = 0; i < li.Size(); i++) {
        std::cout << li.Link(i) << ' ';
    }
    std::cout << std::endl;

    return 0;
}