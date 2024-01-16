//
//
//      uti
//      string_switch.hpp
//

#pragma once

#include <string/string_view.hpp>


namespace uti
{


template< typename T, typename R = T >
class string_switch
{
public:
        explicit constexpr string_switch ( string_view_t const & _str_ ) noexcept
                : str( _str_ ), result(), is_set( false ) {}

        constexpr string_switch ( string_view_t const & _str_, T _default_ ) noexcept
                : str( _str_ ), result( UTI_MOVE( _default_ ) ), is_set( false ) {}

        constexpr string_switch             ( string_switch const &  ) = delete ;
        constexpr string_switch & operator= ( string_switch const &  ) = delete ;
        constexpr string_switch & operator= ( string_switch       && ) = delete ;

        constexpr string_switch ( string_switch && _other_ ) noexcept
                : str( UTI_MOVE( _other_.str ) ), result( UTI_MOVE( _other_.result ) ), is_set( _other_.is_set ) {}

        constexpr ~string_switch () noexcept = default ;

        constexpr string_switch & CASE ( string_view_t const & _s_, T _value_ ) noexcept
        {
                if( !is_set && str.equal_to( _s_ ) )
                {
                        result = UTI_MOVE( _value_ );
                        is_set = true;
                }
                return *this;
        }
        constexpr string_switch & ENDS_WITH ( string_view_t const & _s_, T _value_ ) noexcept
        {
                if( !is_set && str.ends_with( _s_ ) )
                {
                        result = UTI_MOVE( _value_ );
                        is_set = true;
                }
                return *this;
        }
        constexpr string_switch & STARTS_WITH ( string_view_t const & _s_, T _value_ ) noexcept
        {
                if( !is_set && str.starts_with( _s_ ) )
                {
                        result = UTI_MOVE( _value_ );
                        is_set = true;
                }
                return *this;
        }
        constexpr string_switch & CASES ( string_view_t const & _s0_, string_view_t const & _s1_, T _value_ ) noexcept
        {
                return CASE( _s0_, _value_ ).CASE( _s1_, _value_ );
        }
        constexpr string_switch & CASES ( string_view_t const & _s0_, string_view_t const & _s1_,
                                          string_view_t const & _s2_, T _value_ ) noexcept
        {
                return CASE( _s0_, _value_ ).CASES( _s1_, _s2_, _value_ );
        }
        constexpr string_switch & CASES ( string_view_t const & _s0_, string_view_t const & _s1_,
                                          string_view_t const & _s2_, string_view_t const & _s3_, T _value_ ) noexcept
        {
                return CASE( _s0_, _value_ ).CASES( _s1_, _s2_, _s3_, _value_ );
        }
        constexpr string_switch & CASES ( string_view_t const & _s0_, string_view_t const & _s1_,
                                          string_view_t const & _s2_, string_view_t const & _s3_,
                                          string_view_t const & _s4_, T _value_ ) noexcept
        {
                return CASE( _s0_, _value_ ).CASES( _s1_, _s2_, _s3_, _s4_, _value_ );
        }
        constexpr string_switch & CASES ( string_view_t const & _s0_, string_view_t const & _s1_,
                                          string_view_t const & _s2_, string_view_t const & _s3_,
                                          string_view_t const & _s4_, string_view_t const & _s5_, T _value_ ) noexcept
        {
                return CASE( _s0_, _value_ ).CASES( _s1_, _s2_, _s3_, _s4_, _s5_, _value_ );
        }
        constexpr string_switch & CASES ( string_view_t const & _s0_, string_view_t const & _s1_,
                                          string_view_t const & _s2_, string_view_t const & _s3_,
                                          string_view_t const & _s4_, string_view_t const & _s5_,
                                          string_view_t const & _s6_, T _value_ ) noexcept
        {
                return CASE( _s0_, _value_ ).CASES( _s1_, _s2_, _s3_, _s4_, _s5_, _s6_, _value_ );
        }
        constexpr string_switch & CASES ( string_view_t const & _s0_, string_view_t const & _s1_,
                                          string_view_t const & _s2_, string_view_t const & _s3_,
                                          string_view_t const & _s4_, string_view_t const & _s5_,
                                          string_view_t const & _s6_, string_view_t const & _s7_, T _value_ ) noexcept
        {
                return CASE( _s0_, _value_ ).CASES( _s1_, _s2_, _s3_, _s4_, _s5_, _s6_, _s7_, _value_ );
        }
        constexpr string_switch & CASES ( string_view_t const & _s0_, string_view_t const & _s1_,
                                          string_view_t const & _s2_, string_view_t const & _s3_,
                                          string_view_t const & _s4_, string_view_t const & _s5_,
                                          string_view_t const & _s6_, string_view_t const & _s7_,
                                          string_view_t const & _s8_, T _value_ ) noexcept
        {
                return CASE( _s0_, _value_ ).CASES( _s1_, _s2_, _s3_, _s4_, _s5_, _s6_, _s7_, _s8_, _value_ );
        }
        constexpr string_switch & CASES ( string_view_t const & _s0_, string_view_t const & _s1_,
                                          string_view_t const & _s2_, string_view_t const & _s3_,
                                          string_view_t const & _s4_, string_view_t const & _s5_,
                                          string_view_t const & _s6_, string_view_t const & _s7_,
                                          string_view_t const & _s8_, string_view_t const & _s9_, T _value_ ) noexcept
        {
                return CASE( _s0_, _value_ ).CASES( _s1_, _s2_, _s3_, _s4_, _s5_, _s6_, _s7_, _s8_, _s9_, _value_ );
        }

