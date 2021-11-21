#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



int main() {
	std::string s;
	std::getline(std::cin, s);
	int sum = 0;
	int slov = 0;
	s += ".";
	std::string* slova;

	for (int i : s) {
		if ((i == (int)' ') || (i == (int)'.') || (i == (int)',') || (i == (int)'!') || (i == (int)'?')) {
			continue;
		}
		slov++;
	}
	slova = new std::string[slov];
	std::string temp = "";
	std::vector<int> acs;
	int h = 0;

	for (int i : s) {
		temp = temp + (char)i;
		if ((i == (int)' ') || (i == (int)'.') || (i == (int)',') || (i == (int)'!') || (i == (int)'?')) {
			temp.pop_back();

			slova[h] = temp;
			for (int j : slova[h]) {
				sum += j;
			}
			acs.push_back(sum);
			sum = 0;
			h++;
			temp = "";
			continue;
		}

	}
	

}
