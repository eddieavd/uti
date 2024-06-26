//
//
//      uti
//      allocator.hpp
//

#pragma once

#include <util/config.hpp>
#include <meta/uti_traits.hpp>
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
struct block_t
{
        T *      ptr ;
        ssize_t size ;

        constexpr operator bool () const noexcept { return ptr != nullptr ; }
};

template< typename T > using has_block_type = T::block_type ;

template< typename Alloc, typename T >
using has_inplace_realloc = decltype( Alloc::can_realloc_inplace( uti::declval< block_t< T > >(), uti::declval< ssize_t >() ) ) ;


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

        UTI_NODISCARD inline constexpr static
        block_type allocate ( ssize_type _count_ )
        {
                pointer allocation = allocator_type::allocate( _count_ );

                return allocation != nullptr ? block_type{ allocation, _count_ } : block_type{ allocation, 0 } ;
        }
        inline constexpr static
        block_type reallocate ( block_type const & _block_, ssize_type _count_ )
        {
                pointer reallocation = allocator_type::reallocate( _block_.ptr, _count_ ) ;

                return reallocation != nullptr ? block_type{ reallocation, _count_ } : block_type{ reallocation, 0 } ;
        }

        UTI_NODISCARD inline constexpr static
        bool can_realloc_inplace ( block_type const & _block_, ssize_type _count_ ) noexcept requires( is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return allocator_type::can_realloc_inplace( _block_.ptr, _count_ );
        }
        UTI_NODISCARD inline constexpr static
        bool can_realloc_inplace ( block_type const &, ssize_type ) noexcept requires( !is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return false;
        }

        UTI_NODISCARD inline constexpr static
        block_type try_realloc_inplace ( block_type const & _block_, ssize_type _count_ ) noexcept requires( is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                pointer reallocation = allocator_type::try_realloc_inplace( _block_, _count_ );

                return reallocation != nullptr ? block_type{ reallocation, _count_ } : block_type{ reallocation, 0 } ;
        }
        UTI_NODISCARD inline constexpr static
        block_type try_realloc_inplace ( block_type const &, ssize_type ) noexcept requires( !is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return { nullptr, 0 } ;
        }

        inline constexpr static
        void deallocate ( block_type const & _block_ ) noexcept
        {
                allocator_type::deallocate( _block_.ptr );
        }

        template< typename... Args >
        static void construct ( pointer const _ptr_, Args&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, Args... > )
        {
                allocator_type::construct( _ptr_, UTI_FWD( _args_ )... );
        }
        static void destroy ( pointer const _ptr_ ) noexcept
        {
                allocator_type::destroy( _ptr_ );
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

        UTI_NODISCARD inline constexpr static
        block_type allocate ( ssize_type _count_ )
        {
                return allocator_type::allocate( _count_ );
        }
        inline constexpr static
        block_type reallocate ( block_type const & _block_, ssize_type _count_ )
        {
                return allocator_type::reallocate( _block_, _count_ );
        }

        UTI_NODISCARD inline constexpr static
        bool can_realloc_inplace ( block_type const & _block_, ssize_type _count_ ) noexcept requires( is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return allocator_type::can_realloc_inplace( _block_, _count_ );
        }
        UTI_NODISCARD inline constexpr static
        bool can_realloc_inplace ( block_type const &, ssize_type ) noexcept requires( !is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return false;
        }

        UTI_NODISCARD inline constexpr static
        block_type try_realloc_inplace ( block_type const & _block_, ssize_type _count_ ) noexcept requires( is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return allocator_type::try_realloc_inplace( _block_, _count_ );
        }
        UTI_NODISCARD inline constexpr static
        block_type try_realloc_inplace ( block_type const &, ssize_type ) noexcept requires( !is_detected_v< has_inplace_realloc, allocator_type, value_type > )
        {
                return { nullptr, 0 } ;
        }

        inline constexpr static
        void deallocate ( block_type const & _block_ ) noexcept
        {
                allocator_type::deallocate( _block_ );
        }

        template< typename... Args >
        static void construct ( pointer const _ptr_, Args&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, Args... > )
        {
                allocator_type::construct( _ptr_, UTI_FWD( _args_ )... );
        }
        static void destroy ( pointer const _ptr_ ) noexcept
        {
                allocator_type::destroy( _ptr_ );
        }
};


