#ifndef PQS_META_MERGE_DIM_HPP_INCLUDED
#define PQS_META_MERGE_DIM_HPP_INCLUDED

#include <type_traits>
#include <pqs/concepts/meta/type_list.hpp>
#include <pqs/concepts/base_quantity_exp.hpp>
#include <pqs/meta/merge_sort.hpp>

namespace pqs{

   template <base_quantity_exponent ...D>
   struct dimension_list ;

}

namespace pqs{ namespace meta{

   namespace detail{

      template <typename T, typename DimOut>
      struct append_if_not_zero : eval_if<
         base_quantity_exp_is_zero_legacy<T>,
         DimOut,
         push_back<DimOut,T>
      >{};

      template <typename DimL, typename Op, typename DimR, typename DimOut>
      struct merge_dim;
     
      template <typename DimL, typename Op,typename DimR, typename DimOut>
      struct merge_dim_left : merge_dim<
         typename pop_front<DimL>::type,
         Op,
         DimR,
         typename append_if_not_zero<
            typename front<DimL>::type,
            DimOut
         >::type
      >{};

      template <typename DimL, typename Op, typename DimR, typename DimOut>
      struct merge_dim_right;

      template <typename DimL, typename DimR, typename DimOut>
      struct merge_dim_right<DimL,pqs::times,DimR,DimOut> : merge_dim<
         DimL,
         pqs::times,
         typename pop_front<DimR>::type,
         typename append_if_not_zero<
            typename front<DimR>::type,
            DimOut
         >::type
      >{};

      template <typename DimL, typename DimR, typename DimOut>
      struct merge_dim_right<DimL,pqs::divides,DimR,DimOut> : merge_dim<
         DimL,
         pqs::divides,
         typename pop_front<DimR>::type,
         typename append_if_not_zero<
            typename pqs::unary_op<reciprocal, typename front<DimR>::type >::type,
            DimOut
         >::type
      >{};

      template <typename DimL, typename Op, typename DimR, typename DimOut>
      struct merge_dim_both : merge_dim<
         typename pop_front<DimL>::type,
         Op,
         typename pop_front<DimR>::type,
         typename append_if_not_zero<
            typename pqs::binary_op<
               typename front<DimL>::type,
               Op,
               typename front<DimR>::type
            >::type,
            DimOut
         >::type
      >{};
     
      template <typename DimL, typename Op, typename DimR, typename DimOut>
      struct merge_dim{
         typedef typename front<DimL>::type lhs_front;
         typedef typename front<DimR>::type rhs_front;
         typedef typename pqs::get_base_quantity_legacy<lhs_front>::type lhs_base;
         typedef typename pqs::get_base_quantity_legacy<rhs_front>::type rhs_base;
         typedef typename eval_if<
            pqs::binary_op<lhs_base,pqs::less,rhs_base>,
               merge_dim_left<DimL,Op,DimR,DimOut>,
            pqs::binary_op<rhs_base,pqs::less,lhs_base>,
               merge_dim_right<DimL,Op,DimR,DimOut>,
            merge_dim_both<DimL,Op,DimR,DimOut>
        >::type type;
      };
    
      template <typename DimL, typename Op, typename DimOut>
      struct merge_dim<DimL,Op,pqs::dimension_list<>,DimOut> : merge_dim<
         typename pop_front<DimL>::type ,
         Op,
         pqs::dimension_list<>, 
         typename append_if_not_zero<
            typename front<DimL>::type,DimOut
         >::type
      >{};

      template <typename DimR,typename Op, typename DimOut>
      struct merge_dim<pqs::dimension_list<>,Op,DimR,DimOut> : merge_dim<
         pqs::dimension_list<>,
         Op,
         typename pop_front<DimR>::type ,
         typename append_if_not_zero<
            typename pqs::meta::eval_if<
               std::is_same<Op,pqs::divides>,
                  pqs::unary_op<reciprocal,typename front<DimR>::type>,
               front<DimR>
            >::type,
           DimOut
         >::type
      >{};

      template <typename Op,typename DimOut>
      struct merge_dim<pqs::dimension_list<>,Op, pqs::dimension_list<>,DimOut>{
         typedef DimOut type;
      };

      struct base_quantity_exp_sort_fun{
    
         template <typename LhsExp, typename RhsExp>
         struct apply : pqs::binary_op<
            typename pqs::get_base_quantity_legacy<LhsExp>::type,
            pqs::less,
            typename pqs::get_base_quantity_legacy<RhsExp>::type
         >{};
      };

   }// detail

    // Op is pqs::times or pqs::divides 
   template <typename DimL, typename Op, typename DimR>
   struct merge_dim : pqs::meta::detail::merge_dim<
      typename pqs::meta::merge_sort<
         DimL,pqs::meta::detail::base_quantity_exp_sort_fun
      >::type,
      Op,
      typename pqs::meta::merge_sort<
         DimR,pqs::meta::detail::base_quantity_exp_sort_fun
      >::type, 
      pqs::dimension_list<> 
   >{};
   
}} // pqs::meta

#endif // PQS_META_MERGE_DIM_HPP_INCLUDED
