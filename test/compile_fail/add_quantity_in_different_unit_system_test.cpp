
#include <pqs/systems/si/length.hpp>
#include <pqs/systems/imperial/length.hpp>

int main()
{
    pqs::si::length::mm<> q1{20};
    pqs::imperial::length::ft<> q2{20};

    // should fail since these are different unit systems
    auto q3 = q1 + q2;
    
}
