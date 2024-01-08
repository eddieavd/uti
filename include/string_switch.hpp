//
//
//      uti
//      string_switch.hpp
//

#pragma once

#include <string_view.hpp>


namespace uti
{


template< typename T, typename R = T >
class string_switch
{
public:
        constexpr string_switch ( string_view_t _str_, T _default_ )
                : str( UTI_MOVE( _str_ ) ), result( UTI_MOVE( _default_ ) ) {}

        constexpr string_switch             ( string_switch const &  ) = delete ;
        constexpr string_switch & operator= ( string_switch const &  ) = delete ;
        constexpr string_switch & operator= ( string_switch       && ) = delete ;

        constexpr string_switch ( string_switch && _other_ ) noexcept
                : str( UTI_MOVE( _other_.str ) ), result( UTI_MOVE( _other_.result ) ) {}

        constexpr ~string_switch () noexcept = default ;

        constexpr string_switch & CASE ( string_view_t const & s, T value ) noexcept
        {
                if( !result && str.equal_to( s ) )
                {
                        result = UTI_MOVE( value );
                }
                return *this;
        }
        constexpr string_switch & ENDS_WITH ( string_view_t const & s, T value ) noexcept
        {
                if( !result && str.ends_with( s ) )
                {
                        result = UTI_MOVE( value );
                }
                return *this;
        }
        constexpr string_switch & STARTS_WITH ( string_view_t const & s, T value ) noexcept
        {
                if( !result && str.starts_with( s ) )
                {
                        result = UTI_MOVE( value );
                }
                return *this;
        }
        constexpr string_switch & CASES ( string_view_t const & s0, string_view_t const & s1, T value ) noexcept
        {
                return CASE( s0, value ).CASE( s1, value );
        }
        constexpr string_switch & CASES ( string_view_t const & s0, string_view_t const & s1,
                                          string_view_t const & s2, T value ) noexcept
        {
                return CASE( s0, value ).CASES( s1, s2, value );
        }
        constexpr string_switch & CASES ( string_view_t const & s0, string_view_t const & s1,
                                          string_view_t const & s2, string_view_t const & s3, T value ) noexcept
        {
                return CASE( s0, value ).CASES( s1, s2, s3, value );
        }
        constexpr string_switch & CASES ( string_view_t const & s0, string_view_t const & s1,
                                          string_view_t const & s2, string_view_t const & s3,
                                          string_view_t const & s4, T value ) noexcept
        {
                return CASE( s0, value ).CASES( s1, s2, s3, s4, value );
        }
        constexpr string_switch & CASES ( string_view_t const & s0, string_view_t const & s1,
                                          string_view_t const & s2, string_view_t const & s3,
                                          string_view_t const & s4, string_view_t const & s5, T value ) noexcept
        {
                return CASE( s0, value ).CASES( s1, s2, s3, s4, s5, value );
        }
        constexpr string_switch & CASES ( string_view_t const & s0, string_view_t const & s1,
                                          string_view_t const & s2, string_view_t const & s3,
                                          string_view_t const & s4, string_view_t const & s5,
                                          string_view_t const & s6, T value ) noexcept
        {
                return CASE( s0, value ).CASES( s1, s2, s3, s4, s5, s6, value );
        }
        constexpr string_switch & CASES ( string_view_t const & s0, string_view_t const & s1,
                                          string_view_t const & s2, string_view_t const & s3,
                                          string_view_t const & s4, string_view_t const & s5,
                                          string_view_t const & s6, string_view_t const & s7, T value ) noexcept
        {
                return CASE( s0, value ).CASES( s1, s2, s3, s4, s5, s6, s7, value );
        }
        constexpr string_switch & CASES ( string_view_t const & s0, string_view_t const & s1,
                                          string_view_t const & s2, string_view_t const & s3,
                                          string_view_t const & s4, string_view_t const & s5,
                                          string_view_t const & s6, string_view_t const & s7,
                                          string_view_t const & s8, T value ) noexcept
        {
                return CASE( s0, value ).CASES( s1, s2, s3, s4, s5, s6, s7, s8, value );
        }
        constexpr string_switch & CASES ( string_view_t const & s0, string_view_t const & s1,
                                          string_view_t const & s2, string_view_t const & s3,
                                          string_view_t const & s4, string_view_t const & s5,
                                          string_view_t const & s6, string_view_t const & s7,
                                          string_view_t const & s8, string_view_t const & s9, T value ) noexcept
        {
                return CASE( s0, value ).CASES( s1, s2, s3, s4, s5, s6, s7, s8, s9, value );
        }

