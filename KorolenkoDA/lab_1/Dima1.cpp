
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

using namespace std;

struct Word
{
    int numberInArray;
    int sumASCII;
};

vector<string> arrayWords, arrayWithoutMarks;
vector<Word> words;

void Split(string text);
void SeparatePunctuation();
void CountingValue();
void Sorting();
void Replace();

void OutputArray(vector<string> arr) 
{
    cout << "\n";
    string line = "";
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i][0] == ' ')
            line += arr[i];
        else if (arr[i][1] == ' ') 
        {
            line[line.size() - 1] = arr[i][0];
            line += " ";
        }
        else 
            line += arr[i] + " ";           
    }

    cout << line + "\n";
}

int main()
{
    string message;
    getline(cin, message);           

    Split(message);
    SeparatePunctuation();   
    CountingValue();
    Sorting();
    Replace();
    OutputArray(arrayWithoutMarks);
    return 0;
}

void Split(string text) 
{
    string delimiter = " ";

    size_t pos = 0;
    string token;
    while ((pos = text.find(delimiter)) != string::npos) {
        token = text.substr(0, pos);
        arrayWords.push_back(token);
        text.erase(0, pos + delimiter.length());
    }
    arrayWords.push_back(text);
}

void SeparatePunctuation() 
{   
    for (int i = 0; i < arrayWords.size(); i++)
    {
        string buffer = arrayWords[i];
        bool firstIsMark = false;
        bool lastIsMark = false;
        int marksCount = 0;

        for (int j = 0; j < buffer.size(); j++)
        {
            int code = int(buffer[j]);

            if (((code >= 65 && code <= 90) || (code >= 97 && code <= 122)) == false) {
                
                if (j == 0)
                    firstIsMark = true;

                if (j == buffer.size() - 1)
                    lastIsMark = true;

                marksCount++;
            }                    
        }

        if (marksCount == 0 || marksCount == buffer.size()) {

            arrayWithoutMarks.push_back(buffer);
        }
        else {
            string token = buffer;

            if (firstIsMark == true) {

                string mark = buffer.erase(1);
                arrayWithoutMarks.push_back(" " + mark);
                token = token.substr(1);
            }

            if (lastIsMark == true) {
                string mark = token.substr(token.size() - 1);
                token = token.erase(token.size() - 1);

                arrayWithoutMarks.push_back(token);
                arrayWithoutMarks.push_back(mark + " ");
            }
        }
    }
}

void CountingValue() 
{
    for (int i = 0; i < arrayWithoutMarks.size(); i++)
    {
        string buffer = arrayWithoutMarks[i];
        int code = int(buffer[0]);

        if (((code >= 65 && code <= 90) || (code >= 97 && code <= 122)) == true) {
            
            int count = 0;

            for (int j = 0; j < buffer.size(); j++)
            {
                count += (int)buffer[j];
            }

            Word token = { i, count };
            words.push_back(token);
        }
    }
}


void Sorting() 
{
    for (int i = 0; i < words.size(); i++) {
        bool flag = true;

        for (int j = 0; j < words.size() - i - 1; j++) {

            if (words[j].sumASCII > words[j + 1].sumASCII) {
                flag = false;
                swap(words[j], words[j + 1]);
            }
        }
        if (flag) {
            break;
        }
    }
}

void Replace() 
{
    vector<string> array = arrayWithoutMarks;
    int num = 0;

    for (int i = 0; i < array.size(); i++)
    {
        string buffer = array[i];
        int code = int(buffer[0]);
        
        if (((code >= 65 && code <= 90) || (code >= 97 && code <= 122)) == true) 
        {
            array[i] = arrayWithoutMarks[words[num].numberInArray];
            num++;
        }
    }
    arrayWithoutMarks = array;
}