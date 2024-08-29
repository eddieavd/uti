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

template< typename Iter >
        requires meta::iterator< Iter >
UTI_NODISCARD constexpr auto realloc_typed_buffer ( Iter buffer, ssize_t new_count )
{
        return static_cast< Iter >( static_cast< iter_value_t< Iter > * >( UTI_REALLOC( buffer, new_count * sizeof( iter_value_t< Iter > ) ) ) ) ;
}

constexpr void dealloc_typed_buffer ( meta::iterator auto buffer )
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
        using         pointer = T       * ;
        using   const_pointer = T const * ;
        using       reference = T       & ;
        using const_reference = T const & ;

        using       iterator =       iterator_type ;
        using const_iterator = const_iterator_type ;

        constexpr operator bool () const noexcept { return begin_ != nullptr ; }

        UTI_NODISCARD constexpr       iterator  begin ()       noexcept { return begin_     ; }
        UTI_NODISCARD constexpr const_iterator  begin () const noexcept { return begin_     ; }
        UTI_NODISCARD constexpr const_iterator cbegin () const noexcept { return begin() ; }

        UTI_NODISCARD constexpr       iterator  end ()       noexcept { return begin_ + size_ ; }
        UTI_NODISCARD constexpr const_iterator  end () const noexcept { return begin_ + size_ ; }
        UTI_NODISCARD constexpr const_iterator cend () const noexcept { return end()      ; }

        iterator   begin_ ;
        ssize_type  size_ ;
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
        block_type allocate ( allocator_type & _alloc_, ssize_type _count_ )
        {
                pointer allocation = _alloc_.allocate( _count_ ) ;

                return allocation != nullptr ? block_type{ allocation, _count_ }
                                             : block_type{    nullptr,      0  } ;
        }
        static constexpr
        void reallocate ( allocator_type & _alloc_, block_type & _block_, ssize_type _count_ )
        {
                pointer reallocation = _alloc_.reallocate( _block_.begin_, _count_ ) ;

                if( reallocation )
                {
                        _block_.size_ = _count_ ;
                }
                if( reallocation != _block_.begin_ )
                {
                        _block_.begin_ = reallocation ;
                }
        }

        UTI_NODISCARD static constexpr
        bool realloc_inplace ( allocator_type & _alloc_, block_type & _block_, ssize_type _count_ ) noexcept
                requires( is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                if( _alloc_.realloc_inplace( _block_.begin_, _count_ ) )
                {
                        _block_.size_ = _count_ ;
                        return true ;
                }
                else
                {
                        return false ;
                }
        }
        UTI_NODISCARD static constexpr
        bool realloc_inplace ( allocator_type &, block_type &, ssize_type ) noexcept
                requires( !is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return false ;
        }

        static constexpr
        void deallocate ( allocator_type & _alloc_, block_type & _block_ ) noexcept
        {
                _alloc_.deallocate( _block_.begin_ );
        }

        UTI_NODISCARD static constexpr
        ssize_type max_size ( allocator_type const & _alloc_ ) noexcept
                requires( is_detected_v< has_max_size, allocator_type, value_type > )
        {
                return _alloc_.max_size() ;
        }
        UTI_NODISCARD static constexpr
        ssize_type max_size ( allocator_type const & ) noexcept
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
        block_type allocate ( allocator_type & _alloc_, ssize_type _count_ )
        {
                return _alloc_.allocate( _count_ );
        }
        static constexpr
        void reallocate ( allocator_type & _alloc_, block_type & _block_, ssize_type _count_ )
        {
                _alloc_.reallocate( _block_, _count_ );
        }

        UTI_NODISCARD static constexpr
        bool realloc_inplace ( allocator_type & _alloc_, block_type & _block_, ssize_type _count_ ) noexcept
                requires( is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return _alloc_.realloc_inplace( _block_, _count_ ) ;
        }
        UTI_NODISCARD static constexpr
        bool realloc_inplace ( allocator_type &, block_type &, ssize_type ) noexcept
                requires( !is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return false ;
        }

        static constexpr
        void deallocate ( allocator_type & _alloc_, block_type & _block_ ) noexcept
        {
                _alloc_.deallocate( _block_ );
        }

        UTI_NODISCARD static constexpr
        ssize_type max_size ( allocator_type const & _alloc_ ) noexcept
                requires( is_detected_v< has_max_size, allocator_type, value_type > )
        {
                return _alloc_.max_size() ;
        }
        UTI_NODISCARD static constexpr
        ssize_type max_size ( allocator_type const & ) noexcept
                requires( !is_detected_v< has_max_size, allocator_type, value_type > )
        {
                return i64_t_max ;
        }
};


} // namespace uti
