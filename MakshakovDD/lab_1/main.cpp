	#include <iostream>
	#include <string>
	#include <algorithm>
	#include <vector>
	#include <cctype>
	using namespace std;

	struct Punctuation {
		char symbol;
		int words_before;
	};

	bool compare(string a, string b){
		int sum = 0;
		for (int i = 0; i < a.length(); ++i) {
			sum += (int)a[i];
		}
		for (int i = 0; i < b.length(); ++i) {
			sum -= (int)b[i];
		}
		return sum < 0;
	}

	int main()
	{
		string str;
		getline(cin, str);

		vector<string> words;
		vector<Punctuation> punctuation;
		string word;

		int nwords = 0;
		for (char c : str) {
			if (isalnum(c)) word += c;
			if ((c == ' ' || ispunct(c)) && word.length() != 0) {
				words.push_back(word);
				nwords += 1;
				word = "";
			}
			if (c == ' ' || ispunct(c)) {
				punctuation.push_back(Punctuation{ c, nwords });
				nwords = 0;
			}
		}
		if(word.length() != 0) words.push_back(word);

		sort(words.begin(), words.end(), compare);
		int word_ind = 0;
		for (Punctuation punct : punctuation) {
			if (punct.words_before == 1) {
				cout << words[word_ind];
				word_ind += 1;
			}
			cout << punct.symbol;
		}
		if (word_ind < words.size()) cout << words[word_ind];

		return 0;
		
	}
