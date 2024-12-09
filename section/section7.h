#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <algorithm>
#include <stdexcept>
using namespace std;

template <typename T>
class MyVector
{
private:
    T *data;
    size_t capacity = 2;
    size_t current_size = 0;

    void resize_capacity(size_t new_capacity);

public:
    MyVector();
    ~MyVector();

    bool empty() const;

    void push_back(const T &value);
    void pop_back();

    T max() const;
    T min() const;
    void sortFN();

    T *begin();
    T *end();
};

// maxelement()
template <typename T>
void MyVector<T>::resize_capacity(size_t new_capacity)
{
    T *newdata[capacity];
    for (int i = 0; i < capacity; i++)
    {
        newdata[i] = data[i];
    }
    delete[] data;
    data = newdata;
    capacity = new_capacity;
}

template <typename T>
inline MyVector<T>::~MyVector()
{
    delete[] data;
}

template <typename T>
bool MyVector<T>::empty() const
{
    if (current_size == 0)
    {
        return true;
    }
    return false;
}
template <typename T>
void MyVector<T>::push_back(const T &value)
{
    T *data[capacity];

    if (current_size == capacity)
    {
        if (capacity == 0)
        {
            resize_capacity(1);
        }
        else
        {
            resize_capacity(capacity * 2);
        }
    }
    data[current_size++] = value;
}

template <typename T>
void MyVector<T>::pop_back()
{
    if (current_size == 0)
        return;
    --current_size;
}

template <typename T>
T *MyVector<T>::begin()
{
    return data;
}
template <typename T>
T *MyVector<T>::end()
{
    return current_size + data;
}

template <typename T>
void MyVector<T>::sortFN()
{
    sort(data, data + current_size);
}
template <typename T>
T MyVector<T>::min() const
{
    return min_element(data, data + current_size);
}

template <typename T>
T MyVector<T>::max() const
{
    return max_element(data, data + current_size);
}

#endif