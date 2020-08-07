

#include <pqs/systems/imperial/length.hpp>
#include <pqs/bits/math/floor.hpp>

/*
    split a length in feet into feet and inches using imperial measurement system
*/

using namespace pqs::imperial;
using namespace pqs::imperial::literals;

int main()
{
    std::cout << "PQS feet and inches (imperial measurement system) demo\n\n";

    auto constexpr  q = 1.25q_ft_imperial;

    // feet part demoing explicit cast of value_type to int
    auto constexpr q_ft = explicit_cast<int>(floor(q)); // feet part

    // inch part remainder requires 2 casts :
    // first to length in inches ( implicit_cast shows intent here)
    // then to int value_type
    auto constexpr q_in = explicit_cast<int>(
       implicit_cast< length::in<> >(q - q_ft) 
    );

    std::cout << q << " = " << q_ft << " " << q_in <<'\n';
}