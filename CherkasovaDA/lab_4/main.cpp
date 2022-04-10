#include <iostream>
using namespace std;
 
struct MyType
{
    int a=0;
};

struct ItemList
{
    MyType BodyObject;
    ItemList* NextObject=0;
};
class MyList
{
    ItemList* head;
    int size;
    void printItem(MyType item)
    {
        cout << item.a;
    }
public:

    MyList()
    {
        MyType itemCopy{ 0 };
        head = new ItemList;
        head->BodyObject = itemCopy;
        size = 0;
    }
    MyList(int newsize)
    {
        MyType itemCopy{ 0 };
        head = new ItemList;
        while (size!=newsize)
        {
            AddToEnd(itemCopy);
        }
    }
    ~MyList()
    {
        for (int i = size;i > 0;i--)
        {
            DeleteByIndex(i);
            cout << "удален элемент №" << i<<endl;
        }
    }
    MyList(const MyList& copy)
    {
        head = new ItemList;
        ItemList* copy2 = copy.head;
        for (int i = 1;i <= copy.size;i++)
        {
            AddToEnd(copy2->BodyObject);
            copy2 = copy2->NextObject;
        }
    }
    MyList& operator=(const MyList& copy)
    {
        if (this == &copy)
        {
            return *this;
        }
        for (int i = size;i > 0;i--)
        {
            DeleteByIndex(i);
        }
        head = new ItemList;
        ItemList* copy2 = copy.head;
        for (int i = 1;i <= copy.size;i++)
        {
            AddToEnd(copy2->BodyObject);
            copy2 = copy2->NextObject;
        }
        return *this;
    }
    ItemList* GetItem(int index);
    void AddToFirst(MyType item);
    void AddToEnd(MyType item);
    void AddByIndex(MyType item, int index);
    void DeleteByIndex(int index);
    int GetSize() { return size; };
    void SetByIndex(MyType item, int index);
    void PrintMyList();
    ItemList* DlyaProverki() { return head; }
};

void MyList::AddToFirst(MyType item)
{
    if (size == 0)
    {
        head = new ItemList;
        head->BodyObject = item;
        head->NextObject = 0;
    }
    else
    {
        ItemList* HeadCopy = new ItemList;
        HeadCopy->BodyObject = item;
        HeadCopy->NextObject = head;
        head = HeadCopy;
    }
    ++size;
}

ItemList* MyList::GetItem(int index)
{
    if (index <= 0)
    {
        cout << "Мы не можем вернуть вам элемент с индексом "<<index<<", так как нумерация элементов списка начинается с единицы." << endl;
        return 0;
    }
    else if (size == 0)
    {
        cout << "Мы не можем вернуть вам элемент с индексом " << index << ", так как в вашем списке еще нет ни одного элемента" << endl;
        return 0;
    }
    else if (index > size)
    {
        cout << "Мы не можем вернуть вам элемент с индексом " << index << ", так как размер вашего списка "<<size << endl;
        return 0;
    }
    else
    {
        int count = 1;
        ItemList* cur = head;
        while (count!= index)
        {
            cur = cur->NextObject;
            ++count;
        }
        return cur;
    }
}

void MyList::AddToEnd(MyType item)
{
    if (size == 0)
    {
        head = new ItemList;
        head->BodyObject = item;
        head->NextObject = 0;
    }
    else
    {
        ItemList* CopyEnd = new ItemList;
        CopyEnd->NextObject = 0;
        CopyEnd->BodyObject = item;
        GetItem(size)->NextObject = CopyEnd;
    }
    ++size;
}

void MyList::AddByIndex(MyType item, int index)
{
    if (index == 1 && size == 0)
    {
        head = new ItemList;
        head->BodyObject = item;
        head->NextObject = 0;
    }
    else if (index == size + 1)
    {
        ItemList* CopyEnd = new ItemList;
        GetItem(size)->NextObject = CopyEnd;
        CopyEnd->NextObject = 0;
        CopyEnd->BodyObject = item;
    }
    else if (index > size)
    {
        cout << "Мы не можем добавить элемент с индексом " << index << ", так как размер вашего списка "<< size << endl;
        return;
    }
    else if (index <= 0)
    {
        cout << "Мы не можем добавить элемент с индексом " << index << ", так как нумерация списка начинается с единицы" << endl;
        return;
    }
    else
    {
        ItemList* CopyEnd = new ItemList;
        CopyEnd->NextObject = GetItem(index);
        CopyEnd->BodyObject = item;
        if (index!=1) { GetItem(index - 1)->NextObject = CopyEnd; }
        else {
            head = CopyEnd;
        }
    }
    ++size;
}

void MyList::DeleteByIndex(int index)
{
    if (index > size)
    {
        cout << "Мы не можем удалить элемент с индексом " << index << ", так как размер вашего списка " << size << endl;
        return;
    }
    else if (size == 0)
    {
        cout << "Мы не можем удалить элемент с индексом " << index << ", так как в вашем списке еще нет ни одного элемента "  << endl;
        return;
    }
    else if (index<=0){
        cout << "Мы не можем удалить элемент с индексом " << index << ", так как нумерация списка начинается с единицы" << endl;
        return;
    }
    else if (size == 1)
    {
        delete head;
    }
    else if (index == 1)
    {
        ItemList* Copy = head;
        head = head->NextObject;
        delete Copy;
    }
    else {
        ItemList* Copy = GetItem(index);
        GetItem(index - 1)->NextObject = GetItem(index)->NextObject;
        delete Copy;
    }
    --size;
}

void MyList::SetByIndex(MyType item, int index)
{
    if (index > size)
    {
        cout << "Мы не можем изменить элемент с индексом " << index << ", так как размер вашего списка " << size << endl;
        return;
    }
    else if (index <= 0)
    {
        cout << "Мы не можем добавить элемент с индексом " << index << ", так как нумерация списка начинается с единицы" << endl;
        return;
    }
    GetItem(index)->BodyObject = item;
}

void MyList::PrintMyList()
{
    if (size == 0)
    {
        cout << "В вашем списке нет элементов" << endl;
        return;
    }
    ItemList* cur = head;
    for (int i = 1;i <= size;i++)
    {
        cout << "элемент №" << i << " = ";
        printItem(cur->BodyObject);
        cout<< ";" << endl;
        cur = cur->NextObject;
    }
    cout << endl;
}

int main()
{
    setlocale(0, "");
    cout << "Нумерация элементов списка начинается с единицы!" << endl;
    MyList list1(3);
    list1.PrintMyList();
    list1.DeleteByIndex(1);
    list1.PrintMyList();
    MyType body{ 32 };
    list1.SetByIndex(body, 1);
    body.a = 40;
    list1.SetByIndex(body, 2);
    list1.PrintMyList();
    list1.DeleteByIndex(2);
    list1.PrintMyList();
    body.a = 43;
    list1.AddByIndex(body, 1);
    list1.PrintMyList();
    for (int i = 0;i < 3;i++)
    {
        body.a = i;
        list1.AddToEnd(body);
        list1.AddToFirst(body);
    }
    list1.PrintMyList();
    cout << list1.GetItem(3)->BodyObject.a << endl;
    MyList list2 = list1;
    list2.PrintMyList();
    cout << list1.DlyaProverki() << endl;
    cout << list2.DlyaProverki() << endl;
    list1 = list2;
    list1.PrintMyList();
    cout << list1.DlyaProverki() << endl;
    list2.PrintMyList();
    cout << list2.DlyaProverki() << endl;
    MyList list3;
    list3.AddByIndex(body,1);
    list3.PrintMyList();
}
