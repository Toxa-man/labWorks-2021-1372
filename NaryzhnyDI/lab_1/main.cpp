main.cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;
bool checking(char symbol){
    if ((symbol >= 'A' && symbol <= 'Z' ) || (symbol >= 'a' && symbol <= 'z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}
// By diapason, we check either it's a punct. mark or it's a word
int Ascii(string the_word){
    int count_summa = 0;
    if (the_word[0] == ',' || the_word[0] == '!' || the_word[0] == '?' || the_word[0] == '.' || the_word[0] == ' ')
        return count_summa;
    for (int i = 0; i < the_word.length(); i++) {
        count_summa += int(the_word[i]);
    }
    return count_summa;
}
// This function is made to sum Ascii of the sentence's words. It determines symbols and punctuation marks

int main() {
    vector<string> words;
    vector<int> znach;
    vector<string> ok;
    string str, the_word = "";
    int a, b;
    a = 0;
    cout << "Please, write any sentence below you'd like to: " << endl;
    getline(cin, str);
    b = str.size();
    while ((checking(str[a]) == 1) && (a < b)){
        int so = 0;
        do {
            the_word += str[a];
            so += int(str[a]);
            a++;
        } while ((checking(str[a]) == 1) && (a < b));
        words.push_back(the_word); // putting our words here
        the_word.clear();
        znach.push_back(so);

        a++;
    }
    while ((checking(str[a]) != 1) && (a < b)) {
        do {
            the_word += str[a];
            a++;
        } while ((checking(str[a]) == 0) && (a < b));
        words.push_back(the_word); //putting our symbols here
        the_word.clear();

        a++;

    }

    for (int i = 0; i < words.size(); i++) {
        for (int j = 0; j< words.size()-1; j++) {
            if (znach[j] > znach[j + 1]) {
                int b = znach[j]; 
                znach[j] = znach[j + 1]; 
                znach[j + 1] = b; 
                string a = words[j]; 
                words[j] = words[j + 1];
                words[j + 1] = a;
            }
        }
    }
    for (int i= 0; i< words.size();i++){
        cout << words[i];
    }
    return 0;
}


