#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct name
{
    int sum;
    string io;
};
vector<string>sim;
vector<name>words;
bool simbol(char ff)
{
    if (int(ff) >= 'a' && int(ff) <= 'z' || int(ff) >= 'A' && int(ff) <= 'Z') {
        return 1;
    }
    else {
        return 0;
    }
}
void delit(string text) 
{
    name tr;
    string word;
    string znak;
    int i = 0, summ;
    while (i < text.size())
    {
        word = "";
        znak = "";
        summ = 0;
        do {
            if (simbol(text[i]) == 1 && i < text.size()) {
                word += text[i];
                summ += int(text[i]);
                i++;
            }
        } while (simbol(text[i]) == 1 && i < text.size());
        tr.io = word;
tr.sum = summ;
        words.push_back(tr);
       
            do {
                if (simbol(text[i]) == 0 && i < text.size()) {
                    znak += text[i];
                    i++;
                }
            } while (simbol(text[i]) == 0 && i < text.size());
            sim.push_back(znak);
    }
}
int main()
{
    string str;
    getline(cin, str);
    delit(str);
        for (int i = 0; i < words.size(); i++) {
            bool no = true;
            for (int j = 0; j < words.size() - (i + 1); j++) {
                if (words[j].sum > words[j + 1].sum) {
                    no = false;
                    swap(words[j], words[j + 1]);
                }
            }
            if (no) {
                break;
            }
        }
    
    for (int i = 0; i < sim.size(); i++)
    {
        cout << words[i].io << sim[i];
    }
    if (words.size() > sim.size()) 
    {
        cout << words[sim.size()].io;
    }
}