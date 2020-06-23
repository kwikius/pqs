// physical_quantities pqs-1-00-00 03:50 29/11/2003
// feedback to andy@servocomm.freeserve.co.uk
//generic.hpp
//  Copyright (C) Andy Little, White Light Device 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

//definition of generic p_quantity

#ifndef PHYSICAL_QUANTITY_CLASS_TEMPLATE_GENERIC_CLASS_HPP_INCLUDED2911030401
#define PHYSICAL_QUANTITY_CLASS_TEMPLATE_GENERIC_CLASS_HPP_INCLUDED2911030401

#include <cmath>
#include "./interface/interface.hpp"
#include "dimless.hpp"
#include "./mpl_like/math_promote.hpp"
#include "units_out.hpp"
#include "concept_checking.hpp"

namespace physical_quantities{

    template
    <
        typename Abstract_pq,
        typename Value_type,
        typename Units,
        quantity_mx Q_mx
    >
    class p_quantity {
   
    public:
        typedef p_quantity
        <
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        > identity;

        p_quantity
        <
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        >():m_value(0){}

        // get at the raw value.!
        Value_type const& operator()()const{return m_value;}
        Value_type operator()(){return m_value;}

        //explicit ctor by scalar quantity
       // template<typename Value_type1>
        explicit p_quantity
        <
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        > (Value_type const& value_in)
        :m_value(value_in){}

        // copy ctor
        template <typename Value_type1>
        p_quantity<
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        > (p_quantity<
            Abstract_pq,
            Value_type1,
            Units,
            Q_mx
           > const& in)
            :m_value(in()){};
            
        // copy-unit convert ctor
        template
        <
            typename From_abstract_pq, //for D.A. checking
            typename Value_type1,
            typename Units1,
            quantity_mx Q_mx1
        >
#ifdef PHYSICAL_QUANTITIES_USE_EXPLICIT_CONVERSION_CTOR
        explicit 
#endif
        p_quantity
        <
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        >
        (p_quantity
        <
            From_abstract_pq,
            Value_type1,
            Units1,
            Q_mx1 
        > const& pq1)
        :m_value(scale_from
            <
                Value_type1,
                Units1,
                Q_mx1 
            >(pq1()))//possible Value_type conversion warning
        {

            //D.A.checking
            void (*pf)()
                = &DimensionallyEquivalentConcept
                <
                    Abstract_pq,
                    From_abstract_pq
                >;pf=pf;
#ifndef PHYSICAL_QUANTITIES_USE_EXPLICIT_CONVERSION_CTOR
#ifdef PHYSICAL_QUANTITIES_WARN_ON_UNIT_CONVERSIONS
             void (*pf1)() = 
                &UnitConversionWarningConcept
                <
                    Units,
                    Q_mx,
                    Units1,
                    Q_mx1
                >;pf1=pf1;
#endif
#endif
        }

        // = pq of same powers
        // may be different units and Value_type
        template
        <  
            typename From_abstract_pq,
            typename Value_type1,
            typename Units1,
            quantity_mx Q_mx1
        >
        p_quantity
        <
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        >&
            operator =
                (p_quantity
                <
                    From_abstract_pq,
                    Value_type1,
                    Units1,
                    Q_mx1
                 > const& pq1)
            {
                //D.A.checking
                void (*pf)()
                = &DimensionallyEquivalentConcept
                <
                    Abstract_pq,
                    From_abstract_pq
                >;pf=pf;
#ifdef PHYSICAL_QUANTITIES_WARN_ON_UNIT_CONVERSIONS
                void (*pf1)() = 
                    &UnitConversionWarningConcept
                    <
                        Units,
                        Q_mx,
                        Units1,
                        Q_mx1
                    >;pf1=pf1;
#endif
                m_value = scale_from
                            <
                                Value_type1,
                                Units1,
                                Q_mx1 
                            >(pq1()) ;
                return *this;
            }

       //unary + -
       p_quantity
        <
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        > operator +()
       {
           return p_quantity
                    <
                        Abstract_pq,
                        Value_type,
                        Units,
                        Q_mx
                    >(m_value);
       }

       p_quantity
        <
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        > operator -()
        {
            return p_quantity
                    <
                        Abstract_pq,
                        Value_type,
                        Units,
                        Q_mx
                    >(-m_value);
        }

        bool operator!()
        {
            return m_value == 0;
        }

        //+= same power diff units and Value_type
        template
        <
            typename From_abstract_pq,
            typename Value_type1,
            typename Units1,
            quantity_mx Q_mx1
        >
        p_quantity
        <
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        >&
            operator +=
                (p_quantity
                <
                    From_abstract_pq,
                    Value_type1,
                    Units1,
                    Q_mx1 
                > const& pq1)
            {
                //D.A.checking
                void (*pf)()
                = &DimensionallyEquivalentConcept
                <
                    Abstract_pq,
                    From_abstract_pq
                >;pf=pf;
#ifdef PHYSICAL_QUANTITIES_WARN_ON_UNIT_CONVERSIONS
                void (*pf1)() = 
                    &UnitConversionWarningConcept
                    <
                        Units,
                        Q_mx,
                        Units1,
                        Q_mx1
                    >;pf1=pf1;
#endif
                m_value += scale_from
                            <
                                Value_type1,
                                Units1,
                                Q_mx1 
                            >(pq1());
                return *this;
            }

