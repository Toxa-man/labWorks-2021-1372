#include <iostream>
//Динамический массив
class d_array {
	//Массив
	int* array;
	//Емкость массива
	int array_capacity = 10;
	//Размер массива
	int array_size = 0;
	//Прирост
	int array_offset = 10;

public:
	//Инициализация массива
	d_array() {
		array = new int[array_capacity];
	}
	//Вставка в конец
	void append(int a) {
		if (array_capacity == array_size) {
			array_capacity += array_offset;
			int* new_array = new int[array_capacity];
			for (int i = 0; i < array_size; i++) {
				new_array[i] = array[i];
			}
			delete[] array;
			array = new_array;
		}
		array[array_size] = a;
		array_size += 1;
		
	}
	//Вставка по индексу
	void insert(int index, int a) {
		if (index >= array_size) {
			append(a);
			return;
		}

		if (array_capacity == array_size) {
			array_capacity += array_offset;
			int* new_array = new int[array_capacity];
			for (int i = 0; i < array_size; i++) {
				new_array[i] = array[i];
			}
			delete[] array;
			array = new_array;
		}
		for (int i = array_size - 1; i >= index; i--) {
			array[i + 1] = array[i];
		}
		array[index] = a;
		array_size += 1;
	}
	//Удаление по индексу
	void erase(int index){
		if (index >= array_size) {
			std::cout << "Error";
			return;
		}
		for (int i = index; i < array_size - 1; i++) {
			array[i] = array[i + 1];
		}
		array_size -= 1;
	}
	//Размер массива
	int size() {
		return array_size;
	}
	//Получение элемента по индексу
	int get(int index) {
		if (index >= array_size) {
			return 0;
		}
		return array[index];
	}
	//Вывод элементов
	void print() {
		for (int i = 0; i < array_size; i++) {
			std::cout << array[i] << " ";
		}
	}

};



//Однопоточный список
struct elem {
	int data;
	elem* next_elem;
};

class list {
	elem* first_elem = nullptr;
	elem* last_elem = nullptr;
	
public:
	//Вставка в конец cписка
	void append(int a) {
		elem* new_elem;
		new_elem = new elem;
		new_elem->data = a;
		new_elem->next_elem = nullptr;
		if (first_elem == nullptr) {
			first_elem = new_elem;
		}
		else {
			last_elem->next_elem = new_elem;
		}
		last_elem = new_elem;
	}

	//Вывод всех элементов
	void print() {
		elem* now_elem = first_elem;
		while (now_elem != nullptr) {
			std::cout << now_elem->data << " ";
			now_elem = now_elem->next_elem;
		}
		std::cout << "\n";
	}
	//Размер
	int size() {
		int size_list = 0;
		elem* now_elem = first_elem;
		while (now_elem != nullptr) {
			size_list += 1;
			now_elem = now_elem->next_elem;
		}
		return (size_list);
	}

	//Вставка элемента по индексу
	void insert(int index, int a) {
		elem* now_elem = first_elem;
		if (index >= size()) {
			append(a);

		}
		else if (index == 0) {
			elem* new_elem;
			new_elem = new elem;
			new_elem->data = a;
			new_elem->next_elem = first_elem;
			first_elem = new_elem;

		}
		else {
			for (int i = 1; i  < index - 1; i++) {
				now_elem = now_elem->next_elem;
			}
			elem* new_elem;
			new_elem = new elem;
			new_elem->data = a ;
			new_elem->next_elem = now_elem->next_elem;
			now_elem->next_elem = new_elem;
		}

	}
	//Удаление элемента по индексу
	void erase(int index) {
		elem* now_elem = first_elem;
		if (index == 0) {
			elem* delet_elem;
			delet_elem = first_elem;
			first_elem = delet_elem->next_elem;
			if (first_elem == nullptr) {
				last_elem = nullptr;
			}
			delete delet_elem;
		}
		else {
			for (int i = 0; i < index - 1; i++) {
				now_elem = now_elem->next_elem;
			}

			elem* delet_elem;
			delet_elem = now_elem->next_elem;
			now_elem->next_elem = delet_elem->next_elem;
			if (delet_elem->next_elem == nullptr) {
				last_elem = now_elem;
			}
			delete delet_elem;
		}		
	}
	//Получение элемента по индексу
	int get(int index) {
		elem* now_elem = first_elem;
		if (index >= size()) {
			return 0;
		}

		else {
			for (int i = 1; i <= index; i++) {
				now_elem = now_elem->next_elem;
			}
			return now_elem->data;
		}

	}
};


int main() {
}
	
