#include <string>
#include <iostream>

using namespace std;

class LibraryItem{
    public:
        virtual void displayInfo()=0;
        void checkOut(){cout << "Checked out\n";};
        void checkOut(int days){cout << "Checked out for " << days << " days\n" << endl;};

};

class Book : public LibraryItem{
    private:
        string title;
        string author;
    public:
        Book(string t, string a) : title(t), author(a){}
        void displayInfo() override{cout << "Book - Title: " << title << " , Author: " << author<< endl;};
        bool operator==(Book &other){return title == other.title && author == other.author;};
};

class Magazine : public LibraryItem{
    private:
        string title;
        int issueNumber;
    public:
        Magazine(string t, int i) : title(t), issueNumber(i){};
        void displayInfo() override{cout << "Magazine - Title: " << title << " , IssueNumber: " << issueNumber << endl;};
        operator int(){return issueNumber;};
};

int main(){
    LibraryItem *library;
    Book book1("To kill a mockingbird", "Loai Hataba");
    Book book2("Harry Potter", "abdullah mohammed");
    Book book3("Harry Potter", "abdullah mohammed");
    Magazine mag1("Tech monthly", 10);

    cout <<"\nLibrary Item Details:\n" << endl;
    library = &book1;
    library->displayInfo();
    library = &mag1;
    library->displayInfo();
    cout << endl;

    cout << "Function overloading for checking out:\n";
    book1.checkOut();
    book2.checkOut(5);
    cout << "Operator overloading for Book comparison:\n";
    if (book1 == book2)cout << "The books are identical\n";
    else cout << "The books 1,2 are not identical\n";
    if (book3 == book2)cout << "The books 2,3 are identical\n";
    else cout << "The books are not identical\n";
    cout << endl;

    cout << "Type casting in Magazine:\n";
    int issue = mag1;
    cout << "Issue Number: " << issue << endl << endl;

    cout << "Dummy Example:"<< endl;
    Magazine mag2("Techno", 6);
    cout << mag1 + mag2 << endl;
    return 0;
}