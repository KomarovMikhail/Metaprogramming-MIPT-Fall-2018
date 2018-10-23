#ifndef TYPELIST_TYPELIST_H
#define TYPELIST_TYPELIST_H


#include <glob.h>


// TypeList struct

template <typename ...T>
struct TypeList;

struct EmptyList {};

template <typename H>
struct TypeList<H> {
    using head = H;
    using tail = EmptyList;
};

template <typename H, typename ...T>
struct TypeList<H, T...> {
    using head = H;
    using tail = TypeList<T...>;
};


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
    using result = GetAt<typename TypeList<T...>::tail, i - 1>;
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



#endif //TYPELIST_TYPELIST_H
