//
//
//      uti
//      meta.hpp
//

#pragma once

#include <meta/traits.hpp>


namespace uti
{


////////////////////////////////////////////////////////////////////////////////
/// empty

template< typename... > struct type_list {} ;

template< typename List >
struct empty : false_type {} ;

template< template< typename... > typename TypeList >
struct empty< TypeList<> > : true_type {} ;

template< typename... Ts >
inline constexpr bool empty_v = empty< Ts... >::value ;

static_assert( is_v    < empty< type_list<     > > > ) ;
static_assert( is_not_v< empty< type_list< int > > > ) ;

////////////////////////////////////////////////////////////////////////////////
/// front

template< typename List > struct front ;

template< template< typename... > typename TypeList, typename T0, typename... Ts >
struct front< TypeList< T0, Ts... > > : type_identity< T0 > {} ;

template< typename List >
using front_t = typename front< List >::type ;

static_assert( is_same_v< front_t< type_list< int, float > >, int > ) ;

////////////////////////////////////////////////////////////////////////////////
/// pop_front

template< typename List > struct pop_front ;

template< template< typename... > typename TypeList, typename T0, typename... Ts >
struct pop_front< TypeList< T0, Ts... > > : type_identity< TypeList< Ts... > > {} ;

template< typename List >
using pop_front_t = typename pop_front< List >::type ;

static_assert( is_same_v< pop_front_t< type_list< int, float, double > >, type_list< float, double > > ) ;

////////////////////////////////////////////////////////////////////////////////
/// back

template< typename List > struct back : back< pop_front_t< List > > {} ;

template< template< typename... > typename TypeList, typename T >
struct back< TypeList< T > > : type_identity< T > {} ;

template< typename List >
using back_t = typename back< List >::type ;

static_assert( is_same_v< double, back_t< type_list< int, float, double > > > ) ;

////////////////////////////////////////////////////////////////////////////////
/// push_back

template< typename List, typename T > struct push_back ;

template< template< typename... > typename TypeList, typename... Ts, typename T >
struct push_back< TypeList< Ts... >, T > : type_identity< TypeList< Ts..., T > > {} ;

template< template< typename... > typename TypeList, typename T >
struct push_back< TypeList<>, T > : type_identity< TypeList< T > > {} ;

template< typename List, typename T >
using push_back_t = typename push_back< List, T >::type ;

static_assert( is_same_v< push_back_t< type_list<            >, double >, type_list<             double > > ) ;
static_assert( is_same_v< push_back_t< type_list< int, float >, double >, type_list< int, float, double > > ) ;

////////////////////////////////////////////////////////////////////////////////
/// pop_back

template< typename List, typename RetList = type_list<> > struct pop_back ;

template< template< typename... > typename TypeList, typename T, typename RetList >
struct pop_back< TypeList< T >, RetList > : type_identity< RetList > {} ;

template< template< typename... > typename TypeList, typename T0, typename T1, typename... Ts, typename RetList >
struct pop_back< TypeList< T0, T1, Ts... >, RetList > : pop_back< TypeList< T1, Ts... >, push_back_t< RetList, T0 > > {} ;

template< typename List >
using pop_back_t = typename pop_back< List >::type ;

static_assert( is_same_v< pop_back_t< type_list< int        > >, type_list<     > > ) ;
static_assert( is_same_v< pop_back_t< type_list< int, float > >, type_list< int > > ) ;

////////////////////////////////////////////////////////////////////////////////
/// any_match

template< template< typename > typename Predicate, typename List >
struct any_match ;

template< template< typename > typename Predicate, template< typename... > typename List >
struct any_match< Predicate, List<> > : false_type {} ;

template< template< typename > typename Predicate, typename List >
struct any_match : conditional_t
                <
                        Predicate< front_t< List > >::value,
                        true_type,
                        typename
                        any_match
                        <
                                Predicate,
                                pop_front_t< List >
                        >::type
                > {} ;

template< template< typename > typename Predicate, typename List >
inline constexpr bool any_match_v = any_match< Predicate, List >::value ;

static_assert(  any_match_v< is_integral, type_list< int, double > > ) ;
static_assert( !any_match_v< is_empty   , type_list< int, double > > ) ;

////////////////////////////////////////////////////////////////////////////////
/// contains_type

template< typename T >
struct same_as
{
        template< typename U >
        struct predicate : is_same< T, U > {} ;
};


template< typename Needle, typename Haystack >
using contains_type = any_match< same_as< Needle >::template predicate, Haystack > ;

template< typename Needle, typename Haystack >
inline constexpr bool contains_type_v = contains_type< Needle, Haystack >::value ;

static_assert( contains_type_v< int, type_list<    int,  float, double > > ) ;
static_assert( contains_type_v< int, type_list< double,    int,  float > > ) ;
static_assert( contains_type_v< int, type_list<  float, double,    int > > ) ;

static_assert( !contains_type_v< int, type_list<               > > ) ;
static_assert( !contains_type_v< int, type_list< float, double > > ) ;

////////////////////////////////////////////////////////////////////////////////

template< ssize_t Idx, typename List > struct at : at< Idx - 1, pop_front_t< List > > {} ;

template< typename List >
struct at< 0, List > : front< List > {} ;

template< ssize_t Idx, typename List >
using at_t = typename at< Idx, List >::type ;

static_assert( is_same_v<    int, at_t< 0, type_list< int, float, double > > > ) ;
static_assert( is_same_v<  float, at_t< 1, type_list< int, float, double > > > ) ;
static_assert( is_same_v< double, at_t< 2, type_list< int, float, double > > > ) ;


} // namespace uti
