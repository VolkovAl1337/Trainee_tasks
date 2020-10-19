#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include <cstring>

class NegativeIndexException{};
class TooBigIndexException{};

template <typename T>
class Vector {
private:
    T* vectorPtr = NULL;
    int size = 0;
    int capasity = 1;
public:
    Vector(int s);
    Vector(int s, T element);

    int getSize();
    int getCapasity();

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
    if (s < 0) {
        throw NegativeIndexException();
    }

    size = s;
    capasity = s * 2;
    vectorPtr = new T[capasity];
}

template <typename T>
Vector<T>::Vector(int s, T element)
{
    if (s < 0) {
        throw NegativeIndexException();
    }

    size = s;
    capasity = s * 2;
    vectorPtr = new T[capasity];

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
int Vector<T>::getCapasity()
{
    return capasity;
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
    if (size + 1 <= capasity) {
        *(vectorPtr + size) = newElement;
        size += 1;
        return;
    }
    capasity *= 2;
    T* newPtr = new T[capasity];
    std::memcpy(newPtr, vectorPtr, size * sizeof(T));
    delete[] vectorPtr;

    vectorPtr = newPtr;

    *(vectorPtr + size) = newElement;
    size += 1;
}

template <typename T>
void Vector<T>::pushFront(T newElement)
{
    if (size + 1 <= capasity) {
        std::memcpy(vectorPtr + 1, vectorPtr, size * sizeof(T));
        size += 1;
        *vectorPtr = newElement;
        return;
    }
    capasity *= 2;
    T* newPtr = new T[capasity];
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

    if (size + 1 <= capasity) {
        std::memcpy(vectorPtr + pos + 1, vectorPtr + pos, sizeof(T) * (size - pos));
        *(vectorPtr + pos) = newElement;
        size += 1;
        return;
    }
    capasity *= 2;
    T* newPtr = new T[capasity];
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

    std::memcpy(vectorPtr, vectorPtr + 1, sizeof(T) * (size - 1));
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

    std::memcpy(vectorPtr + pos, vectorPtr + pos + 1, sizeof(T) * (size - pos - 1));
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
        throw TooBigIndexException();
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
        throw TooBigIndexException();
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
