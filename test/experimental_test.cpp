

#include <pqs/concepts/meta/bool_constant.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/bits/base_dimension.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/meta/or.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>

namespace pqs{

   // the application universe that is being modelled
   struct get_universe;

   template <typename T>
   struct is_base_dimension ;

   template <typename T, typename Universe> 
   struct is_base_dimension_of;

   namespace impl {

      template <typename Where = void>
      struct get_universe_impl : pqs::undefined{};

      template <typename T, typename Universe, typename Where = void> 
      struct is_base_dimension_of_impl : std::false_type{};

      template <typename T, typename Where = void> 
      struct is_base_dimension_impl : std::false_type{};

   }// impl

   template <typename T>
   struct is_base_dimension : impl::is_base_dimension_impl<T>{};

   template <typename T, typename U>
   struct is_base_dimension_of : impl::is_base_dimension_of_impl<T, U>{};


#if defined __cpp_concepts

// TODO

#endif


}

void  experimental_test()
{
    
}