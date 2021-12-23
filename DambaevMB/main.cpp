#include <iostream>
#include <string>

using namespace std;

int main()
{
	int i, k, l;
	i = 0;
	k = 0;
	l = 0;
	int arr[100];
	cout << "Please, enter string: " << endl;
	string str;
	string new_str[100];
	string line;
	getline(cin, str);
	str += " ";

	while (i < str.length() - 1) 
	{
		do
		{
			new_str[k] += str[i];
			i++;
		} 
		while (str[i] != '.' && str[i] != ' ' && str[i] != ',' && str[i] != '?' && str[i] != '!');
		k++;

	while (str[i] == '.' || str[i] == ' ' || str[i] == ',' || str[i] == '?' || str[i] == '!')
		{
			new_str[k] += str[i];
			i++;
		}
		k++;
	}
	for (int i = 0; i <= k; i++) {
		arr[i] = -1;
		if (new_str[i][0] != ' ' && new_str[i][0] != ',' && new_str[i][0] != '.' && new_str[i][0] != '!' && new_str[i][0] != '?') {
			for (int z = 0; z < new_str[i].length(); z++) {
				arr[i] += new_str[i][z];
			}
		}
	}
	for (int i = 0; i <= k; i++) {
		if (arr[i] != -1) {
			for (int z = i + 1; z <= k; z++) {
				if (arr[z] < arr[i] && arr[z] != -1 && arr[i] != -1) {
					line = new_str[i];
					new_str[i] = new_str[z];
					new_str[z] = line;
					l = arr[i];
					arr[i] = arr[z];
					arr[z] = l;
				}
			}
		}
	}
	for (int i = 0; i <= k; i++)
		cout << new_str[i];
}