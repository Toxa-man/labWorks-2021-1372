#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Words {
	string word;
	int words_sum;
};
int main(){
	string phrase;
	vector <string> punct_marks;
	vector <Words> phrase_marks;
	cout << "Enter a phrase using the letters A-Z (a-z) and the symbols '.' ',' '!' '?'"<<endl;
	getline(cin, phrase);
	int i = 0;
	while ( i < phrase.size()) {
		string text = "";
		string punct = "";
		Words pl;
		int sum=0;
		if (((int(phrase[i]) >= 'A' && int(phrase[i]) <= 'Z') || (int(phrase[i]) >= 'a' && int(phrase[i]) <= 'z')) && i < phrase.size()) {
			do {
				text += phrase[i];
				sum += int(phrase[i]);
				++i;
			} while (((int(phrase[i]) >= 'A' && int(phrase[i]) <= 'Z') || (int(phrase[i]) >= 'a' && int(phrase[i]) <= 'z')) && i < phrase.size() );
			pl.word=text;
			pl.words_sum = sum;
			phrase_marks.push_back(pl);
		}
		if (int(phrase[i]) <='?' && i < phrase.size()) {
			do {
				punct += phrase[i];
				++i;
			} while (int(phrase[i]) <= '?' && i < phrase.size());
			punct_marks.push_back(punct);
		}
	}
	for (int i = 0; i < phrase_marks.size(); i++) {
		bool flag = true;
		for (int j = 0; j < phrase_marks.size() - i - 1; j++) {
			if (phrase_marks[j].words_sum > phrase_marks[j+1].words_sum) {
				flag = false;
				swap(phrase_marks[j], phrase_marks[j + 1]);
			}
		}
		if (flag) {
			break;
		}
	}
	int count = punct_marks.size() + phrase_marks.size();
	if (count%2==0) {
		int i = 0;
		while (count / 2 -i> 0) {
			cout << phrase_marks[i].word << punct_marks[i];
			i++;
		}
	}
	else {
		count--;
		int i = 0;
		while (count / 2 - i > 0) {
			cout << phrase_marks[i].word << punct_marks[i];
			i++;
		}
		cout << phrase_marks[i].word;
	}
}