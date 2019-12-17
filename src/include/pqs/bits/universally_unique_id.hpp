#ifndef PQS_UNIVERSALLY_UNIQUE_ID_HPP_INCLUDED
#define PQS_UNIVERSALLY_UNIQUE_ID_HPP_INCLUDED

#include <cstdint>
#include <pqs/bits/binary_op.hpp>
#include <pqs/meta/and.hpp>
#include <pqs/bits/where.hpp>

namespace pqs{

   /*
     order msb , , , lsb
   */
   template <uint16_t... Id>
   struct universally_unique_id;

   template <>
   struct universally_unique_id<> {
      typedef universally_unique_id type;
      static constexpr std::size_t num_elements = 0;
   };

   template <uint16_t Msb, uint16_t...Rest>
   struct universally_unique_id<Msb,Rest...> : universally_unique_id<Rest... > {
      typedef universally_unique_id type;
      typedef universally_unique_id<Rest... >  ls_type;
      static constexpr uint16_t msb = Msb;
      static constexpr std::size_t num_elements = sizeof...(Rest) + 1;
   };

   namespace detail{

      template <typename T>
      struct is_uuid : std::is_base_of< pqs::universally_unique_id<> , T>{};

      template <std::size_t I,typename T>
      struct at_uuid{
         static constexpr uint16_t value = at_uuid<I-1,typename T::ls_type>::value;
      };

      template <typename T>
      struct at_uuid<0,T>{
         static_assert(T::num_elements > 0,"invalid uuid");
         static constexpr uint16_t value = T::msb;
      };

      template <typename T>
      struct shorten_uuid : pqs::meta::eval_if_c<
         ((T::num_elements == 1) || T::msb), 
         T, 
         shorten_uuid<typename T::ls_type> 
      >{};

      template <>
      struct shorten_uuid<universally_unique_id<> > { typedef void type;};

      //UUIDS UL UR must be same length
      template <typename UL, typename UR>
      struct compare_uuid :  pqs::meta::eval_if<
         std::integral_constant<bool,(at_uuid<0,UL>::value > at_uuid<0,UR>::value)>,
            std::integral_constant<int,1>,
         std::integral_constant<bool,(at_uuid<0,UL>::value < at_uuid<0,UR>::value)>,
            std::integral_constant<int,-1>,
         std::integral_constant<bool,(UL::num_elements > 1)>,
            compare_uuid<typename UL::ls_type, typename UR::ls_type>,
         std::integral_constant<int, 0>
      >{};

      template <typename UL, typename UR>
      struct less_uuid : std::integral_constant<
         bool, 
         (compare_uuid<
            typename shorten_uuid<UL>::type,typename shorten_uuid<UR>::type
         >::type::value < 0)
      >{};

      template <typename UL, typename UR>
      struct equal_to_uuid : std::integral_constant<
         bool, 
         (compare_uuid<
            typename shorten_uuid<UL>::type,typename shorten_uuid<UR>::type
         >::type::value == 0)
      >{};
   }

  namespace impl {

      template <typename TL, typename TR >
      struct binary_op_impl<
         TL,
         pqs::meta::less,
         TR,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::detail::is_uuid<TL>,
               pqs::detail::is_uuid<TR>
            >
         >::type
       > : pqs::detail::less_uuid<TL,TR>{};

      template <typename TL, typename TR >
      struct binary_op_impl<
         TL,
         pqs::meta::equal_to,
         TR,
         typename pqs::where_<
            pqs::meta::and_<
               pqs::detail::is_uuid<TL>,
               pqs::detail::is_uuid<TR>
            >
         >::type
       > : pqs::detail::equal_to_uuid<TL,TR>{};

  }// impl
}

#endif // PQS_UUID_H_INCLUDEDPQS_UNIVERSALLY_UNIQUE_ID_HPP_INCLUDED
