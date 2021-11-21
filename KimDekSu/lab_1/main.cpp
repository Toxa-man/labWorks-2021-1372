#include <iostream>
#include <string>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	string line, word[100];
	int i = 0, a = 0, b = 0, sum[100];
	cout << "Введите строку - ";
	getline(cin, line);
	line += " ";
	while (i < line.length() - 1) {
		while (line[i] != ' ' && line[i] != '.' && line[i] != ',' && line[i] != '?' && line[i] != '!') {
			word[a] += line[i];
			i++;
		}
		a++;
			while (line[i] == ' ' || line[i] == '.' || line[i] == ',' || line[i] == '?' || line[i] == '!') {
				word[a] += line[i];
				i++;
			}
		if (word[a].length() >= 2) {
			if ((word[a][0] == '.' || word[a][0] == ',' || word[a][0] == '?' || word[a][0] == '!') && (word[a][1] == '.' || word[a][1] == ',' || word[a][1] == '?' || word[a][1] == '!')) {

				cout << "Ошибка, знак препинания не может встретиться в середине слова, только в конце и/или в начале. Перед словом и/или после  не может встретиться более одного знака препинания";
				return 0;
			}
			if ((word[a][word[a].length() - 1] == '.' || word[a][word[a].length() - 1] == ',' || word[a][word[a].length() - 1] == '?' || word[a][word[a].length() - 1]== '!') && (word[a][word[a].length() - 2] == '.' || word[a][word[a].length() - 2] == ',' || word[a][word[a].length() - 2] == '?' || word[a][word[a].length() - 2] == '!')){
			cout << "Ошибка, знак препинания не может встретиться в середине слова, только в конце и/или в начале. Перед словом и/или после  не может встретиться более одного знака препинания";
			return 0;
}
		}
		if (word[a] == "." || word[a] == "," || word[a] == "?" || word[a] == "!") {
			cout << "Ошибка, знак препинания не может встретиться в середине слова, только в конце и/или в начале. Перед словом и/или после  не может встретиться более одного знака препинания";
			return 0;
		}
		a++;
	}
	a--;
	char s;
	for (int i = 0; i <= a; i++) {
		sum[i] = -1;
		if (word[i][0] != ' ' && word[i][0] != '.' && word[i][0] != ',' && word[i][0] != '?' && word[i][0] != '!') {
			for (int b = 0; b < word[i].length();b++) {
				s = word[i][b];
				sum[i] += s;
			}
		}
	}
	string subst1;
	int subst2;
	  for (int i = 0; i <= a; i++) {
		  if (sum[i] != -1) {
			  for (int b = i + 1; b <= a; b++) {
				  if (sum[i] != -1 && sum[b] != -1 && sum[b] < sum[i]) {
					  subst1 = word[i];
					  word[i] = word[b];
					  word[b] = subst1;
					  subst2 = sum[i];
					  sum[i] = sum[b];
					  sum[b] = subst2;
				  }
			  }
		  }
	  }
  for (int i = 0; i <= a; i++) {
	  cout << word[i];
  }
}