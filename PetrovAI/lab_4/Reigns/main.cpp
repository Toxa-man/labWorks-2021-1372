#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "character.h"

int main() {
	setlocale(LC_ALL, "Russian");

	int religion = 50;
	int society = 50;
	int army = 50;
	int finance = 50;

	//Подсчет количества строк в файле
	std::string str_check = "";
	int count_string = 0;
	std::ifstream file("Events_list.txt");
	while (std::getline(file, str_check)) {
		count_string += 1;
	}
	file.close();

	sf::RenderWindow window(sf::VideoMode(700, 854), "Reigns");

	sf::Texture Background_t;
	Background_t.loadFromFile("Фон.jpg");
	sf::Sprite Background_s(Background_t);

	

	enum game_status {
		move, //ход происходит
		game_start,//игра начилась
		game_end,//игра закончилась
		press_left,
		press_right,
		end_move
	};

	game_status status = game_start;

	//Создаем шрифт 
	sf::Font font;//шрифт 
	font.loadFromFile("Персонажи\\Шрифт.ttf");//передаем нашему шрифту файл шрифта
	
	//Создаем объект класса character
	character now_character;

	sf::Texture pic_t;
	sf::Sprite pic_s;
	pic_s.setPosition(152, 318);
	
	sf::Text phrase_left_txt("Нет.", font, 38);
	phrase_left_txt.setPosition(30, 500);

	sf::Text phrase_right_txt("Да.", font, 38);
	phrase_right_txt.setPosition(590, 500); 


	sf::Text phrase_txt;//создаем объект фразы персонажа.
	phrase_txt.setFont(font);
	phrase_txt.setCharacterSize(38);
	phrase_txt.setPosition(0, 160);

	sf::Text name_txt;//создаем объект имени персонажа.
	name_txt.setFont(font);
	name_txt.setCharacterSize(38);
	name_txt.setPosition(210, 720);

	//создаем объекты 4 переменных
	sf::Text religion_txt;
	religion_txt.setFont(font);
	religion_txt.setCharacterSize(45);
	religion_txt.setPosition(10, 46);

	sf::Text society_txt;
	society_txt.setFont(font);
	society_txt.setCharacterSize(45);
	society_txt.setPosition(170, 46);

	sf::Text army_txt;
	army_txt.setFont(font);
	army_txt.setCharacterSize(45);
	army_txt.setPosition(340, 46);

	sf::Text finance_txt;
	finance_txt.setFont(font);
	finance_txt.setCharacterSize(45);
	finance_txt.setPosition(500, 46);

	character death;
	death.adres = "Смерть.jpg";
	death.name = "Нажмите Enter";
	death.phrase = "Вы погибли";
	while (window.isOpen()) {
		//Обработка очереди событий в цикле 
		sf::Event event;

		std::string redact_txt;
		
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (status == move && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) {
				status = press_left;
			}
			
			else if (status == move && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) {
				status = press_right;
			}

			else if (status == end_move && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
				status = game_start;
			}
		}

		if (status == game_start) {
			now_character = create_character(count_string);
			
			phrase_txt.setString(text_redactor(now_character.phrase));
			name_txt.setString(text_redactor(now_character.name));
			religion_txt.setString(std::to_string(religion));
			society_txt.setString(std::to_string(society));
			army_txt.setString(std::to_string(army));
			finance_txt.setString(std::to_string(finance));
			pic_t.loadFromFile(now_character.adres);
			pic_s.setTexture(pic_t);
			status = move;
		}
		else if (status == press_left) {
			now_character.change(now_character.cons_left, religion, society, army, finance);
			religion_txt.setString(std::to_string(religion));
			society_txt.setString(std::to_string(society));
			army_txt.setString(std::to_string(army));
			finance_txt.setString(std::to_string(finance));
			if (if_you_lose(religion, society, army, finance)) {
				status = game_end;
			}
			else {
				status = game_start;
			}
		}
		else if (status == press_right) {
			now_character.change(now_character.cons_right, religion, society, army, finance);
			religion_txt.setString(std::to_string(religion));
			society_txt.setString(std::to_string(society));
			army_txt.setString(std::to_string(army));
			finance_txt.setString(std::to_string(finance));
			if (if_you_lose(religion, society, army, finance)) {
				status = game_end;
			}
			else {
				status = game_start;
			}
		}

		else if (status == game_end) {
			now_character = death;
			phrase_txt.setString(text_redactor(now_character.phrase));
			name_txt.setString(text_redactor(now_character.name));
			pic_t.loadFromFile(now_character.adres);
			pic_s.setTexture(pic_t);
			status = end_move;
			religion = 50;
			society = 50;
			army = 50;
			finance = 50;
		}
		
		//Отрисовка

		window.draw(Background_s);
		window.draw(pic_s);
		window.draw(phrase_left_txt);
		window.draw(phrase_right_txt);
		window.draw(phrase_txt);
		window.draw(religion_txt);
		window.draw(society_txt);
		window.draw(army_txt);
		window.draw(finance_txt);
		window.draw(name_txt);
		window.display();
	}
}
	


