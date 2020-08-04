/*
 Copyright (c) 2003-2019 Andy Little.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see http://www.gnu.org/licenses./
*/

#include <iostream>

#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/time.hpp>
#include <pqs/systems/si/area.hpp>
#include <pqs/systems/si/volume.hpp>

using namespace pqs::si;
using namespace pqs::si::literals;

void simple_quantities()
{
  using distance = length::m<>;
  using q_time = time::s<>;

  constexpr distance km = 1.0q_km;
  constexpr distance miles = 1.0q_mi;

  constexpr q_time sec = 1.0q_s;
  constexpr q_time min = 1.0q_min;
  constexpr q_time hr = 1.0q_hr;

  std::cout << "A physical quantities library can choose the simple\n";
  std::cout << "option to provide output using a single type for each base unit:\n\n";
  std::cout << km << '\n';
  std::cout << miles << '\n';
  std::cout << sec << '\n';
  std::cout << min << '\n';
  std::cout << hr << "\n\n";
}

void quantities_with_typed_units()
{
  constexpr length::km<> km = 1.0q_km;
  constexpr length::mi<> miles = 1.0q_mi;

  constexpr time::s<> sec = 1q_s;
  constexpr time::min<> min = 1q_min;
  constexpr time::hr<> hr = 1q_hr;

  std::cout << "A more flexible option is to provide separate types for each unit,\n\n";
  std::cout << km << '\n';
  std::cout << miles << '\n';
  std::cout << sec << '\n';
  std::cout << min << '\n';
  std::cout << hr << "\n\n";

  constexpr length::m<> meter = 1q_m;
  std::cout << "then a wide range of pre-defined units can be defined and converted,\n"
               " for consistency and repeatability across applications:\n\n";

  std::cout << meter << '\n';

  std::cout << " = " << length::AU<>(meter) << '\n';
  std::cout << " = " << length::angstrom<>(meter) << '\n';
  std::cout << " = " << length::ch<>(meter) << '\n';
  std::cout << " = " << length::fathom<>(meter) << '\n';
  std::cout << " = " << length::fathom_us<>(meter) << '\n';
  std::cout << " = " << length::ft<>(meter) << '\n';
  std::cout << " = " << length::ft_us<>(meter) << '\n';
  std::cout << " = " << length::in<>(meter) << '\n';
  std::cout << " = " << length::l_y<>(meter) << '\n';
  std::cout << " = " << length::mi<>(meter) << '\n';
  std::cout << " = " << length::mi_naut<>(meter) << '\n';
  std::cout << " = " << length::pc<>(meter) << '\n';
  std::cout << " = " << length::pica_comp<>(meter) << '\n';
  std::cout << " = " << length::pica_prn<>(meter) << '\n';
  std::cout << " = " << length::point_comp<>(meter) << '\n';
  std::cout << " = " << length::point_prn<>(meter) << '\n';
  std::cout << " = " << length::rd<>(meter) << '\n';
  std::cout << " = " << length::yd<>(meter) << '\n';
}

void calcs_comparison()
{
  std::cout << "\nA distinct unit for each type is efficient and accurate\n"
               "when adding two values of the same very big\n"
               "or very small type:\n\n";

  length::fm<float> L1A = explicit_cast<float>(2.q_fm);
  length::fm<float> L2A = explicit_cast<float>(3.q_fm);
  length::fm<float> LrA = explicit_cast<float>(L1A + L2A);
  
  std::cout.precision(20);
  std::cout << L1A << " + " << L2A  << " = " << LrA <<'\n';
 // fmt::print("{:%.30Q %q}\n + {:%.30Q %q}\n   = {:%.30Q %q}\n\n",L1A,L2A,LrA);

  std::cout << "The single unit method must convert large\n"
               "or small values in other units to the base unit.\n"
               "This is both inefficient and inaccurate\n\n";

  length::m<float> L1B = L1A;
  length::m<float> L2B = L2A;
  length::m<float> LrB = L1B + L2B;
   
  std::cout << L1B << " + " << L2B  << " = " << LrB <<'\n';
 // fmt::print("{:%.30Q %q}\n + {:%.30Q %q}\n   = {:%.30Q %q}\n\n",L1B,L2B,LrB);

  std::cout << "In multiplication and division:\n\n";

  area::fm2<float> ArA = L1A * L2A;
   
  std::cout << L1A << " + " << L2A  << " = " << ArA <<'\n';
 // fmt::print("{:%.30Q %q}\n * {:%.30Q %q}\n   = {:%.30Q %q}\n\n",L1A,L2A,ArA);

  std::cout << "similar problems arise\n\n";

  area::m2<float> ArB = L1B * L2B;

  std::cout << L1B << " * " << L2B  << " = " << ArB <<'\n';
  //fmt::print("{:%.30Q %q}\n * {:%.30Q %q}\n   = {:%.30Q %q}\n\n",L1B,L2B,ArB);
}

int main()
{
  std::cout << "This demo was originally posted on comp.lang.c++.moderated in 2006\n";
  std::cout << "http://compgroups.net/comp.lang.c++.moderated/dimensional-analysis-units/51712\n";

  simple_quantities();
  quantities_with_typed_units();
  calcs_comparison();
}
