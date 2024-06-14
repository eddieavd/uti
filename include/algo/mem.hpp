//
//
//      uti
//      mem.hpp
//

#pragma once

#include <type/traits.hpp>


namespace uti
{


template< typename InputIter, typename Sentinel, typename DestIter >
void _memmove_impl ( InputIter begin, Sentinel end, DestIter dest )
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
void memmove ( InVal * begin, InVal * end, OutVal * dest )
{
        _memmove_impl( begin, end, dest ) ;
}

template< typename InputIter, typename Sentinel, typename DestIter >
void _memmove_back_impl ( InputIter begin, Sentinel end, DestIter dest )
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
void memmove_back ( InVal * begin, InVal * end, OutVal * dest )
{
        _memmove_back_impl( begin, end, dest ) ;
}

template< typename T >
void memclr ( T * begin, T * end )
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
void memset ( T * begin, T const * end, T const & val )
{
        while( begin != end )
        {
                *begin = val ;
                ++begin ;
        }
}


} // namespace uti
