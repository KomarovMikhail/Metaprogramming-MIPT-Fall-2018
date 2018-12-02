#ifndef TYPELIST_HIERARCHIES_H
#define TYPELIST_HIERARCHIES_H

#include "typelist.h"


template<int N>
struct Fib {
    static constexpr size_t value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template<>
struct Fib<0> {
    static constexpr size_t value = 1;
};

template<>
struct Fib<1> {
    static constexpr size_t value = 1;
};


template<class, class B>
struct Unit : public B {};


// generates N-classes linear hierarchy

template<unsigned int N, class TypeList, template <class, class> class Unit>
struct GenLinearHierarchy;

template<unsigned int N, typename H, typename ...T, template <class, class> class Unit>
struct GenLinearHierarchy<N, TypeList<H, T...>, Unit> :
        public Unit<H, GenLinearHierarchy<N - 1, TypeList<T...>, Unit>> {};

template<typename H, typename ...T, template <class, class> class Unit>
struct GenLinearHierarchy<0, TypeList<H, T...>, Unit> {};

template<unsigned int N, template <class, class> class Unit>
struct GenLinearHierarchy<N, EmptyList, Unit> {};


// Fibonacci hierarchy

template<unsigned int i, typename TypeList, template <class, class> class Unit>
struct FibHierarchy;

template<unsigned int i, typename H, typename ...T, template <class, class> class Unit>
struct FibHierarchy<i, TypeList<H, T...>, Unit>
        : public GenLinearHierarchy<Fib<i>::value, TypeList<H, T...>, Unit>,
          public FibHierarchy<i + 1, typename Skip<TypeList<H, T...>, Fib<i>::value>::result, Unit> {};

template <unsigned int i, template <class, class> class Unit>
class FibHierarchy<i, EmptyList, Unit> {};

template <typename TypeList, template <class, class> class Unit>
using GenScatterHierarchy = FibHierarchy<0, TypeList, Unit>;


#endif //TYPELIST_HIERARCHIES_H
