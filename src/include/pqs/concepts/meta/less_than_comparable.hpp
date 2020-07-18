#ifndef PQS_CONCEPTS_META_LESS_THAN_COMPARABLE_HPP_INCLUDED
#define PQS_CONCEPTS_META_LESS_THAN_COMPARABLE_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/associated/binary_op.hpp>
#include <pqs/concepts/meta/bool_constant.hpp>

namespace pqs{ namespace meta{

   namespace impl {

      template <typename TL, typename TR, typename Where = void>
      struct are_less_than_comparable_impl : pqs::meta::is_bool_constant<
         pqs::binary_op<TL,pqs::less,TR>
      >{};

   }

   /**
   * @brief Are 2 meta types less than comparable at compile time?
   *
   * The notion is false by default so needs implementation
   * for a pair of types.
   * The pqs compile time op is achieved by defining a specialisation of
   * pqs::meta::impl::binary_op_impl<TL,less,TR>
   * which rhas a true false value for those types you want to
   * model.
   */
   template <typename TL,typename TR>
   concept less_than_comparable = impl::are_less_than_comparable_impl<
      std::remove_cvref_t<TL>,
      std::remove_cvref_t<TR>
   >::value;

}}


#endif // PQS_CONCEPTS_META_LESS_THAN_COMPARABLE_HPP_INCLUDED
