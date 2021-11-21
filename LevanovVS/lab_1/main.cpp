#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct MyStruct
{
    int sum;
    string io;
};
vector<string>we;
vector<MyStruct>words;
bool sad(char f)
{
    if (int(f) >= 'a' && int(f) <= 'z' || int(f) >= 'A' && int(f) <= 'Z') {
        return 1;
    }
    else {
        return 0;
    }
}
void delit(string rts) 
{
    MyStruct tr;
    string WORDS;
    string znaki;
    int i = 0, summ;
    while (i < rts.size())
    {
        WORDS = "";
        znaki = "";
        summ = 0;
        do {
            if (sad(rts[i]) == 1 && i < rts.size()) {
                WORDS += rts[i];
                summ += int(rts[i]);
                i++;
            }
        } while (sad(rts[i]) == 1 && i < rts.size());
        tr.io = WORDS;
        tr.sum = summ;
        words.push_back(tr);
        if (words.size()>1)
        {
            for (int i = 0; i < words.size(); i++) {
                bool ban = true;
                for (int j = 0; j < words.size() - (i + 1); j++) {
                    if (words[j].sum > words[j + 1].sum) {
                        ban = false;
                        swap(words[j], words[j + 1]);
                    }
                }
                if (ban) {
                    break;
                }
            }
        }
            do {
                if (sad(rts[i]) == 0 && i < rts.size()) {
                    znaki += rts[i];
                    i++;
                }
            } while (sad(rts[i]) == 0 && i < rts.size());
            we.push_back(znaki);
    }   
}
int main()
{
    string str;
    getline(cin, str);
    delit(str);
    for (int i = 0; i < we.size(); i++)
    {
        cout << words[i].io << we[i];
    }
    if (words.size() > we.size()) 
    {
        cout << words[we.size()].io;
    }
}