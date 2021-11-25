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


	for (int i = 0; i < acs.size(); i++) {
		for (int j = i; j < acs.size(); j++) {
			if (acs[i] > acs[j]) {
				int buf;
				buf = acs[i];
				acs[i] = acs[j];
				acs[j] = buf;
				std::string buf_s;
				buf_s = slova[i];
				slova[i] = slova[j];
				slova[j] = buf_s;
			}

		}

	}
	std::string res = "";
	int res_c;
	res_c = 0;
	int k;
	k = 1;
	std::string hh;

	hh = "";

	for (int i : s) {
		if ((i == (int)' ') || (i == (int)'.') || (i == (int)',') || (i == (int)'!') || (i == (int)'?')) {

			if (k == 1) {
				hh = slova[res_c + 2];
				res += hh;
				hh = " ";
				k--;

			}
			if (k == 0) {
				res += (char)i;
				k++;
			}

			res_c++;


		}


	}

	res = res.substr(0, res.size() - 1);
	std::cout << res << std::endl;
}
