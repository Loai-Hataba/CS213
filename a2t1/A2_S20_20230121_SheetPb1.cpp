#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class LabelGenerator{
protected:
    string label;
    int startingIndex = 1;

public:
    LabelGenerator(string l, int s){
        label = l;
        startingIndex = s;
    }
    virtual string nextLabel(){
        string res = label+" "+ to_string(startingIndex++);
        return res;
    }
};


class FileLabelGenerator:public LabelGenerator{
private:
    ifstream labelText;
    vector<string>lines;
public:
    FileLabelGenerator(string l, int s, string fileName):LabelGenerator(l,s){
        labelText.open(fileName,ios::in);
        if (labelText){
            cout<<"\n\nText file opened successfully.  (:\n\n";
        }
        else {
            cout<<"Couldn't open specified file opened default file instead\n";
            labelText.open("input.txt",ios::in);
        }
    }
    ~FileLabelGenerator(){
        labelText.close();
    }
    string nextLabel(){
        string line;
        while(getline(labelText, line)){
            lines.push_back(line);
        }
        if(lines[startingIndex].empty()){
            return "Empty line";
        }
        string res = label + ' '+to_string(startingIndex)+' '+lines[startingIndex++];
        return res;
    }
};

void sequentialLabels(){
    string label;
    int n,start;
    cout<<"Enter label name: ";
    cin.ignore();
    getline(cin,label);
    cout<<"Enter label starting count value : ";
    cin>>start;
    cout<<"Enter amount of labels to be generated: ";
    cin>>n;
    LabelGenerator labelNumbers(label, start);
    cout<<label<<" numbers: ";
    for (int i = 0; i < n; i++) {
        if (i == 0)cout <<labelNumbers.nextLabel();
        else cout << ", "<<labelNumbers.nextLabel();
    }
    while(true){
        int choice,x;
        cout<<"\nmore labels of "<<label<<" ?\n"
              "1. yes     any other num --> no\n";
        cin>>choice;
        if (choice == 1){
            cout<<"Enter amount of new labels: ";
            cin>>x;
            for (int i = 0; i < x; i++) {
                if (i == 0)cout <<labelNumbers.nextLabel();
                else cout << ", "<<labelNumbers.nextLabel();
            }
        }
        else return;
    }
}

void fileLabels(){
    string label;
    int n,start;
    string fileName;
    cout<<"Enter existing input file name with .txt extension (default is input.txt and has only 4 lines): ";
    cin.ignore();
    getline(cin, fileName);
    cout<<"Enter label name: ";
    getline(cin,label);
    cout<<"Enter label starting line in text file : ";
    cin>>start;
    cout<<"Enter amount of labels to be generated: ";
    cin>>n;
    FileLabelGenerator fileLabels(label, start, fileName);
    cout << label << " labels: \n";
    for (int i = 0; i < n; i++) {
        cout<<fileLabels.nextLabel()<<"."<<endl;
    }
    while(true){
        int choice,x;
        cout<<"\nmore labels of "<<label<<" ?\n"
              "1. yes     any other num --> no\n";
        cin>>choice;
        if (choice == 1){
            cout<<"Enter amount of new labels: ";
            cin>>x;
            for (int i = 0; i < x; i++) {
                cout<<fileLabels.nextLabel()<<"."<<endl;
            }
        }
        else return;
    }
}
void menu(){
    cout << "\n   Label Generator\n"
            "1. Sequential labels\n"
            "2. labels from text file captions\n"
            "3. Exit\n"
            "Enter your choice: ";
}

int main() {
    int choice;
    while (true) {
        menu();
        cin >> choice;
        switch (choice) {
            case 1:
                sequentialLabels();
                break;
            case 2:
                fileLabels();
                break;
            case 3:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again: ";
        }
    }
    return 0;
}