#include <pqs/si/speed.hpp>

int main()
{
  // should fail as only explicit conversion allowed
  auto q = pqs::implicit_cast<pqs::si::speed::m_per_s>(1.0);
}