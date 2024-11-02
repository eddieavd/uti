//
//
//      uti
//      allocator.hpp
//

#pragma once

#include <util/config.hpp>
#include <iterator/meta.hpp>
#include <iterator/base.hpp>
#include <container/meta.hpp>
#include <algo/copy.hpp>

#include <new>

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


UTI_NODISCARD inline constexpr
u8_t * alloc_buffer ( ssize_t count ) noexcept
{
        return static_cast< u8_t * >( UTI_MALLOC( count ) ) ;
}

UTI_NODISCARD inline constexpr
u8_t * realloc_buffer ( void * buffer, ssize_t count ) noexcept
{
        return static_cast< u8_t * >( UTI_REALLOC( buffer, count ) ) ;
}

inline constexpr
void dealloc_buffer ( void * buffer ) noexcept
{
        UTI_FREE( buffer ) ;
}


template< typename T >
struct block_t
{
private:
        using       iterator_type = iterator_base< T      , random_access_iterator_tag > ;
        using const_iterator_type = iterator_base< T const, random_access_iterator_tag > ;
public:
        using      value_type =         T ;
        using       size_type =    size_t ;
        using      ssize_type =   ssize_t ;
        using difference_type = ptrdiff_t ;

        using         pointer = value_type       * ;
        using   const_pointer = value_type const * ;
        using       reference = value_type       & ;
        using const_reference = value_type const & ;

        using       iterator =       iterator_type ;
        using const_iterator = const_iterator_type ;

        constexpr operator bool () const noexcept { return begin_ != nullptr ; }

        template< typename T1 >
                requires is_same_v< T, u8_t >
        constexpr operator block_t< T1 > () const noexcept
        {
                block_t< T1 > block ;

                block.begin_ = static_cast< typename block_t< T1 >::iterator >(
                                static_cast< typename block_t< T1 >::pointer >(
                                        static_cast< void * >( begin_ )
                                )
                ) ;
                block.size_ = size_ / sizeof( typename block_t< T1 >::value_type ) ;

                return block ;
        }

        constexpr operator block_t< u8_t > () const noexcept
                requires( !is_same_v< T, u8_t > )
        {
                block_t< u8_t > block ;

                block.begin_ = static_cast< typename block_t< u8_t >::iterator >(
                                static_cast< typename block_t< u8_t >::pointer >(
                                        static_cast< void * >( begin_ )
                                )
                ) ;
                block.size_ = size_ * sizeof( value_type ) ;

                return block ;
        }

        UTI_NODISCARD constexpr       iterator  begin ()       noexcept { return begin_     ; }
        UTI_NODISCARD constexpr const_iterator  begin () const noexcept { return begin_     ; }
        UTI_NODISCARD constexpr const_iterator cbegin () const noexcept { return begin()    ; }

        UTI_NODISCARD constexpr       iterator  end ()       noexcept { return begin_ + size_ ; }
        UTI_NODISCARD constexpr const_iterator  end () const noexcept { return begin_ + size_ ; }
        UTI_NODISCARD constexpr const_iterator cend () const noexcept { return end()          ; }

        iterator   begin_ ;
        ssize_type  size_ ;
};


template< typename T > using has_block_type = T::block_type ;

template< typename Alloc, typename T >
using has_inplace_realloc = decltype( Alloc::realloc_inplace( uti::declval< block_t< T > & >(), uti::declval< ssize_t >() ) ) ;

template< typename Alloc, typename T >
using has_max_size = decltype( Alloc::max_size() ) ;


template< typename Alloc, typename = void >
class allocator_traits
{
public:
        using  allocator_type = Alloc ;
        using      value_type = allocator_type::value_type ;
        using       size_type = detected_or_t<  size_t, meta::      has_size_type, allocator_type > ;
        using      ssize_type = detected_or_t< ssize_t, meta::     has_ssize_type, allocator_type > ;
        using difference_type = detected_or_t< ssize_t, meta::has_difference_type, allocator_type > ;

        using      block_type = block_t< value_type > ;

        using         pointer = detected_or_t< value_type       *, meta::        has_pointer, allocator_type > ;
        using   const_pointer = detected_or_t< value_type const *, meta::  has_const_pointer, allocator_type > ;
        using       reference = detected_or_t< value_type       &, meta::      has_reference, allocator_type > ;
        using const_reference = detected_or_t< value_type const &, meta::has_const_reference, allocator_type > ;

