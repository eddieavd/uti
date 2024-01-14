//
//
//      uti
//      type_traits.hpp
//

#pragma once

#ifndef UTI_MOVE
#define UTI_MOVE(...) \
        static_cast< typename uti::remove_reference_t< decltype(__VA_ARGS__)>&&>(__VA_ARGS__)
#endif

#ifndef UTI_FWD
#define UTI_FWD(...) \
        static_cast< decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#endif


namespace uti
{


using  i8_t =           char ;
using  u8_t = unsigned  char ;
using i16_t =          short ;
using u16_t = unsigned short ;
using i32_t =            int ;
using u32_t = unsigned   int ;
using i64_t =           long ;
using u64_t = unsigned  long ;

static_assert( sizeof(  i8_t ) == 1 ) ;
static_assert( sizeof(  u8_t ) == 1 ) ;
static_assert( sizeof( i16_t ) == 2 ) ;
static_assert( sizeof( u16_t ) == 2 ) ;
static_assert( sizeof( i32_t ) == 4 ) ;
static_assert( sizeof( u32_t ) == 4 ) ;
static_assert( sizeof( i64_t ) == 8 ) ;
static_assert( sizeof( u64_t ) == 8 ) ;

using  size_t = u64_t ;
using ssize_t = i64_t ;


constexpr bool is_constant_evaluated () noexcept
{
        if consteval
        {
                return true;
        }
        return false;
}


template< typename T >
struct type_identity
{
        using type = T ;
};

template< typename T >
using type_identity_t = typename type_identity< T >::type ;


template< typename T >
struct remove_reference : type_identity< T > {} ;

template< typename T >
struct remove_reference< T & > : type_identity< T > {} ;

template< typename T >
struct remove_reference< T && > : type_identity< T > {} ;

template< typename T >
using remove_reference_t = typename remove_reference< T >::type ;


} // namespace uti
