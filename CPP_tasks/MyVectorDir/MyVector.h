#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include <cstring>

class NegativeIndexException{};
class EmptyVectorException{};
class TooBigIndexException{};

template <typename T>
class Vector {
private:
    T* vectorPtr = NULL;
    int size = 0;
    int capacity = 0;
public:
    Vector(int sizeNew);
    Vector(int sizeNew, T element);

    int getSize();
    int getCapacity();

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
    inline void sizeNegativeCheck(int size);
    inline void emptyVectorCheck(int size);
    inline void tooBigSizeCheck(int size);
    T operator [](int index) const;
    T& operator [](int index);

    ~Vector();
};

template <typename T>
inline void Vector<T>::sizeNegativeCheck(int size) {
    if (size < 0) {
        throw NegativeIndexException();
    }
}

template <typename T>
inline void Vector<T>::emptyVectorCheck(int size) {
    if (size == 0) {
        throw EmptyVectorException();
    }
}

template <typename T>
inline void Vector<T>::tooBigSizeCheck(int index) {
    if (index => size) {
        throw EmptyVectorException();
    }
}

template <typename T>
Vector<T>::Vector(int sizeNew)
{
    sizeNegativeCheck(sizeNew);

    size = sizeNew;
    capacity = sizeNew * 2;
    vectorPtr = new T[capacity];
}

template <typename T>
Vector<T>::Vector(int sizeNew, T element)
{
    sizeNegativeCheck(sizeNew);

    size = sizeNew;
    capacity = sizeNew * 2;
    vectorPtr = new T[capacity];

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
int Vector<T>::getCapacity()
{
    return capacity;
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
    if (size < capacity) {
        *(vectorPtr + size) = newElement;
        size += 1;
        return;
    }
    capacity *= 2;
    T* newPtr = new T[capacity];
    std::memcpy(newPtr, vectorPtr, size * sizeof(T));
    delete[] vectorPtr;

    vectorPtr = newPtr;

    *(vectorPtr + size) = newElement;
    size += 1;
}

template <typename T>
void Vector<T>::pushFront(T newElement)
{
    if (size < capacity) {
        std::memcpy(vectorPtr + 1, vectorPtr, size * sizeof(T));
        size += 1;
        *vectorPtr = newElement;
        return;
    }
    capacity *= 2;
    T* newPtr = new T[capacity];
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

    if (size < capacity) {
        std::memcpy(vectorPtr + pos + 1, vectorPtr + pos, sizeof(T) * (size - pos));
        *(vectorPtr + pos) = newElement;
        size += 1;
        return;
    }

    capacity *= 2;
    T* newPtr = new T[capacity];
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
    emptyVectorCheck(size);

    T tmp = *vectorPtr;

    std::memcpy(vectorPtr, vectorPtr + 1, sizeof(T) * (size - 1));
    size -= 1;

    return tmp;
}

template <typename T>
T Vector<T>::popBack()
{
    emptyVectorCheck(size);

    T tmp = *(vectorPtr + size - 1);

    size -= 1;

    return tmp;
}

template <typename T>
T Vector<T>::pop(int pos)
{
    emptyVectorCheck(size);

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
    capacity = 0;
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

    tooBigSizeCheck(index);

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

    tooBigSizeCheck(index);

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
