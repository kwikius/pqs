#ifndef PQS_CONCEPTS_QUANTITY_DEFINITION_HPP_INCLUDED
#define PQS_CONCEPTS_QUANTITY_DEFINITION_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/dimensionless_quantity.hpp>
#include <pqs/concepts/associated/get_unit.hpp>
#include <pqs/concepts/associated/get_dimension.hpp>
#include <pqs/concepts/associated/get_numeric_type.hpp>
#include <pqs/concepts/associated/get_conversion_factor.hpp>
#include <pqs/concepts/associated/get_measurement_system.hpp>

namespace pqs{

   namespace impl{

      template <typename T>
      inline constexpr bool is_quantity_impl = false;

   }// impl

   template <typename T>
   concept quantity = impl::is_quantity_impl< std::remove_cvref_t<T> >;

   namespace impl{

      template <quantity Q>
      struct get_dimension_impl<Q>
      : get_dimension<get_unit<Q> >{};

      template <quantity Q>
      struct get_conversion_factor_impl<Q>
      : get_conversion_factor<get_unit<Q> >{};

      template <quantity Q>
      struct get_measurement_system_impl<Q>
      : get_measurement_system<get_unit<Q> >{};

      template <quantity Q>
      struct get_simple_dimension_impl<Q>
      : get_simple_dimension<get_unit<Q> >{};

      template <typename Lhs, typename Rhs>
      struct provide_operator_plus_impl : std::true_type{};
      template <typename Lhs, typename Rhs>
      struct provide_operator_minus_impl : std::true_type{};
      template <typename Lhs, typename Rhs>
      struct provide_operator_times_impl :std::true_type{};
      template <typename Lhs, typename Rhs>
      struct provide_operator_divides_impl : std::true_type{};
      template <typename Lhs, typename Rhs>
      struct provide_operator_cmp_impl : std::true_type{};

      template <typename Q,int N,int D>
      struct provide_operator_pow_impl : std::true_type{};

    }

// TODO this should maybe test the semantic
    // e.g dimensionally_equivalent
    template <quantity Lhs, quantity Rhs>
    inline constexpr bool provide_operator_plus =
    impl::provide_operator_plus_impl<
       std::remove_cvref_t<Lhs>, std::remove_cvref_t<Rhs>
    >::value;

    template <quantity Lhs, quantity Rhs>
    inline constexpr bool provide_operator_minus =
    impl::provide_operator_minus_impl<
       std::remove_cvref_t<Lhs>, std::remove_cvref_t<Rhs>
    >::value;

    template <typename Lhs, typename Rhs>
    inline constexpr bool provide_operator_times =
    impl::provide_operator_times_impl<
       std::remove_cvref_t<Lhs>, std::remove_cvref_t<Rhs>
    >::value;

    template <typename Lhs, typename Rhs>
    inline constexpr bool provide_operator_divides =
    impl::provide_operator_divides_impl<
       std::remove_cvref_t<Lhs>, std::remove_cvref_t<Rhs>
    >::value;

    template <typename Lhs, typename Rhs>
    inline constexpr bool provide_operator_cmp =
    impl::provide_operator_cmp_impl<
       std::remove_cvref_t<Lhs>, std::remove_cvref_t<Rhs>
    >::value;

    template <quantity QL, quantity QR>
    inline constexpr bool same_measurement_system<QL,QR> =
      same_measurement_system<get_unit<QL>,get_unit<QR> >;

    template <quantity Qj,quantity Qk>
    inline constexpr bool dimensionally_equivalent<Qj,Qk> =
       dimensionally_equivalent<
          get_dimension<Qj>,
          get_dimension<Qk>
       >;

    template  <typename Q,int N,int D>
    inline constexpr bool provide_operator_pow =
    impl::provide_operator_pow_impl<
       std::remove_cvref_t<Q>,N,D
    >::value;

}// pqs

#endif // PQS_CONCEPTS_QUANTITY_HPP_INCLUDED
