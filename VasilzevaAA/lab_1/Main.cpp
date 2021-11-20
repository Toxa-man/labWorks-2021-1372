#include <iostream>
#include <string>
#include <vector>

int main() {
	std::string in_str; // ������� ������
	std::cout << "Write a sentance: ";
	std::getline(std::cin, in_str);
	in_str = in_str + " "; // ������ ������ ��� ��������� ������� ��������� �� �������

	std::vector <std::string> word; // ������ ��� ���� �� ��������� ����
	std::vector <int> summ_code; // ������ ��� ���� ����� ��������� ������� word

	int c_word = 0; // ���������� ����
	std::string curr; // ���������� ��� �������� ��������, ������ �� ������� � ������ str
	curr = in_str[0];

	for (int i = 1; i < in_str.length(); i++) {
		if (in_str[i] == ' ' && curr != "\0") { //��� ������� ������� �������� �������� curr � ������ word � ������� ����� � ������� summ_code ��� ����� ����� �������� ������ word[i]
			word.push_back(curr);
			summ_code.push_back(0);

			curr.erase(0, i);
			c_word ++;
		}
		if (isalpha(in_str[i])) { curr += in_str[i]; } //�������� �������� ������ in_str � ������ curr �� ������� �������
	}

	for (int i = 0; i < word.size(); i ++) { // ���� ����� ����� ��������� ������� word, ���������� �� � ������ summ_code
		if (isalpha(word[i][0])) {
			for (int j = 0; j < word[i].length(); j++) {
				summ_code[i] += (int)word[i][j];
			}
		}
	}

	for (int i = 0; i < c_word-1; i++) { // ��� ������ ���������� ������� summ_code ��������� ������ word
		for (int j = i+1; j < c_word; j++) {
			if (summ_code[i] > summ_code[j]) {

				int c = summ_code[i];
				summ_code[i] = summ_code[j];
				summ_code[j] = c;

				std::string f = word[i];
				word[i] = word[j];
				word[j] = f;
			}
		}
	}

	std::cout << "Your improved sentance: "; // �����
	bool f1 = false; // ���������� ��� �������� ���������� �� ������ ���������� ��������
	int f2 = 0; // ���������� ��� �������� ���������� ��������� ������� word
	for (int i = 0; i < in_str.length(); i++) { 

		if (isalpha(in_str[i])) { f1 = true; } // ��������� ���������� �� ������ ��������
		if (!isalpha(in_str[i]) && f1) { // ��� ������� � "�����������" �������� ��� �������� � ������, ���� ����� ��� ���� ��������, ������� ����� �� ����
			std::cout << word[f2];
			f1 = false; f2++;
		}	
		if (!isalpha(in_str[i])) { std::cout << in_str[i]; } // ������� "�����������" ������ ��� ������
	}

}