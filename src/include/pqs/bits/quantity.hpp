#ifndef PQS_QUANTITY_HPP_INCLUDED
#define PQS_QUANTITY_HPP_INCLUDED

namespace pqs{

   template <typename U, typename V = double>
   struct quantity{
      constexpr explicit quantity(V const & v) : m_numeric_value{v}{}
      constexpr explicit quantity() : m_numeric_value{V{0}}{}

      constexpr V numeric_value() const { return m_numeric_value; }

      private:
        V m_numeric_value;
   };

}

#endif // PQS_QUANTITY_FWD_HPP_INCLUDED
