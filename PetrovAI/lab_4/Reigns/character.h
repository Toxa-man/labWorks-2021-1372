#include <string>
#include <iostream>
#include <fstream>

class character {
public:
	std::string name;
	std::string phrase;//Фраза 
	//прописать картинку

	//Последсвия каждого выбора 
	int cons_left[4];
	int cons_right[4];
	//Адрес картинки персонажа
	std::string adres = "";


	void change(int cons[4], int& r, int& s, int& a, int& f);
};

character create_character(int N);

bool if_you_lose(int r, int s, int a, int f);

std::string text_redactor(std::string str);