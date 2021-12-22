#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Fuctions.h"

using namespace std;
bool isPunct(char& c)
{
	return c == '.' || c == ',' || c == '!' || c == '?' || c == ' ';
}
int sum(string word)
{
	int s = 0;
	bool flag = false;
	for (int i = 0; i < word.length(); i++)
		if (!isPunct(word[i]))
			s += word[i];
		else
			flag = true;
	if (flag)
		s *= -1;
	return s;
}

bool f(string left, string right)
{
	return sum(left) < sum(right);
}


void cut(string& str, string& before, string& after)
{
	int b = 0, e = str.length() - 1;
	if (isPunct(str[b]))
	{
		before = str[b];
		b++;
	}
	if (isPunct(str[e]))
	{
		after = str[e];
		e--;
	}
	str = str.substr(b, e - b + 1);
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
		int s = sum(str);
		string before = "";
		string after = "";
		if (s > 0)
			v.push_back(str);
		else if (s < 0)
		{
			cut(str, before, after);
			v.push_back(str);
		}
		if (before != "")
		{
			all.push_back(before);
			before = "";
		}
		all.push_back(str);
		if (after != "")
		{
			all.push_back(after);
			after = "";
		}
		all.push_back(string(" "));
	}
	sort(v.begin(), v.end(), f);
	int j = 0;
	for (int i = 0; i < all.size(); i++)
	{
		int s = sum(all[i]);
		if (s)
		{
			cout << v[j];
			j++;
		}
		else
			cout << all[i];
	}
	cout << endl;
	return 0;
}
