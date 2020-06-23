// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//multiplied_log_enum.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

#ifndef PHYSICAL_QUANTITIES_MULTIPLIED_LOG_ENUM_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITIES_MULTIPLIED_LOG_ENUM_HPP_INCLUDED2911030401

namespace physical_quantities{
   
    template <typename T, T t>
    struct multiplied_log_enum {
        typedef multiplied_log_enum<T,t> type;
        static const T value = t ;
        static long const value_as_long = t;
    };

}// namespace physical_quantities
#endif
