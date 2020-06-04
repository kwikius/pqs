#ifndef PQS_BITS_DETAIL_BASE_QUANTITY_EXP_BASE_CLASS_HPP_INCLUDED
#define PQS_BITS_DETAIL_BASE_QUANTITY_EXP_BASE_CLASS_HPP_INCLUDED


#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/bits/where.hpp>

namespace pqs{ 

   namespace detail{

      struct base_quantity_exp_base_class{};
   }
  
   namespace impl{

      // TODO speciiaise per base_quantity_exp
      // then can detect derived
      template <typename T>
      struct is_base_quantity_exp_impl <
          T,
         typename pqs::where_<
            std::is_base_of<pqs::detail::base_quantity_exp_base_class,T>
         >::type
      > : std::true_type{};

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

}

#endif // PQS_BITS_DETAIL_BASE_QUANTITY_EXP_BASE_CLASS_HPP_INCLUDED
