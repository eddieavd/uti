//
//
//      uti
//      tuple.hpp
//

#pragma once

#include <meta/traits.hpp>
#include <meta/ref_wrap.hpp>
#include <meta/sequence.hpp>
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


template< typename Tuple > struct tuple_size ;

template< typename... Ts >
struct tuple_size< tuple< Ts... > > : integral_constant< sizeof...( Ts ) > {} ;

template< typename Tuple >
inline constexpr ssize_t tuple_size_v = tuple_size< remove_cv_t< Tuple > >::value ;


namespace _detail
{


template< ssize_t Idx, typename Tuple >
struct get_impl : get_impl< Idx - 1, pop_front_t< Tuple > > {} ;

template< typename Tuple >
struct get_impl< 0, Tuple >
{
        template< typename T >
        static constexpr decltype( auto ) get ( T && t )
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

template< typename Tup1, typename Tup2, ssize_t... Idxs1, ssize_t... Idxs2 >
static constexpr auto cat_from_indices ( Tup1&& t1, Tup2&& t2, index_sequence< Idxs1... >, index_sequence< Idxs2... > )
{
        return tuple{ get< Idxs1 >( UTI_FWD( t1 ) )..., get< Idxs2 >( UTI_FWD( t2 ) )... };
}

struct tuple_cat_impl
{
        template< typename Tup1, typename Tup2 >
        static constexpr auto fn ( Tup1&& t1, Tup2&& t2 )
        {
                return cat_from_indices( UTI_FWD( t1 ),
                                         UTI_FWD( t2 ),
                                         make_index_sequence< tuple_size_v< remove_cvref_t< Tup1 > > > {},
                                         make_index_sequence< tuple_size_v< remove_cvref_t< Tup2 > > > {}
                );
        }
};


} // namespace _detail


template< ssize_t Idx, typename Tuple >
constexpr decltype( auto ) get ( Tuple && tup )
{
        return _detail::get_impl< Idx, remove_cvref_t< Tuple > >::get( UTI_FWD( tup ) );
}

template< typename... Tups >
constexpr auto tuple_cat ( Tups&&... tups )
{
        return _detail::tuple_cat_impl::fn( UTI_FWD( tups )... );
}


} // namespace uti
