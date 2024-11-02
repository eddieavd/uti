//
//
//      uti
//      distance.hpp
//

#pragma once

#include <type/traits.hpp>
#include <iterator/meta.hpp>


namespace uti
{


template< typename Iter >
constexpr typename iterator_traits< Iter >::difference_type _distance ( Iter _begin_, Iter _end_, input_iterator_tag ) noexcept
{
        typename iterator_traits< Iter >::difference_type dist { 0 } ;

        for( ; _begin_ != _end_; ++_begin_ )
        {
                ++dist ;
        }
        return dist ;
}

template< typename Iter >
constexpr typename iterator_traits< Iter >::difference_type
_distance ( Iter _begin_, Iter _end_, random_access_iterator_tag ) noexcept
{
        return _end_ - _begin_ ;
}

template< typename Iter >
constexpr typename iterator_traits< Iter >::difference_type
distance ( Iter _begin_, Iter _end_ ) noexcept
{
        return ::uti::_distance( _begin_, _end_, typename iterator_traits< Iter >::iterator_category{} ) ;
}


} // namespace uti