template< typename T >
class allocator
{
public:
        using      value_type =       T    ;
        using       size_type =  size_t    ;
        using      ssize_type = ssize_t    ;
        using difference_type = ssize_type ;

        using      block_type = block_t< value_type > ;

        using         pointer = value_type       * ;
        using   const_pointer = value_type const * ;
        using       reference = value_type       & ;
        using const_reference = value_type const & ;

        using        iterator =       pointer ;
        using  const_iterator = const_pointer ;

        static block_type allocate ( ssize_type const _capacity_ )
        {
                auto ptr = alloc_typed_buffer< value_type >( _capacity_ ) ;
                return ptr != nullptr ? block_type{ ptr, _capacity_ } : block_type{ ptr, 0 } ;
        }
        static block_type reallocate ( block_type const & _block_, ssize_type const _new_capacity_ )
        {
                auto ptr = realloc_typed_buffer( _block_.ptr, _new_capacity_ ) ;
                return ptr != nullptr ? block_type{ ptr, _new_capacity_ } : block_type{ ptr, 0 } ;
        }
        static void deallocate ( block_type const & _block_ ) noexcept
        {
                dealloc_typed_buffer( _block_.ptr );
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


template< typename T, ssize_t MemSize >
class static_bump_allocator
{
        static constexpr ssize_t memsize { MemSize } ;
public:
        using      value_type =       T    ;
        using       size_type =  size_t    ;
        using      ssize_type = ssize_t    ;
        using difference_type = ssize_type ;

        using      block_type = block_t< value_type > ;

        using         pointer = value_type       * ;
        using   const_pointer = value_type const * ;
        using       reference = value_type       & ;
        using const_reference = value_type const & ;

        using        iterator =       pointer ;
        using  const_iterator = const_pointer ;

        static constexpr block_type allocate ( ssize_type const _capacity_ ) noexcept
        {
                if( _mem_available() >= _capacity_ )
                {
                        end += _capacity_ ;
                        return { end - _capacity_, _capacity_ } ;
                }
                return { nullptr, 0 } ;
        }
        static constexpr block_type reallocate ( block_type const & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                if( !can_realloc_inplace( _block_, _new_capacity_ ) )
                {
                        block_type new_block = allocate( _new_capacity_ );
                        ::uti::copy( _block_.ptr, _block_.ptr + _block_.size, new_block.ptr );
                        return new_block;
                }
                return _realloc_inplace( _block_, _new_capacity_ );
        }
        static constexpr bool can_realloc_inplace ( block_type const & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                return _is_last_block( _block_ ) && _mem_available() >= ( _new_capacity_ - _block_.size ) ;
        }
        static constexpr block_type try_realloc_inplace ( block_type const & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                if( can_realloc_inplace( _block_, _new_capacity_ ) )
                {
                        return _realloc_inplace( _block_, _new_capacity_ );
                }
                return block_type{ nullptr, 0 };
        }
        static constexpr void deallocate ( block_type const & _block_ ) noexcept
        {
                if( ( _block_.ptr + _block_.size ) == end )
                {
                        end = _block_.ptr;
                }
        }
        template< typename... Args >
        static constexpr void construct ( pointer const _ptr_, Args&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, Args... > )
        {
                ::new ( ( void * ) _ptr_ ) value_type( UTI_FWD( _args_ )... ) ;
        }
        static constexpr void destroy ( pointer const _ptr_ ) noexcept
        {
                _ptr_->~value_type();
        }
private:
        inline static T   mem [ memsize ] ;
        inline static T * end { mem     } ;

        static constexpr ssize_type _mem_available () noexcept { return memsize - ( end - mem ) ; }

        static constexpr bool _is_last_block ( block_type const & _block_ ) noexcept { return _block_.ptr == end - _block_.size ; }

        static constexpr block_type _realloc_inplace ( block_type const & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                end += _new_capacity_ - _block_.size ;
                return block_type{ _block_.ptr, _new_capacity_ } ;
        }
};


} // namespace uti
