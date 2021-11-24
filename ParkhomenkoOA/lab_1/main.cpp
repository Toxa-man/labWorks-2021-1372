#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> inputWords;
vector<string> wordsSums;
vector<string> inputMarks;

char dictionaryOfMarks[4] = { '.', ',', '!', '?' };

bool isMark(char ch) {
	int x = std::distance(dictionaryOfMarks, std::find(dictionaryOfMarks, dictionaryOfMarks + 4, ch));
	if (x == 4) {
		return 0;
	}
	else return 1;
}

int sumOfSymbols(string str) {
	int sum{0};
	for (int i = 0; i < str.length(); i++)
		sum += (int)str[i];
	return sum;
}

void swap(string* xp, string* yp) {
	string temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubbleSort(vector<string>& vec, int n) {
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (sumOfSymbols(vec[j]) > sumOfSymbols(vec[j + 1]))
				swap(&vec[j], &vec[j + 1]);
}

void stringProcessing(string str) {
	string currentWord = "";
	string currentMarks = "";

	for (int i = 0; i < str.length(); i++) {

		if (not(isMark(str[i])) && str[i] != ' ') {
			currentWord += str[i];
			if (isMark(str[i+1]) || str[i+1] == ' ' || str[i+1] == '\0') {
				inputWords.push_back(currentWord);
				currentWord = "";
			}
		}
		
		if (isMark(str[i]) || str[i] == ' ') {
			currentMarks += str[i];
			if ((not(isMark(str[i+1])) && str[i+1] != ' ') || str[i+1] == '\0') {
				inputMarks.push_back(currentMarks);
				currentMarks = "";
			}
		}
	}
}

int main() {
	string inputStr;
	cout << "Enter string: ";
	getline(cin, inputStr);
	stringProcessing(inputStr);
	int n = inputWords.size();
	bubbleSort(inputWords, n);

	if (inputWords.size() == inputMarks.size()) {
		for (int i = 0; i < inputWords.size(); i++) {
			cout << inputWords[i];
			cout << inputMarks[i];
		}
	}
	if (inputWords.size() > inputMarks.size()) {
		for (int i = 0; i < inputWords.size()-1; i++) {
			cout << inputWords[i];
			cout << inputMarks[i];
		}
		cout << inputWords[inputWords.size()-1];
	}
	if (inputWords.size() < inputMarks.size()) {
		for (int i = 0; i < inputMarks.size() - 1; i++) {
			cout << inputMarks[i];
			cout << inputWords[i];
		}
		cout << inputMarks[inputMarks.size() - 1];
	}

	return 0;
}