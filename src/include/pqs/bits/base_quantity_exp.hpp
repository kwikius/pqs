#ifndef PQS_BITS_DETAIL_BASE_QUANTITY_EXP_BASE_CLASS_HPP_INCLUDED
#define PQS_BITS_DETAIL_BASE_QUANTITY_EXP_BASE_CLASS_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/bits/where.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/meta/and.hpp>

namespace pqs{ 

   namespace detail{

      struct base_quantity_exp_base_class{};
   }
  
   namespace impl{

      template <typename T>
      struct get_base_quantity_impl<
         T,
         typename pqs::where_<
            std::is_base_of<pqs::detail::base_quantity_exp_base_class,T>
         >::type
      > : T::base_type {};

      template <typename T>
      struct get_exponent_impl<
         T,
         typename pqs::where_<
            std::is_base_of<pqs::detail::base_quantity_exp_base_class,T>
         >::type
      > {
         typedef typename T::exponent type;
      };

   }//impl

   template <typename T>
   struct is_derived_from_base_quantity_exp : pqs::meta::and_<
      std::is_base_of<pqs::detail::base_quantity_exp_base_class,T>,
      pqs::meta::not_<pqs::is_base_quantity_exp<T> >
   >{};

}

#endif // PQS_BITS_DETAIL_BASE_QUANTITY_EXP_BASE_CLASS_HPP_INCLUDED
