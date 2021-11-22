#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

int main()
{
    string str;
    cout << "Введите строку\n";
    getline(cin, str);
    int a = 100;
    int massiv_znakov[100]{}, massiv_codov[100]{}, massiv_sum[100]{};
    string massiv_charov[100]{};
    string massiv_slov[100];
    int zapomnit_j = 0;


    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '.' || str[i] == ' ' || str[i] == ',' || str[i] == '!' || str[i] == '?') {
            massiv_znakov[i] = (int)str[i];
            massiv_charov[i] = str[i];
        }
        if (str[i] != ' ' && str[i] != '?' && str[i] != '!' && str[i] != '.' && str[i] != ',') {
            massiv_codov[i] = (int)str[i];
            massiv_charov[i] = str[i];
        }
    }

    for (int i = 0; i < 100; i++) {
        if (massiv_codov[i] == 0) {
            continue;
        }

        if (massiv_codov[i] != 0) {
            for (int j = i; j < 100; j++) {
                if (massiv_codov[j] != 0) {
                    massiv_sum[i] += massiv_codov[j];
                    massiv_slov[i] += massiv_charov[j];

                }
                if (massiv_codov[j] == 0)
                {
                    zapomnit_j = j;
                    break;
                }

            }


        }
        i = zapomnit_j;

    }

    for (int z = 0; z < 100; z++) {
        for (int j = z + 1; j < 100; j++) {
            if (massiv_sum[z] > massiv_sum[j]) {
                if (massiv_sum[j] == 0) {
                    continue;
                }
                int zamena = massiv_sum[z];
                massiv_sum[z] = massiv_sum[j];
                massiv_sum[j] = zamena;
                string zamena2 = massiv_slov[z];
                massiv_slov[z] = massiv_slov[j];
                massiv_slov[j] = zamena2;


            }
        }
    }

    for (int i = 0; i < 100; i++) {
        if (massiv_codov[i] == 0 && massiv_znakov[i] != 0)
        {

            cout << (char)massiv_znakov[i];




        }
        if (massiv_codov[i] != 0 && massiv_znakov[i] == 0) {
            cout << massiv_slov[i]; 


        }


    }




}