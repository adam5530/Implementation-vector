#include <iostream>
#include <vector>

using namespace std;

template<class T>class Vector
{
private:
    unsigned int m_size;
    unsigned int m_capacity;
    unsigned int m_currentIndex;
    T* m_buffer;
public:
    Vector();
    Vector(const unsigned int &size);
    Vector(const Vector<T>& val);
    ~Vector();
    T& operator[] (unsigned int index);
    Vector<T> & operator= (const Vector<T>&);
    void push_back(const T& val);
    void pop_back();
    void clear();
    unsigned size();
    unsigned capacity() const;
    bool empty() const;
    typedef T* Iterator;
    Iterator begin();
    Iterator end();
};

template<class T> Vector<T>::Vector()
    : m_size{0}
    , m_capacity{0}
    , m_currentIndex{0}
{

}

template<class T> Vector<T>::Vector(const unsigned int& size)
    : m_size{size}
    , m_capacity{size}
    , m_currentIndex{0}
    , m_buffer{new T[m_size]}
{
    for(unsigned int i = 0; i < m_size; i++)
        m_buffer[i] = 0;
}

template<class T> Vector<T>::Vector(const Vector<T>& val)
    : m_size{val.m_size}
    , m_capacity{val.m_capacity}
    , m_currentIndex{val.m_currentIndex}
    , m_buffer{new T[val.m_size]}
{
    for(unsigned int i = 0; i < m_size; i++)
        m_buffer[i] = val.m_buffer[i];
}

template<class T> Vector<T>::~Vector()
{
    delete []m_buffer;
}

template<class T> T& Vector<T>::operator [](unsigned int index)
{
    return m_buffer[index];
}

template<class T> void Vector<T>::push_back(const T& val)
{
    if(m_buffer == nullptr)
        m_buffer = new T[0];
    if(m_capacity == m_currentIndex && m_size == 0)
    {
        m_capacity++;
        m_buffer = new T[1];
        m_buffer[0] = val;
    }
    if(m_capacity == m_currentIndex && m_currentIndex == 1)
    {
        m_capacity = 2;
        T* temp = new T[1];
        temp[0] = m_buffer[0];
        delete []m_buffer;
        m_buffer = new T[2];
        m_buffer[0] = temp[0];
        delete []temp;
    }
    if(m_capacity == m_currentIndex)
    {
        T* temp = new T[m_capacity];
        for(unsigned int i = 0; i < m_capacity; i++)
            temp[i] = m_buffer[i];
        delete [] m_buffer;
        m_capacity *= 2;
        m_buffer = new T[m_capacity];
        for(unsigned int i = 0; i < m_capacity/2; i++)
            m_buffer[i] = temp[i];
        delete[] temp;
    }
    m_buffer[m_currentIndex++] = val;
    m_size++;
}

template<class T> void Vector<T>::pop_back()
{
    m_size--;
}

template<class T> void Vector<T>::clear()
{
    m_size = 0;
    m_capacity = 0;
    m_currentIndex = 0;
    delete []m_buffer;
}

template<class T> unsigned int Vector<T>::size()
{
    return m_size;
}

template<class T> unsigned int Vector<T>::capacity() const
{
    return m_capacity;
}

template<class T> bool Vector<T>::empty() const
{
    return m_size == 0;
}

template<class T> typename Vector<T>::Iterator Vector<T>::begin()
{
    return m_buffer;
}

template<class T> typename Vector<T>::Iterator Vector<T>::end()
{
    return m_buffer + size();
}

int main()
{
    Vector<int>vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(7);
    cout << "Size of vector: " << vec.size() << endl;
    cout << "Capacity of vector: " << vec.capacity() << endl;
    vec.clear();
    cout << "Size of vector: " << vec.size() << endl;
    return 0;
}
