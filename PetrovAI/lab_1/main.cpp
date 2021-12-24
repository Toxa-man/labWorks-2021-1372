#include <iostream>
#include <string>
#include <vector>
/*
ASCII
[48:57] - Цифры
[65:90] - Заглавные буквы
[97:122] - Прописные
44, 46, 33, 63 - Знаки препинания
*/
enum SYMBOL {
	letter,
	prep,
	error
};

int sum_symb(std::string a) {
	int q = 0;
	for (int i = 0; i < a.size(); i++) {
		q += a[i];
	}
	return q;
}
//Функция определяет тип символа(буква, знак препинания или недопустимый знак)
SYMBOL  checking_symbol(char a) {
	SYMBOL znach;
	if ((a >= 48 && a <= 57) || (a >= 65 && a <= 90) || (a >= 97 && a <= 122)) {
		znach = letter;
	}
	else if (a == 33 || a == 44 || a == 46 || a == 63) {
		znach = prep;
	}
	else {
		znach = error;
	}
	return znach;
}
enum MIDDLE_SYMBOLS {
	letters, 
	preps,
	errors,
	start
};
//Функция определяет тип середины строки, без первого и последниего символа(набор букв, набор знаков препинания или недопустимая комбинация)
MIDDLE_SYMBOLS  checking_middle_symbols(std::string x) {
	MIDDLE_SYMBOLS znach = start;
	for (int i = 0; i < x.size(); i++) {

		if (checking_symbol(x[i]) == letter && znach != preps) {
			znach = letters;
		}

		else if (checking_symbol(x[i]) == prep && znach != letters) {
			znach = preps;
		}

		else {//Во всех остальных случаях, либо стоит недопустимый символ, либо в строке содержаться и буквы и знаки препинания
			znach = errors;
			break;
		}

		return znach;
	}
}

enum TYPE {
	front_prep,
	after_prep,
	simp_prep,
	simp_word
};
struct Word {
	TYPE type;
	/*
	Тип элемента
	front_prep - знак препинания перед словом
	after_prep - знак препинания после слова
	prep - набор знаков препинвния
	simp_word - просто слово
	*/
	int size;// Размер слова
	std::string symbols; //Символы строки

};

