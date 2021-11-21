#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
using namespace std;
vector<string> single_words(string sentence)
{
    vector<string> word_vector;
    string result_word;
    for (char& character : sentence)
    {
        if ((character != ' ')  && (character!='?') && (character != ',') && (character != '.') && (character != '!'))  
        {
            result_word += character;
        }
        else if ((character == ' ') && (result_word!="")) {
            word_vector.push_back(result_word);
            result_word = "";
        }
    }
    if (result_word != "") {
        word_vector.push_back(result_word);
    }
    return(word_vector);
}
vector<int> sum_ch(string sentence)
{


    vector <int> sum;
    int chislo=0;
    for (char& character : sentence)
    {   
        if ((character != ' ') && (character != 63) && (character != ',') && (character != '.') && (character != '!'))
        {
            chislo += character;
            
        }
        else if(character == ' '){
            sum.push_back(chislo);
            chislo = 0;
        }
    }
    sum.push_back(chislo);
    return(sum);
}
vector<string> signs(string sentence)
{
    vector <string> vector_signs;
    string result_sign="";
    for (char& character : sentence)
    {
        if ((character == ' ') || (character == 63) || (character == ',') || (character == '.') || (character == '!'))
        {   
            result_sign += character;
        }
        else if ((result_sign!="")) {
            vector_signs.push_back(result_sign);
            result_sign = "";
        }
    }
    vector_signs.push_back(result_sign);
    return(vector_signs);
}
int main() {
    string sentence;
    int m = 0;
    cout << "Please enter your sentence. Remember: use only symbols((A...Z) or (a...z)) and signs ('!', '.', ',' ,'?') for correct work of program\n";
    getline(cin, sentence);
    vector<string> result = single_words(sentence);
    vector<int> otbor = sum_ch(sentence);
    vector <string> ready_sign = signs(sentence);
    for (int i = 0; i < result.size(); i++) { 
        for (int j = 0; j< result.size()-1; j++) {
            if (otbor[j] > otbor[j + 1]) {
                int b = otbor[j]; // создали дополнительную переменную
                otbor[j] = otbor[j + 1]; // меняем местами
                otbor[j + 1] = b; 
                string c = result[j];
                result[j] = result[j + 1];  
                result[j + 1] = c;
            }
        }
    }
     for (int i = 0; i<result.size(); i++) {

     cout << result[i];
     if (ready_sign[m] > "") {// ( m <= ready_sign.size())
         cout << ready_sign[m];
         m++;
     } 
 }