//
//
//      uti
//      swap.hpp
//

#pragma once

#include <meta/traits.hpp>


namespace uti
{


template< typename T >
inline constexpr
enable_if_t
<
        conjunction_v
        <
                is_not< _is_tuple_like< T > >,
                is_move_constructible< T >,
                is_move_assignable< T >
        >
>
swap ( T & _lhs_, T & _rhs_ )
        noexcept( is_nothrow_move_constructible_v< T > && is_nothrow_move_assignable_v< T > )
{
        T _tmp_( UTI_MOVE( _lhs_ ) ) ;
        _lhs_ =  UTI_MOVE( _rhs_ )   ;
        _rhs_ =  UTI_MOVE( _tmp_ )   ;
}

template< typename T, ssize_t N >
inline constexpr
enable_if_t< _is_swappable< T >::value >
swap ( T ( & a )[ N ], T ( & b )[ N ] ) noexcept( _is_nothrow_swappable< T >::value ) ;



} // namespace uti
