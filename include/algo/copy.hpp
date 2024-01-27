//
//
//      uti
//      copy.hpp
//

#pragma once

#include <meta/traits.hpp>

#if !__has_builtin( __builtin_memmove ) && defined( UTI_HAS_STL )
#include <cstring>
#endif


namespace uti
{


template< typename InputIter, typename Sentinel, typename DestIter >
void _copy_impl ( InputIter begin, Sentinel end, DestIter dest )
{
        while( begin != end )
        {
                *dest = *begin;
                ++dest;
                ++begin;
        }
}

template< typename InVal, typename OutVal,
          typename = enable_if_t< is_same_v< remove_cv_t< InVal >, OutVal > > >
void copy ( InVal * begin, InVal * end, OutVal * dest )
{
        if constexpr( is_trivially_relocatable_v< InVal > )
        {
                ssize_t const n = static_cast< ssize_t >( end - begin );
                if( n > 0 )
                {
#if __has_builtin( __builtin_memmove )
                        __builtin_memmove( dest, begin, n * sizeof( OutVal ) );
#elif defined( UTI_HAS_STL )
                        std::memmove( dest, begin, n * sizeof( OutVal ) );
#else
                        _copy_impl( begin, end, dest );
#endif
                }
        }
        else
        {
                _copy_impl( begin, end, dest );
        }
}


} // namespace uti
