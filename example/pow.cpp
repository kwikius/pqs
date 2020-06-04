
#include <pqs/math/root.hpp>
#include <iostream>


int main()
{
    auto x = pqs::root<2>(100.);

    std::cout << x <<'\n';
}