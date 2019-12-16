#ifndef PQS_META_DETAIL_YES_NO_TYPE_HPP_INCLUDED
#define PQS_META_DETAIL_YES_NO_TYPE_HPP_INCLUDED
#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

namespace pqs{ namespace meta{ namespace detail{

      struct yes_type{};

      struct no_type{
         char array [2 * sizeof(yes_type)];
      };
}}}

#endif


