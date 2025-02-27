#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class Set
{
private:
    vector<T> items;

    bool contains(T item)
    {
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i] == item)
            {
                return true;
            }
        }
        return false;
    }

public:
    Set() = default;

    void add(T item)
    {
        if (!contains(item))
        {
            items.push_back(item);
        }
    }

    void remove(T item)
    {
        for (auto it = items.begin(); it != items.end(); it++)
        {
            if (*it == item)
            {
                items.erase(it);
                return;
            }
        }
    }

    int getSize()
    {
        return items.size();
    }

    void isMember(T item)
    {
        if (contains(item))
        {
            cout << item << " exists in the set." << endl;
        }
        else
            cout << item << " doesn't exist in the set." << endl;
    }

    T *toArray()
    {
        T *array = new T[items.size()];
        for (int i = 0; i < items.size(); i++)
        {
            array[i] = items[i];
        }
        return array;
    }

    void display()
    {
        for (int i = 0; i < items.size(); ++i)
        {
            cout << items[i] << " ";
        }
        cout << endl;
    }
};

class MyClass
{
private:
    int val;

public:
    MyClass(int v) : val(v) {}

    bool operator==(const MyClass &other) const
    {
        return val == other.val;
    }

    bool operator!=(const MyClass &other) const
    {
        return val != other.val;
    }

    friend ostream &operator<<(ostream &os, MyClass obj)
    {
        os << obj.val;
        return os;
    }
};

int main()
{
    Set<string> s;
    s.add("Hello");
    s.add("hello");
    s.add("HELLO");
    s.add("hELLo");
    s.add("Hello0");
    s.add("hello0");
    s.display();
    /*
    // Int Set
    Set<int> intSet;
    intSet.add(10);
    intSet.add(20);
    intSet.add(10); // Duplicate -> ignored
    intSet.display();
    intSet.remove(20);
    intSet.display();

    // String Set
    Set<string> stringSet;
    stringSet.add("hello");
    stringSet.add("world");
    stringSet.add("hello"); // Duplicate -> ignored
    string s = "buh";
    stringSet.isMember(s);
    stringSet.display();

    // Custom Class Set
    Set<MyClass> myClassSet;
    myClassSet.add(MyClass(1));
    myClassSet.add(MyClass(2));
    myClassSet.add(MyClass(3));
    myClassSet.add(MyClass(1)); // Duplicate -> ignored
    myClassSet.display();

    // Convert to dynamically allocated array
    int* arr = intSet.toArray();
    for (int i = 0; i < intSet.getSize(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    string* stringArr = stringSet.toArray();
    for (int i = 0; i < stringSet.getSize(); ++i) {
        cout << stringArr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    delete[] stringArr;
    */
    return 0;
}