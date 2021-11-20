

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int isExistLetter(string str) //функция проверки есть ли в слове буква(состоит ли оно из букв или нет)
{
	for (auto item : str)
	{
		if (item >= 65 && item <= 90 || item >= 97 && item <= 122) return 1;
	}
	return 0;
}
   
struct Word     //структура типа Word , хранит данные о слове
{
	string word;      //само слово
	int weight = -1;    //его вес(сумма аски кодов букв)
	bool isWord = false;       //флажок для проверки буквенное слово или символьное
};

void Sorting(vector<Word>& sortedWeight)  //функция сортирующая массив по весам(сортировка методом пузырька, не оптимизированная)
{
	Word temp;
	for (int i = 0; i < sortedWeight.size() - 1; i++)
	{
		if (!sortedWeight[i].isWord) continue;    //пропускаем слова, которые не состоят из букв(они должны остаться на своем месте)
		for (int j = i + 1; j < sortedWeight.size(); j++)
		{
			if (!sortedWeight[j].isWord) continue;         //пропускаем слова, которые не состоят из букв(они должны остаться на своем месте)
			if (sortedWeight[i].weight > sortedWeight[j].weight)
			{
				temp = sortedWeight[i];
				sortedWeight[i] = sortedWeight[j];
				sortedWeight[j] = temp;
			}
		}

	}
}

int main()
{
	string str;
	getline(cin, str);
	string temp;     //временная переменная для хранения слова
	//cout << int(' ');
	vector<Word> sortedWords;      //вектор(массив) данных типа Word
	for (auto item : str)
	{
		if (item == '.' || item == ',' || item == '!' || item == '?' || item == ' ')
		{
			if (!isExistLetter(temp)) temp += item;      //если слово не из букв то собираем его дальше

			else               //иначе оно из букв и закончилось(в конце появился пробел и т.д) значит добавляем его в массив
			{
				int w0 = 0;
				for (auto ch : temp)//считаем его вес
				{
					w0 += (int)ch;
				}
				sortedWords.push_back(Word{ temp, w0, true });
				temp = item;
			}
		}


		else if (item >= 65 && item <= 90 || item >= 97 && item <= 122)    //иначе если это буква то
		{
			//если слово не из букв то это конец слова из символов и мы добавляем его в наш массив(вес = -1, признак того что он нам не нужен)
			//флажок отрицательный, потому что это не буквенное слово а символьное)
			if (!isExistLetter(temp) && temp.size() > 0) { sortedWords.push_back(Word{ temp, -1, false }); temp = item; }

			else temp += item;//иначе собираем буквенное слово(продолжаем собирать)
		}
	}
	//след. кусок кода дублирует вещи которые уже были , потому что когда мы доходим до конца строки, то не добавляем слово которые у нас могло остаться во временной переменной
	if (temp.size() != 0 && !isExistLetter(temp)) sortedWords.push_back(Word{ temp, -1, false });
	if (temp.size() != 0 && isExistLetter(temp))
	{
		int w0 = 0;
		for (auto ch : temp)
		{
			w0 += (int)ch;
		}
		sortedWords.push_back(Word{ temp, w0, true });
	}

	Sorting(sortedWords);
	//передаем наш массив(вектор) в функцию сортировки по ссылке разумеется
	for (auto item : sortedWords)
		
	{
		cout << item.word;
	}
	return 0;
}