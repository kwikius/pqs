#ifndef PQS_CONCEPTS_QUANTITY_COMPARE_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_COMPARE_HPP_INCLUDED

#include <pqs/concepts/associated/binary_op_semantic.hpp>
#include <pqs/concepts/quantity/definition.hpp>
#include <pqs/concepts/quantity/minus.hpp>

namespace pqs::impl{

   template < quantity Lhs, quantity Rhs> 
   struct binary_op_semantic< Lhs, less, Rhs>{

      static constexpr auto apply( Lhs const & lhs, Rhs const & rhs)
      {
         using numeric_type = get_numeric_type<decltype(lhs - rhs)>;
         return get_numeric_value(lhs - rhs) < numeric_type{0};
      }

   };

   template < quantity Lhs, quantity Rhs> 
   struct binary_op_semantic< Lhs, less_equal, Rhs>{
      static constexpr auto apply( Lhs const & lhs, Rhs const & rhs)
      {
         using numeric_type = get_numeric_type<decltype(lhs- rhs)>;
         return get_numeric_value(lhs - rhs) <= numeric_type{0};
      }
   };

   template < quantity Lhs, quantity Rhs> 
   struct binary_op_semantic< Lhs, equal_to, Rhs>{
      static constexpr auto apply( Lhs const & lhs, Rhs const & rhs)
      {
         using numeric_type = get_numeric_type<decltype(lhs - rhs)>;
         return get_numeric_value(lhs - rhs) == numeric_type{0};
      }
   };

   template < quantity Lhs, quantity Rhs> 
   struct binary_op_semantic< Lhs, not_equal_to, Rhs>{
      static constexpr auto apply( Lhs const & lhs, Rhs const & rhs)
      {
         using numeric_type = get_numeric_type<decltype(lhs - rhs)>;
         return get_numeric_value(lhs - rhs) != numeric_type{0};
      }
   };
   template < quantity Lhs, quantity Rhs> 
   struct binary_op_semantic< Lhs, greater_equal, Rhs>{
      static constexpr auto apply( Lhs const & lhs, Rhs const & rhs)
      {
         using numeric_type = get_numeric_type<decltype(lhs- rhs)>;
         return get_numeric_value(lhs - rhs) >= numeric_type{0};
      }
   };

   template < quantity Lhs, quantity Rhs> 
   struct binary_op_semantic< Lhs, greater, Rhs>{      
      static constexpr auto apply( Lhs const & lhs, Rhs const & rhs)
      {
         using numeric_type = get_numeric_type<decltype(lhs- rhs)>;
         return get_numeric_value(lhs - rhs) > numeric_type{0};
      }
   };

} // pqs::impl

namespace pqs{

   template <quantity Lhs, quantity Rhs>
      requires  
         same_measurement_system<Lhs,Rhs> &&
         dimensionally_equivalent<Lhs,Rhs> &&
         provide_operator_cmp<Lhs,Rhs>
   inline constexpr 
   bool operator<(Lhs const & lhs, Rhs const & rhs)
   {
      return impl::binary_op_semantic<Lhs,less,Rhs>::apply(lhs, rhs);
   }

   template <quantity Lhs, quantity Rhs>
      requires  
         same_measurement_system<Lhs,Rhs> &&
         dimensionally_equivalent<Lhs,Rhs> &&
         provide_operator_cmp<Lhs,Rhs>
   inline constexpr 
   bool operator<=(Lhs const & lhs, Rhs const & rhs)
   {
      return impl::binary_op_semantic<Lhs,less_equal,Rhs>::apply(lhs, rhs);
   }

   template <quantity Lhs, quantity Rhs>
      requires  
         same_measurement_system<Lhs,Rhs> &&
         dimensionally_equivalent<Lhs,Rhs> &&
         provide_operator_cmp<Lhs,Rhs>
   inline constexpr 
   bool operator==(Lhs const & lhs, Rhs const & rhs)
   {
      return impl::binary_op_semantic<Lhs,equal_to,Rhs>::apply(lhs, rhs);
   }

   template <quantity Lhs, quantity Rhs>
      requires  
         same_measurement_system<Lhs,Rhs> &&
         dimensionally_equivalent<Lhs,Rhs> &&
         provide_operator_cmp<Lhs,Rhs>
   inline constexpr 
   bool operator!=(Lhs const & lhs, Rhs const & rhs)
   {
      return impl::binary_op_semantic<Lhs,not_equal_to,Rhs>::apply(lhs, rhs);
   }

   template <quantity Lhs, quantity Rhs>
      requires  
         same_measurement_system<Lhs,Rhs> &&
         dimensionally_equivalent<Lhs,Rhs> &&
         provide_operator_cmp<Lhs,Rhs>
   inline constexpr 
   bool operator>=(Lhs const & lhs, Rhs const & rhs)
   {
      return impl::binary_op_semantic<Lhs,greater_equal,Rhs>::apply(lhs, rhs);
   }

   template <quantity Lhs, quantity Rhs>
      requires  
         same_measurement_system<Lhs,Rhs> &&
         dimensionally_equivalent<Lhs,Rhs> &&
         provide_operator_cmp<Lhs,Rhs>
   inline constexpr 
   bool operator>(Lhs const & lhs, Rhs const & rhs)
   {
      return impl::binary_op_semantic<Lhs,greater,Rhs>::apply(lhs, rhs);
   }

} //pqs

#endif // PQS_CONCEPTS_QUANTITY_COMPARE_HPP_INCLUDED
