#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct slovo{
    string word;
    int sumASC;
    bool checksigns,check1sign,checklastsign;
};

slovo enterslovo(){
    string signs = "!?.,";
    slovo str;
    cin >> str.word;
    str.sumASC = 0;
    str.checksigns = true;
    int CountOfSigns = 0;
    for (int i = 0; i < str.word.length(); i++ ){
        str.sumASC += str.word[i];
        if (signs.find(str.word[i]) != string::npos){
            CountOfSigns++;
        }
    }
    if (CountOfSigns == str.word.length()){
        str.checksigns = false;
    }

    str.check1sign = false;
    str.checklastsign = false;

    if (str.checksigns){
        if (signs.find(str.word[0]) != string::npos) {str.check1sign = true;}
        if (signs.find(str.word[str.word.length() - 1]) != string::npos) {str.checklastsign = true;}
    }
    return str;
}

slovo firstsign(slovo str){
    slovo sign;
    sign.word = str.word[0];
    sign.sumASC = 0;
    sign.checksigns = false;
    sign.check1sign = true;
    sign.checklastsign = false;
    return sign;
}

slovo lastsign(slovo str){
    slovo sign;
    sign.word = str.word[str.word.length() - 1];
    sign.sumASC = 0;
    sign.checksigns = false;
    sign.check1sign = false;
    sign.checklastsign = true;
    return sign;
}

slovo deletefirstsign(slovo str){
    str.sumASC -= str.word[0];
    str.word.erase(0, 1);
    str.check1sign = false;
    return str;
}

slovo deletelastsign(slovo str){
    str.sumASC -= str.word[str.word.length() - 1];
    str.word.erase(str.word.length() - 1, 1);
    str.checklastsign = false;
    return str;
}

int main() {
    string signs = "!?.,";
    cout << "Enter a line: ";
    vector <slovo> line;

    slovo str = enterslovo(),sign;

    if (str.check1sign){
        sign = firstsign(str);
        line.push_back(sign);
        str = deletefirstsign(str);
    }

    if (str.checklastsign){
        sign = lastsign(str);
        str = deletelastsign(str);
        line.push_back(str);
        line.push_back(sign);
    } else {
        line.push_back(str);
    }



    while (cin.peek() != '\n'){
        str = enterslovo();

        if (str.check1sign){
            sign = firstsign(str);
            line.push_back(sign);
            str = deletefirstsign(str);
        }

        if (str.checklastsign){
            sign = lastsign(str);
            str = deletelastsign(str);
            line.push_back(str);
            line.push_back(sign);
        } else {
            line.push_back(str);
        }
    }

    for (int i = 0; i < line.size() - 1; i++){
        int j = i+1;
        while (j != line.size()){
            if ((line[j].checksigns) && (line[i].checksigns) && (line[i].sumASC > line[j].sumASC)) {
                str = line[j];
                line[j] = line[i];
                line[i] = str;
            }
            j++;
        }
    }

    for (int i = 0; i < line.size() - 1; i++) {
        cout << line[i].word;
        if (!line[i+1].checklastsign && !line[i].check1sign) {cout << ' ';}
    }
    cout << line[line.size() - 1].word << '\n';

    system("pause");

    return 0;
}
