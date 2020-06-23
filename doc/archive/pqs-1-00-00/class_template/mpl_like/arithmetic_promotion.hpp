// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//arithmetic_promotion.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.


#ifndef PHYSICAL_QUANTITIES_ARITHMETIC_PROMOTION_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_ARITHMETIC_PROMOTION_HPP_INCLUDED2911030401

namespace physical_quantities {

    template <typename T>
    class arithmetic_promotion;

    template<>
    class arithmetic_promotion<bool>{
    public:
        static int const value=1;
    };
    template<>
    class arithmetic_promotion<char>{
    public:
        static int const value=2;
    };
    template<>
    class arithmetic_promotion<signed char>{
    public:
        static int const value=3;
    };
    template<>
    class arithmetic_promotion<unsigned char>{
    public:
        static int const value=4;
    };
    template<>
    class arithmetic_promotion<short>{
    public:
        static int const value=5;
    };
    template<>
    class arithmetic_promotion<unsigned short>{
    public:
        static int const value=6;
    };
    template<>
    class arithmetic_promotion<int>{
    public:
        static int const value=7;
    };
    template<>
    class arithmetic_promotion<unsigned int>{
    public:
        static int const value=8;
    };
    template<>
    class arithmetic_promotion<long>{
    public:
        static int const value=9;
    };
    template<>
    class arithmetic_promotion<unsigned long>{
    public:
        static int const value=10;
    };
    template<>
    class arithmetic_promotion<float>{
    public:
        static int const value=11;
    };

    template<>
    class arithmetic_promotion<double>{
    public:
        static int const value=12;
    };
    template<>
    class arithmetic_promotion<long double>{
    public:
        static int const value=13;
    };
}
#endif


//revision
// 17 10 03         cheap'n cheerful arithmetic_promotion
