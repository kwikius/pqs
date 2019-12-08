#ifndef PQS_META_RATIO_EXP_DEF_HPP_INCLUDED
#define PQS_META_RATIO_EXP_DEF_HPP_INCLUDED

#include <ratio>
#include <type_traits>

namespace pqs{ namespace meta{

   template <typename T> struct is_ratio_exp : std::false_type{};

   template < typename Ratio, int64_t Exp>
   struct ratio_exp{
       typedef Ratio ratio;
       static constexpr int64_t exp = Exp;
       typedef ratio_exp type;
   };

   template < int64_t Rn, int64_t Rd, int64_t Exp>
   struct is_ratio_exp<ratio_exp<std::ratio<Rn,Rd>,Exp> > : std::true_type{};

}}

#endif // PQS_META_RATIO_EXP_DEF_HPP_INCLUDED
