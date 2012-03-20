#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <stdexcept>

using namespace std;


namespace test_namespace
{
template <class T>
class Array;

template <class T>
void f(Array<T>& a);

template<class T>
Array<T>* combine(Array<T>& a1, Array<T>& a2);

template <class T> class Array
{
    T* array;
    int size;

public:
    Array(int sz): size(sz)
    {
        array = new T[size];
        memset(array, 0, size * sizeof(T));
    }

    Array(const Array& a)
    {
        size = a.size;
        array = new T[size];
        memcpy_s(array, a.array, sizeof(T));
    }

    T& operator[](int i)
    {
        return *(array + i);
    }

    int Length()
    {
        return size;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
            cout << *(array + i) << " ";

        cout << endl;
    }

    //template<class T>
    friend Array<T>* combine<>(Array<T>& a1, Array<T>& a2);

    // If you replace the friend declaration with the int-specific
    // version, only the int specialization will be a friend.
    // The code in the generic f will fail
    // with C2248: 'Array<T>::size' :
    // cannot access private member declared in class 'Array<T>'.
    //friend void f<int>(Array<int>& a);

    friend void f<>(Array<T>& a);
};


// f function template, friend of Array<T>
template <class T>
void f(Array<T>& a)
{
    cout << a.size << " generic" << endl;
}

// Specialization of f for int arrays
// will be a friend because the template f is a friend.
template<> void f(Array<int>& a)
{
    cout << a.size << " int" << endl;
}

template<class T>
Array<T>* combine(Array<T>& a1, Array<T>& a2)
{
    Array<T>* a = new Array<T>(a1.size + a2.size);
    for (int i = 0; i < a1.size; i++)
        (*a)[i] = *(a1.array + i);

    for (int i = 0; i < a2.size; i++)
        (*a)[i + a1.size] = *(a2.array + i);

    return a;
}

int test_Array()
{
    {
        /// test friend template func combine ...
        Array<char> alpha1(26);
        for (int i = 0 ; i < alpha1.Length() ; i++)
            alpha1[i] = 'A' + i;

        alpha1.print();

        Array<char> alpha2(26);
        for (int i = 0 ; i < alpha2.Length() ; i++)
            alpha2[i] = 'a' + i;

        alpha2.print();
        Array<char>*alpha3 = combine(alpha1, alpha2);
        alpha3->print();
        delete alpha3;
    }
    {
        /// test friend template func f ...
        Array<char> ac(10);
        f(ac);

        Array<int> a(10);
        f(a);
    }
    return 0;
}
} /// namespace test_namespace

int main()
{
    {
        using namespace test_namespace;
        test_Array();
    }
    cout << " Hello world!" << endl;
    return 0;
}
