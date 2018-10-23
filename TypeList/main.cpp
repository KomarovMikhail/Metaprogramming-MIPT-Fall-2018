#include <iostream>
#include "typelist.h"
#include <typeinfo>

using list = TypeList<int, char, double>;

using list2 = Add<list, float>::result;

int main() {

    std::cout << Length<list2>::value << std::endl;

    return 0;
}