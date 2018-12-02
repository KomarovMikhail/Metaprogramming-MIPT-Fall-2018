#include <iostream>
#include "hierarchies.h"


class Focuss {};

using list = TypeList<int, char, double>;

using list2 = Add<list, Focuss>::result;

using LinearHierarchy = GenLinearHierarchy<Fib<2>::value, list, Unit>;
using ScatterHierarchy = GenScatterHierarchy<list2, Unit>;

int main() {
    std::cout << Length<list2>::value << std::endl;
    GetAt<list2, 2>::result var = 0.1;
    std::cout << var << std::endl;
    Print<list2> ();

    return 0;
}