        constexpr string_switch & CASE_LOWER ( string_view_t const & s, T value ) noexcept
        {
                if( !result && str.equal_to_insensitive( s ) )
                {
                        result = UTI_MOVE( value );
                }
                return *this;
        }
        constexpr string_switch & ENDS_WITH_LOWER ( string_view_t const & s, T value ) noexcept
        {
                if( !result && str.ends_with_insensitive( s ) )
                {
                        result = UTI_MOVE( value );
                }
                return *this;
        }
        constexpr string_switch & STARTS_WITH_LOWER ( string_view_t const & s, T value ) noexcept
        {
                if( !result && str.starts_with_insensitive( s ) )
                {
                        result = UTI_MOVE( value );
                }
                return *this;
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & s0, string_view_t const & s1, T value ) noexcept
        {
                return CASE_LOWER( s0, value ).CASE_LOWER( s1, value );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & s0, string_view_t const & s1,
                                                string_view_t const & s2, T value ) noexcept
        {
                return CASE_LOWER( s0, value ).CASES_LOWER( s1, s2, value );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & s0, string_view_t const & s1,
                                                string_view_t const & s2, string_view_t const & s3, T value ) noexcept
        {
                return CASE_LOWER( s0, value ).CASES_LOWER( s1, s2, s3, value );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & s0, string_view_t const & s1,
                                                string_view_t const & s2, string_view_t const & s3,
                                                string_view_t const & s4, T value ) noexcept
        {
                return CASE_LOWER( s0, value ).CASES_LOWER( s1, s2, s3, s4, value );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & s0, string_view_t const & s1,
                                                string_view_t const & s2, string_view_t const & s3,
                                                string_view_t const & s4, string_view_t const & s5, T value ) noexcept
        {
                return CASE_LOWER( s0, value ).CASES_LOWER( s1, s2, s3, s4, s5, value );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & s0, string_view_t const & s1,
                                                string_view_t const & s2, string_view_t const & s3,
                                                string_view_t const & s4, string_view_t const & s5,
                                                string_view_t const & s6, T value ) noexcept
        {
                return CASE_LOWER( s0, value ).CASES_LOWER( s1, s2, s3, s4, s5, s6, value );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & s0, string_view_t const & s1,
                                                string_view_t const & s2, string_view_t const & s3,
                                                string_view_t const & s4, string_view_t const & s5,
                                                string_view_t const & s6, string_view_t const & s7, T value ) noexcept
        {
                return CASE_LOWER( s0, value ).CASES_LOWER( s1, s2, s3, s4, s5, s6, s7, value );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & s0, string_view_t const & s1,
                                                string_view_t const & s2, string_view_t const & s3,
                                                string_view_t const & s4, string_view_t const & s5,
                                                string_view_t const & s6, string_view_t const & s7,
                                                string_view_t const & s8, T value ) noexcept
        {
                return CASE_LOWER( s0, value ).CASES_LOWER( s1, s2, s3, s4, s5, s6, s7, s8, value );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & s0, string_view_t const & s1,
                                                string_view_t const & s2, string_view_t const & s3,
                                                string_view_t const & s4, string_view_t const & s5,
                                                string_view_t const & s6, string_view_t const & s7,
                                                string_view_t const & s8, string_view_t const & s9, T value ) noexcept
        {
                return CASE_LOWER( s0, value ).CASES_LOWER( s1, s2, s3, s4, s5, s6, s7, s8, s9, value );
        }

        [[ nodiscard ]] constexpr operator R () noexcept
        {
                return UTI_MOVE( result );
        }
private:
        string_view_t const str ;
        T result ;
};


} // namespace uti
