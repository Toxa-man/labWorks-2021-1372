#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int sum(string word)
{
	int s = 0;
	for (int i = 0; i < word.length(); i++)
		if (word[i] != '.' && word[i] != ',' && word[i] != '!' && word[i] != '?')
			s += word[i];
	return s;
}

bool f(string left, string right)
{
	return sum(left) < sum(right);
}


int main()
{
	string str;
	string input;
	getline(cin, input);
	stringstream sin(input);
	vector<string> v, all;
	while (sin >> str)
	{
		if (sum(str))
			v.push_back(str);
		all.push_back(str);

	}
	sort(v.begin(), v.end(), f);
	int j = 0;
	for (int i = 0; i < all.size(); i++)
	{
		if (sum(all[i]))
		{
			cout << v[j] << " ";
			j++;
		}
		else
			cout << all[i] << " ";
	}
	cout << endl;
	return 0;
}