int main() {
	setlocale(LC_ALL, "Russian");
	std::vector<Word> word_vector;
	std::string now_str;

	std::cout << "Введите строку:\n";
	std::cin >> now_str;

	int qual = 1;
	while (true) {
		//Обработка элементов, состоящих из одного символа
		if (now_str.size() == 1) {

			if (checking_symbol(now_str[0]) == letter) {
				Word word_1;
				word_1.size = now_str[0];
				word_1.symbols = now_str;
				word_1.type = simp_word;
				word_vector.push_back(word_1);
			}
			else if (checking_symbol(now_str[0]) == prep) {
				Word word_1;
				word_1.symbols = now_str;
				word_1.type = simp_prep;
				word_vector.push_back(word_1);
			}
			else {
				std::cout << "Ошибка при введении строки";
				qual = 0;
				break;
			}
		}
		//Обработка элементов, состоящих из двух символов
		else if (now_str.size() == 2) {

			if (checking_symbol(now_str[0]) == letter && checking_symbol(now_str[1]) == letter) {
				Word word_1;
				word_1.size = sum_symb(now_str);
				word_1.symbols = now_str;
				word_1.type = simp_word;
				word_vector.push_back(word_1);
			}
			else if (checking_symbol(now_str[0]) == prep && checking_symbol(now_str[1]) == prep) {
				Word word_1;
				word_1.symbols = now_str;
				word_1.type = simp_prep;
				word_vector.push_back(word_1);
			}
			else if (checking_symbol(now_str[0]) == prep && checking_symbol(now_str[1]) == letter) {
				Word word_1;
				word_1.symbols = now_str[0];
				word_1.type = front_prep;
				word_vector.push_back(word_1);

				Word word_2;
				word_2.size = now_str[1];
				word_2.symbols = now_str[1];
				word_2.type = simp_word;
				word_vector.push_back(word_2);
			}
			else if (checking_symbol(now_str[0]) == letter && checking_symbol(now_str[1]) == prep) {
				Word word_1;
				word_1.size = now_str[0];
				word_1.symbols = now_str[0];
				word_1.type = simp_word;
				word_vector.push_back(word_1);

				Word word_2;
				word_2.symbols = now_str[1];
				word_2.type = after_prep;
				word_vector.push_back(word_2);
			}
			else {
				std::cout << "Ошибка при введении строки";
				qual = 0;
				break;
			}

		}

		else {
			//Для слов длинее трех элементов проверяем крайние элементы и оставшуюся серидину
			std::string middle_str = now_str;
			middle_str.erase(0, 1);
			middle_str.erase(middle_str.size() - 1, 1);

			if (checking_symbol(now_str[0]) == letter && checking_symbol(now_str[now_str.size() - 1]) == letter && checking_middle_symbols(middle_str) == letters) {
				Word word_1;
				word_1.symbols = now_str;
				word_1.type = simp_word;
				word_1.size = sum_symb(now_str);
				word_vector.push_back(word_1);
			}

			else if (checking_symbol(now_str[0]) == prep && checking_symbol(now_str[now_str.size() - 1]) == prep && checking_middle_symbols(middle_str) == preps) {
				Word word_1;
				word_1.symbols = now_str;
				word_1.type = simp_prep;
				word_vector.push_back(word_1);
			}

			else if (checking_symbol(now_str[0]) == prep && checking_symbol(now_str[now_str.size() - 1]) == prep && checking_middle_symbols(middle_str) == letters) {

				Word word_1;
				word_1.symbols = now_str[0];
				word_1.type = front_prep;
				word_vector.push_back(word_1);

				Word word_2;
				word_2.symbols = middle_str;
				word_2.type = simp_word;
				word_1.size = sum_symb(middle_str);
				word_vector.push_back(word_2);

				Word word_3;
				word_3.symbols = now_str[now_str.size() - 1];
				word_3.type = after_prep;
				word_vector.push_back(word_3);
			}

			else if (checking_symbol(now_str[0]) == prep && checking_symbol(now_str[now_str.size() - 1]) == letter && checking_middle_symbols(middle_str) == letters) {
				Word word_1;
				word_1.symbols = now_str[0];
				word_1.type = front_prep;
				word_vector.push_back(word_1);

				Word word_2;
				word_2.symbols = middle_str + now_str[now_str.size() - 1];
				word_2.type = simp_word;
				word_1.size = sum_symb(middle_str) + now_str[now_str.size() - 1];
				word_vector.push_back(word_2);
			}

			else if (checking_symbol(now_str[0]) == letter && checking_symbol(now_str[now_str.size() - 1]) == prep && checking_middle_symbols(middle_str) == letters) {
				Word word_1;
				word_1.symbols = now_str[0] + middle_str;
				word_1.type = simp_word;
				word_1.size = sum_symb(middle_str) + now_str[0];
				word_vector.push_back(word_1);

				Word word_2;
				word_2.symbols = now_str[now_str.size() - 1];
				word_2.type = after_prep;
				word_vector.push_back(word_2);
			}
			else {
				std::cout << "Ошибка при введении строки";
				qual = 0;
				break;
			}


		}

		if (std::cin.peek() == '\n') {
			break;
		}
		std::cin >> now_str;
	}


	if (qual == 0) {
		return 0;
	}
	//Сортировка
	for (int i = 0; i < word_vector.size() - 2; i++) {
		for (int j = i + 1; j < word_vector.size() - 1; j++) {

			if (word_vector[i].size > word_vector[j].size && word_vector[i].type == simp_word && word_vector[j].type == simp_word) {

				Word interiem;
				interiem.size = word_vector[j].size;
				interiem.type = word_vector[j].type;
				interiem.symbols = word_vector[j].symbols;

				word_vector[j] = word_vector[i];
				word_vector[i] = interiem;
			}
		}
	}
	for (int i = 0; i < word_vector.size(); i++) {

		if (word_vector[i].type == front_prep) {
			std::cout << word_vector[i].symbols;
		}

		else if (word_vector[i].type == simp_word && (i != word_vector.size() - 1) && word_vector[i + 1].type == after_prep) {
			std::cout << word_vector[i].symbols;
		}
		else if (word_vector[i].type == simp_word && (i != word_vector.size() - 1) && word_vector[i + 1].type != after_prep) {
			std::cout << word_vector[i].symbols << " ";
		}
		else if (word_vector[i].type == simp_word && i == word_vector.size() - 1) {
			std::cout << word_vector[i].symbols << " ";
		}
		else if (word_vector[i].type == after_prep || word_vector[i].type == simp_prep) {
			std::cout << word_vector[i].symbols << " ";
		}
	}
}
