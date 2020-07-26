
#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/time.hpp>

int main()
{
    pqs::si::length::mm<> q1{20};
    pqs::si::time::ms<> q2{20};

    // should fail since these are not dimensionally equvalent
    auto q3 = q1 + q2; 
}
