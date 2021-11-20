#include <iostream>
#include <string>
#include <vector>

int main() {
	std::string in_str; // входная строка
	std::cout << "Write a sentance: ";
	std::getline(std::cin, in_str);
	in_str = in_str + " "; // пробел вконце для упрощения условий приработе со строкой

	std::vector <std::string> word; // массив для слов из латинских букв
	std::vector <int> summ_code; // массив для сумм кодов элементов массива word

	int c_word = 0; // количество слов
	std::string curr; // переменная для хранения символов, идущих до пробела в строке str
	curr = in_str[0];

	for (int i = 1; i < in_str.length(); i++) {
		if (in_str[i] == ' ' && curr != "\0") { //при встрече пробела передаем значение curr в массив word и отводим место в массиве summ_code для суммы кодов символов строки word[i]
			word.push_back(curr);
			summ_code.push_back(0);

			curr.erase(0, i);
			c_word ++;
		}
		if (isalpha(in_str[i])) { curr += in_str[i]; } //копируем элементы строки in_str в строку curr до первого пробела
	}

	for (int i = 0; i < word.size(); i ++) { // ищем суммы кодов элементов массива word, записываем их в массив summ_code
		if (isalpha(word[i][0])) {
			for (int j = 0; j < word[i].length(); j++) {
				summ_code[i] += (int)word[i][j];
			}
		}
	}

	for (int i = 0; i < c_word-1; i++) { // при помощи сортировки массива summ_code сортируем массив word
		for (int j = i+1; j < c_word; j++) {
			if (summ_code[i] > summ_code[j]) {

				int c = summ_code[i];
				summ_code[i] = summ_code[j];
				summ_code[j] = c;

				std::string f = word[i];
				word[i] = word[j];
				word[j] = f;
			}
		}
	}

	std::cout << "Your improved sentance: "; // вывод
	bool f1 = false; // переменная для проверки встречался ли символ латинского алфавита
	int f2 = 0; // переменная для подсчета выведенных элементов массива word
	for (int i = 0; i < in_str.length(); i++) { 

		if (isalpha(in_str[i])) { f1 = true; } // проверяем встречался ли символ латиницы
		if (!isalpha(in_str[i]) && f1) { // при встрече с "специальным" символом или пробелом в случае, если перед ним была латиница, выводим слово из букв
			std::cout << word[f2];
			f1 = false; f2++;
		}	
		if (!isalpha(in_str[i])) { std::cout << in_str[i]; } // выводим "специальный" символ или пробел
	}

}