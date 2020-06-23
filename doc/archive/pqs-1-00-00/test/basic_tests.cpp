// physical_quantities pqs-1-00-00 03:50 29/11/2003
//basic_tests.cpp
// feedback to andy@servocomm.freeserve.co.uk
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

// basic tests

#include "tests.hpp"

int Constructors()
{
    using namespace physical_quantities;

    q_pressure::Pa                  p1;
    if (!(!p1)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    q_pressure::MPa                 p2(1);
    if (!p2) return PHYSICAL_QUANTITIES_TEST_FAIL;
    q_pressure::Pa                  p3(p1);
    if (!(!p3)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    q_pressure::Pa                  p4 = p1;
    if (!(!p4)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    q_pressure::Pa                  p4a = p2;
    if (!p4a) return PHYSICAL_QUANTITIES_TEST_FAIL;
    q_pressure::mbar                p5(p1);
    if (!(!p5)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    q_pressure::psi                 p6 = p1;
    if (!(!p6)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    q_pressure::psi                 p6a = p2;
    if (!p6a) return PHYSICAL_QUANTITIES_TEST_FAIL;

    pq_pressure<bool>::Pa           p7(true);
    pq_pressure<char>::Pa           p8 = p7;
    pq_pressure<int>::Pa            p9 = p8;
    pq_pressure<long>::Pa           p10 = p9;
    pq_pressure<float>::Pa          p11(1);
    pq_pressure<double>::Pa         p12 = p11;
    pq_pressure<long double>::Pa    p13 = p12;

    return PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclareBaseVariables()
{
    if (DeclareLengths() != PHYSICAL_QUANTITIES_TEST_SUCCESS) {
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclareTimes()  != PHYSICAL_QUANTITIES_TEST_SUCCESS){
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclareMasses()  != PHYSICAL_QUANTITIES_TEST_SUCCESS){
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclareTemperatures()!= PHYSICAL_QUANTITIES_TEST_SUCCESS){
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclareCurrents() != PHYSICAL_QUANTITIES_TEST_SUCCESS){
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    
    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclareLengths()
{
    using namespace physical_quantities;

    q_length::nm           nm(1);
    q_length::um           um(1);
    q_length::mm           mm(1);
    q_length::cm           cm(1);
    q_length::in           in(1);
    q_length::dm           dm(1);

    q_length::ft           ft(1);
    q_length::yd           yd(1);
    q_length::m            m(1);
    q_length::km           km(1);
    q_length::mi           mi(1);
    q_length::AU           AU(1);
    q_length::l_y_         l_y_(1);
    q_length::pc           pc(1);
    
    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}
int DeclareTimes()
{
    using namespace physical_quantities;

    q_time::ps               ps(1);
    q_time::ns               ns(1);
    q_time::us               us(1);
    q_time::ms               ms(1);
    q_time::s                s(1);
    q_time::min              min(1);
    q_time::h                h(1);
    q_time::d                d(1);
    q_time::weeks            weeks(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}
int DeclareMasses()
{
    using namespace physical_quantities;

    q_mass::ug       ug(1);
    q_mass::mg       mg(1);
    q_mass::g         g(1);
    q_mass::oz       oz(1);
    q_mass::lb       lb(1);
    q_mass::kg       kg(1);
    q_mass::t        t(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}
int DeclareTemperatures()
{
    using namespace physical_quantities;

    q_temperature::K   K(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}
int DeclareCurrents()
{
    using namespace physical_quantities;

    q_current::pA        pA(1);
    q_current::nA        nA(1);
    q_current::uA        uA(1);
    q_current::mA        mA(1);
    q_current::A         A(1);
    q_current::abampere  abampere(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}
int DeclareSubstance()
{
    using namespace physical_quantities;

    q_substance::mol mol(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclareIntensity()
{
    using namespace physical_quantities;

    q_intensity::cd cd(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclareMechanicsVariables()
{
    if (DeclareAreas() != PHYSICAL_QUANTITIES_TEST_SUCCESS) {
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclareVolumes() != PHYSICAL_QUANTITIES_TEST_SUCCESS) {
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclareFrequencies() != PHYSICAL_QUANTITIES_TEST_SUCCESS) {
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclareVelocities() != PHYSICAL_QUANTITIES_TEST_SUCCESS) {
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclareAccelerations() != PHYSICAL_QUANTITIES_TEST_SUCCESS) {
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclareForces() != PHYSICAL_QUANTITIES_TEST_SUCCESS) {
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclarePowers() != PHYSICAL_QUANTITIES_TEST_SUCCESS) {
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclareEnergies() != PHYSICAL_QUANTITIES_TEST_SUCCESS) {
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }
    if (DeclarePressures() != PHYSICAL_QUANTITIES_TEST_SUCCESS) {
        return PHYSICAL_QUANTITIES_TEST_FAIL;
    }

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclareAreas()
{
    using namespace physical_quantities;

    q_area::um2    um2(1);
    q_area::mm2    mm2(1);
    q_area::cm2    cm2(1);
    q_area::in2    in2(1);
    q_area::ft2    ft2(1);
    q_area::yd2    yd2(1);
    q_area::m2     m2(1);
    q_area::km2    km2(1);
    q_area::mi2    mi2(1);
    q_area::AU2    AU2(1);
    q_area::l_y_2  l_y_2(1);
    q_area::pc2    pc2(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclareVolumes()
{
    using namespace physical_quantities;

    q_volume::um3        um3(1);
    q_volume::mm3        mm3(1);
    q_volume::cm3        cm3(1);
    q_volume::in3        in3(1);
    q_volume::L          L(1);
    q_volume::us_gallon  us_gallon(1);
    q_volume::imp_gallon imp_gallon(1);
    q_volume::ft3        ft3(1);
    q_volume::yd3        yd3(1);
    q_volume::m3         m3(1);
    q_volume::km3        km3(1);
    q_volume::mi3        mi3(1);
    q_volume::AU3        AU3(1);
    q_volume::l_y_3      l_y_3(1);
    q_volume::pc3        pc3(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclareFrequencies()
{
    using namespace physical_quantities;

    q_frequency::THz    THz(1);
    q_frequency::GHz    GHz(1);
    q_frequency::MHz    MHz(1);
    q_frequency::kHz    kHz(1);
    q_frequency::Hz     Hz(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}
int DeclareVelocities()
{
    using namespace physical_quantities;

    q_velocity::mm_div_s    mm_div_s(1);
    q_velocity::ft_div_s    ft_div_s(1);
    q_velocity::km_div_h    km_div_h(1);
    q_velocity::mi_div_h    mi_div_h(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclareAccelerations()
{
    using namespace physical_quantities;

    q_acceleration::ft_div_s2   ft_div_s2(1);
    q_acceleration::m_div_s2    m_div_s2(1);
    q_acceleration::km_div_s2   km_div_s2(1);
    q_acceleration::mi_div_s2   mi_div_s2(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclareForces()
{
     using namespace physical_quantities;

     q_force::dyn   dyn(1);
     q_force::N     N(1);
     q_force::lbf   lbf(1);
     q_force::kgf   kgf(1);
     q_force::kN    kN(1);

     return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclarePowers()
{
    using namespace physical_quantities;

    q_power::erg_div_s  erg_div_s(1);
    q_power::W          W(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclareEnergies()
{
    using namespace physical_quantities;

    q_energy::J       J(1);
    
    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int DeclarePressures()
{
    using namespace physical_quantities;

    q_pressure::Pa      Pa(1);
    q_pressure::kPa     kPa(1);
    q_pressure::MPa     MPa(1);
    q_pressure::mbar    mbar(1);
    q_pressure::psi     psi(1);

    return  PHYSICAL_QUANTITIES_TEST_SUCCESS;
}


int CompareVariablesDifferentUnits()
{
    using namespace physical_quantities;
    q_force::N f1(1);
    q_force::kgf f2(f1);

    if (f2 > f1) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if (f1 > f2) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f2>=f1)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f1>=f2)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f1<=f2)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f2<=f1)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if( f1!=f2 ) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if( f2!=f1 ) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f2==f1))return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f1==f2))return PHYSICAL_QUANTITIES_TEST_FAIL;

   return PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

int CompareVariablesSameUnits()
{
    using namespace physical_quantities;
    
    q_force::N f1(1);
    q_force::N f2(f1);

    
    if (f2 > f1) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if (f1 > f2) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f2>=f1)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f1>=f2)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f1<=f2)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f2<=f1)) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if( f1!=f2 ) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if( f2!=f1 ) return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f2==f1))return PHYSICAL_QUANTITIES_TEST_FAIL;
    if(!(f1==f2))return PHYSICAL_QUANTITIES_TEST_FAIL;

    return PHYSICAL_QUANTITIES_TEST_SUCCESS;
}
int AddSubVariablesDifferentUnits()
{
   using namespace physical_quantities;

    q_velocity::m_div_s     v1(1);
    q_velocity::mi_div_h    v2(2);
    q_velocity::ft_div_s    v3;

    v2 = v1;
    v3 += v2;
    v3 -= v2;
   
    v3 = v1 + v2;
    v3 = v2 + v1;
    v3 = v1 - v2;
    v3 = v2 - v1;

    return PHYSICAL_QUANTITIES_TEST_SUCCESS;
 }

int AddSubVariablesSameUnits()
{
   using namespace physical_quantities;

    q_velocity::mi_div_h    v1(1);
    q_velocity::mi_div_h    v2(2);
    q_velocity::mi_div_h    v3;

    + v1;
    - v2;
    v2 = v1;
    v3 += v2;
    v3 -= v2;
   
    v3 = v1 + v2;
    v3 = v2 + v1;
    v3 = v1 - v2;
    v3 = v2 - v1;

    return PHYSICAL_QUANTITIES_TEST_SUCCESS;
 }

int MulVariablesDifferentUnits()
{
   using namespace physical_quantities;

   q_length::ft             L(1);
   q_velocity::m_div_s      V(1); 
   q_time::min              T(1);
   float                    val = 10;
    L *= val;
    V /= val;
    L * val;
    val *  L;
    V  *  10;
    10 *  V;
    T  / 10;
    10 / T;
    L= V * T;
    L / V;
    val / T;
    
    return PHYSICAL_QUANTITIES_TEST_SUCCESS;
 }

int MulVariablesSameUnits()
{
  using namespace physical_quantities;

   q_length::m             L(1);
   q_velocity::m_div_s      V(1); 
   q_time::s             T(1);
   float                    val = 10;
    L *= val;
    V /= val;
    L * val;
    val * L;
    val / T;
    V  * 10;
    10 * V;
    T  / 10;
    10 / T;
    L = V * T;
    L / V;
    
    return PHYSICAL_QUANTITIES_TEST_SUCCESS;
 }

int PowerRoot()
{
    using namespace physical_quantities;

    q_length::mm   L1;
    q_volume::mm3  vol1 = power<3>(L1);
    L1 = root<3>(vol1);

    return PHYSICAL_QUANTITIES_TEST_SUCCESS;
}

    
