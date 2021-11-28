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
    vector<int> znach;
    vector<string> ok;
    string str, the_word = "";
    int a, b;
    a = 0;
    cout << "Please, write any sentence below you'd like to: " << endl;
    getline(cin, str);
    b = str.length();
    while(a<b){
        while ((checking(str[a]) == 1) && (a < b)) {
            int so = 0;
            do {
                the_word += str[a];
                so += str[a];
                a++;
            } while ((checking(str[a]) == 1) && (a < b));
            words.push_back(the_word); // Here I put the user's word into the vector named "words"
            the_word.clear();
            znach.push_back(so);
        }
        while ((checking(str[a]) != 1) && (a < b)) {
            do {
                the_word += str[a];
                a++;
            } while ((checking(str[a]) == 0) && (a < b));
            ok.push_back(the_word); //Here I put the user's punctuation symbol into the vector named "ok"
            the_word.clear();

        }
    }

// I've used the Bubble sort
    for (int i = 0; i < words.size(); i++) {
        for (int j = 0; j < words.size() - 1; j++) {
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
        if(words.size()==ok.size()){
            for (int i = 0; i < words.size(); i++){
                cout<<words[i]<<ok[i];
            }
        }
        else{
            int a;
            for (int i = 0; i < ok.size(); i++){
                cout<<words[i]<<ok[i+1];
                a=i;
            }
            cout << words[a+1];
        }

}


