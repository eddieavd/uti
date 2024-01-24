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
using _swap_result_t = enable_if_t
<
        conjunction_v
        <
                is_not< _is_tuple_like< T > >,
                is_move_constructible< T >,
                is_move_assignable< T >
        >
>;

template< typename T >
inline constexpr _swap_result_t< T > swap ( T & _lhs_, T & _rhs_ )
        noexcept( is_nothrow_move_constructible_v< T > && is_nothrow_move_assignable_v< T > )
{
        T _tmp_( UTI_MOVE( _lhs_ ) ) ;
        _lhs_ =  UTI_MOVE( _rhs_ )   ;
        _rhs_ =  UTI_MOVE( _tmp_ )   ;
}


} // namespace uti
