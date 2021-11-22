#include <iostream>
#include <string>
using namespace std;
int main()
{
    int i = 0, j = 0, asc[70];
    setlocale(LC_ALL, "Russian");
    cout << "Введите строку: ";
    string str,str_new[70];
    getline(cin, str);
    str += " ";

    while (i < str.length() - 1) {
        while (str[i] != ' ' && str[i] != '.' && str[i] != ',' && str[i] != '!' && str[i] != '?') {
            str_new[j] += str[i];
            i++;
        }
        j++;
        while (str[i] == ' ' || str[i] == '.' || str[i] == ',' || str[i] == '!' || str[i] == '?') {
            str_new[j] += str[i];
            i++;
        }
        j++;
    }

    for (int i = 0; i <= j; i++) {
        asc[i] = -1;
        if (str_new[i][0] != ' ' && str_new[i][0] != ',' && str_new[i][0] != '.' && str_new[i][0] != '!' && str_new[i][0] != '?') {
            for (int k = 0; k < str_new[i].length(); k++) {
                asc[i] += str_new[i][k];
            }
        }
    }

    string c1;
    int c2;
    for (int i = 0; i <= j; i++) {
        if (asc[i] != -1) {
            for (int k = i + 1; k <= j; k++) {
                if (asc[k] < asc[i] && asc[k] != -1 && asc[i] != -1) {
                    c1 = str_new[i];
                    str_new[i] = str_new[k];
                    str_new[k] = c1;
                    c2 = asc[i];
                    asc[i] = asc[k];
                    asc[k] = c2;
                }
            }
        }
    }

    for (int i = 0; i <= j; i++) {
        cout << str_new[i];
    }
}