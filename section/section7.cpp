#include "section7.h"
#include <iostream>

using namespace std;

int main()
{
    MyVector<int> vec;

    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(8);
    vec.push_back(1);

    cout << "MAX: " << vec.max() << el;
    cout << "MIN: " << vec.min() << el;

    vec.sortFN();

    cout << "SORTED: ";
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        cout << *it << " ";
    }
    cout << el;

    MyVector<string> s;
    s.push_back("banana");
    s.push_back("apple");
    s.push_back("cherry");
    cout << "MAX: " << s.max() << el;
    cout << "MIN: " << s.min() << el;

    s.sortFN();
    cout << "SORTED: ";
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        cout << *it << " ";
    }
    cout << el;
    return 0;
}