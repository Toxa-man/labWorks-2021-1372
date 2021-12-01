#include <iostream>
#include <string>
#include <vector>

// checking for punctuation marks

bool is_punctuation(char ch) {
	if (ch == ',' || ch == '!' || ch == '?' || ch == '.' || ch == ' ')
		return true;
	else
		return false;
}

// counting sum of ASCII chars

int sum_count(std::string word) {
	int sum = 0;
	
	if (is_punctuation(word[0]))
		return sum;
	for (int i = 0; i < word.length(); i++) {
		sum += int(word[i]);
	}
	return sum;
}

int main()
{
	int i = 0;
	std::vector<int>sums;
	std::vector<std::string>words;
	std::string sentence, word;

	std::cout << "Enter your string: ";
	std::getline(std::cin, sentence);

	// parsing sentence into words

	while (i < sentence.length()) {
		while (!is_punctuation(sentence[i]) && sentence[i] != '\0') {
			word += sentence[i];
			i++;
		}

		if (word.length() != 0) {
			words.push_back(word);
			word.clear();
		}

		while (is_punctuation(sentence[i])) {
			word += sentence[i];
			i++;
		}

		if (word.length() != 0) {
			words.push_back(word);
			word.clear();
		}
	}
	
	// filling vector of sums

	for (int i = 0; i < words.size(); i++) {
		sums.push_back(sum_count(words[i]));
	}

	// sorting words by sorting sums
	
	for (int i = 0; i < sums.size(); i++) {
		int min = sums[i];
		int index = i;
		for (int j = i + 1; j < sums.size(); j++) {
			if (sums[j] != 0 && sums[j] < min) {
				min = sums[j];
				index = j;
			}
		}
		std::swap(sums[i], sums[index]);
		std::swap(words[i], words[index]);
	}
	for (int i = 0; i < words.size(); i++) {
		std::cout << words[i]; 
	}
}
