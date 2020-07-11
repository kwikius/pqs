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
      struct append_if_not_zero : eval_if_c<
         base_quantity_exp_is_zero<T>,
         DimOut,
         push_back<DimOut,T>
      >{};

      template <typename T, typename DimOut>
      using append_if_not_zero_t = 
         typename append_if_not_zero<T,DimOut>::type;

      template <typename DimL, typename Op, typename DimR, typename DimOut>
      struct merge_dim;
     
      template <typename DimL, typename Op,typename DimR, typename DimOut>
      struct merge_dim_left : merge_dim<
         pop_front_t<DimL>,
         Op,
         DimR,
         append_if_not_zero_t<
            front_t<DimL>,
            DimOut
         >
      >{};

      template <typename DimL, typename Op, typename DimR, typename DimOut>
      struct merge_dim_right;

      template <typename DimL, typename DimR, typename DimOut>
      struct merge_dim_right<DimL,pqs::times,DimR,DimOut> : merge_dim<
         DimL,
         times,
         pop_front_t<DimR>,
         append_if_not_zero_t<
            front_t<DimR>,
            DimOut
         >
      >{};

      template <typename DimL, typename DimR, typename DimOut>
      struct merge_dim_right<DimL,divides,DimR,DimOut> : merge_dim<
         DimL,
         divides,
         pop_front_t<DimR>,
         append_if_not_zero_t<
            unary_op_t<reciprocal,front_t<DimR> >,
            DimOut
         >
      >{};

      template <typename DimL, typename Op, typename DimR, typename DimOut>
      struct merge_dim_both : merge_dim<
         pop_front_t<DimL>,
         Op,
         pop_front_t<DimR>,
         append_if_not_zero_t<
            binary_op_t<front_t<DimL>,Op,front_t<DimR> >,
            DimOut
         >
      >{};
     
      template <typename DimL, typename Op, typename DimR, typename DimOut>
      struct merge_dim{
         using lhs_front = front_t<DimL>;
         using rhs_front = front_t<DimR>;
         using lhs_base = get_base_quantity<lhs_front> ;
         using rhs_base = get_base_quantity<rhs_front> ;
         using type = eval_if_t<
            binary_op<lhs_base,less,rhs_base>,
               merge_dim_left<DimL,Op,DimR,DimOut>,
            binary_op<rhs_base,less,lhs_base>,
               merge_dim_right<DimL,Op,DimR,DimOut>,
            merge_dim_both<DimL,Op,DimR,DimOut>
         >;
      };
    
      template <typename DimL, typename Op, typename DimOut>
      struct merge_dim<DimL,Op,dimension_list<>,DimOut> : merge_dim<
         pop_front_t<DimL>,
         Op,
         dimension_list<>, 
         append_if_not_zero_t<
            front_t<DimL>,DimOut
         >
      >{};

      template <typename DimR,typename Op, typename DimOut>
      struct merge_dim<dimension_list<>,Op,DimR,DimOut> : merge_dim<
         dimension_list<>,
         Op,
         pop_front_t<DimR> ,
         append_if_not_zero_t<
            pqs::meta::eval_if_t<
               std::is_same<Op,pqs::divides>,
                  pqs::unary_op<reciprocal,front_t<DimR> >,
               front<DimR>
            >,
           DimOut
         >
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
