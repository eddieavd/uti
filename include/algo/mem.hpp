//
//
//      uti
//      mem.hpp
//

#pragma once

#include <type/traits.hpp>
#include <iterator/meta.hpp>


namespace uti
{


template< meta::iterator Iter, typename... Args >
constexpr void construct ( Iter iter, Args&&... args )
        noexcept( is_nothrow_constructible_v< iter_value_t< Iter >, Args... > )
{
        ::new ( ( void * ) iter ) iter_value_t< Iter >( UTI_FWD( args )... ) ;
}

template< meta::iterator Iter, typename... Args >
constexpr void destroy ( Iter iter )
        noexcept( is_nothrow_destructible_v< iter_value_t< Iter > > )
{
        iter->~iter_value_t< Iter >() ;
}

template< meta::forward_iterator Iter >
constexpr void memclr ( Iter begin, Iter const & end )
{
        u8_t * mem = static_cast< u8_t * >( static_cast< void * >( begin ) ) ;
        u8_t * fin = static_cast< u8_t * >( static_cast< void * >(   end ) ) ;

        while( mem != fin )
        {
                *mem = 0 ;
                ++mem ;
        }
}

template< meta::forward_iterator Iter >
constexpr void memset ( Iter begin, Iter const & end, iter_value_t< Iter > const & val )
{
        while( begin != end )
        {
                *begin = val ;
                ++begin ;
        }
}


} // namespace uti