        constexpr string_switch & CASE_LOWER ( string_view_t const & s, T _value_ ) noexcept
        {
                if( !is_set && str.equal_to_insensitive( s ) )
                {
                        result = UTI_MOVE( _value_ );
                        is_set = true;
                }
                return *this;
        }
        constexpr string_switch & ENDS_WITH_LOWER ( string_view_t const & s, T _value_ ) noexcept
        {
                if( !is_set && str.ends_with_insensitive( s ) )
                {
                        result = UTI_MOVE( _value_ );
                        is_set = true;
                }
                return *this;
        }
        constexpr string_switch & STARTS_WITH_LOWER ( string_view_t const & s, T _value_ ) noexcept
        {
                if( !is_set && str.starts_with_insensitive( s ) )
                {
                        result = UTI_MOVE( _value_ );
                        is_set = true;
                }
                return *this;
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & _s0_, string_view_t const & _s1_, T _value_ ) noexcept
        {
                return CASE_LOWER( _s0_, _value_ ).CASE_LOWER( _s1_, _value_ );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & _s0_, string_view_t const & _s1_,
                                                string_view_t const & _s2_, T _value_ ) noexcept
        {
                return CASE_LOWER( _s0_, _value_ ).CASES_LOWER( _s1_, _s2_, _value_ );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & _s0_, string_view_t const & _s1_,
                                                string_view_t const & _s2_, string_view_t const & _s3_, T _value_ ) noexcept
        {
                return CASE_LOWER( _s0_, _value_ ).CASES_LOWER( _s1_, _s2_, _s3_, _value_ );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & _s0_, string_view_t const & _s1_,
                                                string_view_t const & _s2_, string_view_t const & _s3_,
                                                string_view_t const & _s4_, T _value_ ) noexcept
        {
                return CASE_LOWER( _s0_, _value_ ).CASES_LOWER( _s1_, _s2_, _s3_, _s4_, _value_ );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & _s0_, string_view_t const & _s1_,
                                                string_view_t const & _s2_, string_view_t const & _s3_,
                                                string_view_t const & _s4_, string_view_t const & _s5_, T _value_ ) noexcept
        {
                return CASE_LOWER( _s0_, _value_ ).CASES_LOWER( _s1_, _s2_, _s3_, _s4_, _s5_, _value_ );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & _s0_, string_view_t const & _s1_,
                                                string_view_t const & _s2_, string_view_t const & _s3_,
                                                string_view_t const & _s4_, string_view_t const & _s5_,
                                                string_view_t const & _s6_, T _value_ ) noexcept
        {
                return CASE_LOWER( _s0_, _value_ ).CASES_LOWER( _s1_, _s2_, _s3_, _s4_, _s5_, _s6_, _value_ );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & _s0_, string_view_t const & _s1_,
                                                string_view_t const & _s2_, string_view_t const & _s3_,
                                                string_view_t const & _s4_, string_view_t const & _s5_,
                                                string_view_t const & _s6_, string_view_t const & _s7_, T _value_ ) noexcept
        {
                return CASE_LOWER( _s0_, _value_ ).CASES_LOWER( _s1_, _s2_, _s3_, _s4_, _s5_, _s6_, _s7_, _value_ );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & _s0_, string_view_t const & _s1_,
                                                string_view_t const & _s2_, string_view_t const & _s3_,
                                                string_view_t const & _s4_, string_view_t const & _s5_,
                                                string_view_t const & _s6_, string_view_t const & _s7_,
                                                string_view_t const & _s8_, T _value_ ) noexcept
        {
                return CASE_LOWER( _s0_, _value_ ).CASES_LOWER( _s1_, _s2_, _s3_, _s4_, _s5_, _s6_, _s7_, _s8_, _value_ );
        }
        constexpr string_switch & CASES_LOWER ( string_view_t const & _s0_, string_view_t const & _s1_,
                                                string_view_t const & _s2_, string_view_t const & _s3_,
                                                string_view_t const & _s4_, string_view_t const & _s5_,
                                                string_view_t const & _s6_, string_view_t const & _s7_,
                                                string_view_t const & _s8_, string_view_t const & _s9_, T _value_ ) noexcept
        {
                return CASE_LOWER( _s0_, _value_ ).CASES_LOWER( _s1_, _s2_, _s3_, _s4_, _s5_, _s6_, _s7_, _s8_, _s9_, _value_ );
        }

        [[ nodiscard ]] constexpr R DEFAULT ( T _value_ ) noexcept
        {
                if( is_set )
                {
                        return UTI_MOVE( result );
                }
                return _value_;
        }
        [[ nodiscard ]] constexpr operator R () noexcept
        {
                return UTI_MOVE( result );
        }
private:
        string_view_t str ;
        T    result ;
        bool is_set ;
};


} // namespace uti
