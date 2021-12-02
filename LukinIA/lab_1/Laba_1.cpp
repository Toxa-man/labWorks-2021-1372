#include <vector>
#include <string>
#include <iostream>
using std::cin;
using std::cout;
using std::string;
using std::endl;
int main() {
	std::vector<string>Mass_slov;
	int index_Mass_slov = 0;
	std::vector<string>Mass_symbols;
	int index_Mass_symbols = 0;
	string str;
	string slovo;
	slovo = "";
	string symbols;
	symbols = "";
	cout << "Enter your line using 'abc...' , 'ABC...' and (,) , (.) , (!) , (?) , ( ) only,please." << endl;
	getline(cin, str);
	Mass_slov.resize(str.size());
	Mass_symbols.resize(str.size());
	
	for (int i = 0; i < str.size(); ++i) {
		if ((str[i] != ' ') && (str[i] != ',') && (str[i] != '.') && (str[i] != '?')&&(str[i]!='!')) {
			slovo.push_back(str[i]);	// в текущее слово добавляем элемент строки,если это не символы (до тех пор,пока не встретиться символ) 
			if (symbols != "") {
				for (int p = 0; p < symbols.size(); ++p) {
					Mass_symbols[index_Mass_symbols].push_back(symbols[p]); // в p-ый индекс массива символо запихиваем текущий набор символов 
				}
				index_Mass_symbols++;						// передвигаемся в (index_Mass_symbols + 1) индекс массива символов
				symbols = "";				// обнуляем набор символом
			}
		}
		else {
			symbols.push_back(str[i]);		// в текущий набор символов добавляем элемент строки,если это символ (до тех пор,пока  встречается символ)
			if (slovo != "") {
				for (int j = 0; j < slovo.size(); ++j) {
					Mass_slov[index_Mass_slov].push_back(slovo[j]);				 // в index_Mass_slov -ый индекс массива слов запихиваем посимвольно текущее слово
				}
				index_Mass_slov++;								// передвигаемся в (index_Mass_slov + 1) индекс массива слов
				slovo = "";                       // обнуляем текущее слово
			}
		}
	}
	if (slovo != "") {
		for (int j = 0; j < slovo.size(); ++j) {
			Mass_slov[index_Mass_slov].push_back(slovo[j]);
		}
	}

	if (symbols != "") {
		for (int j = 0; j < symbols.size(); ++j) {
			Mass_symbols[index_Mass_slov].push_back(symbols[j]);
		}
	}
	std::vector<int>Sums;
	for (int i = 0; i < Mass_slov.size(); ++i) {
		int SumAscii = 0;
		if (Mass_slov[i] == "0") {
			break;
		}else {
			for (int j = 0; j < Mass_slov[i].size(); ++j) {
				char c = Mass_slov[i][j];
				SumAscii += (int)c;
			}
		}
		if (SumAscii != 0) {
			Sums.push_back(SumAscii);
		}
		else break;
	}
	for (int i = 0; i < Sums.size(); ++i) {
		for (int j = i+1; j < Sums.size(); ++j) {
			if (Sums[i] > Sums[j]) {
				int tmp = Sums[i];
				Sums[i] = Sums[j];
				Sums[j] = tmp;
				string temp = Mass_slov[i];
				Mass_slov[i] = Mass_slov[j];
				Mass_slov[j] = temp;
			}
		}
	}
	int m = 0;
	cout << "The result of this program " << "is : " << endl;
	for (int n=0; n < Mass_symbols.size(); n++) {
		if ((str[0] == ' ') || (str[0] == '!') || (str[0] == '?') || (str[0] == ',') || (str[0] == '.')) {
			cout << Mass_symbols[n] << Mass_slov[m];
		}
		else {
			cout << Mass_slov[m] << Mass_symbols[n];
		}
		m++;
	}
}