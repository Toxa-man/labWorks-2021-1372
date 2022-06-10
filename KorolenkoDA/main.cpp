#include <iostream>

using namespace std;


class vector
{
private:
	unsigned size;
	int* parr;
	unsigned capacity;

public:
	void capacity() 
	{
		capacity *= 2;
		int* lit = parr;
		parr = new int[capacity];
		for (int i = 0; i < size; i++) 
			parr[i] = lit[i];
		delete[] parr;
	}

	vector() 
	{
		parr = nullptr;
		size = 0;
		capacity = 2;
		parr = new int[capacity];
	}
	~vector() 
	{
		delete[]parr;
		parr = nullptr;
	}
	void insert(int val, int index)
	{
		if (index == size)
			pushback(val);
		else if (index < size)
		{
			if (size == capacity)
				capacity();
			size += 1;
			int* lit = parr;
			parr = new int[capacity];
			for (int i = 0; i < index; i++)
				parr[i] = lit[i];
			parr[index] = val;
			for (int j = index + 1; j < size; j++)
				parr[j] = lit[j - 1];
			delete[]lit;
		}
		else
			cout << "Error" << endl;
	}
	void wipe(int index)
	{
		if (index >= size)
			cout << "Error" << endl;
		else
		{
			size -= 1;
			int* lit = parr;
			parr = new int[capacity];
			for (int i = 0; i < index; i++)
				parr[i] = lit[i];
			for (int p = index; p < size; p++)
				parr[p] = lit[p + 1];
			delete[]lit;
		}
	}
	vector(int amount) 
	{
		size = amount;
		capacity = size * 2;
		parr = new int[capacity];
	}
	void pushback(int increase)
	{
		if (size == capacity) 
			capacity();
		parr[size] = increase;
		size++;
	}
	int &get_the_link(int index) 
	{
		if (index >= size) 
			cout << "Error" << endl;
		else
			return parr[index];
	}
	int get_size()
		return size;
	int vector_size()
		return size;
};
//______________________________________________________________________________________________________________________________________
//______________________________________________________________________________________________________________________________________
template<typename T>
class list 
{
private:
	int sizelist;
	template<typename T>
	class ellist
	{
		ellist* pnext;
		T data;
		ellist(T data, ellist* pnext = nullptr)
		{
			this->data = data;
			this->pnext = pnext;
		}
	};
	ellist<T>* head;
	void clear() {
		while (sizelist != 0)
			front();
	}
	void front() {
		ellist<T>* tmp = head;
		head = head->pnext;
		delete tmp;
		sizelist -= 1;
	}
public:
	list() 
	{
		int sizelist = 0;
		head = nullptr;
	}
	~list() 
		clear();
	
	void pushback(T data)
	{
		if (head == nullptr)
			head = new ellist<T>(data);
		else 
		{
			ellista<T>* tmp = this->head;
			while (tmp->pnext != nullptr) 
				tmp = tmp->pnext;
			tmp->pnext = new ellist<T>(data);
		}
		sizelist += 1;
	}
	
	T& getreference(int index) 
	{
		int count = 0;
		ellist<T>* tmp = this->head;
		while (count != index) 
		{
			tmp = tmp->pnext;
			count += 1;
		}
		return tmp->data;

	}
	void insert(T data, int index) 
	{
		if (index == 0)
			push_front(data);
		else 
		{
			ellist<T>* tmp = this->head;
			for (int i = 0; i < index - 1; ++i) 
				tmp = tmp->pnext;
			ellist<T>* newelement = new ellist<T>(data, tmp->pnext);
			tmp->pnext = newelement;
			sizelist += 1;
		}
	}
	void erase(int index) 
	{
		if (index == 0)
			pop_front();
		else
		{
			ellist<T>* tmp = this->head;
			for (int i = 0; i < index - 1; ++i)
				tmp = tmp->pnext;
			ellist<T>* deleteelement = tmp->pnext;
			tmp->pnext = deleteelement->pnext;
			delete deleteelement;
			sizelist -= 1;
		}
	}
	void pushfront(T data)
	{
		head = new ellist<T>(data, head);
		sizelist += 1;
	}
	int getsize()
		return sizelist;
};
