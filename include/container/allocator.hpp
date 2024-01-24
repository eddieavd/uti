//
//
//      uti
//      allocator.hpp
//

#pragma once

#include <util/config.hpp>
#include <meta/traits.hpp>


#if    defined( UTI_MALLOC ) &&  defined( UTI_REALLOC ) &&  defined( UTI_FREE )
#elif !defined( UTI_MALLOC ) && !defined( UTI_REALLOC ) && !defined( UTI_FREE )
#else
#error "uti: must define all or none of 'UTI_MALLOC', 'UTI_REALLOC', 'UTI_FREE'"
#endif

#ifndef UTI_MALLOC
#include <stdlib.h>
#define UTI_MALLOC(           size )  malloc(          size )
#define UTI_REALLOC( ptr, new_size ) realloc( ptr, new_size )
#define UTI_FREE(   ptr            )    free( ptr           )
#endif


namespace uti
{


template< typename T >
UTI_NODISCARD T * alloc_typed_buffer ( ssize_t count )
{
        return static_cast< T * >( UTI_MALLOC( count * sizeof( T ) ) );
}

template< typename T >
UTI_NODISCARD T * realloc_typed_buffer ( T * buffer, ssize_t new_count )
{
        return static_cast< T * >( UTI_REALLOC( buffer, new_count * sizeof( T ) ) );
}

template< typename T >
void dealloc_typed_buffer ( T * buffer )
{
        UTI_FREE( buffer );
}


template< typename T >
class allocator
{
public:
        using      value_type =       T    ;
        using       size_type =  size_t    ;
        using      ssize_type = ssize_t    ;
        using difference_type = ssize_type ;

        using         pointer = value_type       * ;
        using   const_pointer = value_type const * ;
        using       reference = value_type       & ;
        using const_reference = value_type const & ;

        using        iterator =       pointer ;
        using  const_iterator = const_pointer ;

        static pointer allocate ( ssize_type const _capacity_ )
        {
                return static_cast< pointer >( UTI_MALLOC( _capacity_ ) );
        }
        static pointer reallocate ( pointer const _ptr_, ssize_type const _new_capacity_ )
        {
                return static_cast< pointer >( UTI_REALLOC( _ptr_, _new_capacity_ ) );
        }
        static void deallocate ( pointer const _ptr_ ) noexcept
        {
                UTI_FREE( _ptr_ );
        }

        template< typename... Args >
        static void construct ( pointer const _ptr_, Args&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, Args... > )
        {
                ::new ( ( void * ) _ptr_ ) value_type( UTI_FWD( _args_ )... ) ;
        }
        static void destroy ( pointer const _ptr_ ) noexcept
        {
                _ptr_->~value_type();
        }
};


} // namespace uti