        using        iterator = detected_or_t<       pointer, meta::      has_iterator, allocator_type > ;
        using  const_iterator = detected_or_t< const_pointer, meta::has_const_iterator, allocator_type > ;

        UTI_NODISCARD UTI_DEEP_INLINE static constexpr
        block_type allocate ( ssize_type _count_ )
        {
                pointer allocation = allocator_type::allocate( _count_ ) ;

                return allocation != nullptr ? block_type{ allocation, _count_ }
                                             : block_type{    nullptr,      0  } ;
        }
        UTI_DEEP_INLINE static constexpr
        void reallocate ( block_type & _block_, ssize_type _count_ )
        {
                pointer reallocation = allocator_type::reallocate( _block_.begin_, _count_ ) ;

                if( reallocation )
                {
                        _block_.size_ = _count_ ;
                }
                if( reallocation != _block_.begin_ )
                {
                        _block_.begin_ = reallocation ;
                }
        }

        UTI_NODISCARD UTI_DEEP_INLINE static constexpr
        bool realloc_inplace ( block_type & _block_, ssize_type _count_ ) noexcept
                requires( is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                if( allocator_type::realloc_inplace( _block_.begin_, _count_ ) )
                {
                        _block_.size_ = _count_ ;
                        return true ;
                }
                else
                {
                        return false ;
                }
        }
        UTI_NODISCARD UTI_DEEP_INLINE static constexpr
        bool realloc_inplace ( block_type &, ssize_type ) noexcept
                requires( !is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return false ;
        }

        UTI_DEEP_INLINE static constexpr
        void deallocate ( block_type & _block_ ) noexcept
        {
                allocator_type::deallocate( _block_.begin_ );
        }

        UTI_NODISCARD UTI_DEEP_INLINE static constexpr
        ssize_type max_size () noexcept
                requires( is_detected_v< has_max_size, allocator_type, value_type > )
        {
                return allocator_type::max_size() ;
        }
        UTI_NODISCARD UTI_DEEP_INLINE static constexpr
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
        using       size_type = detected_or_t<  size_t, meta::      has_size_type, allocator_type > ;
        using      ssize_type = detected_or_t< ssize_t, meta::     has_ssize_type, allocator_type > ;
        using difference_type = detected_or_t< ssize_t, meta::has_difference_type, allocator_type > ;

        using      block_type = typename allocator_type::block_type ;

        using         pointer = detected_or_t< value_type       *, meta::        has_pointer, allocator_type > ;
        using   const_pointer = detected_or_t< value_type const *, meta::  has_const_pointer, allocator_type > ;
        using       reference = detected_or_t< value_type       &, meta::      has_reference, allocator_type > ;
        using const_reference = detected_or_t< value_type const &, meta::has_const_reference, allocator_type > ;

        using        iterator = detected_or_t<       pointer, meta::      has_iterator, allocator_type > ;
        using  const_iterator = detected_or_t< const_pointer, meta::has_const_iterator, allocator_type > ;

        UTI_NODISCARD UTI_DEEP_INLINE static constexpr
        block_type allocate ( ssize_type _count_ )
        {
                return allocator_type::allocate( _count_ );
        }
        UTI_DEEP_INLINE static constexpr
        void reallocate ( block_type & _block_, ssize_type _count_ )
        {
                allocator_type::reallocate( _block_, _count_ );
        }

        UTI_NODISCARD UTI_DEEP_INLINE static constexpr
        bool realloc_inplace ( block_type & _block_, ssize_type _count_ ) noexcept
                requires( is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return allocator_type::realloc_inplace( _block_, _count_ ) ;
        }
        UTI_NODISCARD UTI_DEEP_INLINE static constexpr
        bool realloc_inplace ( block_type &, ssize_type ) noexcept
                requires( !is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return false ;
        }

        UTI_DEEP_INLINE static constexpr
        void deallocate ( block_type & _block_ ) noexcept
        {
                allocator_type::deallocate( _block_ );
        }

        UTI_NODISCARD UTI_DEEP_INLINE static constexpr
        ssize_type max_size () noexcept
                requires( is_detected_v< has_max_size, allocator_type, value_type > )
        {
                return allocator_type::max_size() ;
        }
        UTI_NODISCARD UTI_DEEP_INLINE static constexpr
        ssize_type max_size () noexcept
                requires( !is_detected_v< has_max_size, allocator_type, value_type > )
        {
                return i64_t_max ;
        }
};


} // namespace uti
