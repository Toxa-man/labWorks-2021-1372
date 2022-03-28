#define CAPACITY 5

#include <iostream>

//#include <vector>
using namespace std;

template <typename T>
class _vector {
private:
	T *mas;
	int size;
	int realSize;
	int capacity;

	//проверка массива на заполнение
	bool checkForCompletion() {
		if (size == realSize) {
			return true;
		}
		else { return false; }
	}
	bool checkForCompletion(int _size) {
		if (_size == realSize) {
			return true;
		}
		else { return false; }
	}
	//создание нового массива после заполнения старого
	void newMas() {
		T* temp = new T[size * capacity];
		for (int i = 0; i < size; i++) {
			temp[i] = mas[i];
		}
		mas = temp;
		realSize = size * capacity;
	}
public:
	_vector() {
		size = 0;
		capacity = CAPACITY;
		realSize = capacity;
		mas = new T[capacity];
	}
	_vector(int _size) {
		size = _size;
		capacity = CAPACITY;
		realSize = _size * capacity;
		mas = new T[realSize];
		
	}
	//возвращает размер массива
	int getSize() { return size; }
	//возвращает количество элементов которые может содержать массив без выделения дополнительной памяти
	int getCapacity() { 
		if (size == 0) { return capacity; }
		else { return realSize; }
	}

	//перегрузка оператора []
	T& operator [](int index){
		if (index >= 0 && index < size) {
			return mas[index];
		}
	}

	/*T& operator=(T temp) {
		*this = temp;
		return *this;
	}*/

	//вставка в конец массива
	void push_back(T temp) {
		if (checkForCompletion()) {
			newMas();
		}
		mas[size] = temp;
		size++;
		
	}
	//вставка элемента по индексу
	void push(T temp, int index) {
		if (index >= 0 && index < size) {
			int tmp;
			if (checkForCompletion(size + 1)) {
				newMas();
			}
			for (int i = 0; i < size + 1; i++) {
				if (i == index) {
					tmp = mas[i];
					mas[i] = temp;
					i++;
					while (i < size + 1) {
						temp = tmp;
						tmp = mas[i];
						mas[i] = temp;
						i++;
					}
					size++;
					return;
				}
			}
		}
		else {
			cout << "Error::array out of bounds";
		}
	}

	void erase(int index) {
		if (index >= 0 && index < getSize()) {
			for (int i = index; i < getSize()-1; i++) {
				mas[i] = mas[i + 1];
			}
			size--;
			realSize = size * capacity;
		}
		else {
			cout << "Error::array out of bounds";
		}
		
	}

	~_vector() {
		delete mas;
	}
};

int main() {
	_vector <int> mas(10);
	mas[1] = 24;
	cout << mas[1] << endl;
	cout << endl << "--------------" << endl;
	cout << mas.getSize() << endl;
	cout << endl << "--------------" << endl;
	mas.push_back(5);
	cout << mas[10]<<endl;
	cout << endl << "--------------" << endl;
	cout << mas.getCapacity() << endl;
	cout << endl << "--------------" << endl;
	_vector <int> arr;
	for (int i = 0; i < 6;i++) {
		arr.push_back(i);
		cout << arr[i] << " ";
	}
	cout << endl << arr.getSize() << " " << arr.getCapacity() << endl;
	cout << endl << "--------------" << endl;
	arr.push(24, 1);
	for (int i = 0; i < arr.getSize(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl << "--------------" << endl;
	arr.erase(0);
	int size = arr.getSize();
	for (int i = 0; i < arr.getSize(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl << arr.getSize()<<" "<<arr.getCapacity() << endl;
	system("pause");
	return 0;
}