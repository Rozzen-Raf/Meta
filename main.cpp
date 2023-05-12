#include <iostream>
#include <type_traits>
using namespace std;

template<typename... U>
struct TypeList
{
    static const size_t lenght = 0;
};

template<typename T, typename ...U>
struct TypeList<T, U...>
{
    typedef T Head;
    typedef TypeList<U...> Tail;

    static const size_t lenght = Tail::lenght + 1;
};
//-------------------------------------------------------------

template<class TList, uint32_t index> struct TypeAt;

template<class Head, class... Tail>
struct TypeAt<TypeList<Head, Tail...>, 0>
{
    typedef Head Result;
};

template<class Head, class... Tail, uint32_t i>
struct TypeAt<TypeList<Head, Tail...>, i>
{
    typedef typename TypeAt<TypeList<Tail...>, i - 1>::Result Result;
};
//-------------------------------------------------------------

template<class TList, class T> struct Append;

template<class Head, class... Tail, class T>
struct Append<TypeList<Head, Tail...>, T>
{
    typedef TypeList<Head, Tail..., T> Result;
};
//-------------------------------------------------------------
template<class TList, class T> struct IndexOf;

template<class... Tail, class T>
struct IndexOf<TypeList<Tail...>, T>
{

};

template<class... Tail, class T>
struct IndexOf<TypeList<T, Tail...>, T>
{
    static const ssize_t value = 0;
};

template< class T, class Head, class... Tail>
struct IndexOf<TypeList<Head, Tail...>, T>
{
    static const ssize_t value = IndexOf<TypeList<Tail...>, T>::value + 1;
};
//-------------------------------------------------------------

struct Division{};
typedef TypeList<int, Division, char> Test;

int main()
{
    cout << Test::lenght << endl;

    cout << Append<Test, double>::Result::lenght << endl;

    cout << typeid (TypeAt<Append<Test, double>::Result, 3>::Result).name() << endl;

    cout << IndexOf<Test, char>::value << endl;

    return 0;
}
