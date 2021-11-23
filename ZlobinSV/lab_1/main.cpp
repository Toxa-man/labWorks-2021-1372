#include <iostream>
#include <string>
using namespace std;

bool is_punctuation_or_space(char ch) {
    if (ch == ' ' || ch == ',' || ch == '.' || ch == '!' || ch == '?')
        return true;
    else return false;
}

bool is_punctuation(char ch) {
    if (ch == ',' || ch == '.' || ch == '!' || ch == '?')
        return true;
    else return false;
}

int main()
{
    int i = 0, zam2, n = 0, k = 0, sum[100];
    string zam1, str, word[100];
    char a;

    cout << "Enter the string: ";

    getline(cin, str);

    str += " ";

    while (i < str.length() - 1) {
        while (is_punctuation_or_space(str[i]) == 0) {
            word[n] += str[i];
            i++;
        }
        n++;
        while (is_punctuation_or_space(str[i]) == 1) {
            word[n] += str[i];
            i++;
        }
        if ((word[0] != "") || (n != 1) || (word[n].length() != 1) && (word[n][word[n].length() - 1] != ' ')) {
                if (word[n].length() >= 2) {
                    if ((is_punctuation(word[n][0]) == 1) && (is_punctuation(word[n][1]) == 1)) {
                        cout << "Error! The pinching mark is in the middle of a word or more than one pinning mark appears after / before the word.";
                        return 0;
                    }
                    if ((is_punctuation(word[n][word[n].length() - 1]) == 1) && (is_punctuation(word[n][word[n].length() - 2]) == 1)) {
                        cout << "Error! The pinching mark is in the middle of a word or more than one pinning mark appears after / before the word.";
                        return 0;
                    }
                }
                if (word[n] == "," || word[n] == "." || word[n] == "!" || word[n] == "?") {
                    cout << "Error! The pinching mark is in the middle of a word or more than one pinning mark appears after / before the word.";
                    return 0;
                }
            }
        n++;
    }



    for (int i = 0; i < n; i++) {
        sum[i] = -1;
        if (word[i][0] != ' ' && word[i][0] != ',' && word[i][0] != '.' && word[i][0] != '!' && word[i][0] != '?') {
            for (int k = 0; k < word[i].length(); k++) {

                a = word[i][k];
                sum[i] += a;
            }
        }
    }


    for (int i = 0; i < n; i++) {
        if (sum[i] != -1) {
            for (int k = i + 1; k < n; k++) {
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

    for (int i = 0; i < n; i++) {
        cout << word[i];
    }

}