        //-= same power diff units and Value_type
        template
        <
            typename From_abstract_pq,
            typename Value_type1,
            typename Units1,
            quantity_mx Q_mx1
        >
        p_quantity
        <
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        >&
            operator -=
                (p_quantity
                <
                    From_abstract_pq,
                    Value_type1,
                    Units1,
                    Q_mx1
                > const& pq1)
            {
                //D.A.checking
                void (*pf)()
                = &DimensionallyEquivalentConcept
                <
                    Abstract_pq,
                    From_abstract_pq
                >;pf=pf;
#ifdef PHYSICAL_QUANTITIES_WARN_ON_UNIT_CONVERSIONS
             void (*pf1)() = 
                &UnitConversionWarningConcept
                <
                    Units,
                    Q_mx,
                    Units1,
                    Q_mx1
                >;pf1=pf1;
#endif
                m_value -= scale_from
                            <
                                Value_type1,
                                Units1,
                                Q_mx1 
                            >(pq1());
                return *this;
            }

        // *= scalar different Value_type
        //param may be unnecessary
       // template<typename Value_type1>
        p_quantity
        <
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        >&
            operator *=(Value_type const& v)
            {m_value *= v;return *this;}

        //  /= scalar different Value_type
       // template<typename Value_type1>
        p_quantity
        <
            Abstract_pq,
            Value_type,
            Units,
            Q_mx
        >&
            operator /=(Value_type const& v)
            {m_value /= v;return *this;}

        // scale from PQ same powers different units,Value_type
        // force to minimum of float 'scale' type for integer integer calcs
        // could improve this so some integer calcs allowed.
        // note function looks unwieldy but
        // static 'scale' variable is only computed first time through
        template
        <
            typename Value_type1,
            typename Units1,
            quantity_mx Q_mx1
        >
        static inline typename math_promote
                      <
                        Value_type,
                        Value_type1
                      > ::type 
            scale_from(Value_type1 const& v)
            {
                typedef typename math_promote
                <
                    typename math_promote
                    <
                        Value_type,
                        Value_type1 
                    > ::type,
                    float 
                > ::type  calc_type; 
                // experimental multiplier appears to make no difference
                static long mx = 1000000000;  //or 1;
                static calc_type
                     const scale 
                    = 
                    (  std::pow( (static_cast<calc_type>(of_length::template unit_traits
                          <Units1::u_length::value>::number_of_std_units_in())* mx )
                             / (static_cast<calc_type>( of_length::template unit_traits
                             <Units::u_length::value>::number_of_std_units_in())* mx ),   
                               Abstract_pq::pwr_length)
                         * std::pow( (static_cast<calc_type>(of_time::template unit_traits
                               <Units1::u_time::value> ::number_of_std_units_in())* mx)
                             /(static_cast<calc_type>( of_time::unit_traits
                               <Units::u_time::value> ::number_of_std_units_in())* mx),
                             Abstract_pq::pwr_time)
                         * std::pow( (static_cast<calc_type>(of_mass::template unit_traits
                            <Units1::u_mass::value>::number_of_std_units_in())* mx )
                                  /(static_cast<calc_type>(of_mass::template unit_traits
                                  <Units::u_mass::value>::number_of_std_units_in()) * mx),
                               Abstract_pq::pwr_mass)
                           * std::pow((static_cast<calc_type>(of_temperature::template unit_traits
                            <Units1::u_temperature::value>::number_of_std_units_in())*mx)
                                  /(static_cast<calc_type>(of_temperature::template unit_traits
                                  <Units::u_temperature::value>::number_of_std_units_in())* mx),
                               Abstract_pq::pwr_temperature)
                           * std::pow((static_cast<calc_type>(of_current::template unit_traits
                            <Units1::u_current::value>::number_of_std_units_in())* mx )
                                  /(static_cast<calc_type>(of_current::template unit_traits
                                  <Units::u_current::value>::number_of_std_units_in())*mx ),
                               Abstract_pq::pwr_current)
                           * std::pow((static_cast<calc_type>(of_substance::template unit_traits
                            <Units1::u_substance::value>::number_of_std_units_in())* mx )
                                  /(static_cast<calc_type>(of_substance::template unit_traits
                                  <Units::u_substance::value>::number_of_std_units_in())* mx ),
                               Abstract_pq::pwr_substance)
                           * std::pow((static_cast<calc_type>(of_intensity::template unit_traits
                            <Units1::u_intensity::value>::number_of_std_units_in())* mx)
                                  /(static_cast<calc_type>(of_intensity::template unit_traits
                                  <Units::u_intensity::value>::number_of_std_units_in())* mx),
                               Abstract_pq::pwr_intensity)
                        )
                        * ((static_cast<calc_type>(of_quantity::template mx_traits<Q_mx1>::number_of_dub_in())* mx) 
                        / (static_cast<calc_type>(of_quantity::template mx_traits<Q_mx>::number_of_dub_in())* mx) );

                return v * scale;
            }

        // for ostream operator <<
        // to output basic units
        inline static physical_quantity_dub_units_out
        <
            Abstract_pq,
            Units,
            Q_mx 
        >  
            units()
            {
                return physical_quantity_dub_units_out
                <
                    Abstract_pq,
                    Units,
                    Q_mx 
                >();
            }
        
    private:
        Value_type m_value;
    }; //p_quantity
} // physical_quantities

#endif
