#include "character.h"
#include <iostream>
#include <fstream>
#include <string>

void character::change(int cons[4], int& r, int& s, int& a, int& f) {
	r += cons[0];
	s += cons[1];
	a += cons[2];
	f += cons[3];
}

character create_character(int N) {

	std::string str;
	std::ifstream file("Events_list.txt");

	srand(time(NULL));
	int random_number = rand() % N + 1;
	for (int i = 0; i < random_number; i++) {
		std::getline(file, str);
	}

	std::string now_symbl;
	character character_obj;

	now_symbl = str[0];
	//Чтение именни персонажа
	while (now_symbl != ";") {
		character_obj.name += now_symbl;
		str.erase(0, 1);
		now_symbl = str[0];
	}

	str.erase(0, 1);
	now_symbl = str[0];

	//Чтение фразы персонажа
	while (now_symbl != ";") {
		character_obj.phrase += now_symbl;
		str.erase(0, 1);
		now_symbl = str[0];
	}
	str.erase(0, 1);
	now_symbl = str[0];


	//Чтение последствий выбора 
	for (int i = 0; i < 4; i++) {
		std::string x = "";
		while (now_symbl != ";") {
			x += now_symbl;
			str.erase(0, 1);
			now_symbl = str[0];
		}
		str.erase(0, 1);
		now_symbl = str[0];
		int res = std::stoi(x);
		character_obj.cons_left[i] = res;
	}

	for (int i = 0; i < 4; i++) {
		std::string x = "";
		while (now_symbl != ";") {
			x += now_symbl;
			str.erase(0, 1);
			now_symbl = str[0];
		}
		str.erase(0, 1);
		now_symbl = str[0];
		int res = std::stoi(x);
		character_obj.cons_right[i] = res;
	}

	//Cоздание картинки персонажа

	while (now_symbl != ";") {
		character_obj.adres += now_symbl;
		str.erase(0, 1);
		now_symbl = str[0];
	}
	str.erase(0, 1);
	now_symbl = str[0];



	return character_obj;
}

bool if_you_lose(int r, int s, int a, int f) {
	if (r >= 100 || r <= 0) {
		return true;
	}
	if (s >= 100 || s <= 0) {
		return true;
	}
	if (a >= 100 || a <= 0) {
		return true;
	}
	if (f >= 100 || f <= 0) {
		return true;
	}
	return false;
}

std::string text_redactor(std::string str) {
	std::string new_str = "";
	std::string now_str = "";
	std::string word = "";

	if (str.size() < 30) {

		new_str += str;
		return new_str;
	}

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			if (now_str.size() + word.size() <= 29) {
				now_str = now_str + ' ' + word;
				word = "";
			}

			else if (now_str.size() + word.size() > 29) {

				new_str = new_str + now_str + '\n';
				now_str = word;
				word = "";
			}
		}
		else {

			word += str[i];
		}
	}


	return new_str + now_str + ' ' + word;
}