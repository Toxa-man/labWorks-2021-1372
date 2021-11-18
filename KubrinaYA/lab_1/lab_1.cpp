#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct _Word { // структура, хранящая слово и его код
	string _word = ""; //слово
	int _code = 0;//код
};
bool checkSpace(char a, int size, int i); //проверяет входящий символ (буква или разделитель)
void sortStr(vector <_Word>& mas); //сортирует слова
int main() {
	vector <_Word> mas; // массив слов и их кодов
	string str; //входная строка
	setlocale(LC_ALL, "Rus");
	cout << "Введите строку: ";
	getline(cin, str);
	setlocale(LC_ALL, 0);
	int temp = 0; //временная переменная для записи кода слова
	string buffer = ""; //временная переменная для записи слова
	for (int i = 0; i < str.length() + 1; i++) { //разделение строки на массив слов + запись соответствующих кодов
		if (i + 1 == str.length() && checkSpace(str[i], str.length(), i)) {
			buffer += str[i];
			temp += (int)str[i];
		}
		else if (checkSpace(str[i], str.length(), i)) {
			buffer += str[i];
			temp += (int)str[i];
		}
		else {
			if (buffer != "") {
				_Word a; //экземпляр структуры
				a._word = buffer;
				a._code = temp;
				mas.push_back(a);
				buffer = "";
				temp = 0;
			}
		}
	}
	sortStr(mas);
	setlocale(LC_ALL, "Rus");
	cout << "Отсортированное предложение:" << endl;
	setlocale(LC_ALL, 0);
	for (int i = 0, j = 0; i < mas.size(); i++) { //вывод отсортированной строки (со знаками препинания)
		cout << mas[i]._word;
		while (j < str.length()) {
			if (!checkSpace(str[j], str.length(), j)) {
				cout << str[j];
				if (str[j] == ' ' && checkSpace(str[j + 1], str.length(), j + 1)) {
					j++;
					break;
				}
			}
			j++;
		}
	}
	cout << endl;
	system("pause");
	return 0;
}

bool checkSpace(char a, int size, int i) {
	if (a == ' ' || a == ',' || a == '?' || a == '.' || a == '!' || i == size) {
		return false;
	}
	else {
		return true;
	}
}

void sortStr(vector <_Word>& mas) {
	_Word a;
	for (int i = 0; i < mas.size(); i++) {
		for (int j = 1; j < mas.size() - i; j++) {
			if (mas[j]._code < mas[j - 1]._code) {
				a._code = mas[j]._code;
				a._word = mas[j]._word;
				mas[j]._code = mas[j - 1]._code;
				mas[j]._word = mas[j - 1]._word;
				mas[j - 1]._code = a._code;
				mas[j - 1]._word = a._word;
			}
		}
	}
}