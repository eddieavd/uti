//
//
//      uti
//      allocator/static_bump.hpp
//

#pragma once

#include <allocator/meta.hpp>


namespace uti
{


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

        UTI_NODISCARD static constexpr block_type allocate ( ssize_type const _capacity_ ) noexcept
        {
                if( _mem_available() >= _capacity_ )
                {
                        end += _capacity_ ;
                        return { end - _capacity_, _capacity_ } ;
                }
                return { nullptr, 0 } ;
        }
        UTI_NODISCARD static constexpr block_type reallocate ( block_type const & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                if( !_can_realloc_inplace( _block_, _new_capacity_ ) )
                {
                        block_type new_block = allocate( _new_capacity_ );
                        ::uti::copy( _block_.ptr, _block_.ptr + _block_.size, new_block.ptr );
                        return new_block;
                }
                _realloc_inplace( _block_, _new_capacity_ ) ;

                return { _block_.ptr, _new_capacity_ } ;
        }
        UTI_NODISCARD static constexpr bool realloc_inplace ( block_type const & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                if( _can_realloc_inplace( _block_, _new_capacity_ ) )
                {
                        _realloc_inplace( _block_, _new_capacity_ ) ;
                        return true ;
                }
                return false ;
        }
        static constexpr void deallocate ( block_type const & _block_ ) noexcept
        {
                if( ( _block_.ptr + _block_.size ) == end )
                {
                        end = _block_.ptr;
                }
        }
private:
        inline static T   mem [ memsize ] ;
        inline static T * end { mem     } ;

        static constexpr ssize_type _mem_available () noexcept { return memsize - ( end - mem ) ; }

        static constexpr bool _is_last_block ( block_type const & _block_ ) noexcept { return _block_.ptr == end - _block_.size ; }

        static constexpr bool _can_realloc_inplace ( block_type const & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                return _is_last_block( _block_ ) && _mem_available() >= ( _new_capacity_ - _block_.size ) ;
        }

        static constexpr void _realloc_inplace ( block_type const & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                end += _new_capacity_ - _block_.size ;
        }
};


} // namespace uti
