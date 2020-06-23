// physical_quantities pqs-1-00-00 03:50 29/11/2003
//lab_example.cpp
//  feedback to andy@servocomm.freeserve.co.uk
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.


//This example was originally presented on the boost mailing list:
//http://lists.boost.org/MailArchives/boost/msg55344.php
//and was intended to show why I am not particularly keen on making all conversions
//explicit. I still hold the same view.
//note: I have changed the example to use the alternate syntax ie:
//q_velocity::mm_div_s
//rather than
//pq_velocity<float>::mm_div_s in the original example

#include "../pqs.hpp"

using namespace physical_quantities;

// function works in standard units
q_force::N  Force(
                    q_mass::kg           const& mass,
                    q_velocity::m_div_s  const& initial_veloc,
                    q_velocity::m_div_s  const& final_veloc,
                    q_time::s            const& t)
{
            return   mass * (final_veloc - initial_veloc) / t;
}

int main()
{
    //lab technician works in "odd units"...

    q_mass::g               const mass(0.1f);
    q_velocity::mm_div_min  const initial_v(5);
    q_velocity::mm_div_min  const final_v(5.5f);
    q_time::min             const t_min(10);
    q_time::s               const t_sec( 12);

    // function does the work ... he doesnt have to...

    std::cout << Force(mass,initial_v, final_v, t_min + t_sec) << '\n';

    // the alternative with explicit conversions...

    std::cout << Force(q_mass::kg(mass),
                q_velocity::m_div_s(initial_v),
                q_velocity::m_div_s(final_v),
                q_time::s(t_min) + t_sec ) <<'\n';

    // I prefer the first
  return 0;
}
