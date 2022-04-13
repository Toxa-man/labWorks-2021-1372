#include <iostream>

using namespace std;

using MyType = int;

class MyVector
{
    int size = 0;
    int capasity = 0;
    MyType* massiv = 0;
   
    MyType NullItem()
    {
        MyType ItemNull{ };
        return ItemNull;
    }
    void PrintOneItem(int index)
    {
        cout << massiv[index];
    }
    void IncreasingTheCapasity()
    {
        capasity = capasity * 2;
        MyType* massivCopy = new MyType[capasity];
        for (int i = 0;i < size;i++)
        {
            massivCopy[i] = massiv[i];
        }
        for (int i = size + 1;i < capasity;i++)
        {
            massivCopy[i] = NullItem();
        }
        delete[] massiv;
        massiv = massivCopy;
        massivCopy = 0;
    }
public:
    MyVector()
    {
        size = 0;
        capasity = 2;
        
    }
    MyVector(int newsize) 
    {
        size = newsize;
        capasity = 2 * size;
        massiv = new MyType[capasity];
        for (int i = 0;i < capasity;i++)
        {
            massiv[i]=NullItem();
        }
    }

    ~MyVector()
    {
        delete[] massiv;
    }

    MyVector(const MyVector& copy)
    {
        massiv = new MyType[copy.capasity];
        for (int i = 0;i < copy.capasity;i++)
        {
            massiv[i]= copy.massiv[i];
        }
        size = copy.size;
        capasity = copy.capasity;

    }
    
    MyVector& operator=(const MyVector &copy)
    {
        if (this == &copy)
        {
            return *this;
        }
        delete [] massiv;
        size=copy.size;
        capasity = copy.capasity;
        massiv = new MyType[capasity];
        for (int i = 0;i <capasity;i++)
        {
            massiv[i] = copy.massiv[i];
        }
        return *this;
    }

    void AddToEnd(MyType item);
    void AddByIndex(MyType item,int index);
    void DeleteByIndex(int index);
    int GetSize() {return size;};
    MyType *GetItem(int index);
    void FillByIndex(MyType item, int index);
    void PrintMyVector();
};

void MyVector::AddToEnd(MyType item)
{
    if (size == capasity)
    {
        IncreasingTheCapasity();
    }
    if (massiv == 0)
    {
        massiv = new MyType[capasity];
        for (int i = 0;i < capasity;i++)
        {
            massiv[i] = NullItem();
        }
    }
    
        massiv[size] = item;
        ++size;
}  

void MyVector::AddByIndex(MyType item,int index)
{
    if (index < 0)
    {
       //cout << "Мы не можем добавить элемент с индексом " << index << ", так как нумерация элементов в массиве начинается с нуля" << endl;
        return;
    }
    if (size == 0)
    {
        //cout << "Мы не можем добавить элемент с индексом " << index << ", так как размер вашего массива равен 0" << endl;
        return;
    }
    if (index >= size)
    {
        // << "Мы не можем добавить элемент с индексом "<<index<<", так как индекс последнего элемента в вашем массиве "<<size-1<< endl;
        return;
    }
    if (size-1 == capasity-1)
    {
        IncreasingTheCapasity();
    }
    if (massiv == 0)
    {
        massiv = new MyType[capasity];
        for (int i = 0;i < capasity;i++)
        {
            massiv[i] = NullItem();
        }
    }
    for (int i = size;i > index;i--)
    {
        massiv[i] = massiv[i - 1];
    }
    massiv[index] = item;
    ++size;
}

void MyVector::DeleteByIndex(int index)
{
    if (index < 0)
    {
        //cout << "Мы не можем удалить элемент с индексом " << index << ", так как нумерация элементов в массиве начинается с нуля" << endl;
        return;
    }
    if (size == 0)
    {
        //cout << "Мы не можем удалить элемент с индексом " << index << ", так как размер вашего массива равен 0" << endl;
        return;
    }
    if (index >= size)
    {
        //cout << "Мы не можем удалить элемент с индексом " << index << ", так как индекс последнего элемента в вашем массиве " << size-1 << endl;
        return;
    }
    if (massiv == 0)
    {
        return;
    }
    for (int i = index;i <size;i++)
    {
        massiv[i] = massiv[i + 1];
    }
    massiv[size]=NullItem();
    --size;
}

MyType* MyVector::GetItem(int index)
{
    if (index < 0)
    {
        //cout << "Элемента с индексом " << index << " не существует, так как нумерация элементов в массиве начинается с нуля" << endl;
        return nullptr;
    }
    if (size == 0)
    {
        //cout << "Элемента с индексом " << index << " не существует, так как размер вашего массива равен 0" << endl;
        return nullptr;
    }
    if (index >= size)
    {
        //cout << "Элемента с индексом " << index << " не существует, так как индекс последнего элемента в вашем массиве " << size-1 << endl;
        return nullptr;
    }
    return &massiv[index];
}

void MyVector::FillByIndex(MyType item, int index)
{
    if (index < 0)
    {
        //cout << "Мы не можем заполнить элемент с индексом " << index << ", так как нумерация элементов в массиве начинается с нуля" << endl;
        return;
    }
    if (size == 0)
    {
       // cout << "Мы не можем заполнить элемент с индексом " << index << ", так как размер вашего массива равен 0" << endl;
        return;
    }
    if (index >= size)
    {
        //cout << "Мы не можем заполнить элемент с индексом " << index << ", так как индекс последнего элемента в вашем массиве " << size-1 << endl;
        return;
    }
    massiv[index] = item;
}

void MyVector::PrintMyVector()
{
    if (size == 0)
    {
       //cout << "Размер вашего массива равен 0" << endl;
        return;
    }
    for (int i = 0;i < size;i++)
    {
        cout << "элемент №" << i << " = "; 
        PrintOneItem(i);
        cout<< "; ";
    }
    cout << endl;
}

int main()
{
    setlocale(0, "");
    cout << "Не забывайте, что нумерация элементов начинается с нуля. Размер массива - это количество элементов, а не номер последнего элемента." << endl;
    int n = 2;
    MyVector Vector(n);
    for (int i = 0;i < n;i++)
    {
        MyType items{ i };
        Vector.FillByIndex(items, i);
    }
    Vector.PrintMyVector();
    for (int i = 0;i < 4;i++)
    {
        MyType items{ i+5 };
        Vector.AddByIndex(items, i);
       Vector.PrintMyVector();
    }
    MyType* items1;
    items1 = Vector.GetItem(3);
    if (items1)cout << items1 << endl;
    Vector.DeleteByIndex(5);
    Vector.PrintMyVector();
    MyType items{ 10 };
    Vector.FillByIndex(items,0);
    Vector.PrintMyVector();
    Vector.AddByIndex(items, 3);
    Vector.PrintMyVector();
    Vector.AddToEnd(items);
    Vector.PrintMyVector(); 
    Vector.DeleteByIndex(-4);
    
}