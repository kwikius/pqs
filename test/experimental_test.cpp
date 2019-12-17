

#include <type_traits>
#include <pqs/bits/dimension.hpp>
#include <pqs/exposition/base_quantity_exp.hpp>
#include <pqs/bits/binary_op.hpp>
#include <pqs/meta/join_list.hpp>

#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/base_quantity/mass.hpp>

namespace pqs{ namespace meta{

   template <typename T, typename OutList>
   struct append_if_not_zero : eval_if<
      base_quantity_exp_is_zero<T>,
      OutList,
      push_front<OutList,T>
   >{};

   template <typename Lhs, typename Rhs, typename Out>
   struct merge_dim;
  
   template <typename Lhs, typename Rhs, typename Out>
   struct merge_dim_left{
      typedef typename front<Lhs>::type lhs_front;
      typedef typename pop_front<Lhs>::type next_lhs;
      typedef typename append_if_not_zero<lhs_front,Out>::type next_list;
      typedef typename merge_dim<next_lhs,Rhs,next_list>::type type;
   };

   template <typename Lhs, typename Rhs, typename Out>
   struct merge_dim_right{
      typedef typename front<Rhs>::type rhs_front;
      typedef typename pop_front<Rhs>::type next_rhs;
      typedef typename append_if_not_zero<rhs_front,Out>::type next_list;
      typedef typename merge_dim<Lhs,next_rhs,next_list>::type type;
   };

   template <typename Lhs, typename Rhs, typename Out>
   struct merge_dim_both{
      typedef typename front<Lhs>::type lhs_front;
      typedef typename front<Rhs>::type rhs_front;
      typedef typename pop_front<Lhs>::type next_lhs;
      typedef typename pop_front<Rhs>::type next_rhs;
      typedef typename pqs::binary_op<lhs_front,pqs::plus,rhs_front>::type plus_front;
      
      typedef typename append_if_not_zero<plus_front,Out>::type next_list;
      typedef typename merge_dim<next_lhs,next_rhs,next_list>::type type;
   };
  
   template <typename Lhs, typename Rhs, typename Out>
   struct merge_dim{
      typedef typename front<Lhs>::type lhs_front;
      typedef typename front<Rhs>::type rhs_front;
      typedef typename pqs::get_base_quantity<lhs_front>::type lhs_base;
      typedef typename pqs::get_base_quantity<rhs_front>::type rhs_base;
      typedef typename eval_if<
         pqs::binary_op<lhs_base,pqs::less,rhs_base>,
           merge_dim_left<Lhs,Rhs,Out>,
         pqs::binary_op<rhs_base,pqs::less,lhs_base>,
           merge_dim_right<Lhs,Rhs,Out>,
         merge_dim_both<Lhs,Rhs,Out>
     >::type type;
   
   };
 

   template <typename Lhs, typename Out>
   struct merge_dim<Lhs,pqs::meta::type_list<>,Out>{
      typedef typename front<Lhs>::type lhs_front;
      typedef typename merge_dim<
         typename pop_front<Lhs>::type ,
         pqs::meta::type_list<>, 
         typename append_if_not_zero<lhs_front,Out>::type
      >::type type;
   };

   template <typename Rhs, typename Out>
   struct merge_dim<pqs::meta::type_list<>,Rhs,Out>{
     typedef typename front<Rhs>::type rhs_front;
      typedef typename merge_dim<
         typename pop_front<Rhs>::type ,
         pqs::meta::type_list<>, 
         typename append_if_not_zero<rhs_front,Out>::type
      >::type type;
   };

   template <typename Out>
   struct merge_dim<pqs::meta::type_list<>,pqs::meta::type_list<>,Out>{
      typedef Out type;
   };

}} // pqs::meta

using pqs::dimension;
using pqs_exposition::exp;
using pqs::base_time;
void  experimental_test()
{
    typedef pqs::meta::type_list<exp<base_time,1> > dim;

//    typedef pqs::binary_op<exp<base_time,1>,pqs::plus,exp<base_time,1> >::type add;
//    typedef pqs::binary_op<exp<base_time,1>,pqs::less,exp<base_time,1> >::type cond;
//
//     static_assert(!std::is_same<cond,pqs::undefined>::value,"aha");
     typedef pqs::meta::merge_dim<dim,dim,dimension<> >::type type1;

   // int x = cond{};
   
}