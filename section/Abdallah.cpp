#include <iostream>
#include <string>
using namespace std;
class LibraryItem
{
public:
    void virtual displayInfo() = 0;
    void checkOut()
    {
        cout << "Item Checked Out" << el;
    }
    void checkOut(int days)
    {
        cout << "Item Checked Out for " << days << " days" << el;
    }
};
class Book : public LibraryItem
{
    string title;
    string author;

public:
    Book(string t, string a)
    {
        title = t;
        author = a;
    }
    void displayInfo()
    {
        cout << "Book Title : " << title << el;
        cout << "Book author : " << author << el;
    }
    string getTitle() { return title; }
    string getAuthor() { return author; }

    bool operator==(Book &b)
    {
        if (title == b.getTitle() && author == getAuthor())
            return true;
        else
            return false;
    }
};
class Magazine : public LibraryItem
{
    string title;
    int issueNumber;

public:
    Magazine(string t, int i)
    {
        title = t;
        issueNumber = i;
    }
    void displayInfo()
    {
        cout << "Magazine Title : " << title << el;
        cout << "Magazine Issue Number : " << issueNumber << el;
    }
    operator int() { return issueNumber; }
};
int main()
{
    LibraryItem *library;
    Book book1("C++ Programming", "Bjarne Stroustrup");
    Book book2("C++ Programming", "Bjarne Stroustrup");
    Magazine mag1("Tech Monthly", 5);
    cout << "Library Item Details !!" << el;
    library = &book1;
    library->displayInfo();
    cout << el;
    library = &mag1;
    library->displayInfo();
    cout << el;

    cout << "Function overLoading for CheckOut " << el;
    book1.checkOut();
    book1.checkOut(7);
    cout << el;
    cout << "operator OverLoading for book Comparison : " << el;

    if (book1 == book2)
        cout << "books Are Identical ." << el;
    else
        cout << "Books Are Not identical." << el;
    cout << el;
    cout << "Type Casting in magazine : " << el;
    int issue = mag1;
    cout << "Issue number :  " << issue << el;
    cout << "Dummpy example : " << el;
    Magazine mag2("Tech Monthly", 6);
    cout << mag1 + mag2 << el;

    return 0;
}