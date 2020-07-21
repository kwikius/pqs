#ifndef PQS_TYPE_TEMPLATES_EXPONENT10_FWD_HPP_INCLUDED
#define PQS_TYPE_TEMPLATES_EXPONENT10_FWD_HPP_INCLUDED

#include <type_traits>
namespace pqs{

   template <int N, int D = 1> 
   struct exponent10;

   namespace impl{
         
     template <typename T>
     constexpr inline bool is_exponent10_impl = false;

     template <int N, int D > 
     constexpr inline bool is_exponent10_impl<pqs::exponent10<N,D> > = true;
      
   }

   template <typename T>
   inline constexpr bool is_exponent10 = impl::is_exponent10_impl<std::remove_cvref_t<T> >;
    
}
#endif // PQS_TYPE_TEMPLATES_EXPONENT10_FWD_HPP_INCLUDED
