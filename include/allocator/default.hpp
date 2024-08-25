//
//
//      uti
//      allocator/default.hpp
//

#pragma once

#include <allocator/meta.hpp>


namespace uti
{


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

        UTI_NODISCARD static constexpr block_type allocate ( ssize_type const _capacity_ )
        {
                auto ptr = alloc_typed_buffer< value_type >( _capacity_ ) ;
                return ptr != nullptr ? block_type{ ptr, _capacity_ } : block_type{ ptr, 0 } ;
        }
        UTI_NODISCARD static constexpr block_type reallocate ( block_type const & _block_, ssize_type const _new_capacity_ )
        {
                auto ptr = realloc_typed_buffer( _block_.ptr, _new_capacity_ ) ;
                return ptr != nullptr ? block_type{ ptr, _new_capacity_ } : block_type{ ptr, 0 } ;
        }
        static constexpr void deallocate ( block_type const & _block_ ) noexcept
        {
                dealloc_typed_buffer( _block_.ptr );
        }
};


} // namespace uti
