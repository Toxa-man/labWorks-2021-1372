// The code is written in Сlion (IDE)
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
// By the stated diapason, the bool function "checking" returns true (1) in case of a letter

int main() {
    vector<string> words;
    vector<int> ascii_znach;
    vector<string> p_symbols;
    string str, the_word;
    int a;
    a = 0;
    cout << "Please, write any sentence below you'd like to: " << endl;
    getline(cin, str);
    while(a<str.length()){
        while ((checking(str[a]) == 1) && (a < str.length())) {
            int ascii_zn = 0;
            do {
                the_word += str[a];
                ascii_zn += str[a];
                a++;
            } while ((checking(str[a]) == 1) && (a < str.length()));
            words.push_back(the_word); // Here I put the user's word into the vector named "words"
            the_word.clear();
            ascii_znach.push_back(ascii_zn);
        }
        while ((checking(str[a]) != 1) && (a < str.length())) {
            do {
                the_word += str[a];
                a++;
            } while ((checking(str[a]) == 0) && (a < str.length()));
            p_symbols.push_back(the_word); //Here I put the user's punctuation symbol into the vector named "p_symbols"
            the_word.clear();

        }
    }

// I've used the Bubble sort
    for (int i = 0; i < words.size(); i++) {
        for (int j = 0; j < words.size() - 1; j++) {
            if (ascii_znach[j] > ascii_znach[j + 1]) {
                int local2 = ascii_znach[j];
                ascii_znach[j] = ascii_znach[j + 1];
                ascii_znach[j + 1] = local2;
                string local1 = words[j];
                words[j] = words[j + 1];
                words[j + 1] = local1;
            }
        }
    }
        if(words.size()==p_symbols.size()){
            for (int i = 0; i < words.size(); i++){
                cout<<words[i]<<p_symbols[i];
            }
        }
        else{
            int local3;
            for (int i = 0; i < p_symbols.size(); i++){
                cout<<words[i]<<p_symbols[i+1];
                local3=i;
            }
            cout << words[local3+1];
        }

}


