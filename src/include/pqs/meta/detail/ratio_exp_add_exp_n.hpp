#ifndef PQS_META_RATIO_EXP_ADD_EXP_N_HPP_INCLUDED
#define PQS_META_RATIO_EXP_ADD_EXP_N_HPP_INCLUDED

#include <pqs/meta/ratio_exp_def.hpp>
#include <pqs/meta/eval_if.hpp>

namespace pqs{ namespace meta{ namespace detail{


    // ratio_exp::exp -> ratio_exp::exp + n
    template <typename RatioExp, int64_t N>
    struct ratio_exp_add_exp_n{

        typedef typename pqs::meta::eval_if_c<
           N > 0  // ratio/ 10 , exp +1
           ,ratio_exp<
              std::ratio_multiply<typename RatioExp::exp,std::ratio<10> >
              ,N-1
           >
           , N < 0
    };

}}}

#endif // PQS_META_RATIO_EXP_SHIFT_EXP_HPP_INCLUDED
