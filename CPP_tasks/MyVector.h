#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include <cstring>

template <typename T>
class Vector {
private:
    T* vectorPtr = NULL;
    int size = 0;
public:
    Vector(int s);
    Vector(int s, T element);

    int getSize();

    T* front();
    T* back();
    void pushBack(T newElement);
    void pushFront(T newElement);
    void insert(T newElement, int pos);
    T popFront();
    T popBack();
    T pop(int pos);
    void clear();
    void outputAll();

    T operator [](int index) const;
    T& operator [](int index);

    ~Vector();
};

template <typename T>
Vector<T>::Vector(int s)
{
    if (s < 1) {
        s = 1;
    }
    vectorPtr = new T[s];
    size = s;
}

template <typename T>
Vector<T>::Vector(int s, T element)
{
    vectorPtr = new T[s];
    size = s;
    for (int iter = 0; iter < size ; iter++)
    {
        *(vectorPtr + iter) = element;
    }
}

template <typename T>
int Vector<T>::getSize()
{
    return size;
}

template <typename T>
T* Vector<T>::front()
{
    return vectorPtr;
}

template <typename T>
T* Vector<T>::back()
{
    return vectorPtr + size - 1;
}

template <typename T>
void Vector<T>::pushBack(T newElement)
{
    T* newPtr = new T[size + 1];
    std::memcpy(newPtr, vectorPtr, size * sizeof(T));
    delete[] vectorPtr;

    vectorPtr = newPtr;

    *(vectorPtr + size) = newElement;
    size += 1;
}

template <typename T>
void Vector<T>::pushFront(T newElement)
{
    T* newPtr = new T[size + 1];
    std::memcpy(newPtr + 1, vectorPtr, size * sizeof(T));
    delete[] vectorPtr;

    *newPtr = newElement;

    vectorPtr = newPtr;
    size += 1;
}

//count of pos starts with 0
template <typename T>
void Vector<T>::insert(T newElement, int pos)
{
    if (pos >= size) {
        pushBack(newElement);
        return;
    } else if (pos <= 0) {
        pushFront(newElement);
        return;
    }
    T* newPtr = new T[size + 1];
    std::memcpy(newPtr, vectorPtr, sizeof(T) * pos);
    *(newPtr + pos) = newElement;
    std::memcpy(newPtr + pos + 1, vectorPtr + pos, sizeof(T) * (size - pos));

    delete[] vectorPtr;
    vectorPtr = newPtr;
    size += 1;
}

template <typename T>
T Vector<T>::popFront()
{
    if (size < 1) {
        return 0;
    }

    T tmp = *vectorPtr;
    T* newPtr = new T[size - 1];

    std::memcpy(newPtr, vectorPtr + 1, sizeof(T) * (size - 1));

    delete[] vectorPtr;
    vectorPtr = newPtr;
    size -= 1;

    return tmp;
}

template <typename T>
T Vector<T>::popBack()
{
    if (size < 1) {
        return 0;
    }

    T tmp = *(vectorPtr + size - 1);
    T* newPtr = new T[size - 1];

    std::memcpy(newPtr, vectorPtr, sizeof(T) * (size - 1));

    delete[] vectorPtr;
    vectorPtr = newPtr;
    size -= 1;

    return tmp;
}

template <typename T>
T Vector<T>::pop(int pos)
{
    if (size < 1) {
        return 0;
    }
    pos %= size;
    T tmp = *(vectorPtr + pos);
    T* newPtr = new T[size - 1];

    std::memcpy(newPtr, vectorPtr, sizeof(T) * (pos));
    std::memcpy(newPtr + pos, vectorPtr + pos + 1, sizeof(T) * (size - pos - 1));

    delete[] vectorPtr;
    vectorPtr = newPtr;
    size -= 1;

    return tmp;
}

template <typename T>
void Vector<T>::clear()
{
    delete[] vectorPtr;
    vectorPtr = NULL;
    size = 0;
}

template <typename T>
void Vector<T>::outputAll()
{
    int iter = 0;

    for (; iter < size - 1; iter++) {
        std::cout << "el[" << iter << "] " << *(vectorPtr + iter) << " at " << vectorPtr + iter << std::endl;
    }

    std::cout << "el[" << iter<< "] "<< *(vectorPtr + iter) << " at " << vectorPtr + iter;
}

//negative index returns data starting from back of vector
template <typename T>
T Vector<T>::operator[](int index) const
{
    if (index < 0) {
        index = -index;
        index %= size;
        if (index == 0) {
            index = 1;
        }
        return *(vectorPtr + size - index);
    }

    if (index >= size) {
        index %= size;
        return *(vectorPtr + index);
    }

    return *(vectorPtr + index);
}

//negative index returns data starting from back of vector
template <typename T>
T& Vector<T>::operator[](int index) {
    if (index < 0) {
        index = -index;
        index %= size;
        if (index == 0) {
            index = 1;
        }
        return *(vectorPtr + size - index);
    }

    if (index >= size) {
        index %= size;
        return *(vectorPtr + index);
    }

    return *(vectorPtr + index);
}

template <typename T>
Vector<T>::~Vector()
{
    if (vectorPtr) {
        delete[] vectorPtr;
    }
}
#endif
