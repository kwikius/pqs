#include "pq_acceleration.hpp"

// gravitational constant S.I units
template<>
physical_quantities::pq_acceleration<
    physical_quantities::pq_default_value_type
>::m_div_s2 const
physical_quantities::pq_acceleration<
    physical_quantities::pq_default_value_type
>::SI::g(9.80665f);
