#ifndef TYPELIST_TYPELIST_H
#define TYPELIST_TYPELIST_H


#include <glob.h>
#include <iostream>
#include <typeinfo>


// TypeList struct

struct NullType {};

template<typename ...T>
struct TypeList {
    using head = NullType;
    using tail = NullType;
};

using EmptyList = TypeList<>;

template<typename H, typename ...T>
struct TypeList<H, T...> {
    using head = H;
    using tail = TypeList<T...>;
};


// Prints TypeList

template<typename T>
void Print() {
    std::cout << typeid(typename T::head).name() << " ";
    Print<typename T::tail>();
}

template<>
void Print<EmptyList>() {
    std::cout << std::endl;
}


// Length method

template <typename TypeList>
struct Length;

template <>
struct Length<EmptyList> {
    static constexpr size_t value = 0;
};

template <typename ...T>
struct Length<TypeList<T...>> {
    static constexpr size_t value = 1 + Length<typename TypeList<T...>::tail>::value;
};


// GetAt method

template <typename TypeList, size_t i>
struct GetAt;

template <typename ...T>
struct GetAt<TypeList<T...>, 0> {
    using result = typename TypeList<T...>::head;
};

template <typename ...T, size_t i>
struct GetAt<TypeList<T...>, i> {
    using result = typename GetAt<typename TypeList<T...>::tail, i - 1>::result;
};


// Add method

template <typename TypeList, typename T>
struct Add;

template <typename T>
struct Add<EmptyList, T> {
    using result = TypeList<T>;
};

template <typename ...H, typename T>
struct Add<TypeList<H...>, T> {
    using result = TypeList<H..., T>;
};


// Skip method: Skips first N elements

template<typename TypeList, size_t N>
struct Skip;

template<typename TypeList>
struct Skip<TypeList, 0> {
    using result = TypeList;
};

template<unsigned int N>
struct Skip<EmptyList, N> {
    using result = EmptyList;
};

template<>
struct Skip<EmptyList, 0> {
    using result = EmptyList;
};

template<typename TypeList, size_t N>
struct Skip {
    using result = typename Skip<typename TypeList::tail, N - 1>::result;
};



#endif //TYPELIST_TYPELIST_H
