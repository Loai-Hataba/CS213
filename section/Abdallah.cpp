#include <iostream>
#include <string>
using namespace std ;
class LibraryItem 
{
    public :
    void virtual displayInfo () = 0;
    void checkOut()
    {
        cout << "Item Checked Out" <<endl; 
    }
    void checkOut(int days){
        cout << "Item Checked Out for " << days << " days" << endl;
    }
};
class Book : public LibraryItem
{
    string title ;
    string author ;
    public: 
    Book(string t , string a )
    {
        title = t ;
        author = a ;
    }
    void displayInfo()
    {
        cout << "Book Title : " << title <<endl; 
        cout << "Book author : " << author <<endl; 
    }
    string getTitle(){ return title ; }
    string getAuthor () {return author ; } 

    bool operator == (Book& b) 
    {
        if(title == b.getTitle() && author == getAuthor() ) return true ;
        else return false ; 
    }

};
class Magazine  : public LibraryItem
{
    string title ;
    int issueNumber ;
    public :
    Magazine(string t , int i ) 
    {
        title = t ;
        issueNumber = i ;
    }
    void displayInfo() 
    {
        cout << "Magazine Title : " << title << endl;
        cout << "Magazine Issue Number : " << issueNumber << endl;
    }
     operator int(){return issueNumber ;} 
};
int main()
{
    LibraryItem * library ;
    Book book1("C++ Programming" , "Bjarne Stroustrup");
    Book book2("C++ Programming" , "Bjarne Stroustrup");
    Magazine mag1("Tech Monthly" ,5) ;
    cout << "Library Item Details !!" <<endl;
    library =&book1 ;
    library->displayInfo() ;
    cout << endl;
    library = &mag1;
    library->displayInfo();
    cout << endl;

    cout << "Function overLoading for CheckOut " <<endl; 
    book1.checkOut();
    book1.checkOut(7);
    cout <<endl; 
    cout << "operator OverLoading for book Comparison : " <<endl; 

    if(book1 == book2) cout << "books Are Identical ."<<endl;
    else cout << "Books Are Not identical." <<endl ; 
    cout << endl;
    cout << "Type Casting in magazine : "<<endl;
    int issue = mag1 ;
    cout << "Issue number :  " << issue <<endl; 
    cout << "Dummpy example : " <<endl; 
    Magazine mag2 ("Tech Monthly" , 6) ;
    cout << mag1 + mag2 <<endl;

    return 0 ;
}