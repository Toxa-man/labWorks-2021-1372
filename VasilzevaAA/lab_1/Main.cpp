#include <iostream>
#include <string>
#include <vector>

struct Word {
	std::string word;
	int code = 0;
};

int main() {
	std::string in_str; // входная строка
	std::cout << "Write a sentance: ";
	std::getline(std::cin, in_str);
	in_str = in_str + " "; // пробел вконце для упрощения условий приработе со строкой

	std::vector <Word> word_s;
	Word temp;

	std::string curr; // переменная для хранения символов, идущих до пробела в строке str
	curr = in_str[0]; // первый символ не буква

	for (int i = 1; i < in_str.length(); i++) {
		if (in_str[i] == ' ' && curr != "\0") { //при встрече пробела передаем значение curr в массив word и отводим место в массиве summ_code для суммы кодов символов строки word[i]
			temp.word = curr;

			if (isalpha(curr[0])) {
				for (int j = 0; j < curr.length(); j++) {
					temp.code += (int)curr[j];
				}				
			}

			word_s.push_back(temp);

			temp.code = 0;
			curr.erase(0, i);
		}
		if (isalpha(in_str[i])) { curr += in_str[i]; } //копируем элементы строки in_str в строку curr до первого пробела
	}


	for (int i = 0; i < word_s.size() - 1; i++) { // при помощи сортировки массива summ_code сортируем массив word
		for (int j = i + 1; j < word_s.size(); j++) {
			if (word_s[i].code > word_s[j].code) {

				temp = word_s[i];
				word_s[i] = word_s[j];
				word_s[j] = temp;

			}
		}
	}

	std::cout << "Your improved sentance: "; // вывод
	bool alpha = false; // переменная для проверки встречался ли символ латинского алфавита
	int num_word = 0; // переменная для подсчета выведенных элементов массива word
	for (int i = 0; i < in_str.length(); i++) {

		if (isalpha(in_str[i])) { alpha = true; } // проверяем встречался ли символ латиницы
		if (!isalpha(in_str[i]) && alpha) { // при встрече с "специальным" символом или пробелом в случае, если перед ним была латиница, выводим слово из букв

			std::cout << word_s[num_word].word;

			alpha = false; num_word++;
		}
		if (!isalpha(in_str[i])) { std::cout << in_str[i]; } // выводим "специальный" символ или пробел
	}

}
