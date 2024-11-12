#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <cctype>
using namespace std;

int main()
{   
    string sentence;
    cout << "\n       Welcome to the Word Counter!!!\n\n";
    while (true){
        cout << "\nEnter file to read (type \"exit\" to exit): ";
        string path;
        cin >> path;
        string temp;
        temp.resize(path.size());
        transform(path.begin(), path.end(), temp.begin(), ::tolower);
        if (temp == "exit"){cout << "Thank you for using me!!\n";return 0;}
        ifstream inputFile(path);
        if (inputFile.is_open()) {
            cout << "File opened successfully." << endl;
            stringstream content;
            content << inputFile.rdbuf();
            sentence = content.str();
            inputFile.close();
        }
        else{cout << "couldn't open file " << path << endl; continue;}
        unordered_map<string, int> frequencyMap;
        stringstream stream(sentence);
        string word;
        while (stream >> word) {
            word.erase(remove_if(word.begin(), word.end(), [](char c) {return ispunct(c) && c != '-';}), word.end()); //remove punctuation but not the "-"
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            frequencyMap[word]++;
        }
        for (auto &words : frequencyMap)
        {
            cout << words.first << ": " << words.second << endl;
        }
        cout << endl;
    }
    return 0;
}