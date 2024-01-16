//
//
//      uti
//      tuple.hpp
//

#pragma once

#include <traits/traits.hpp>
#include <traits/ref_wrap.hpp>
#include <meta/meta.hpp>


namespace uti
{


template< typename... Ts >
struct tuple
{
        constexpr tuple () noexcept = default ;
};

template< typename T0, typename... Ts >
struct tuple< T0, Ts... > : tuple< Ts... >
{
        using _base = tuple< Ts... > ;

        template< typename T0_, typename... Ts_ >
        explicit constexpr tuple ( T0_&& t0, Ts_&&... rest ) : _base( UTI_FWD( rest )... ), data( UTI_FWD( t0 ) ) {}

        T0 data ;
};

template< typename T, typename... Ts >
tuple ( T t, Ts... rest ) -> tuple< unwrap_ref_decay_t< T >, unwrap_ref_decay_t< Ts >... > ;


template< typename... Ts >
constexpr auto make_tuple ( Ts&&... ts )
{
        return tuple< unwrap_ref_decay_t< Ts >... > { UTI_FWD( ts )... } ;
}

////////////////////////////////////////////////////////////////////////////////

namespace _detail
{


template< ssize_t Idx, typename Tuple >
struct get_impl : get_impl< Idx - 1, pop_front_t< Tuple > > {} ;

template< typename Tuple >
struct get_impl< 0, Tuple >
{
        template< typename T >
        constexpr static decltype( auto ) get ( T && t )
        {
                constexpr bool is_const = is_const_v< remove_reference_t< T > > ;
                constexpr bool is_lvref = is_lvalue_reference_v< T > ;

                using data_t = front_t< Tuple > ;

                if constexpr( is_lvref && is_const )
                {
                        return static_cast< data_t const & >( static_cast< Tuple const & >( t ).data );
                }
                if constexpr( is_lvref && !is_const )
                {
                        return static_cast< data_t & >( static_cast< Tuple & >( t ).data );
                }
                if constexpr( !is_lvref && is_const )
                {
                        return static_cast< data_t const && >( static_cast< Tuple const && >( t ).data );
                }
                if constexpr( !is_lvref && !is_const )
                {
                        return static_cast< data_t && >( static_cast< Tuple && >( t ).data );
                }
        }
};


} // namespace _detail

////////////////////////////////////////////////////////////////////////////////

template< ssize_t Idx, typename Tuple >
constexpr decltype( auto ) get ( Tuple && tup )
{
        return _detail::get_impl< Idx, remove_cvref_t< Tuple > >::get( UTI_FWD( tup ) );
}


} // namespace uti
