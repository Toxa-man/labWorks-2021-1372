#include <iostream>
#include <string>
using namespace std;

int main()
{
    int i = 0, zam2, n = 0, k = 0, sum[100];
    string zam1,str,word[100];
    char a;
    
    cout << "Enter the string: ";

    getline(cin, str);
    
    str += " ";

     while (i < str.length()-1) {
        while (str[i] != ' ' && str[i] != ',' && str[i] != '.' && str[i] != '!' && str[i] != '?') {
            word[n] += str[i];
            i++;
        }
        n++;
        while (str[i] == ' ' || str[i] == ',' || str[i] == '.' || str[i] == '!' || str[i] == '?') {
            word[n] += str[i];
            i++;
        }
        n++;
    }
     n--;
     

    for (int i = 0; i <= n; i++) {
        sum[i] = -1;
        if (word[i][0] != ' ' && word[i][0] != ',' && word[i][0] != '.' && word[i][0] != '!' && word[i][0] != '?') {
            for (int k = 0; k < word[i].length(); k++) {

                a = word[i][k];
                sum[i] += a;
            }
        }
    }


    for (int i = 0; i <= n; i++) {
        if (sum[i] != -1) {
            for (int k = i + 1; k <= n; k++) {
                if (sum[k] < sum[i] && sum[k] != -1 && sum[i] != -1) {
                        zam1 = word[i];
                        word[i] = word[k];
                        word[k] = zam1;
                        zam2 = sum[i];
                        sum[i] = sum[k];
                        sum[k] = zam2;
                }
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        cout << word[i];
    }
    
}