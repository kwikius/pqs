

#include <pqs/concepts/meta/bool_constant.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>

#include <pqs/bits/binary_op.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/meta/or.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/bits/undefined.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>
//#include <pqs/bits/base_dimension_exp.hpp>

namespace pqs{

   // the application universe that is being modelled
   struct get_universe;

   template <typename T>
   struct is_base_quantity ;

   namespace impl {

      template <typename Where = void>
      struct get_universe_impl : pqs::undefined{};

      template <typename T, typename Universe, typename Where = void> 
      struct is_base_dimension_of_impl : std::false_type{};

      template <typename T, typename Where = void> 
      struct is_base_dimension_impl : std::false_type{};

   }// impl

   template <typename T>
   struct is_base_quantity : impl::is_base_dimension_impl<T>{};

#if defined __cpp_concepts

// TODO

#endif

}

void  experimental_test()
{
    
}