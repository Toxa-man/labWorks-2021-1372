#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct  Word {
	int summa;
	string word;
};
int main() {
	string stroka;
	vector <string>znaki; //вектор для знаков преп
	vector <Word> word; //вектор для слов
	cout << "Please enter stroky, consist of a-z or A-Z, and also you can use .,!?" << endl;
	getline(cin, stroka);
	int j = 0;
	int i;
	i = 0;
	int c; //элемент строки
	while (i < stroka.size()) {
		string isBykv = "";
		string znachki = "";
		Word c; //элемент строки
		int sum = 0;
		if (((int(stroka[i]) >= 'A' && int(stroka[i]) <= 'Z') || (int(stroka[i]) >= 'a' && int(stroka[i]) <= 'z')) && i < stroka.size()) {
			do {
				isBykv += stroka[i];
				sum += int(stroka[i]);
				++i; //возвращает увеличенное значение
			} while (((int(stroka[i]) >= 'A' && int(stroka[i]) <= 'Z') || (int(stroka[i]) >= 'a' && int(stroka[i]) <= 'z')) && i < stroka.size()); {
				c.word = isBykv;
				c.summa = sum;
				word.push_back(c);


			}
			if ((stroka[i] == '.' || stroka[i] == ',' || stroka[i] == '!' || stroka[i] == '?' || stroka[i] == ' ') && (i < stroka.size())) {
				do {
					znachki += stroka[i]; //в вектор добавили знак преп
					++i;

				} while ((stroka[i] == '.' || stroka[i] == ',' || stroka[i] == '!' || stroka[i] == '?' || stroka[i] == ' ') && (i < stroka.size()));
				znaki.push_back(znachki); //вставили знак в вектор
			}

		}

	}
	for (int i = 0; i < word.size(); i++) {
		for (int j = 0; j < word.size() - 1; j++) {
			if (word[j].summa > word[j + 1].summa) {
				Word a;
				a = word[j];
				word[j] = word[j + 1];
				word[j + 1] = a;
			}
		}
	}
	for (int i = 0; i < znaki.size(); i++) { 
		cout << word[i].word << znaki[i]; //фраза заканчивается знаком препинания   word[i] вектор слов, word -из структуры
	}
	
}
