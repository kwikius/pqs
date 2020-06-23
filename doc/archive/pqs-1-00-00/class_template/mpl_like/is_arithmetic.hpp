// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
// is_arithmetic.hpp

// initially from C++ templates the complete guide by David Vandevvorde &  Nicolai M.Josuttis

// from boost::type_trait::is_arithmetic<T> which is
// (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
// Permission to copy, use, modify, sell and distribute this software is 
// granted provided this copyright notice appears in all copies. This software 
// is provided "as is" without express or implied warranty, and with no claim 
// as to its suitability for any purpose.
//
// See http://www.boost.org for most recent version including documentation.

#ifndef PHYSICAL_QUANTITIES_IS_ARITHMETIC_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_IS_ARITHMETIC_HPP_INCLUDED2911030401

namespace physical_quantities{

    template<typename T>
    class is_arithmetic{
    public:
        enum {value=0};
    };

    template<>
    class is_arithmetic<char>{
    public:
        enum {value=1};
    };
    template<>
    class is_arithmetic<unsigned char>{
    public:
        enum {value=1};
    };
    template<>
    class is_arithmetic<signed char>{
    public:
        enum {value=1};
    };
    template<>
    class is_arithmetic<unsigned short>{
    public:
        enum {value=1};
    };
    template<>
    class is_arithmetic<signed short>{
    public:
        enum {value=1};
    };
    template<>
    class is_arithmetic<unsigned int>{
    public:
        enum {value=1};
    };
    template<>
    class is_arithmetic<int>{
    public:
        enum {value=1};
    };
    template<>
    class is_arithmetic<unsigned long>{
    public:
        enum {value=1};
    };
    template<>
    class is_arithmetic<long>{
    public:
        enum {value=1};
    };
    template<>
    class is_arithmetic<float>{
    public:
        enum {value=1};
    };
    template<>
    class is_arithmetic<double>{
    public:
        enum {value=1};
    };
    template<>
    class is_arithmetic<long double>{
    public:
        enum {value=1};
    };
}

#endif


