#include <iostream>
#include <string>


int sumAscii(const std::string sum_of_letter) {
	int count = 0;
	for (int i = 0; i < sum_of_letter.size(); i++) {
		if (sum_of_letter[i] >= 'A') {
			count += (int)sum_of_letter[i];
		}
		else {
			count = 0;
			break;
		}
	}
	return count;
}
//Функция подсчета суммы ASCII символов

int main() {

	std::cout << "Enter your string: ";
	std::string text;
	std::getline(std::cin, text);
	int k = 0, i = 0, j;
	std::string tmp, words[100];
	//Объявление переменных

	for (int i = 1; i < text.size(); i++) {
		if ((text[i] < 'A') && (text[i] != ' ') && ((text[i - 1] >= 'A' && text[i + 1] >= 'A') || (text[i - 1] >= 'A' && text[i + 1] < 'A' && text[i + 1] > ' ') || (text[i - 1] < 'A' && text[i + 1] >= 'A' && text[i - 1] > ' '))) {
			std::cout << "The punctuation mark should not be inside the word, two punctuation marks should not stand in a row before or after word, enter string again: ";
			std::cout << std::endl;
			std::cout << "Enter your string: ";
			std::getline(std::cin, text);
			i = 0;
		}
	}
	//Проверка на некорректный ввод
	
	text += ' ';
	while (i < text.size() - 1) {
		while (text[i] != '.' && text[i] != ',' && text[i] != '!' && text[i] != '?' && text[i] != ':' && text[i] != ';' && text[i] != ' ') {
			words[k] += text[i];
			i++;
		}
		k++;
		while (text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?' || text[i] == ':' || text[i] == ';' || text[i] == ' ') {
			words[k] += text[i];
			i++;
		}
		k++;
	}
	//Заполнение массива words словами/знаками препинания

	for (int i = 0; i < k; i++) {
		if (sumAscii(words[i]) != 0) {
			j = i;
			for (int m = i; m < k; m++) {
				if (sumAscii(words[j]) > sumAscii(words[m]) && sumAscii(words[j]) != 0 && sumAscii(words[m]) != 0) {
					j = m;
				}
			}
			tmp = words[i];
			words[i] = words[j];
			words[j] = tmp;
		}
	}
	//сортировка

	for (int i = 0; i < k; i++) {
		std::cout << words[i];
	}
	//Вывод

	return 0;
}
