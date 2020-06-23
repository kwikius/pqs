// physical_quantities pqs-1-00-00 03:50 29/11/2003
//orig-demo.cpp
// feedback to andy@servocomm.freeserve.co.uk
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.
/*
Update of the original demo from my site at
http://www.servocomm.freeserve.co.uk/Cpp/physical_quantity/index.html

pqs-1-00-00 solves two problems in the original version
1 the comparisons problem
2 the result of an operation on two pqs which is now order independent
note: Also updated to use the shorter syntax and SI style naming:
q_velocity::m_div_s
instead of:
pq_velocity<>::m_per_s
*/

#include  "../pqs.hpp"

using namespace physical_quantities;

int main()
{
    std::cout << "The original demonstration of"
    "\nthe physical quantities type"
    "\nnow implemented in pqs-1-00-00\n\n";

    // compare physical_quantities etc of same type/pq_value but different units...
    q_length::m      length1 (7);
    q_length::ft     length2 = length1 ; // == length1 but diff units
    std::cout << length2 << " == " << length1 
    << " is " << std::boolalpha << (length2 == length1)<<'\n';
    std::cout << length1 << " == " << length2 
    << " is " << std::boolalpha << (length1 == length2) <<'\n';
    
    if ( length2 != length1) 
        std::cout << "conversion error is " <<  ((length1 > length2)
                       
                ? length1-length2 : length2-length1)  << '\n';

    if ( length1 != length2) 
        std::cout << "conversion error is " <<  ((length2 > length1)
    
                ? length2-length1 : length1-length2)  << '\n';
    std::cout << "ratio of length1 to length2 is " << length1/length2 <<'\n'
    << std::endl;

//-------------

    // calculate length of a hypotenuse for 3,4,5 right angled triangle:
    q_length::mm const    opposite (3000);
    q_length::m  const       adjacent    (4);
    q_length::ft        hypotenuse;          // in feet...:-)
    std::cout << "length of hypotenuse for right-angled triangle"
    "\nof opposite-side of length "         << opposite
    << "\nand adjacent-side of length "     << adjacent
    << "\nis "                              << ( hypotenuse = 
            root<2>( power<2>(adjacent) + power<2>(opposite) ) );

    std::cout << " or " << q_length::km(hypotenuse) << '\n';
    std::cout << "BTW - its a 3,4,5 triangle :-)\n"; 
    std::cout << std::endl;

//-----------------

    // calc  dist = u * t + 1/2 a * t*t;
    q_time::s                   const time_taken(10);
    q_velocity::mi_div_h        const initial_velocity( q_velocity::m_div_s(10) );
    q_acceleration::m_div_s2    const acceleration(9.8);
    q_length::mi                distance_travelled;
    
    std:: cout 
    << "Distance travelled in "        << time_taken 
    << "\nwith initial velocity of "   << initial_velocity
    << "\nand acceleration of "        << acceleration
    << "\nis "                         << ( distance_travelled = 
            initial_velocity * time_taken + 0.5 * 
                acceleration * power<2>(time_taken) );
    std::cout << " or " << q_length::m(distance_travelled) << '\n';
    std:: cout << "BTW - " << initial_velocity
    << " is " << q_velocity::m_div_s(initial_velocity) <<'\n'
    << std::endl;

//-------------

    // calculate a force
    q_mass::g              const m(0.001);    
    q_velocity::m_div_s    const v0(200);
    q_velocity::m_div_s    const v1(10000);
    q_time::us             const t(40);
    q_force::N                   f;
    std::cout 
    << "For a mass of "                     << m 
    << "\nwith an initial velocity of "     << v0
    << "\nto acquire a final velocity of "  << v1 
    << "\nin "                              <<  t 
    // note: uses the "newtons" ostream << specialisation
    << "\nrequires a force of " 
    << ( f = m * (v1 - v0) / t ) << '\n';
    // uses the kgf ostream specialisation
    std:: cout << "which is equal to "<< q_force::kgf(f)
    << std::endl;
   
    return 0;
}


