#ifndef PQS_BITS_DIMENSION_DEF_HPP_INCLUDED
#define PQS_BITS_DIMENSION_DEF_HPP_INCLUDED

#include <cstdint>
#include <type_traits>
#include <pqs/meta/not.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/concepts/dimension.hpp>

namespace pqs{

   namespace detail {
      struct dimension_base_class{};
   }

   template <typename ...D>
   struct dimension : pqs::detail::dimension_base_class{
      typedef dimension type;
      static constexpr uint32_t num_elements = sizeof...(D);
   };

   // Probably not needed... 
   template <> struct dimension<>{
      typedef dimension type;
      static constexpr uint32_t num_elements = 0;
   };

   // Thse two should probably be sorted 
   // maybe is_basic_dimension so is_dimension is is_basic or derived?
   // is_raw_dimension
   // is_dimension becomes is_raw_dimension
   // is_dimension is anything derived from dimension base_class
   template <typename ... D >
   struct is_dimension<pqs::dimension<D...> > : std::true_type{};


   // derived dimension is a dimension surely
   // maybe unnamed dimension for raw dimension
   // or named_abstract_quantity
   template <typename D>
   struct is_derived_dimension : 
      pqs::meta::and_<
         pqs::meta::not_<is_dimension<D> >,
         std::is_base_of<pqs::detail::dimension_base_class,D>
      >{};

}

#endif // PQS_BITS_DIMENSION_DEF_HPP_INCLUDED
