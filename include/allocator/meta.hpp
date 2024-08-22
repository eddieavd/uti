//
//
//      uti
//      allocator.hpp
//

#pragma once

#include <util/config.hpp>
#include <container/meta.hpp>
#include <algo/copy.hpp>

#include <new>

#ifndef UTI_STATIC_MEM_SIZE
#define UTI_STATIC_MEM_SIZE 8 * 1024 * 1024
#endif

#if    defined( UTI_MALLOC ) &&  defined( UTI_REALLOC ) &&  defined( UTI_FREE )
#elif !defined( UTI_MALLOC ) && !defined( UTI_REALLOC ) && !defined( UTI_FREE )
#else
#error "uti: must define all or none of 'UTI_MALLOC', 'UTI_REALLOC', 'UTI_FREE'"
#endif

#ifndef UTI_MALLOC
#include <stdlib.h>
#define UTI_MALLOC(           size )  malloc(          size )
#define UTI_REALLOC( ptr, new_size ) realloc( ptr, new_size )
#define UTI_FREE(    ptr           )    free( ptr           )
#endif


namespace uti
{


template< typename T >
UTI_NODISCARD constexpr T * alloc_typed_buffer ( ssize_t count )
{
        return static_cast< T * >( UTI_MALLOC( count * sizeof( T ) ) );
}

template< typename T >
UTI_NODISCARD constexpr T * realloc_typed_buffer ( T * buffer, ssize_t new_count )
{
        return static_cast< T * >( UTI_REALLOC( buffer, new_count * sizeof( T ) ) );
}

template< typename T >
constexpr void dealloc_typed_buffer ( T * buffer )
{
        UTI_FREE( buffer );
}


template< typename T >
struct block_t
{
        T *      ptr ;
        ssize_t size ;

        constexpr operator bool () const noexcept { return ptr != nullptr ; }
};

template< typename T > using has_block_type = T::block_type ;

template< typename Alloc, typename T >
using has_inplace_realloc = decltype( Alloc::realloc_inplace( uti::declval< block_t< T > >(), uti::declval< ssize_t >() ) ) ;

template< typename Alloc, typename T >
using has_max_size = decltype( Alloc::max_size() ) ;


template< typename Alloc, typename = void >
class allocator_traits
{
public:
        using  allocator_type = Alloc ;
        using      value_type = allocator_type::value_type ;
        using       size_type = detected_or_t<  size_t,       has_size_type, allocator_type > ;
        using      ssize_type = detected_or_t< ssize_t,      has_ssize_type, allocator_type > ;
        using difference_type = detected_or_t< ssize_t, has_difference_type, allocator_type > ;

        using      block_type = block_t< value_type > ;

        using         pointer = detected_or_t< value_type       *,         has_pointer, allocator_type > ;
        using   const_pointer = detected_or_t< value_type const *,   has_const_pointer, allocator_type > ;
        using       reference = detected_or_t< value_type       &,       has_reference, allocator_type > ;
        using const_reference = detected_or_t< value_type const &, has_const_reference, allocator_type > ;

        using        iterator = detected_or_t<       pointer,       has_iterator, allocator_type > ;
        using  const_iterator = detected_or_t< const_pointer, has_const_iterator, allocator_type > ;

        UTI_NODISCARD static constexpr
        block_type allocate ( ssize_type _count_ )
        {
                pointer allocation = allocator_type::allocate( _count_ ) ;

                return allocation != nullptr ? block_type{ allocation, _count_ }
                                             : block_type{    nullptr,      0  } ;
        }
        UTI_NODISCARD static constexpr
        block_type reallocate ( block_type const & _block_, ssize_type _count_ )
        {
                pointer reallocation = allocator_type::reallocate( _block_.ptr, _count_ ) ;

                return reallocation != nullptr ? block_type{ reallocation, _count_ }
                                               : block_type{      nullptr,      0  } ;
        }

        UTI_NODISCARD static constexpr
        bool realloc_inplace ( block_type const & _block_, ssize_type _count_ ) noexcept
                requires( is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return allocator_type::realloc_inplace( _block_.ptr, _count_ ) ;
        }
        UTI_NODISCARD static constexpr
        bool realloc_inplace ( block_type const &, ssize_type ) noexcept
                requires( !is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return false ;
        }

        static constexpr
        void deallocate ( block_type const & _block_ ) noexcept
        {
                allocator_type::deallocate( _block_.ptr );
        }

        UTI_NODISCARD static constexpr
        ssize_type max_size () noexcept
                requires( is_detected_v< has_max_size, allocator_type, value_type > )
        {
                return allocator_type::max_size() ;
        }
        UTI_NODISCARD static constexpr
        ssize_type max_size () noexcept
                requires( !is_detected_v< has_max_size, allocator_type, value_type > )
        {
                return i64_t_max ;
        }
};

template< typename Alloc >
class allocator_traits< Alloc, void_t< has_block_type< Alloc > > >
{
public:
        using  allocator_type = Alloc ;
        using      value_type = allocator_type::value_type ;
        using       size_type = detected_or_t<  size_t,       has_size_type, allocator_type > ;
        using      ssize_type = detected_or_t< ssize_t,      has_ssize_type, allocator_type > ;
        using difference_type = detected_or_t< ssize_t, has_difference_type, allocator_type > ;

        using      block_type = typename allocator_type::block_type ;

        using         pointer = detected_or_t< value_type       *,         has_pointer, allocator_type > ;
        using   const_pointer = detected_or_t< value_type const *,   has_const_pointer, allocator_type > ;
        using       reference = detected_or_t< value_type       &,       has_reference, allocator_type > ;
        using const_reference = detected_or_t< value_type const &, has_const_reference, allocator_type > ;

        using        iterator = detected_or_t<       pointer,       has_iterator, allocator_type > ;
        using  const_iterator = detected_or_t< const_pointer, has_const_iterator, allocator_type > ;

        UTI_NODISCARD static constexpr
        block_type allocate ( ssize_type _count_ )
        {
                return allocator_type::allocate( _count_ );
        }
        UTI_NODISCARD static constexpr
        block_type reallocate ( block_type const & _block_, ssize_type _count_ )
        {
                return allocator_type::reallocate( _block_, _count_ );
        }

        UTI_NODISCARD static constexpr
        bool realloc_inplace ( block_type const & _block_, ssize_type _count_ ) noexcept
                requires( is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return allocator_type::realloc_inplace( _block_, _count_ ) ;
        }
        UTI_NODISCARD static constexpr
        bool realloc_inplace ( block_type const &, ssize_type ) noexcept
                requires( !is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return false ;
        }

        static constexpr
        void deallocate ( block_type const & _block_ ) noexcept
        {
                allocator_type::deallocate( _block_ );
        }

        UTI_NODISCARD static constexpr
        ssize_type max_size () noexcept
                requires( is_detected_v< has_max_size, allocator_type, value_type > )
        {
                return allocator_type::max_size() ;
        }
        UTI_NODISCARD static constexpr
        ssize_type max_size () noexcept
                requires( !is_detected_v< has_max_size, allocator_type, value_type > )
        {
                return i64_t_max ;
        }
};


} // namespace uti
