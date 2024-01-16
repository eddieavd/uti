//
//
//      uti
//      int_sequence.hpp
//

#pragma once

#include <traits/traits.hpp>


namespace uti
{


template< typename T, T... Ts >
struct integer_sequence
{
        using value_type =                T ;
        using       type = integer_sequence ;

        static_assert( is_integral_v< value_type >, "uti::integer_sequence can only be instantiated with integral types" );

        static constexpr ssize_t size () noexcept { return sizeof...( Ts ); }
};

template< ssize_t... Ts >
using index_sequence = integer_sequence< ssize_t, Ts... > ;


template< typename Seq1, typename Seq2 >
struct _merge_and_renumber ;

template< typename T, T... I1, T... I2 >
struct _merge_and_renumber< integer_sequence< T, I1... >, integer_sequence< T, I2... > >
        : integer_sequence< T, I1..., ( sizeof...( I1 ) + I2 )... > {} ;

template< ssize_t N >
struct _make_index_sequence
        : _merge_and_renumber< typename _make_index_sequence<     N / 2 >::type,
                               typename _make_index_sequence< N - N / 2 >::type > {} ;

template<> struct _make_index_sequence< 0 > : index_sequence<   > {} ;
template<> struct _make_index_sequence< 1 > : index_sequence< 0 > {} ;


template< ssize_t N >
using make_index_sequence = _make_index_sequence< N > ;

template< typename... Ts >
using index_sequence_for = make_index_sequence< sizeof...( Ts ) > ;


} // namespace uti
