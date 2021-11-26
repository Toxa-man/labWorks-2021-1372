#include <iostream>
#include <string>
#include <vector>


int main() {
	std::string s;
	std::getline(std::cin, s);
	int sum = 0;
	int slov = 0;
	int k_slov = 0;
	s += ".";
	std::string* slova;
	int znak = 0;
	
	for (int i : s) {
		if ((i == (int)' ') || (i == (int)'.') || (i == (int)',') || (i == (int)'!') || (i == (int)'?')) {
			znak++;
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
	std::vector <int> vector;
	for (int i = 0; i < acs.size(); i++) {
		if (acs[i] != 0) {
			vector.push_back(acs[i]);
		}
	}
	
	res_c = (int) abs((double) vector.size() - (double) znak + 1);

	for (int i = 0; i < s.length(); i++) {
		if ((s[i] == (int)' ') || (s[i] == (int)'.') || (s[i] == (int)',') || (s[i] == (int)'!') || (s[i] == (int)'?')) {
			res += s[i];
			continue;

		}
		if ((s[i+1] == (int)' ') || (s[i+1] == (int)'.') || (s[i+1] == (int)',') || (s[i+1] == (int)'!') || (s[i+1] == (int)'?')) {
			
			i++;
			
			res_c++;
			res += slova[res_c];
			res += s[i];
		}
		
	}

	res = res.substr(0, res.size() - 1);
	std::cout << res << std::endl;
}
