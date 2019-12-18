

#include <type_traits>
#include <pqs/bits/dimension.hpp>
#include <pqs/exposition/base_quantity_exp.hpp>
#include <pqs/bits/binary_op.hpp>
//#include <pqs/meta/join_list.hpp>
#include <pqs/meta/merge_sort.hpp>

#include <pqs/base_quantity/length.hpp>
#include <pqs/base_quantity/time.hpp>
#include <pqs/base_quantity/mass.hpp>


namespace pqs{ namespace meta{

   namespace detail{

      template <typename T, typename ListOut>
      struct append_if_not_zero : eval_if<
         base_quantity_exp_is_zero<T>,
         ListOut,
         push_back<ListOut,T>
      >{};

      template <typename ListL, typename Op, typename ListR, typename ListOut>
      struct merge_dim;
     
      template <typename ListL, typename Op,typename ListR, typename ListOut>
      struct merge_dim_left : merge_dim<
         typename pop_front<ListL>::type,
         Op,
         ListR,
         typename append_if_not_zero<
            typename front<ListL>::type,
            ListOut
         >::type
      >{};

      template <typename ListL,typename Op, typename ListR, typename ListOut>
      struct merge_dim_right : merge_dim<
         ListL,
         Op,
         typename pop_front<ListR>::type,
         typename append_if_not_zero<
            typename front<ListR>::type,
            ListOut
         >::type
      >{};

      template <typename ListL, typename Op, typename ListR, typename ListOut>
      struct merge_dim_both : merge_dim<
         typename pop_front<ListL>::type,
         Op,
         typename pop_front<ListR>::type,
         typename append_if_not_zero<
            typename pqs::binary_op<
               typename front<ListL>::type,
               Op,
               typename front<ListR>::type
            >::type,
            ListOut
         >::type
      >{};
     
      template <typename ListL, typename Op, typename ListR, typename ListOut>
      struct merge_dim{
         typedef typename front<ListL>::type lhs_front;
         typedef typename front<ListR>::type rhs_front;
         typedef typename pqs::get_base_quantity<lhs_front>::type lhs_base;
         typedef typename pqs::get_base_quantity<rhs_front>::type rhs_base;
         typedef typename eval_if<
            pqs::binary_op<lhs_base,pqs::less,rhs_base>,
               merge_dim_left<ListL,Op,ListR,ListOut>,
            pqs::binary_op<rhs_base,pqs::less,lhs_base>,
               merge_dim_right<ListL,Op,ListR,ListOut>,
            merge_dim_both<ListL,Op,ListR,ListOut>
        >::type type;
      };
    
      template <typename ListL, typename Op, typename ListOut>
      struct merge_dim<ListL,Op,pqs::meta::type_list<>,ListOut> : merge_dim<
         typename pop_front<ListL>::type ,
         Op,
         pqs::meta::type_list<>, 
         typename append_if_not_zero<
            typename front<ListL>::type,ListOut
         >::type
      >{};

      template <typename Op,typename ListR, typename ListOut>
      struct merge_dim<pqs::meta::type_list<>,Op,ListR,ListOut> : merge_dim<
         typename pop_front<ListR>::type ,
         Op,
         pqs::meta::type_list<>, 
         typename append_if_not_zero<
            typename front<ListR>::type,ListOut
         >::type
      >{};

      template <typename Op,typename ListOut>
      struct merge_dim<pqs::meta::type_list<>,Op, pqs::meta::type_list<>,ListOut>{
         typedef ListOut type;
      };

      struct sort_fun{
    
         template <typename LhsExp, typename RhsExp>
         struct apply : pqs::binary_op<
            typename pqs::get_base_quantity<LhsExp>::type,
            pqs::less,
            typename pqs::get_base_quantity<RhsExp>::type
          >{};
      };

   }// detail

    // Op is pqs::plus or pqs::minus 
   template <typename ListL, typename Op, typename ListR, typename ListOut>
   struct merge_dim{
      typedef typename pqs::meta::merge_sort<ListL,pqs::meta::detail::sort_fun>::type lhs_list;
      typedef typename pqs::meta::merge_sort<ListR,pqs::meta::detail::sort_fun>::type rhs_list;
      typedef typename pqs::meta::detail::merge_dim<lhs_list,Op,rhs_list,ListOut>::type type;
   };
   
}} // pqs::meta

using pqs::dimension;
using pqs_exposition::exp;
using pqs::base_length;
using pqs::base_time;
using pqs::base_mass;
using pqs::meta::type_list;
using pqs::meta::merge_dim;

void  experimental_test()
{
   // n.b must be sorted
   typedef type_list<exp<base_time,1> > dim1;
   typedef merge_dim<dim1,pqs::plus,dim1,type_list<> >::type result1;
   typedef type_list<exp<base_time,2> > expected1;
   static_assert(std::is_same<result1,expected1>::value,"");

   typedef type_list<exp<base_length,-2>, exp<base_time,2> >  dim2;
   typedef merge_dim<dim1,pqs::plus,dim2,type_list<> >::type result2;
   typedef type_list<exp<base_length,-2>, exp<base_time,3> > expected2;
   static_assert(std::is_same<result2,expected2 >::value,"");

   typedef type_list<exp<base_length,-1>, exp<base_time,1>, exp<base_mass,2> >  dim3;
   typedef merge_dim<dim2,pqs::plus,dim3,type_list<> >::type result3;
   typedef type_list<exp<base_length,-3>, exp<base_mass,2>, exp<base_time,3>  > expected3;
   static_assert(std::is_same<result3,expected3>::value,"");

   typedef type_list<exp<base_length,1>, exp<base_time,1>, exp<base_mass,2> >  dim4;
   typedef merge_dim<dim3,pqs::plus,dim4,type_list<> >::type result4;
   typedef type_list<exp<base_mass,4>,exp<base_time,2> > expected4;
   static_assert(std::is_same<result4,expected4>::value,"");

   typedef type_list<exp<base_length,-1>, exp<base_time,-1>, exp<base_mass,-2> >  dim5;
   typedef merge_dim<dim4,pqs::plus,dim5,type_list<> >::type result5;
   typedef type_list<> expected5;
   static_assert(std::is_same<result5,expected5>::value,"");

}



