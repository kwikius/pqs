#ifndef PQS_UNIVERSALLY_UNIQUE_ID_HPP_INCLUDED
#define PQS_UNIVERSALLY_UNIQUE_ID_HPP_INCLUDED

#include <cstdint>
#include <pqs/concepts/associated/binary_op.hpp>


namespace pqs{

   /**
    * @brief a variadic uuid class
    */
   template <uint16_t... Id>
   struct uuid;

   template <>
   struct uuid<> {
      typedef uuid type;
      static constexpr std::size_t num_elements = 0;
   };

   template <uint16_t Msb, uint16_t...Rest>
   struct uuid<Msb,Rest...> : uuid<Rest... > {
      typedef uuid type;
      typedef uuid<Rest... >  ls_type;
      static constexpr uint16_t msb = Msb;
      static constexpr std::size_t num_elements = sizeof...(Rest) + 1;
   };

   namespace detail{

      template <typename T>
      inline constexpr bool is_uuid = std::is_base_of_v< pqs::uuid<> , T>;

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
      struct shorten_uuid<uuid<> > { typedef void type;};

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
   }

  namespace impl {

      template <typename TL, typename TR >
         requires  
            pqs::detail::is_uuid<TL> &&
            pqs::detail::is_uuid<TR>
      struct binary_op_impl<
         TL,
         pqs::less,
         TR
       > : std::bool_constant<
         (pqs::detail::compare_uuid<
            typename pqs::detail::shorten_uuid<TL>::type,
            typename pqs::detail::shorten_uuid<TR>::type
         >::type::value < 0)
      >{};

      template <typename TL, typename TR >
         requires  
            pqs::detail::is_uuid<TL> &&
            pqs::detail::is_uuid<TR>
      struct binary_op_impl<
         TL,
         pqs::equal_to,
         TR
       > : std::bool_constant<
         (pqs::detail::compare_uuid<
            typename pqs::detail::shorten_uuid<TL>::type,
            typename pqs::detail::shorten_uuid<TR>::type
         >::type::value == 0)
      >{};

  }// impl
}

#endif // PQS_UUID_H_INCLUDEDPQS_UNIVERSALLY_UNIQUE_ID_HPP_INCLUDED
