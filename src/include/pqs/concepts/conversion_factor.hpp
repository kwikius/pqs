#ifndef PQS_CONCEPTS_CONVERSION_FACTOR_HPP_INCLUDED
#define PQS_CONCEPTS_CONVERSION_FACTOR_HPP_INCLUDED

namespace pqs{

   namespace impl{

      template <typename T, typename Where = void> 
      struct is_conversion_factor_impl : std::false_type{};

   }

    template <typename T>
   struct is_conversion_factor : impl::is_conversion_factor_impl<T>{};

}

#endif // PQS_CONCEPTS_CONVERSION_FACTOR_HPP_INCLUDED
