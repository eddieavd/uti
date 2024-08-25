//
//
//      uti
//      copy.hpp
//

#pragma once

#include <type/traits.hpp>
#include <algo/distance.hpp>
#include <iterator/meta.hpp>

#if !__has_builtin( __builtin_memmove ) && defined( UTI_HAS_STL )
#include <cstring>
#endif


namespace uti
{


template< meta::forward_iterator Iter, meta::forward_iterator DestIter >
void _copy_impl ( Iter begin, Iter end, DestIter dest )
{
        while( begin != end )
        {
                *dest = *begin ;
                ++dest  ;
                ++begin ;
        }
}

template< meta::forward_iterator Iter, meta::forward_iterator DestIter >
void copy ( Iter begin, Iter const & end, DestIter dest )
{
        using value_type = iterator_traits< Iter >::value_type ;

        if constexpr( is_trivially_relocatable_v< value_type > )
        {
                ssize_t const n = ::uti::distance( begin, end ) ;
#if UTI_HAS_BUILTIN( __builtin_memcpy )
                __builtin_memcpy( dest, begin, n * sizeof( value_type ) ) ;
#elif defined( UTI_HAS_STL )
                std::memcpy( dest, begin, n * sizeof( value_type ) ) ;
#else
                _copy_impl( begin, end, dest ) ;
#endif
        }
        else
        {
                _copy_impl( begin, end, dest ) ;
        }
}


template< meta::bidirectional_iterator Iter, meta::bidirectional_iterator DestIter >
void _copy_back_impl ( Iter begin, Iter end, DestIter dest )
{
        while( begin != end )
        {
                *dest = *begin ;
                --dest ;
                --begin ;
        }
}

template< meta::random_access_iterator Iter, meta::random_access_iterator DestIter >
void copy_backward ( Iter begin, Iter const & end, DestIter dest )
{
        using value_type = iterator_traits< Iter >::value_type ;

        if constexpr( is_trivially_relocatable_v< value_type > )
        {
                ssize_t const n = ::uti::distance( end, begin ) ;
#if UTI_HAS_BUILTIN( __builtin_memmove )
                __builtin_memmove( dest - n, end, n * sizeof( value_type ) ) ;
#elif defined( UTI_HAS_STL )
                std::memmove( dest - n, end, n * sizeof( value_type ) ) ;
#else
                _copy_back_impl( begin, end, dest ) ;
#endif
        }
        else
        {
                _copy_back_impl( begin, end, dest ) ;
        }
}

template< meta::bidirectional_iterator Iter, meta::bidirectional_iterator DestIter >
void copy_backward ( Iter begin, Iter const & end, DestIter dest )
{
        _copy_back_impl( begin, end, dest ) ;
}


} // namespace uti
