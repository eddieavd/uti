//
//
//      uti
//      copy.hpp
//

#pragma once

#include <type/traits.hpp>
#include <algo/distance.hpp>

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
                *dest++ = *begin++;
        }
}

template< typename InIter, typename OutIter, typename ValT = remove_pointer_t< InIter > /* = iter_value_t< InIter > */ >
void copy ( InIter begin, InIter const & end, OutIter dest )
{
        if constexpr( is_trivially_relocatable_v< ValT > )
        {
                ssize_t const n = distance( begin, end ) ;
                if( n > 0 )
                {
#if UTI_HAS_BUILTIN( __builtin_memcpy )
                        __builtin_memcpy( dest, begin, n * sizeof( ValT ) );
#elif defined( UTI_HAS_STL )
                        std::memcpy( dest, begin, n * sizeof( ValT ) );
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
