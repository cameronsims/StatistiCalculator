#ifndef VECTOR_H
#define VECTOR_H

#include "Exception.h"
#include <memory>

#define VECTOR_RESIZE(n) ( (size_t)(1.5 * n) + 8 )

template<typename T>
class Vector {
public:

    // Constructors ////////////////////////////////////////////

                   Vector      (size_t             p_size = 1);
                   Vector      (const Vector<T>&        p_src);
    Vector<T>&     operator=   (const Vector<T>&        p_src);
                   ~Vector     (                             );

    ////////////////////////////////////////////////////////////




    // Iteratable Functions ////////////////////////////////////

    size_t         size        (                             ) const;
    Vector<T>&     push        (const T&            p_element);
          T&       operator[]  (size_t                p_index);
    const T&       operator[]  (size_t                p_index) const;

    ////////////////////////////////////////////////////////////

private:

    // Private Helper Functions ////////////////////////////////

    void           m_copy      (const Vector<T>&        p_src);
    void           m_alloc     (size_t                 p_size);
    void           m_realloc   (size_t                 p_size);
    bool           m_inBound   (size_t                p_index);
                                                     
    ////////////////////////////////////////////////////////////




    // Private Member Variables ////////////////////////////////

    T* m_data;
    size_t m_size;
    size_t m_capacity;

    ////////////////////////////////////////////////////////////
};












template<typename T>
Vector<T>::Vector(size_t p_size) {
    m_alloc(p_size);
}

template<typename T>
Vector<T>::Vector(const Vector<T>& p_src) {
    this->m_copy(p_src);
}

template<typename T>
Vector<T>& Vector<T>::operator= (const Vector<T>& p_src) {
    this->m_copy(p_src);
    return *this;
}

template<typename T>
Vector<T>::~Vector() {
    delete[] m_data;
    m_data = nullptr;
}

template<typename T>
size_t Vector<T>::size() const {
    return this->m_size;
}

template<typename T>
Vector<T>& Vector<T>::push(const T& p_element) {
    if (this->m_size >= this->m_capacity) {
        this->m_realloc(VECTOR_RESIZE(m_size));
    }
    this->m_data[this->m_size] = p_element;
    this->m_size++;
    return (*this);
}

template<typename T>
T& Vector<T>::operator[](size_t p_index) {
    if (this->m_size >= this->m_capacity) {
        this->m_realloc(VECTOR_RESIZE(p_index));
    }
    if (this->m_size <= p_index) {
        this->m_size = p_index + 1 ;
    }
    return this->m_data[p_index];
}

template<typename T>
const T& Vector<T>::operator[](size_t p_index) const {
    if (this->m_size <= p_index || this->m_size >= this->m_capacity) {
        throw OutOfRange();
    }
    return this->m_data[p_index];
}

template<typename T>
void Vector<T>::m_copy(const Vector<T>& p_src) {
    // Check if at same memory address
    if (this == &p_src) {
        return;
    }
    
    // If our capacity is smaller
    if (this->m_capacity < p_src.m_capacity) {
        this->m_alloc(p_src.m_capacity);
    }
    // Set values over
    this->m_size = p_src.m_size;
    for (size_t i = 0; i < this->m_size; i++) {
        this->m_data[i] = p_src.m_data[i];
    }
}

template<typename T>
void Vector<T>::m_alloc(size_t p_size) {
    m_capacity = p_size;
    m_size = 0;
    try {
        m_data = new T[m_capacity];
    } catch (const std::bad_alloc&) {
        // Throw own error
        m_capacity = 0;
        throw BadAlloc();
    }
}

template<typename T>
void Vector<T>::m_realloc(size_t p_size) {
    // Copy to temp
    const size_t oldSize = this->size();
    T* temp = new T[oldSize];
    for (size_t i = 0; i < oldSize; i++) {
        temp[i] = this->m_data[i];
    }

    // Re allocate
    this->m_alloc(p_size);
    this->m_size = oldSize;

    // Save
    for (size_t i = 0; i < oldSize; i++) {
        this->m_data[i] = temp[i];
    }

    delete[] temp;
}

template<typename T>
bool Vector<T>::m_inBound(size_t p_index) {
    return (m_capacity != 0 && this->m_size < p_index);
}









#endif