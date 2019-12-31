

#include <pqs/bits/scaled_value.hpp>
#include <iostream>

#if defined PQS_STANDALONE
int main()
#else
void sandbox()
#endif
{
  try{
      typedef pqs::conversion_factor<std::ratio<1>,std::ratio<0> > cf_from;  
      typedef pqs::conversion_factor<std::ratio<1,7>,std::ratio<0> > cf_to;

      constexpr pqs::scaled_value<double,cf_from> sv{30.0};

      pqs::scaled_value<int8_t,cf_to> sv2{sv, pqs::saturating_conversion{}};

      std::cout << static_cast<int>(sv2.numeric_value()) <<'\n';
   }catch(std::exception & e){
      std::cout << "exception \"" << e.what() << "\"\n";
   }

}