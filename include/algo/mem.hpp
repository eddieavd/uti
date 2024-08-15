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


template< typename InputIter, typename Sentinel, typename DestIter >
constexpr void _memmove_impl ( InputIter begin, Sentinel end, DestIter dest )
{
        while( begin != end )
        {
                *dest = *begin ;
                ++dest  ;
                ++begin ;
        }
}

template< typename InVal, typename OutVal >
        requires( is_same_v< remove_cv_t< InVal >, OutVal > )
constexpr void memmove ( InVal * begin, InVal * end, OutVal * dest )
{
        _memmove_impl( begin, end, dest ) ;
}

template< typename InputIter, typename Sentinel, typename DestIter >
constexpr void _memmove_back_impl ( InputIter begin, Sentinel end, DestIter dest )
{
        while( begin != end )
        {
                *dest = *begin ;
                --dest  ;
                --begin ;
        }
}

template< typename InVal, typename OutVal >
        requires( is_same_v< remove_cv_t< InVal >, OutVal > )
constexpr void memmove_back ( InVal * begin, InVal * end, OutVal * dest )
{
        _memmove_back_impl( begin, end, dest ) ;
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
