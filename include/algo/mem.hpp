//
//
//      uti
//      mem.hpp
//

#pragma once

#include <type/traits.hpp>


namespace uti
{


template< typename T, typename... Args >
constexpr void construct ( T * ptr, Args&&... args )
        noexcept( is_nothrow_constructible_v< T, Args... > )
{
                ::new ( ( void * ) ptr ) T( UTI_FWD( args )... ) ;
}

template< typename T >
constexpr void destroy ( T * ptr )
        noexcept( is_nothrow_destructible_v< T > )
{
                ptr->~T();
}

template< typename T >
constexpr void memclr ( T * begin, T * end )
{
        u8_t * mem = static_cast< u8_t * >( begin ) ;
        u8_t * fin = static_cast< u8_t * >(   end ) ;

        while( mem != fin )
        {
                *mem = 0 ;
                ++mem ;
        }
}

template< typename T >
constexpr void memset ( T * begin, T const * end, T const & val )
{
        while( begin != end )
        {
                *begin = val ;
                ++begin ;
        }
}


} // namespace uti
