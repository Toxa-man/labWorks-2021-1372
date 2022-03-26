#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct _Word { // ���������, �������� ����� � ��� ���
	string _word = ""; //�����
	int _code = 0;//���
};
bool checkSpace(char a, int size, int i); //��������� �������� ������ (����� ��� �����������)
void sortStr(vector <_Word>& mas); //��������� �����
int main() {
	vector <_Word> mas; // ������ ���� � �� �����
	string str; //������� ������
	setlocale(LC_ALL, "Rus");
	cout << "������� ������: ";
	getline(cin, str);
	setlocale(LC_ALL, 0);
	int temp = 0; //��������� ���������� ��� ������ ���� �����
	string buffer = ""; //��������� ���������� ��� ������ �����
	for (int i = 0; i < str.length() + 1; i++) { //���������� ������ �� ������ ���� + ������ ��������������� �����
		if (i + 1 == str.length() && checkSpace(str[i], str.length(), i)) {
			buffer += str[i];
			temp += (int)str[i];
		}
		else if (checkSpace(str[i], str.length(), i)) {
			buffer += str[i];
			temp += (int)str[i];
		}
		else {
			if (buffer != "") {
				_Word a; //��������� ���������
				a._word = buffer;
				a._code = temp;
				mas.push_back(a);
				buffer = "";
				temp = 0;
			}
		}
	}
	sortStr(mas);
	setlocale(LC_ALL, "Rus");
	cout << "��������������� �����������:" << endl;
	setlocale(LC_ALL, 0);
	for (int i = 0, j = 0; i < mas.size(); i++) { //����� ��������������� ������ (�� ������� ����������)
		cout << mas[i]._word;
		while (j < str.length()) {
			if (!checkSpace(str[j], str.length(), j)) {
				cout << str[j];
				if (str[j] == ' ' && checkSpace(str[j + 1], str.length(), j + 1)) {
					j++;
					break;
				}
			}
			j++;
		}
	}
	cout << endl;
	system("pause");
	return 0;
}

bool checkSpace(char a, int size, int i) {
	if (a == ' ' || a == ',' || a == '?' || a == '.' || a == '!' || i == size) {
		return false;
	}
	else {
		return true;
	}
}

void sortStr(vector <_Word>& mas) {
	_Word a;
	for (int i = 0; i < mas.size(); i++) {
		for (int j = 1; j < mas.size() - i; j++) {
			if (mas[j]._code < mas[j - 1]._code) {
				a._code = mas[j]._code;
				a._word = mas[j]._word;
				mas[j]._code = mas[j - 1]._code;
				mas[j]._word = mas[j - 1]._word;
				mas[j - 1]._code = a._code;
				mas[j - 1]._word = a._word;
			}
		}
	}
}