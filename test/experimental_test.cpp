

#include <pqs/concepts/meta/bool_constant.hpp>
#include <pqs/concepts/meta/totally_ordered.hpp>
#include <pqs/bits/base_dimension.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/meta/or.hpp>
#include <pqs/meta/not.hpp>
#include <pqs/bits/undefined.hpp>

namespace pqs{

   namespace impl {

      /*
          implement these for your set of base dimensions to fulfill the requirement
          that your base dimensions are totally_ordered within your quantity_system
      */

      template <typename BaseDimensionL, typename BaseDimensionR, typename Where = void>
      struct base_dimension_less_than_impl : pqs::undefined{};

      template <typename BaseDimensionL, typename BaseDimensionR, typename Where = void>
      struct base_dimension_equal_to_impl : pqs::undefined{};

  }

   template <typename BaseDimensionL, typename BaseDimensionR>
   struct base_dimension_less_than : impl::base_dimension_less_than_impl<BaseDimensionL, BaseDimensionR>{};

   template <typename BaseDimensionL, typename BaseDimensionR>
   struct base_dimension_equal_to : impl::base_dimension_equal_to_impl<BaseDimensionL, BaseDimensionR>{};

   template <typename BaseDimensionL, typename BaseDimensionR>
   struct base_dimension_not_equal_to : pqs::meta::not_< base_dimension_equal_to<BaseDimensionL, BaseDimensionR> >{};

   template <typename BaseDimensionL, typename BaseDimensionR>
   struct base_dimension_greater_than : pqs::meta::not_<
      pqs::meta::or_< 
         base_dimension_less_than<BaseDimensionL, BaseDimensionR >,
         base_dimension_equal_to<BaseDimensionL, BaseDimensionR >
      >
   >{};

#if defined __cpp_concepts



#endif


}




void  experimental_test()
{
    
}