// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//box_example_explicit.cpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

//Implementation of the pq_box example dicussed in the abstract
// this version uses 'explicit' unit conversion ctors
// works with the PHYSICAL_QUANTITIES_USE_EXPLICIT_CONVERSION_CTOR switch
// defined in ../pq_types/default.hpp

//NOTE: requires compilation of ."./pq_types/acceleration.cpp" for gravity constant

#include "../pqs.hpp"
using namespace physical_quantities;

class PQ_box{
public:
    PQ_box(q_length::m const & l,q_length::m const& w, q_length::m const& h)
    : length(l),width(w),height(h){}
	
	q_force::kgf weight()
	{
		q_volume::m3 volume = length * width * height;
		q_mass::kg mass = contents.density * volume;
		return q_force::kgf(mass * q_acceleration::SI::g);  
	}
private:
    struct PQ_contents{
        PQ_contents()
        :density(1000){};
        q_density::kg_div_m3 density;
    }contents;
    q_length::m length;
	q_length::m width;
    q_length::m height;
};

int main()
{
    PQ_box pq_box(q_length::m(1) ,q_length::m(.5),q_length::m(.2));
    std::cout << pq_box.weight() <<'\n';
}
