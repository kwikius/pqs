#ifndef PQS_BASE_QUANTITIES_SUBSTANCE_HPP_INCLUDED
#define PQS_BASE_QUANTITIES_SUBSTANCE_HPP_INCLUDED

#include <type_traits>
#include <ratio>
#include <pqs/bits/base_quantity_of.hpp>
#include <pqs/types/base_quantity/uuids.hpp>
#include <pqs/concepts/associated/base_quantity_exponent_base_class.hpp>

namespace pqs{ 
   /**
    * @addtogroup base_quantity_model
    * @{ **/
   /**
    * @brief implement substance as a model of base_quantity
   */
    struct base_substance : pqs::impl::base_quantity_of<pqs::newtonian_universe::substance_uuid>{
       typedef base_substance type;
    };
    /** @} */

   template <int... N>
   struct exp_substance;

   template <int N, int D>
   struct exp_substance<N,D> : pqs::detail::base_quantity_exp_base_class {
      typedef base_substance  base_type;
      typedef typename std::ratio<N,D>::type exponent;
      typedef exp_substance type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_substance<N> : pqs::detail::base_quantity_exp_base_class {
      typedef base_substance  base_type;
      typedef typename std::ratio<N,1>::type exponent;
      typedef exp_substance type; // identity
      typedef type simple_dimension;
   };

   template <int N>
   struct exp_substance<N,1> : exp_substance<N>{};

   namespace impl{

      template <int N>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_substance<N>  > = true;

      template <int N,int D>
      constexpr inline bool is_base_quantity_exp_impl< pqs::exp_substance<N,D>  > = true;

      template <typename Ratio>
      struct make_base_quantity_exp_impl<pqs::newtonian_universe::substance_uuid,Ratio>
      : exp_substance<Ratio::type::num, Ratio::type::den>{};

   }// impl

   using abstract_substance_t = exp_substance<1>;

   inline constexpr auto abstract_substance_v = abstract_substance_t{};

}

#endif //PQS_BASE_QUANTITIES_SUBSTANCE_HPP_INCLUDED
