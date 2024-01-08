//
//
//      uti
//      type_traits.hpp
//

#pragma once

#ifndef UTI_MOVE
#define UTI_MOVE(...) \
        static_cast< uti::remove_reference_t< decltype(__VA_ARGS__)>&&>(__VA_ARGS__)
#endif

#ifndef UTI_FWD
#define UTI_FWD(...) \
        static_cast< decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#endif


namespace uti
{


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
